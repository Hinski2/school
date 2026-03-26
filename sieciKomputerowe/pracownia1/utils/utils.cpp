// Jakub Iliński 346796 
#include "utils.hpp"

#include <cstdint>
#include <stdexcept>
#include <string.h>
#include <cerrno>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace utils {
    std::string ERROR() {
        return std::string(strerror(errno));
    }

    bool is_valid_ip_addr(const std::string& ip_addr) {
        struct in_addr tmp;
        return inet_pton(AF_INET, ip_addr.c_str(), &tmp) == 1;
    }

    uint16_t compute_icmp_checksum(const void* data, size_t length) {
        const uint16_t* ptr = reinterpret_cast<const uint16_t*>(data);
        uint32_t sum = 0;

        if(length % 2) {
            throw std::runtime_error("compute_icp_checksum error: data lenght is odd");
        }

        for(; length > 0; length -= 2)
            sum += *ptr++;

        sum = (sum >> 16U) + (sum & 0xffffU);
        return ~(sum + (sum >> 16U));
    }
}
