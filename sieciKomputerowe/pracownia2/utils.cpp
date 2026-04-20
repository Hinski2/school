// Jakub Iliński 346796
#include "utils.hpp"
#include <arpa/inet.h>

// [0-3] - adres sieci, [4] - długość prefiksu, [5-8] - odległość
std::array<uint8_t, DATAGRAM_SIZE> encode(const DvPacket& pkt) {
    std::array<uint8_t, DATAGRAM_SIZE> buf{};
    const uint32_t net_big_endian = htonl(pkt.network.addr);
    const uint32_t global_dist = (pkt.dist >= LOCAL_INF_DIST) ? GLOBAL_INF_DIST : pkt.dist;
    const uint32_t dist_big_endian = htonl(global_dist);

    buf[0] = (net_big_endian >> 24) & 0xFF;
    buf[1] = (net_big_endian >> 16) & 0xFF;
    buf[2] = (net_big_endian >> 8) & 0xFF;
    buf[3] = (net_big_endian) & 0xFF;
    buf[4] = pkt.network.prefix;
    buf[5] = (dist_big_endian >> 24) & 0xFF;
    buf[6] = (dist_big_endian >> 16) & 0xFF;
    buf[7] = (dist_big_endian >> 8) & 0xFF;
    buf[8] = (dist_big_endian) & 0xFF;

    return buf;
}

DvPacket decode(const std::array<uint8_t, DATAGRAM_SIZE>& buf) {
    const uint32_t net_big_endian = (uint32_t(buf[0]) << 24) | (uint32_t(buf[1]) << 16) | (uint32_t(buf[2]) <<  8) | uint32_t(buf[3]);
    const uint32_t dist_big_endian = (uint32_t(buf[5]) << 24) | (uint32_t(buf[6]) << 16) | (uint32_t(buf[7]) << 8) | uint32_t(buf[8]);
    const uint32_t global_dist = ntohl(dist_big_endian);
    const uint32_t local_dist = (global_dist == GLOBAL_INF_DIST) ? LOCAL_INF_DIST : global_dist;

    return DvPacket{Network{ntohl(net_big_endian), buf[4]}, local_dist};
}

uint32_t saturate(uint32_t a, uint32_t b) {
    const uint32_t sum = a + b;
    return (sum < a or sum >= LOCAL_INF_DIST) ? LOCAL_INF_DIST : sum;
}
