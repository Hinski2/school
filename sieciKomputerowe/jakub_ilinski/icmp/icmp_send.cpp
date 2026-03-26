// Jakub Iliński 346796 
#include "icmp_send.hpp"
#include "../utils/utils.hpp"

#include <arpa/inet.h>
#include <cstdint>
#include <netinet/ip_icmp.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>


namespace icmp_send {
    void send_echo_request(int socket_fd, const std::string& dest_ip, uint16_t id, uint16_t seq) {
        struct icmp header = {};
        header.icmp_type = ICMP_ECHO;
        header.icmp_code = 0;
        header.icmp_hun.ih_idseq.icd_id = htons(id);
        header.icmp_hun.ih_idseq.icd_seq = htons(seq);
        header.icmp_cksum = utils::compute_icmp_checksum(reinterpret_cast<uint16_t*>(&header), sizeof(header));
        
        struct sockaddr_in dest = {};
        dest.sin_family = AF_INET;
        if(inet_pton(AF_INET, dest_ip.c_str(), &dest.sin_addr) != 1) {
            throw std::runtime_error("inet_pton error: Invalid IP " + dest_ip);
        }

        ssize_t sent = sendto(socket_fd, &header, sizeof(header), 0, reinterpret_cast<struct sockaddr*>(&dest), sizeof(dest));

        if(sent != static_cast<ssize_t>(sizeof(header))) {
            throw std::runtime_error("sendto error: " + utils::ERROR());
        }
    }
}
