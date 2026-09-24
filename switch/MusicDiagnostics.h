#pragma once
#ifdef __SWITCH__
#include <cstdio>
#include <cstdarg>

namespace dink_music_diagnostics {
inline bool enabled() {
    static const bool value = [] {
        FILE* file = std::fopen("sdmc:/switch/dink-smallwood/music-diagnostic.flag", "rb");
        if (!file) return false;
        std::fclose(file);
        return true;
    }();
    return value;
}
inline void write(const char* format, ...) {
    if (!enabled()) return;
    FILE* file = std::fopen("sdmc:/switch/dink-smallwood/music-diagnostic.txt", "ab");
    if (!file) return;
    std::fseek(file, 0, SEEK_END);
    if (std::ftell(file) < 65536) {
        va_list args;
        va_start(args, format);
        std::vfprintf(file, format, args);
        va_end(args);
        std::fputc('\n', file);
    }
    std::fclose(file);
}
}
#endif
