#pragma once

#include <climits>
#include <cstring>
#include <type_traits>

namespace dink
{
// Open streams must be at their beginning. Only ordinary files may seek:
// Proton's ZIP seek implementation cannot handle compressed entries.
template <typename Stream, typename Record>
bool ReadMapRecord(Stream& stream, int number, bool canSeek, Record& output)
{
    static_assert(std::is_trivially_copyable<Record>::value, "Raw map record required");
    static_assert(sizeof(Record) <= INT_MAX, "Map record exceeds stream API limit");
    const int size = static_cast<int>(sizeof(Record));
    if (number < 1 || number - 1 > (INT_MAX - size) / size) return false;
    int offset = (number - 1) * size;
    if (canSeek)
    {
        stream.SeekFromStart(offset);
    }
    else
    {
        unsigned char discard[4096];
        while (offset > 0)
        {
            const int wanted = offset < 4096 ? offset : 4096;
            const int count = stream.Read(discard, wanted);
            if (count <= 0 || count > wanted) return false;
            offset -= count;
        }
    }

    // A truncated record must not partially replace the current screen.
    Record candidate;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&candidate);
    int remaining = size;
    while (remaining > 0)
    {
        const int count = stream.Read(bytes, remaining);
        if (count <= 0 || count > remaining) return false;
        bytes += count;
        remaining -= count;
    }
    std::memcpy(&output, &candidate, sizeof(Record));
    return true;
}
}
