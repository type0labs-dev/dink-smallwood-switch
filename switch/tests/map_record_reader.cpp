#include "source/dink/MapRecordReader.h"
#include <algorithm>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

static void require(bool value, const char* message)
{
    if (!value) throw std::runtime_error(message);
}

struct MemoryStream
{
    std::vector<unsigned char> data;
    int position = 0, readBytes = 0, seeks = 0, chunk = INT_MAX;
    bool fail = false;
    int Read(unsigned char* out, int wanted)
    {
        if (fail) return -1;
        int count = std::min({wanted, chunk, static_cast<int>(data.size()) - position});
        if (count <= 0) return 0;
        std::memcpy(out, data.data() + position, count);
        position += count;
        readBytes += count;
        return count;
    }
    void SeekFromStart(int offset) { position = offset; ++seeks; }
};

struct FileStream
{
    FILE* file;
    size_t readBytes = 0;
    explicit FileStream(const char* path) : file(std::fopen(path, "rb"))
    {
        require(file != nullptr, "Map fixture missing");
    }
    ~FileStream() { std::fclose(file); }
    void SeekFromStart(int offset) { require(std::fseek(file, offset, SEEK_SET) == 0, "Seek failed"); }
    int Read(unsigned char* out, int wanted)
    {
        int count = static_cast<int>(std::fread(out, 1, wanted, file));
        readBytes += count;
        return count;
    }
};

int main(int argc, char** argv)
{
    try
    {
        using Record = std::array<unsigned char, 32>;
        Record out;
        MemoryStream original;
        for (int i = 0; i < 320; ++i) original.data.push_back(static_cast<unsigned char>(i));
        for (bool seek : {false, true})
        {
            for (int number : {1, 5, 10})
            {
                MemoryStream stream = original;
                stream.chunk = 7; // Reads may return fewer bytes than requested.
                require(dink::ReadMapRecord(stream, number, seek, out), "Valid record failed");
                require(std::memcmp(out.data(), original.data.data() + (number - 1) * 32, 32) == 0,
                        "Record differs from source");
                require(stream.seeks == (seek ? 1 : 0), "Nonseekable stream was sought");
                require(stream.readBytes == (seek ? 32 : number * 32), "Unexpected I/O volume");
            }
            for (int number : {0, -1, INT_MAX, 11, 12})
            {
                MemoryStream stream = original;
                out.fill(0xcc);
                const Record before = out;
                require(!dink::ReadMapRecord(stream, number, seek, out), "Invalid record accepted");
                require(out == before, "Failed read changed output");
            }
            for (bool fail : {false, true})
            {
                MemoryStream stream = original;
                stream.data.resize(319); // Last record is truncated.
                stream.fail = fail;
                out.fill(0xcc);
                const Record before = out;
                require(!dink::ReadMapRecord(stream, 10, seek, out), "Read failure ignored");
                require(out == before, "Partial record published");
            }
        }

        require(argc == 2, "Pass the original map.dat path");
        std::ifstream input(argv[1], std::ios::binary);
        std::vector<unsigned char> map((std::istreambuf_iterator<char>(input)), {});
        // Original Dink disk format: 31,280 bytes per screen.
        using MapRecord = std::array<unsigned char, 31280>;
        require(!map.empty() && map.size() % sizeof(MapRecord) == 0, "Unexpected map layout");
        const size_t count = map.size() / sizeof(MapRecord);
        FileStream file(argv[1]);
        for (size_t number = 1; number <= count; ++number)
        {
            MapRecord record;
            require(dink::ReadMapRecord(file, static_cast<int>(number), true, record), "Real map failed");
            require(std::memcmp(record.data(), map.data() + (number - 1) * sizeof(MapRecord), sizeof(MapRecord)) == 0,
                    "Real map screen differs");
        }
        require(file.readBytes == map.size(), "Real-map seeks read unnecessary data");
        std::cout << "PASS: " << count << " real map records match; short reads, EOF, errors, overflow and sequential fallback checked.\n";
        std::cout << "Last screen: " << map.size() << " -> " << sizeof(MapRecord) << " bytes read (not a console timing benchmark).\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
