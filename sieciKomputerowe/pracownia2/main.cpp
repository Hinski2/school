// Jakub Iliński 346796
#include "router.hpp"
#include <arpa/inet.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static Interface parseInterface(const std::string& line) {
    std::istringstream ss(line);
    std::string cidr, keyword;
    uint32_t dist;
    ss >> cidr >> keyword >> dist;

    const auto slash = cidr.find('/');
    const std::string ip = cidr.substr(0, slash);
    const auto prefix = static_cast<uint8_t>(std::stoi(cidr.substr(slash + 1)));

    in_addr tmp{};
    inet_pton(AF_INET, ip.c_str(), &tmp);
    const uint32_t local_ip = ntohl(tmp.s_addr);

    const uint32_t mask = (prefix == 0u) ? 0u : (0xFFFFFFFFu << (32u - prefix));
    const uint32_t net_addr = local_ip & mask;
    const uint32_t broadcast = net_addr | ~mask;

    return Interface{Network{net_addr, prefix}, local_ip, broadcast, dist};
}

int main() {
    int n; std::cin >> n;
    std::cin.ignore();

    std::vector<Interface> interfaces;
    interfaces.reserve(static_cast<size_t>(n));

    for(int i = 0; i < n; i++) {
        std::string line; std::getline(std::cin, line);
        interfaces.push_back(parseInterface(line));
    }

    Router router(std::move(interfaces));
    router.run();
}