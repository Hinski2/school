#pragma once 
// Jakub Iliński 346796 

class IcmpSocket {
    int socket_fd;

public:
    IcmpSocket();
    ~IcmpSocket();

    IcmpSocket(const IcmpSocket&) = delete;
    IcmpSocket& operator=(const IcmpSocket&) = delete;

    void set_ttl(int ttl);
    int get_fd() const;
};
