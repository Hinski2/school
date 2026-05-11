#pragma once
// Jakub Iliński 346796

#include <chrono>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "chunk.hpp"

class Receiver {
private:
    struct SegmentState {
        std::chrono::steady_clock::time_point lastSentAt;
        std::vector<std::uint8_t> payload;
        bool received;
    };

    static constexpr std::uint16_t MaxChunkSize = 1000;
    static constexpr std::uint32_t WindowCapacitySegmentsSize = 800;
    static constexpr std::chrono::milliseconds RetransmitTimeout{900};

    int fd;
    std::uint32_t totalSize;
    std::uint32_t writtenUpToBytes;
    std::map<std::uint32_t, SegmentState> activeSentSegments;

public:
    Receiver(const std::string& outputPath, std::uint32_t totalSize);
    ~Receiver();

    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;
    Receiver(Receiver&&) = delete;
    Receiver& operator=(Receiver&&) = delete;

    bool isComplete() const;
    std::vector<Chunk> getMissingChunks();
    void writeChunks();
    void addReceivedChunk(const Chunk& chunk, std::vector<std::uint8_t>&& payload);
};