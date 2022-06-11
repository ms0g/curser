#pragma once
#include <iostream>
#include <string_view>
#ifdef __linux__
#include <linux/if_packet.h>
#include <sys/socket.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>
#elif __APPLE__
#include <net/if_dl.h>
#include <sys/socket.h>
#include <net/if_types.h>
#include <net/if.h>
#include <net/ndrv.h>
#endif


class ll_endpoint {
private:
#ifdef __APPLE__
    struct sockaddr_ndrv sockaddr;
#elif __linux__
    struct sockaddr_ll sockaddr;
#endif
public:
    using native_handle_type = decltype(sockaddr);
    
    ll_endpoint() = default;
    ll_endpoint(std::string_view& ifname, uint8_t* sha = nullptr);

    ll_endpoint& operator=(const ll_endpoint& other){
        sockaddr = other.sockaddr;
        return *this;
    }
    
    
    native_handle_type* native_handle() {
        return &sockaddr;
    }
    
    
    size_t size() const {
        return sizeof(sockaddr);
    }

    friend std::ostream& operator<<(std::ostream& os, const ll_endpoint& ep) {
#ifdef __APPLE__
        os << ep.sockaddr.snd_name;
#elif __linux__
        os << ep.sockaddr.sll_ifindex << 
        ": " << ep.sockaddr.sll_addr[0] << ":" 
        << ep.sockaddr.sll_addr[1] << ":" 
        << ep.sockaddr.sll_addr[2] << ":"
        << ep.sockaddr.sll_addr[3] << ":"
        << ep.sockaddr.sll_addr[4] << ":" 
        << ep.sockaddr.sll_addr[5];

#endif
        return os;
    }
};