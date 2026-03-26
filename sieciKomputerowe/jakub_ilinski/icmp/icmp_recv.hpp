#pragma once 
// Jakub Iliński 346796 

#include <chrono>
#include <cstdint>
#include <string>
#include <sys/types.h>
#include <vector>

struct TtlResult {
    int responses = 0;
    std::vector<std::string> sender_ip_addrs;
    std::vector<double> rtts_ms;

    void print(int ttl, int expected) const;
    bool reached(const std::string& ip_addr) const;
};

namespace icmp_recv {
    TtlResult receive_responses(int socket_fd, uint16_t id, uint16_t seq_start, int count, int max_time, std::chrono::steady_clock::time_point send_time);
}


