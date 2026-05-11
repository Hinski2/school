// Jakub Iliński 346796
#include "receiver.hpp"

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <utility>
#include <vector>

Receiver::Receiver(const std::string& outputPath, const std::uint32_t totalSize)
    : fd(-1), totalSize(totalSize), writtenUpToBytes(0), activeSentSegments() {

    fd = open(outputPath.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
        throw std::runtime_error("Error: Failed to open output file");
}

Receiver::~Receiver() {
    if(fd != -1)
        close(fd);
}

bool Receiver::isComplete() const {
    return writtenUpToBytes >= totalSize;
}

std::vector<Chunk> Receiver::getMissingChunks() {
    std::vector<Chunk> missing;
    missing.reserve(WindowCapacitySegmentsSize);

    const auto now = std::chrono::steady_clock::now();
    const std::uint32_t windowBytes = WindowCapacitySegmentsSize * MaxChunkSize;
    const std::uint32_t windowEnd = std::min(totalSize, writtenUpToBytes + windowBytes);

    for(std::uint32_t start = writtenUpToBytes; start < windowEnd; start += MaxChunkSize) {
        const std::uint32_t remaining = totalSize - start;
        const std::uint16_t length = std::min<std::uint32_t>(MaxChunkSize, remaining);

        auto [it, inserted] = activeSentSegments.emplace(start, SegmentState{now, {}, false});
        SegmentState& state = it->second;

        if(inserted) { // nowy
            missing.push_back(Chunk{start, length});
        } else if(!state.received and now - state.lastSentAt >= RetransmitTimeout) { // stary do retransmisji
            state.lastSentAt = now;
            missing.push_back(Chunk{start, length});
        }
    }

    return missing;
}

void Receiver::writeChunks() {
    while(!isComplete()) {
        auto it = activeSentSegments.find(writtenUpToBytes);
        if(it == activeSentSegments.end() or !it->second.received) {
            break;
        }

        std::vector<std::uint8_t>& payload = it->second.payload;
        for(size_t offset = 0; offset < payload.size();) {
            const ssize_t written = write(fd, payload.data() + offset, payload.size() - offset);
            if(written < 0)
                throw std::runtime_error("Error: Failed to write output file");

            offset += written;
        }


        writtenUpToBytes += payload.size();
        activeSentSegments.erase(it);
    }
}

void Receiver::addReceivedChunk(const Chunk& chunk, std::vector<std::uint8_t>&& payload) {
    if(chunk.length == 0 or payload.size() != chunk.length) {
        return;
    }

    auto [it, inserted] = activeSentSegments.emplace(chunk.start, SegmentState{std::chrono::steady_clock::now(), {}, false});
    SegmentState& state = it->second;

    if(!inserted and state.received) { // duplikat
        return;
    }

    state.payload = std::move(payload);
    state.received = true;
}
