#pragma once

#include "ll_endp.h"

class base_socket {};
class raw_socket: public base_socket {
private:
    const int m_family;
    const int m_protocol;
    int m_sock;
    ll_endpoint m_ep;
public:
    raw_socket(const int family, const int protocol);
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