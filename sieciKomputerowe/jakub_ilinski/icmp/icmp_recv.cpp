// Jakub Iliński 346796 
#include "icmp_recv.hpp"
#include "../utils/utils.hpp"

#include <cerrno>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <poll.h>
#include <sys/socket.h>

void TtlResult::print(int ttl, int expected) const {
    std::cout << ttl << ". ";

    if(responses == 0) {
        std::cout << '*' << std::endl;
        return;
    }

    for(const auto& ip_addr: sender_ip_addrs) {
        std::cout << ip_addr << ' ';
    }

    if(responses == expected) {
        double avg = .0;
        for(double t: rtts_ms) 
            avg += t;

        avg /= responses;
        std::cout << static_cast<int>(avg) << "ms\n";
    } else {
        std::cout << "???" << std::endl;
    }
}

bool TtlResult::reached(const std::string& ip_addr) const {
    return std::find(sender_ip_addrs.begin(), sender_ip_addrs.end(), ip_addr) != sender_ip_addrs.end();
}

namespace icmp_recv {
    using clock = std::chrono::steady_clock;
    using ms = std::chrono::milliseconds;

    static bool parse_icmp_response(const uint8_t* buffer, ssize_t packet_len, uint16_t& out_id, uint16_t& out_seq) {
        if(packet_len < static_cast<ssize_t>(sizeof(struct ip)) + 8) 
            return false;

        const struct ip* ip_addr_header = reinterpret_cast<const struct ip*>(buffer);
        ssize_t ip_addr_header_len = 4 * ip_addr_header -> ip_hl;
        const struct icmp* icmp_header = reinterpret_cast<const struct icmp*>(buffer + ip_addr_header_len);
        
        const struct icmp* target_icmp = nullptr;
        if(icmp_header -> icmp_type == ICMP_ECHOREPLY) {
            target_icmp = icmp_header;
        } else if(icmp_header -> icmp_type == ICMP_TIME_EXCEEDED) {
            const uint8_t* inner = buffer + ip_addr_header_len + 8; // wskazuej na początek oryginalnego nagłówka ip + 8 -> nagłówek time exceeded
            ssize_t remaining = packet_len - ip_addr_header_len - 8;

            if(remaining < static_cast<ssize_t>(sizeof(struct ip) + 8))
                return false;

            const struct ip* inner_ip_addr = reinterpret_cast<const struct ip*>(inner);
            target_icmp = reinterpret_cast<const struct icmp*>(inner + 4 * inner_ip_addr -> ip_hl);
        } else {
            return false;
        }
        
        out_id = ntohs(target_icmp -> icmp_hun.ih_idseq.icd_id);
        out_seq = ntohs(target_icmp -> icmp_hun.ih_idseq.icd_seq);
        return true;
    }

    static int remaining_time(clock::time_point start, int time) {
        auto elapsed = std::chrono::duration_cast<ms>(clock::now() - start);
        return std::max(0, time - static_cast<int>(elapsed.count()));
    }


    TtlResult receive_responses(int socket_fd, uint16_t id, uint16_t seq_start, int no_responses, int max_time, std::chrono::steady_clock::time_point send_time) {
        TtlResult result;

        while(result.responses < no_responses) {
            int left_time;
            if((left_time = remaining_time(send_time, max_time)) <= 0) {
                break;
            }

            struct pollfd pfd = {};
            pfd.fd = socket_fd;
            pfd.events = POLLIN;

            int ready = poll(&pfd, 1, left_time); // czekanie bez aktywnego czekania
            if(ready == 0) { // nic nie przyszło
                break;
            } else if(ready < 0) {
                if(errno == EINTR) continue;
                throw std::runtime_error("poll error: " + utils::ERROR());
            }

            struct sockaddr_in sender = {};
            socklen_t sender_len = sizeof(sender);
            uint8_t buffer[IP_MAXPACKET];

            ssize_t packet_len = recvfrom(socket_fd, buffer, IP_MAXPACKET, 0, reinterpret_cast<struct sockaddr*>(&sender), &sender_len);
            if(packet_len < 0) {
                if(errno == EAGAIN) continue;
                throw std::runtime_error("recvfrom error: " + utils::ERROR());
            }

            uint16_t recv_id, recv_seq;
            if(!parse_icmp_response(buffer, packet_len, recv_id, recv_seq)) continue;
            if(recv_id != id) continue;
            if(recv_seq < seq_start or recv_seq >= seq_start + no_responses) continue;

            auto now = clock::now();
            double rtt = std::chrono::duration<double, std::milli>(now - send_time).count();

            result.rtts_ms.push_back(rtt);
            result.responses++;

            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sender.sin_addr, ip_str, sizeof(ip_str));
            std::string sender_ip(ip_str);

            if(std::find(result.sender_ip_addrs.begin(), result.sender_ip_addrs.end(), sender_ip) == result.sender_ip_addrs.end())
                result.sender_ip_addrs.push_back(sender_ip);
        }

        return result;
    }
}


