#pragma once

#include "ll_endp.h"

class base_socket {
};

class raw_socket : public base_socket {
private:
    const int m_family;
    const int m_protocol;
    int m_sock;
    ll_endpoint m_ep;
public:
    raw_socket(int family, int protocol);

    raw_socket();

    ~raw_socket();

    [[nodiscard]] static int type() {
        return SOCK_RAW;
    }

    [[nodiscard]] int family() const {
        return m_family;
    }

    [[nodiscard]] int protocol() const {
        return m_protocol;
    }

    void bind(const ll_endpoint& ep);

    void sendto(const void* buf, size_t len);
};