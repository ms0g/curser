#pragma once
#include <cstdint>

struct eth_frame;
struct arphdr {
        uint16_t hrd;           /* Hardware type */
        uint16_t pro;           /* Protocol type */
        uint8_t hln;            /* Hardware Address Length */
        uint8_t pln;            /* Protocol Address Length */
        uint16_t op;            /* Opcode */
        uint8_t sha[6];         /* Sender Hardware Address */
        uint32_t spa;           /* Sender Protocol Address */
        uint8_t tha[6];         /* Target Hardware Address */
        uint32_t tpa;           /* Target Protocol Address */
    } __attribute__((packed));

struct arphdr *arp_hdr(struct eth_frame *eth);

class ArpBuilder {
private:
    uint8_t raw_pkt[46];
    struct arphdr *arp_pkt;
    struct eth_frame *eth_pkt;
public:
    ArpBuilder();
    ArpBuilder& set_hrd(uint16_t hrd);
    ArpBuilder& set_pro(uint16_t pro);
    ArpBuilder& set_hln(uint8_t hln);
    ArpBuilder& set_pln(uint8_t pln);
    ArpBuilder& set_op(uint16_t op);
    ArpBuilder& set_sha(uint8_t *sha);
    ArpBuilder& set_spa(uint32_t spa);
    ArpBuilder& set_tha(uint8_t *tha);
    ArpBuilder& set_tpa(uint32_t tpa);
    const uint8_t* packet() const;
    size_t size() const;
};