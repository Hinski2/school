#pragma once 
// Jakub Iliński 346796 

#include <cstdint>
#include <string> 

namespace icmp_send {
    void send_echo_request(int socket_fd, const std::string& dest_ip, uint16_t id, uint16_t seq);
}
