#include <iostream>
#include <unistd.h> //close
#include <sys/socket.h> //socket

#ifdef __linux__
#include <arpa/inet.h>
#endif

#include "raw_socket.h"

raw_socket::raw_socket(int family, int protocol) : m_family(family), m_protocol(htons(protocol)) {
    m_sock = socket(family, type(), protocol);
    if (m_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

#ifdef __linux__
raw_socket::raw_socket(): m_family(AF_PACKET), m_protocol(htons(ETH_P_ALL)) {
    m_sock = socket(m_family, type(), m_protocol);
    if (m_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}
#elif __APPLE__

raw_socket::raw_socket() : m_family(AF_NDRV), m_protocol(0) {
    m_sock = socket(m_family, type(), m_protocol);
    if (m_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
}

#endif

raw_socket::~raw_socket() {
    ::close(m_sock);
}

void raw_socket::bind(const ll_endpoint& ep) {
    m_ep = ep;
    if (::bind(m_sock, reinterpret_cast<struct sockaddr*>(m_ep.native_handle()), m_ep.size()) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
}

void raw_socket::sendto(const void* buf, size_t len) {
    if (::sendto(m_sock, buf, len, 0, reinterpret_cast<struct sockaddr*>(m_ep.native_handle()), m_ep.size()) < 0) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
}