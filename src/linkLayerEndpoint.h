#pragma once

#include <iomanip>
#include <iostream>
#include <string_view>
#ifdef __linux__
#include <linux/if_packet.h> //struct sockaddr_ll
#include <net/ethernet.h>
#include <net/if.h>
#elif __APPLE__
#include <net/ndrv.h>
#endif

class LinkLayerEndpoint {
#ifdef __APPLE__
    sockaddr_ndrv sockaddr{};
#elif __linux__
    sockaddr_ll sockaddr{};
#endif
    using native_handle_type = decltype(sockaddr);
public:
    LinkLayerEndpoint() = default;

    LinkLayerEndpoint(const std::string_view& ifname, uint8_t* sha);

    LinkLayerEndpoint& operator=(const LinkLayerEndpoint& other) = default;

    native_handle_type* native_handle() {
        return &sockaddr;
    }

    [[nodiscard]] size_t size() const {
        return sizeof(sockaddr);
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkLayerEndpoint& ep) {
#ifdef __APPLE__
        os << ep.sockaddr.snd_name << ": ";
#elif __linux__
        char ifname[IF_NAMESIZE];
        os << if_indextoname(ep.sockaddr.sll_ifindex, ifname) << ": ";
#endif
        os << std::hex << std::setfill('0')
                << std::setw(2) << static_cast<int>(ep.m_sha[0]) << ":"
                << std::setw(2) << static_cast<int>(ep.m_sha[1]) << ":"
                << std::setw(2) << static_cast<int>(ep.m_sha[2]) << ":"
                << std::setw(2) << static_cast<int>(ep.m_sha[3]) << ":"
                << std::setw(2) << static_cast<int>(ep.m_sha[4]) << ":"
                << std::setw(2) << static_cast<int>(ep.m_sha[5]);
        return os;
    }

private:
    uint8_t* m_sha{nullptr};
};
