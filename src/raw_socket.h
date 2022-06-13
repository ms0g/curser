#pragma once

#include <iostream>
#ifdef __linux__
#include <linux/if_packet.h>
#elif __APPLE__
#include <sys/socket.h>
#include <net/ndrv.h>
 #include <unistd.h>
#endif
#include "ll_endp.h"

class base_socket {};
class raw_socket: public base_socket {
private:
    int m_family;
    int m_protocol;
    int m_sock;
    ll_endpoint m_ep;
public:
    explicit raw_socket(int family, int protocol);
    raw_socket();
    ~raw_socket();

    int type() const {
        return SOCK_RAW;
    }

    int family() const {
        return m_family;
    }

    int protocol() const {
        return m_protocol;
    }

    void bind(const ll_endpoint& ep);
    void sendto(const void* buf, size_t len);
};