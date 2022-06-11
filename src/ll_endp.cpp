#include "ll_endp.h"

ll_endpoint::ll_endpoint(std::string_view &ifname, uint8_t* sha)  {
        memset(&sockaddr, 0, sizeof(sockaddr));
#ifdef __APPLE__
        sockaddr.snd_len = sizeof(sockaddr);
        sockaddr.snd_family = AF_NDRV;
        std::memcpy(sockaddr.snd_name, ifname.data(), ifname.size());
#elif __linux__
        sockaddr.sll_family = AF_PACKET;
        sockaddr.sll_protocol = htons(ETH_P_ALL);
        sockaddr.sll_ifindex = if_nametoindex(ifname.data());
        sockaddr.sll_hatype = 0;
        sockaddr.sll_halen = htons(ETH_ALEN);
        memcpy(sockaddr.sll_addr, sha, ETH_ALEN);
        
#endif

}
