#pragma once
#include <algorithm>
#include <cstdint>
#include <vector>

namespace dink_perf {
// Age subtraction handles the engine's wrapping millisecond clock.
inline uint32_t age(uint32_t now, uint32_t lastUse) { return now - lastUse; }
struct CacheEntry { size_t slot; uint32_t ageMS; };
inline std::vector<CacheEntry> oldestFirst(std::vector<CacheEntry> entries, uint32_t minAge) {
    entries.erase(std::remove_if(entries.begin(), entries.end(), [minAge](const CacheEntry& e) {
        return e.ageMS < minAge;
    }), entries.end());
    std::sort(entries.begin(), entries.end(), [](const CacheEntry& a, const CacheEntry& b) {
        return a.ageMS != b.ageMS ? a.ageMS > b.ageMS : a.slot < b.slot;
    });
    return entries;
}
struct CachePressure {
    bool active = false;
    bool update(int cpu, int texture, int high, int low) {
        if (cpu > high || texture > high) active = true;
        else if (cpu <= low && texture <= low) active = false;
        return active;
    }
};
// Software fallback only; successful swap-interval pacing never also sleeps.
class FramePacer {
public:
    void configure(uint64_t frequency, unsigned fps) {
        period = (frequency + fps/2) / fps;
        deadline = 0;
    }
    void begin(uint64_t now) { if (!deadline) deadline = now + period; }
    uint64_t remaining(uint64_t now) const { return deadline > now ? deadline - now : 0; }
    void finish(uint64_t now) {
        deadline += period;
        if (deadline <= now) deadline = now + period; // No burst after a stall/suspend.
    }
private:
    uint64_t period = 1, deadline = 0;
};
struct FrameStats {
    std::vector<double> intervals;
    uint64_t previous = 0;
    bool record(uint64_t now, uint64_t frequency) {
        if (previous) intervals.push_back(double(now-previous)*1000.0/frequency);
        previous=now;
        return intervals.size() >= 600;
    }
    double percentile(double fraction) {
        if (intervals.empty()) return 0;
        std::sort(intervals.begin(),intervals.end());
        return intervals[size_t((intervals.size()-1)*fraction)];
    }
    void reset() { intervals.clear(); previous=0; }
};

}
