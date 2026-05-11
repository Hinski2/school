#pragma once
// Jakub Iliński 346796

#include <cstdint>

struct Chunk {
    std::uint32_t start;
    std::uint16_t length;

    Chunk(std::uint32_t start_offset, std::uint16_t chunk_length) noexcept;
    std::uint32_t end() const noexcept;
};