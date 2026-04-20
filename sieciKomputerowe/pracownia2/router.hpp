// Jakub Iliński 346796
#pragma once

#include "socket.hpp"
#include "types.hpp"
#include <map>
#include <ostream>
#include <vector>

class Router {
    std::vector<Interface> interfaces;
    std::map<Network, RouteEntry> table;

    UdpSocket socket;
    uint32_t current_turn = 0;

    void processPacket(uint32_t sender_ip, const DvPacket& pkt);
    void advertise();
    void aging();
    const Interface* findInterface(uint32_t sender_ip) const;

public:
    friend std::ostream& operator<<(std::ostream& out, const Router& router);
    explicit Router(std::vector<Interface> interfaces);
    void run();
};
