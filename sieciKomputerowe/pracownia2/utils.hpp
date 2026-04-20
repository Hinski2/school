// Jakub Iliński 346796
#pragma once

#include "types.hpp"
#include <array>
#include <cstdint>

std::array<uint8_t, DATAGRAM_SIZE> encode(const DvPacket& pkt);
DvPacket decode(const std::array<uint8_t, DATAGRAM_SIZE>& buf);

uint32_t saturate(uint32_t a, uint32_t b);
