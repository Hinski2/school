// Jakub Iliński 346796
#include "socket.hpp"
#include <arpa/inet.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

int UdpSocket::get_fd() const { 
    return fd; 
}

UdpSocket::UdpSocket() {
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0)
        throw std::runtime_error("Error: socket failed");

    const int broadcast = 1; // włączamy broadcast
    if(setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
        throw std::runtime_error("Error: setsockopt failed");

    const int reuse = 1; // pozwalamy wielu procesom na ten sam port
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
        throw std::runtime_error("Error: setsockopt failed");

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0)
        throw std::runtime_error("Error: bind failed");
}

UdpSocket::~UdpSocket() {
    if(fd >= 0)
        close(fd);
}

bool UdpSocket::sendTo(uint32_t broadcast_ip, const DvPacket& pkt) const {
    const auto buf = encode(pkt);

    sockaddr_in dest{};
    dest.sin_family = AF_INET;
    dest.sin_port = htons(PORT);
    dest.sin_addr.s_addr = htonl(broadcast_ip);

    const ssize_t sent = sendto(fd, buf.data(), buf.size(), 0, reinterpret_cast<const sockaddr*>(&dest), sizeof(dest));
    if(sent < 0)
        return false;
    return true;
}

std::optional<std::pair<uint32_t, DvPacket>> UdpSocket::tryRecv() const {
    std::array<uint8_t, DATAGRAM_SIZE> buf{};
    sockaddr_in sender{};
    socklen_t sender_len = sizeof(sender);

    const ssize_t n = recvfrom(fd, buf.data(), buf.size(), 0, reinterpret_cast<sockaddr*>(&sender), &sender_len);
    if(n < 0 or static_cast<size_t>(n) != DATAGRAM_SIZE)
        return std::nullopt;

    const uint32_t sender_ip = ntohl(sender.sin_addr.s_addr);
    return std::make_pair(sender_ip, decode(buf));
}
