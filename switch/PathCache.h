#pragma once
#include <string>
#include <unordered_map>
#include <functional>

namespace dink_path_cache {

inline bool isCacheable(const std::string& path) {
    if (path.empty()) return false;
    const auto dot = path.find_last_of('.');
    if (dot == std::string::npos) return false;
    const std::string ext = path.substr(dot);
    if (ext == ".flag" || ext == ".txt" || ext == ".pending" ||
        ext == ".rollback" || ext == ".txn" || ext == ".bak" ||
        ext == ".log") {
        return false;
    }
    // Save files are dynamic and must never be cached
    if (ext == ".dat") {
        const auto slash = path.find_last_of("/\\");
        const std::string name = (slash == std::string::npos) ? path : path.substr(slash + 1);
        if (name.compare(0, 4, "save") == 0 ||
            name.compare(0, 8, "autosave") == 0 ||
            name.compare(0, 9, "quicksave") == 0 ||
            name == "continue_state.dat") {
            return false;
        }
    }
    if (path.find("temp.dmod") != std::string::npos) {
        return false;
    }
    return true;
}

class PathCache {
public:
    static PathCache& instance() {
        static PathCache s_instance;
        return s_instance;
    }

    bool lookupLocation(const std::string& key, std::string& out) const {
        auto it = m_locations.find(key);
        if (it != m_locations.end()) {
            out = it->second;
            return true;
        }
        return false;
    }

    void storeLocation(const std::string& key, const std::string& location) {
        if (m_locations.size() < 4096) {
            m_locations[key] = location;
        }
    }

    bool exists(const std::string& path, const std::function<bool(const std::string&)>& fallback) {
        if (!isCacheable(path)) {
            return fallback(path);
        }
        auto it = m_exists.find(path);
        if (it != m_exists.end()) {
            return it->second;
        }
        bool res = fallback(path);
        if (m_exists.size() < 4096) {
            m_exists[path] = res;
        }
        return res;
    }

    void clear() {
        m_locations.clear();
        m_exists.clear();
    }

    size_t locationCount() const { return m_locations.size(); }
    size_t existsCount() const { return m_exists.size(); }

private:
    std::unordered_map<std::string, std::string> m_locations;
    std::unordered_map<std::string, bool> m_exists;
};

inline bool lookupLocation(const std::string& key, std::string& out) {
    return PathCache::instance().lookupLocation(key, out);
}

inline void storeLocation(const std::string& key, const std::string& location) {
    PathCache::instance().storeLocation(key, location);
}

inline bool exists(const std::string& path, const std::function<bool(const std::string&)>& fallback) {
    return PathCache::instance().exists(path, fallback);
}

inline void clear() {
    PathCache::instance().clear();
}

inline size_t locationCount() {
    return PathCache::instance().locationCount();
}

inline size_t existsCount() {
    return PathCache::instance().existsCount();
}

} // namespace dink_path_cache
