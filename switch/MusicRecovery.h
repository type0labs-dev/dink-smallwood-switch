#pragma once
#include <cctype>
#include <sstream>
#include <string>

namespace dink_music {
// An explicit, local recovery directive can repair an old save that lost its
// track. Never guess a region or override intentional silence in normal saves.
inline std::string recoveryTrack(const std::string& directives, int screen,
                                 int mapMusic, bool active, bool baseGame,
                                 const std::string& savedTrack) {
    if (!active || !baseGame || !savedTrack.empty() || mapMusic != 0 ||
        screen < 1 || screen > 768 || directives.size() > 4096) return {};
    std::istringstream input(directives);
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream fields(line);
        int match;
        std::string track, extra;
        if (!(fields >> match >> track) || (fields >> extra) || match != screen) continue;
        if (track.size() < 5 || track.size() > 63 || track.substr(track.size()-4) != ".mid") continue;
        bool valid = true;
        for (std::size_t i = 0; i < track.size()-4; ++i)
            if (!std::isalnum(static_cast<unsigned char>(track[i])) && track[i] != '_') valid = false;
        if (valid) return track;
    }
    return {};
}
}
