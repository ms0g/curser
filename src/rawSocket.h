#pragma once

#include "linkLayerEndpoint.h"

class ISocket {
};

class RawSocket : public ISocket {
public:
    RawSocket(int family, int protocol);

    RawSocket();

    ~RawSocket();

    [[nodiscard]] int family() const {
        return m_family;
    }

    [[nodiscard]] int protocol() const {
        return m_protocol;
    }

    void bind(const LinkLayerEndpoint& ep);

    void sendto(const void* buf, size_t len);

private:
    int m_family;
    int m_protocol;
    int m_sock;
    LinkLayerEndpoint m_ep;
};
