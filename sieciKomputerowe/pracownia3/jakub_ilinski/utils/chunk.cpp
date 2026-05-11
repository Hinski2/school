// Jakub Iliński 346796
#include "chunk.hpp"

Chunk::Chunk(std::uint32_t start_offset, std::uint16_t chunk_length) noexcept
    : start(start_offset), length(chunk_length) {}

std::uint32_t Chunk::end() const noexcept {
    return start + length;
}
