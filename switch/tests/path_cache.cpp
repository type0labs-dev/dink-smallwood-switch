#include "switch/PathCache.h"
#include <iostream>
#include <stdexcept>
#include <cassert>

static void check(bool yes, const char* message) {
    if (!yes) throw std::runtime_error(message);
}

int main() {
    try {
        dink_path_cache::clear();
        check(dink_path_cache::locationCount() == 0, "initial locations not empty");
        check(dink_path_cache::existsCount() == 0, "initial exists not empty");

        // 1. Test cacheability
        check(dink_path_cache::isCacheable("tiles/ts01.bmp"), "bmp should be cacheable");
        check(dink_path_cache::isCacheable("sound/1.wav"), "wav should be cacheable");
        check(dink_path_cache::isCacheable("sound/1.mid"), "mid should be cacheable");
        check(dink_path_cache::isCacheable("story/main.c"), "script should be cacheable");
        check(dink_path_cache::isCacheable("dink.ini"), "dink.ini should be cacheable");
        check(dink_path_cache::isCacheable("hard.dat"), "hard.dat should be cacheable");

        // Non-cacheable files
        check(!dink_path_cache::isCacheable("save1.dat"), "save1.dat must not be cacheable");
        check(!dink_path_cache::isCacheable("dink/save1.dat"), "dink/save1.dat must not be cacheable");
        check(!dink_path_cache::isCacheable("autosave.dat"), "autosave.dat must not be cacheable");
        check(!dink_path_cache::isCacheable("quicksave.dat"), "quicksave.dat must not be cacheable");
        check(!dink_path_cache::isCacheable("continue_state.dat"), "continue_state.dat must not be cacheable");
        check(!dink_path_cache::isCacheable("music-diagnostic.flag"), "flag must not be cacheable");
        check(!dink_path_cache::isCacheable("music-recovery.txt"), "txt must not be cacheable");
        check(!dink_path_cache::isCacheable("save.dat.pending"), "pending must not be cacheable");
        check(!dink_path_cache::isCacheable("save.dat.rollback"), "rollback must not be cacheable");
        check(!dink_path_cache::isCacheable(".dink-save.txn"), "txn must not be cacheable");
        check(!dink_path_cache::isCacheable("temp.dmod"), "temp.dmod must not be cacheable");

        // 2. Location lookup & store
        std::string loc;
        check(!dink_path_cache::lookupLocation("tiles/ts01.bmp", loc), "lookup before store returned true");
        dink_path_cache::storeLocation("tiles/ts01.bmp", "dink/tiles/ts01.bmp");
        check(dink_path_cache::lookupLocation("tiles/ts01.bmp", loc), "lookup after store returned false");
        check(loc == "dink/tiles/ts01.bmp", "stored location mismatch");
        check(dink_path_cache::locationCount() == 1, "location count mismatch");

        // 3. Exists caching with fallback invocations
        int fallbackCalls = 0;
        auto fakeFs = [&fallbackCalls](const std::string& path) -> bool {
            ++fallbackCalls;
            return path == "sound/1.wav";
        };

        // Cacheable existing file
        bool e1 = dink_path_cache::exists("sound/1.wav", fakeFs);
        check(e1 == true, "first exists check failed");
        check(fallbackCalls == 1, "fallback should be called on first check");

        bool e2 = dink_path_cache::exists("sound/1.wav", fakeFs);
        check(e2 == true, "second exists check failed");
        check(fallbackCalls == 1, "fallback must NOT be called on cached check");

        // Cacheable non-existing file (probe)
        bool e3 = dink_path_cache::exists("sound/missing.wav", fakeFs);
        check(e3 == false, "missing file returned true");
        check(fallbackCalls == 2, "fallback should be called for missing file first check");

        bool e4 = dink_path_cache::exists("sound/missing.wav", fakeFs);
        check(e4 == false, "cached missing file returned true");
        check(fallbackCalls == 2, "cached missing file must not trigger fallback");

        // Non-cacheable file: always invokes fallback
        int saveCalls = 0;
        auto saveFs = [&saveCalls](const std::string&) -> bool {
            ++saveCalls;
            return true;
        };
        dink_path_cache::exists("dink/save1.dat", saveFs);
        check(saveCalls == 1, "first save check should invoke fallback");
        dink_path_cache::exists("dink/save1.dat", saveFs);
        check(saveCalls == 2, "second save check must invoke fallback (bypass cache)");

        // 4. Invalidation / clear
        dink_path_cache::clear();
        check(dink_path_cache::locationCount() == 0, "clear failed to wipe locations");
        check(dink_path_cache::existsCount() == 0, "clear failed to wipe exists");
        check(!dink_path_cache::lookupLocation("tiles/ts01.bmp", loc), "cleared lookup returned true");

        std::cout << "PASS: PathCache hit/miss, dynamic bypass, and clear.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "FAIL: " << e.what() << "\n";
        return 1;
    }
}
