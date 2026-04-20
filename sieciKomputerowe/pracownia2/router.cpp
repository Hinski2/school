// Jakub Iliński 346796
#include "router.hpp"
#include "utils.hpp"
#include <arpa/inet.h>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <string>
#include <sys/select.h>
#include <sys/time.h>


static std::string ipToStr(uint32_t ip) {
    in_addr a{};
    a.s_addr = htonl(ip);

    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &a, buf, sizeof(buf));
    return buf;
}

static std::string networkToStr(const Network& n) {
    return ipToStr(n.addr) + "/" + std::to_string(n.prefix);
}

Router::Router(std::vector<Interface> interfaces)
    : interfaces(std::move(interfaces))
{
    for(const auto& iface: interfaces) {
        table[iface.network] = RouteEntry{iface.dist, std::nullopt, 0};
    }
}

void Router::run() {
    advertise();
    std::cout << *this << std::endl;

    auto turn_deadline = std::chrono::steady_clock::now() + std::chrono::seconds(TURN_SECONDS);
    while(true) {
        const auto now = std::chrono::steady_clock::now();
        const auto remaining = std::chrono::duration_cast<std::chrono::microseconds>(turn_deadline - now);

        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(socket.get_fd(), &rfds);

        timeval tv{};
        tv.tv_sec = std::max(0l, remaining.count() / 1000000);
        tv.tv_usec = std::max(0l, remaining.count() % 1000000);

        const int ready = select(socket.get_fd() + 1, &rfds, nullptr, nullptr, &tv);
        if(ready < 0) {
            throw std::runtime_error("Error: select failed");
        } else if(ready > 0) {
            auto result = socket.tryRecv();
            if(result)
                processPacket(result->first, result->second);
        } else {
            current_turn++;
            aging();
            advertise();
            std::cout << *this << std::endl;
            turn_deadline = std::chrono::steady_clock::now() + std::chrono::seconds(TURN_SECONDS);
        }
    }
}

const Interface* Router::findInterface(uint32_t sender_ip) const {
    for(const auto& iface: interfaces) {
        const uint32_t mask = (iface.network.prefix == 0) ? 0u : (0xFFFFFFFFu << (32u - iface.network.prefix));

        if((sender_ip & mask) == iface.network.addr)
            return &iface;
    }
    return nullptr;
}

void Router::processPacket(uint32_t sender_ip, const DvPacket& pkt) {
    const Interface* iface = findInterface(sender_ip);
    if(!iface or sender_ip == iface->local_ip) // paket od nas
        return;

    const uint32_t candidate = saturate(iface->dist, pkt.dist);
    auto it = table.find(pkt.network);

    if(it == table.end()) { // nowa sieć
        if(candidate < LOCAL_INF_DIST) {
            table[pkt.network] = RouteEntry{candidate, sender_ip, 0};
        }
        return;
    }

    RouteEntry& entry = it->second;
    if(!entry.next_hop) // bezpośrednia sieć
        return;

    const bool from_current_nexthop = entry.next_hop and *entry.next_hop == sender_ip;
    if(from_current_nexthop or candidate < entry.dist) { // aktualizacja
        entry.dist = candidate;
        entry.next_hop = sender_ip;
        entry.turns_since_update = 0;
    }
}

void Router::advertise() {
    for(const auto& iface : interfaces) {
        table[iface.network].dist = iface.dist;

        for(const auto& [network, entry]: table) {
            if(!entry.next_hop and entry.dist >= LOCAL_INF_DIST)
                continue;

            if(entry.next_hop and findInterface(*entry.next_hop) == &iface)
                continue;

            const bool ok = socket.sendTo(iface.broadcast_ip, DvPacket{network, entry.dist});
            if(!ok) {
                table[iface.network].dist = LOCAL_INF_DIST;

                for(auto& [_network, _entry]: table) {
                    if(_entry.next_hop) {
                        const Interface* nhIface = findInterface(*_entry.next_hop);
                        if(nhIface && nhIface->network == iface.network) {
                            _entry.dist = LOCAL_INF_DIST;
                        }
                    }
                }
                break;
            }

        }
    }
}

void Router::aging() {
    for(auto it = table.begin(); it != table.end();) {
        RouteEntry& entry = it->second;
        if(!entry.next_hop) {
            it++;
            continue;
        }

        entry.turns_since_update++;
        if(entry.turns_since_update > 1 && entry.dist < LOCAL_INF_DIST) {
            entry.dist++;
        }

        if(entry.dist >= LOCAL_INF_DIST) {
            it = table.erase(it);
            continue;
        }

        it++;
    }
}

std::ostream& operator<<(std::ostream& out, const Router& router) {
    for(const auto& [network, entry]: router.table) {
        if(entry.dist >= LOCAL_INF_DIST) {
            out << networkToStr(network) << " unreachable";
        } else {
            out << networkToStr(network) << " distance " << entry.dist;
        }

        if(!entry.next_hop) {
            out << " connected directly" << std::endl;
        } else {
            out << " via " << ipToStr(*entry.next_hop) << std::endl;
        }
    }

    return out;
}
