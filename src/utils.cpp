#include "utils.h"
#include <iostream>
#include <cstring>
#include <ifaddrs.h> //getifaddrs
#include <arpa/inet.h> //inet_pton
#ifdef __APPLE__
#include <net/if_dl.h>
#elif __linux__
#include <linux/if.h>
#include <net/ethernet.h>
#include <linux/if_packet.h> //struct sockaddr_ll
#endif

uint32_t inet_bf(const char* addr) {
    sockaddr_in sa{};

    if (inet_pton(AF_INET, addr, &sa.sin_addr) != 1) {
        perror("inet binary formatting failed");
        exit(EXIT_FAILURE);
    }

    return ntohl(sa.sin_addr.s_addr);
}

void getMacAddr(const char* ifname, uint8_t* const mac) {
    ifaddrs* ifaddr = nullptr;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    ifaddrs* ifa = nullptr;
    unsigned char* hwaddr = nullptr;
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        sa_family_t family;
#ifdef __APPLE__
        family = AF_LINK;
#elif __linux__
        family = AF_PACKET;
#endif
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == family) {
            if (strcmp(ifa->ifa_name, ifname) == 0) {
#ifdef __APPLE__
                hwaddr = reinterpret_cast<unsigned char*>(
                    LLADDR(reinterpret_cast<struct sockaddr_dl*>(ifa->ifa_addr)));
#elif __linux__
                hwaddr = reinterpret_cast<unsigned char *>(
                    reinterpret_cast<struct sockaddr_ll*>(ifa->ifa_addr)->sll_addr);
#endif
                memcpy(mac, hwaddr, 6);
                break;
            }
        }
    }
    freeifaddrs(ifaddr);
}
