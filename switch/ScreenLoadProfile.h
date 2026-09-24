#pragma once

#include <chrono>
#include <cstdio>

// Opt-in at process startup; regular gameplay adds no per-screen file writes.
// LogMsg is declared by the game's PlatformPrecomp.h before this header.
class SwitchScreenLoadProfile
{
public:
    explicit SwitchScreenLoadProfile(const char* stage) : m_stage(stage), m_enabled(Enabled())
    {
        if (m_enabled) m_start = Clock::now();
    }
    ~SwitchScreenLoadProfile()
    {
        if (!m_enabled) return;
        const double ms = std::chrono::duration<double, std::milli>(Clock::now() - m_start).count();
        LogMsg("[screen-load] %s: %.3f ms", m_stage, ms);
    }
private:
    using Clock = std::chrono::steady_clock;
public:
    static bool Enabled()
    {
        static const bool enabled = [] {
            FILE* file = std::fopen("profile-screen-loads.flag", "rb");
            if (!file) return false;
            std::fclose(file);
            return true;
        }();
        return enabled;
    }
private:
    const char* m_stage;
    bool m_enabled;
    Clock::time_point m_start;
};
