// Jakub Iliński 346796
#pragma once

#include <cstdint>
#include <optional>

constexpr uint16_t PORT = 54321;
constexpr int TURN_SECONDS = 5;
constexpr uint32_t LOCAL_INF_DIST = 10;
constexpr uint32_t GLOBAL_INF_DIST = 0xFFFFFFFFu;
constexpr size_t DATAGRAM_SIZE = 9;

struct Network {
    uint32_t addr;
    uint8_t prefix;

    bool operator==(const Network& o) const {
        return addr == o.addr && prefix == o.prefix;
    }
    bool operator<(const Network& o) const {
        if(addr != o.addr) return addr < o.addr;
        return prefix < o.prefix;
    }
};

struct Interface {
    Network network;
    uint32_t local_ip;
    uint32_t broadcast_ip;
    uint32_t dist;
};

struct RouteEntry {
    uint32_t dist;
    std::optional<uint32_t> next_hop;
    uint32_t turns_since_update;
};

struct DvPacket {
    Network network;
    uint32_t dist;
};
