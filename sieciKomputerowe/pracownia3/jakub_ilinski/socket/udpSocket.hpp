#pragma once
// Jakub Iliński 346796

#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include <netinet/in.h>

class UdpSocket {
private:
    int fd;
    sockaddr_in serverAddress;

public:
    UdpSocket(std::uint32_t serverIp, std::uint16_t serverPort);
    ~UdpSocket();

    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;
    UdpSocket(UdpSocket&&) = delete;
    UdpSocket& operator=(UdpSocket&&) = delete;

    void send(const std::vector<std::uint8_t>& datagram) const;
    std::optional<std::pair<std::uint32_t, std::vector<std::uint8_t>>> tryRecv() const; // {ip_nadawcy, dane}
};
