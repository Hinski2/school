#include "udpSocket.hpp"
// Jakub Iliński 346796

#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

UdpSocket::UdpSocket(std::uint32_t serverIp, std::uint16_t serverPort)
    : fd(socket(AF_INET, SOCK_DGRAM, 0)), serverAddress{}
{
    if(fd < 0) {
        throw std::runtime_error("Error: cannot create socket");
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = serverIp;
}

UdpSocket::~UdpSocket() {
    if(fd >= 0) {
        close(fd);
    }
}

void UdpSocket::send(const std::vector<std::uint8_t>& datagram) const {
    const ssize_t sent = sendto(
        fd,
        datagram.data(),
        datagram.size(),
        0,
        reinterpret_cast<const sockaddr*>(&serverAddress),
        sizeof(serverAddress)
    );

    if (sent < 0 or static_cast<std::size_t>(sent) != datagram.size()) {
        throw std::runtime_error("Error: failed to send datagram");
    }
}

std::optional<std::pair<std::uint32_t, std::vector<std::uint8_t>>> UdpSocket::tryRecv() const {
    pollfd pollDescriptor{};
    pollDescriptor.fd = fd;
    pollDescriptor.events = POLLIN;

    const int pollResult = poll(&pollDescriptor, 1, 50);
    if(pollResult < 0) {
        throw std::runtime_error("Error: poll failed");
    }

    if(pollResult == 0) {
        return std::nullopt;
    }

    sockaddr_in sender{};
    socklen_t senderLength = sizeof(sender);
    std::vector<std::uint8_t> buffer(2048);
    const ssize_t received = recvfrom(
        fd,
        buffer.data(),
        buffer.size(),
        0,
        reinterpret_cast<sockaddr*>(&sender),
        &senderLength
    );

    if(received < 0) {
        throw std::runtime_error("Error: recvfrom failed");
    }

    buffer.resize(static_cast<std::size_t>(received));
    return std::make_pair(sender.sin_addr.s_addr, std::move(buffer));
}