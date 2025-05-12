#pragma once

#include "ll_endp.h"

class base_socket {
};

class raw_socket : public base_socket {
public:
    raw_socket(int family, int protocol);

    raw_socket();

    ~raw_socket();

    [[nodiscard]] int family() const {
        return m_family;
    }

    [[nodiscard]] int protocol() const {
        return m_protocol;
    }

    void bind(const ll_endpoint& ep);

    void sendto(const void* buf, size_t len);

private:
    int m_family;
    int m_protocol;
    int m_sock;
    ll_endpoint m_ep;
};
