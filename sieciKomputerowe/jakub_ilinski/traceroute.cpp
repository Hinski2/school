// Jakub Iliński 346796 
#include "utils/utils.hpp"
#include "icmp/icmp_socket.hpp"
#include "icmp/icmp_send.hpp"
#include "icmp/icmp_recv.hpp"

#include <chrono>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

static constexpr int MAX_TTL = 30;
static constexpr uint32_t PACKETS_PER_TTL = 3;
static constexpr uint32_t TIMEOUT_MS = 1000;

static bool valid_input(int argc, char** argv) {
    if(argc != 2) { 
        std::cerr << "invalid args no, you have to pass 1 arg" << std::endl;
        return false;
    }

    const std::string target_ip_addr = argv[1];
    if(!utils::is_valid_ip_addr(target_ip_addr)) {
        std::cerr << "invalid ip addr " << target_ip_addr << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char** argv) {
    if(!valid_input(argc, argv)) {
        return EXIT_FAILURE;
    }

    const std::string target_ip_addr = argv[1];
    IcmpSocket socket;
    
    uint16_t id = static_cast<uint16_t>(getpid());
    for(int ttl = 1; ttl <= MAX_TTL; ttl++) {
        socket.set_ttl(ttl);
        uint16_t seq_start = static_cast<uint16_t>(ttl * PACKETS_PER_TTL);
        
        auto send_time = std::chrono::steady_clock::now();
        for(uint32_t i = 0; i < PACKETS_PER_TTL; i++) {
            uint16_t seq = seq_start + static_cast<uint16_t>(i);
            icmp_send::send_echo_request(socket.get_fd(), target_ip_addr, id, seq);
        }
        
        TtlResult result = icmp_recv::receive_responses(socket.get_fd(), id, seq_start, PACKETS_PER_TTL, TIMEOUT_MS, send_time);
        result.print(ttl, PACKETS_PER_TTL);

        if(result.reached(target_ip_addr)) {
            break;
        }
    }
}
