#include "switch/SafeSave.h"
#include "switch/PerformancePolicy.h"
#include <map>
#include <stdexcept>
#include <iostream>
#include <climits>

static void check(bool yes, const char* message) { if (!yes) throw std::runtime_error(message); }
struct Interrupted {};
struct MemoryFS : dink_save::FileOps {
    std::map<std::string,std::string> files;
    int step = 0, interrupt = 0, fail = 0;
    bool after = false;
    bool beforeOp() {
        ++step;
        if (!after && step == interrupt) throw Interrupted();
        return step != fail;
    }
    void afterOp() { if (after && step == interrupt) throw Interrupted(); }
    int exists(const std::string& p) override { return files.count(p) ? 1 : 0; }
    bool remove(const std::string& p) override {
        if (!beforeOp()) return false;
        files.erase(p); afterOp(); return true;
    }
    bool rename(const std::string& a, const std::string& b) override {
        if (!beforeOp() || !files.count(a) || files.count(b)) return false;
        files[b]=files[a]; files.erase(a); afterOp(); return true;
    }
    bool write(const std::string& p, const dink_save::Writer& writer) override {
        if (!beforeOp()) return false;
        FILE* fp=tmpfile(); check(fp, "tmpfile");
        const bool ok=writer(fp) && !ferror(fp) && fflush(fp)==0;
        rewind(fp); std::string data; char b[1024]; size_t n;
        while ((n=fread(b,1,sizeof(b),fp))) data.append(b,n);
        fclose(fp); files[p]=data; afterOp(); return ok;
    }
    bool read(const std::string& p, std::string& data) override {
        if (!files.count(p)) return false;
        data=files[p]; return true;
    }
};
static dink_save::Writer bytes(std::string data) {
    return [data](FILE* f) { return fwrite(data.data(),1,data.size(),f)==data.size(); };
}
static std::vector<dink_save::Item> items() {
    return {{"autosave.dat", bytes("new state")}, {"autosavedb.dat", bytes("new meta")}};
}
static MemoryFS initial(bool existed=true) {
    MemoryFS fs;
    if (existed) { fs.files["test/autosave.dat"]="old state"; fs.files["test/autosavedb.dat"]="old meta"; }
    fs.files["test/save1.dat"]="other slot";
    return fs;
}
static void coherent(MemoryFS& fs, bool existed) {
    const auto& f=fs.files;
    bool old=existed ? f.count("test/autosave.dat") && f.at("test/autosave.dat")=="old state" &&
                      f.count("test/autosavedb.dat") && f.at("test/autosavedb.dat")=="old meta" :
                      !f.count("test/autosave.dat") && !f.count("test/autosavedb.dat");
    bool newer=f.count("test/autosave.dat") && f.at("test/autosave.dat")=="new state" &&
               f.count("test/autosavedb.dat") && f.at("test/autosavedb.dat")=="new meta";
    check(old || newer, "mixed autosave generations or lost save");
    check(f.at("test/save1.dat")=="other slot", "unrelated slot changed");
}
struct BrokenIO : dink_save::FileOps {
    int operation;
    explicit BrokenIO(int op):operation(op){}
    int flush(FILE* f) override { return operation==0 ? -1 : FileOps::flush(f); }
    int sync(FILE* f) override { return operation==1 ? -1 : FileOps::sync(f); }
    int close(FILE* f) override { const int r=FileOps::close(f); return operation==2 ? -1 : r; }
};
int main(int argc,char** argv) {
    try {
        check(argc==2,"pass temporary test directory");
        for (bool existed:{false,true}) {
            auto good=initial(existed);
            check(dink_save::commit("test",items(),good),"successful transaction failed");
            coherent(good,existed);
            if (existed) check(good.files.at("test/autosave.dat.bak")=="old state","backup lost");
            // Fail or interrupt before/after every publication mutation, then restart.
            for (int point=1;point<=good.step+4;++point) {
                for (int mode=0;mode<3;++mode) {
                    auto fs=initial(existed);
                    if (mode==0) fs.fail=point; else { fs.interrupt=point; fs.after=mode==2; }
                    try { dink_save::commit("test",items(),fs); } catch (Interrupted&) {}
                    const auto interrupted=fs.files;
                    fs.fail=fs.interrupt=0;
                    check(dink_save::recover("test",fs),"recovery failed"); coherent(fs,existed);
                    // Recovery itself must survive repeated interruption.
                    for(int recoveryPoint=1;recoveryPoint<=10;++recoveryPoint) {
                        MemoryFS retry; retry.files=interrupted; retry.interrupt=recoveryPoint; retry.after=true;
                        try { dink_save::recover("test",retry); } catch (Interrupted&) {}
                        retry.interrupt=0;
                        check(dink_save::recover("test",retry),"repeated recovery failed"); coherent(retry,existed);
                    }
                }
            }
        }
        for (const std::string invalid:{"DINKSAVE1\n1 ../map.dat\n", "DINKSAVE1\n1 autosave.dat", "DINKSAVE1\n1 autosave.dat\n1 autosave.dat\n"}) {
            auto fs=initial(); fs.files["test/.dink-save.txn"]=invalid;
            const auto before=fs.files;
            check(!dink_save::recover("test",fs),"malformed journal accepted");
            check(fs.files==before,"malformed journal mutated files");
        }
        // A legacy installation may have a state without its metadata file.
        auto mixed=initial(); mixed.files.erase("test/autosavedb.dat");
        mixed.interrupt=7; mixed.after=true;
        try { dink_save::commit("test",items(),mixed); } catch (Interrupted&) {}
        mixed.interrupt=0;
        check(dink_save::recover("test",mixed),"mixed-existing recovery failed");
        check(mixed.files.at("test/autosave.dat")=="old state" && !mixed.files.count("test/autosavedb.dat"),"mixed-existing rollback incorrect");
        check(dink_save::commit("test",items(),mixed),"save after recovery failed");
        coherent(mixed,true);
        auto fs=initial(); auto broken=items(); broken[1].write=[](FILE* f){fputs("partial",f);return false;};
        check(!dink_save::commit("test",broken,fs),"failed serializer accepted"); coherent(fs,true);
        for(int op=0;op<3;++op) { BrokenIO io(op); check(!io.write(std::string(argv[1])+"/broken",bytes("test")),"I/O failure ignored"); }
        dink_save::FileOps io;
        check(!io.write("/dev/full",[](FILE* f){fputs("partial",f);return true;}),"disk full at flush ignored");
        check(!io.write("/dev/full",[](FILE* f){std::string b(65536,'x');fwrite(b.data(),1,b.size(),f);return true;}),"short write ignored");
        check(dink_save::commit(argv[1],items(),io),"real filesystem commit failed");
        check(dink_save::commit(argv[1],items(),io),"real filesystem update failed");
        check(dink_save::recover(argv[1],io),"real filesystem recovery failed");

        auto sorted=dink_perf::oldestFirst({{0,0},{1,5000},{2,2000},{3,1000},{4,10000}},2000);
        check(sorted.size()==3 && sorted[0].slot==4 && sorted[1].slot==1 && sorted[2].slot==2,"cache order/recent protection");
        check(dink_perf::age(10,UINT32_MAX-9)==20,"clock wrap");
        dink_perf::CachePressure pressure;
        check(!pressure.update(170,170,180,160),"premature collection");
        check(pressure.update(181,20,180,160),"CPU pressure ignored");
        check(pressure.update(175,20,180,160),"hysteresis lost");
        check(!pressure.update(160,160,180,160),"collection did not stop at target");
        check(pressure.update(20,181,180,160),"texture pressure ignored");
        for(unsigned fps:{30u,60u}) {
            dink_perf::FramePacer p; p.configure(60000000,fps); const uint64_t period=60000000/fps;
            uint64_t now=123;
            for(int i=0;i<10000;++i) { p.begin(now); check(p.remaining(now+100)==period-100,"pacing drift"); now+=period; p.finish(now); }
            now+=period*100; p.finish(now); check(p.remaining(now)==period,"stall catch-up burst");
        }
        dink_perf::FrameStats stats;
        for (uint64_t i=1;i<=601;++i) stats.record(i*1000,60000);
        check(stats.intervals.size()==600 && stats.percentile(.95)>16.66 && stats.percentile(.95)<16.67,"frame statistics incorrect");
        stats.reset(); check(stats.intervals.empty() && !stats.previous,"frame statistics reset");
        std::cout<<"PASS: save failures/interruption/recovery, real I/O, cache policy, 30/60 FPS scheduling.\n";
    } catch(const std::exception& e) { std::cerr<<e.what()<<'\n';return 1; }
}
