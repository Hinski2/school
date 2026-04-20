// Jakub Iliński 346796
#pragma once

#include "types.hpp"
#include "utils.hpp"
#include <optional>
#include <utility>

class UdpSocket {
int fd;

public:
    UdpSocket();
    ~UdpSocket();

    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;
    UdpSocket(UdpSocket&&) = default;
    UdpSocket& operator=(UdpSocket&&) = default;

    bool sendTo(uint32_t broadcast_ip, const DvPacket& pkt) const;
    std::optional<std::pair<uint32_t, DvPacket>> tryRecv() const;

    int get_fd() const;
};
