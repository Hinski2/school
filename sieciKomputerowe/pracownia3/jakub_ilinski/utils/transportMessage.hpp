#pragma once 
// Jakub Iliński 346796

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include "chunk.hpp"

namespace TransportMessage {
    std::vector<std::uint8_t> buildGetRequest(const Chunk& chunk);
    std::optional<std::pair<Chunk, std::vector<std::uint8_t>>> tryParseDataResponse(const std::vector<std::uint8_t>& datagram);
}