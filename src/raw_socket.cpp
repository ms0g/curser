#include "raw_socket.h"
#include <iostream>
#include <unistd.h> //close
#include <sys/socket.h> //socket

#ifdef __linux__
#include <arpa/inet.h>
#endif

raw_socket::raw_socket(const int family, int protocol) : m_family(family), m_protocol(htons(protocol)) {
    m_sock = socket(m_family, SOCK_RAW, m_protocol);
    if (m_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

raw_socket::raw_socket() {
#ifdef __APPLE__
    m_family = AF_NDRV;
    m_protocol = 0;
#elif __linux__
    m_family = AF_PACKET;
    m_protocol = htons(ETH_P_ALL);
#endif
    m_sock = socket(m_family, SOCK_RAW, m_protocol);

    if (m_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

raw_socket::~raw_socket() {
    close(m_sock);
}

void raw_socket::bind(const ll_endpoint& ep) {
    m_ep = ep;
    if (::bind(m_sock, reinterpret_cast<sockaddr*>(m_ep.native_handle()), m_ep.size()) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

void raw_socket::sendto(const void* buf, size_t len) {
    if (::sendto(m_sock, buf, len, 0, reinterpret_cast<sockaddr*>(m_ep.native_handle()), m_ep.size()) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
}