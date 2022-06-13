#include <iostream>
#include <unistd.h>
#include <ifaddrs.h>
#ifdef __APPLE__
#include <net/ndrv.h>
#include <arpa/inet.h>
#include <net/if_dl.h>
#elif __linux__
#include <linux/if.h>
#endif

#include "utils.h"

uint32_t inet_bf(const char* addr) {
    struct sockaddr_in sa{};

    if (inet_pton(AF_INET, addr, &sa.sin_addr) != 1) {
        perror("inet binary formatting failed");
        exit(EXIT_FAILURE);
    }

    return ntohl(sa.sin_addr.s_addr);
}

void getMacAddr(const char* ifname, uint8_t* mac) {
    struct ifaddrs *ifaddr = nullptr;
    struct ifaddrs *ifa = nullptr;
    unsigned char *hwaddr = nullptr;

    if (getifaddrs(&ifaddr) == -1) {
         perror("getifaddrs");
    } else {
         for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
#ifdef __APPLE__
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_LINK) {
#elif __linux__
            if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET) {
#endif
                if (strcmp(ifa->ifa_name, ifname) == 0) {  
#ifdef __APPLE__
                    hwaddr = (unsigned char *)LLADDR((struct sockaddr_dl *)(ifa)->ifa_addr);
#elif __linux__
                    struct sockaddr_ll *s = (struct sockaddr_ll*)ifa->ifa_addr;
                    hwaddr = s->sll_addr;
#endif
                    memcpy(mac, hwaddr, 6);
                    break;
                }
            }
        }
    }
    freeifaddrs(ifaddr);
    
}