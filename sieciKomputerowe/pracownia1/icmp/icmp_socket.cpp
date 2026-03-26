// Jakub Iliński 346796 
#include "icmp_socket.hpp"
#include "../utils/utils.hpp"

#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

IcmpSocket::IcmpSocket() {
    socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    if(socket_fd < 0) {
        throw std::runtime_error("socket error: " + utils::ERROR());
    }
}

IcmpSocket::~IcmpSocket() {
    if(socket_fd >= 0) {
        close(socket_fd);
    }
}

void IcmpSocket::set_ttl(int ttl) {
    if(setsockopt(socket_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
        throw std::runtime_error("setsockopt error: " + utils::ERROR());
    }
}

int IcmpSocket::get_fd() const {
    return socket_fd;
}
