#pragma once
#include <cstdio>
#include <cerrno>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <sys/stat.h>
#include <unistd.h>

namespace dink_save {
using Writer = std::function<bool(FILE*)>;
struct Item { std::string name; Writer write; };
struct Entry { std::string name; bool existed; };

// Injectable OS boundary for failure and interruption tests. No rename-overwrite
// assumption: libnx/ftpsrv filesystems may reject an existing destination.
struct FileOps {
    virtual ~FileOps() {}
    virtual int exists(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) == 0) return S_ISREG(st.st_mode) ? 1 : -1;
        return errno == ENOENT ? 0 : -1;
    }
    virtual bool remove(const std::string& path) {
        return std::remove(path.c_str()) == 0 || errno == ENOENT;
    }
    virtual bool rename(const std::string& from, const std::string& to) {
        return std::rename(from.c_str(), to.c_str()) == 0;
    }
    virtual int flush(FILE* fp) { return std::fflush(fp); }
    virtual int sync(FILE* fp) { return ::fsync(fileno(fp)); }
    virtual int close(FILE* fp) { return std::fclose(fp); }
    virtual bool write(const std::string& path, const Writer& writer) {
        FILE* fp = std::fopen(path.c_str(), "wb");
        if (!fp) return false;
        // Keep serialization buffered; ferror also catches failures in legacy
        // serializers that don't check every individual fwrite return value.
        const bool serialized = writer(fp);
        const bool flushed = flush(fp) == 0;
        const bool clean = std::ferror(fp) == 0;
        const bool synced = flushed && clean && sync(fp) == 0;
        const bool closed = close(fp) == 0;
        return serialized && flushed && clean && synced && closed;
    }
    virtual bool read(const std::string& path, std::string& text) {
        FILE* fp = std::fopen(path.c_str(), "rb");
        if (!fp) return false;
        char buf[4096];
        const size_t n = std::fread(buf, 1, sizeof(buf), fp);
        const bool ok = n < sizeof(buf) && std::ferror(fp) == 0;
        const bool closed = close(fp) == 0;
        if (ok && closed) text.assign(buf, n);
        return ok && closed;
    }
};
inline bool validName(const std::string& name) {
    if (name.empty() || name.size() > 100 || name[0] == '.') return false;
    for (char c : name) if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                            (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '-')) return false;
    // Journals may only refer to actual save data, never game assets.
    return name.size() > 4 && name.substr(name.size()-4) == ".dat" &&
        (name.compare(0, 4, "save") == 0 || name.compare(0, 8, "autosave") == 0 ||
         name.compare(0, 9, "quicksave") == 0 || name == "continue_state.dat");
}
inline std::string prefix(std::string dir) {
    if (dir.empty()) return "./";
    if (dir.back() != '/') dir += '/';
    return dir;
}
inline bool recover(const std::string& directory, FileOps& fs) {
    const std::string dir = prefix(directory), journal = dir + ".dink-save.txn";
    const int present = fs.exists(journal);
    if (present <= 0) return present == 0;
    std::string data;
    if (!fs.read(journal, data)) return false;
    std::istringstream in(data);
    std::string magic;
    if (!std::getline(in, magic) || magic != "DINKSAVE1") return false;
    std::vector<Entry> entries;
    std::set<std::string> names;
    std::string line;
    while (std::getline(in, line)) {
        if (line.size() < 3 || (line[0] != '0' && line[0] != '1') || line[1] != ' ') return false;
        const std::string name = line.substr(2);
        if (!validName(name) || !names.insert(name).second || entries.size() >= 8) return false;
        entries.push_back({name, line[0] == '1'});
    }
    if (entries.empty() || data.back() != '\n') return false;
    // An extant journal means the whole group must roll back. Repeatable after
    // another interruption, including between restoring two autosave files.
    for (const auto& e : entries) {
        const std::string target = dir + e.name, backup = target + ".rollback";
        const int prior = fs.exists(backup);
        if (prior < 0) return false;
        if (e.existed && prior) {
            if (!fs.remove(target) || !fs.rename(backup, target)) return false;
        } else if (!e.existed && !fs.remove(target)) return false;
        if (!fs.remove(target + ".pending")) return false;
    }
    return fs.remove(journal);
}
inline bool recover(const std::string& dir) { FileOps fs; return recover(dir, fs); }

inline bool commit(const std::string& directory, const std::vector<Item>& items, FileOps& fs) {
    const std::string dir = prefix(directory), journal = dir + ".dink-save.txn";
    if (items.empty() || items.size() > 8 || !recover(dir, fs)) return false;
    std::set<std::string> names;
    for (const auto& item : items)
        if (!validName(item.name) || !names.insert(item.name).second) return false;
    std::vector<Entry> entries;
    std::string text = "DINKSAVE1\n";
    for (const auto& item : items) {
        const std::string target = dir + item.name;
        const int existed = fs.exists(target), rollback = fs.exists(target + ".rollback");
        if (existed < 0 || rollback < 0) return false;
        // Finish backup rotation after an already committed, interrupted cleanup.
        if (rollback && (!existed || !fs.remove(target + ".bak") ||
                         !fs.rename(target + ".rollback", target + ".bak"))) return false;
        if (!fs.write(target + ".pending", item.write)) return false;
        entries.push_back({item.name, existed != 0});
        text += std::string(existed ? "1 " : "0 ") + item.name + "\n";
    }
    if (!fs.write(journal + ".pending", [&text](FILE* fp) {
        return std::fwrite(text.data(), 1, text.size(), fp) == text.size();
    }) || !fs.rename(journal + ".pending", journal)) return false;
    for (const auto& e : entries) {
        const std::string target = dir + e.name;
        if ((e.existed && !fs.rename(target, target + ".rollback")) ||
            !fs.rename(target + ".pending", target)) {
            recover(dir, fs); // Failure leaves journal/backups for the next launch.
            return false;
        }
    }
    if (!fs.remove(journal)) { recover(dir, fs); return false; }
    // Publication is committed; backup cleanup is best effort and recoverable.
    for (const auto& e : entries) if (e.existed) {
        const std::string target = dir + e.name;
        if (fs.remove(target + ".bak")) fs.rename(target + ".rollback", target + ".bak");
    }
    return true;
}
inline bool commit(const std::string& dir, const std::vector<Item>& items) {
    FileOps fs; return commit(dir, items, fs);
}
inline bool write(const std::string& path, const Writer& writer) {
    const auto slash = path.find_last_of('/');
    return commit(slash == std::string::npos ? "./" : path.substr(0, slash+1),
                  {{slash == std::string::npos ? path : path.substr(slash+1), writer}});
}
}
