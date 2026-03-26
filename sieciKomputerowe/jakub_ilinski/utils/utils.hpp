#pragma once 
// Jakub Iliński 346796 

#include <cstdint>
#include <string>

namespace utils {
    bool is_valid_ip_addr(const std::string& ip_addr);
    uint16_t compute_icmp_checksum(const void* data, size_t length);
    std::string ERROR();
}
