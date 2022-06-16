#pragma once

#include <cstdint>

enum class arp_op : uint16_t {
    request = 0x0001,
    reply = 0x0002,
};

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

struct arphdr* arp_hdr(struct eth_frame* eth);

class PktBuilder {
private:
    uint8_t raw_pkt[46];
    struct arphdr* arp_pkt;
    struct eth_frame* eth_pkt;
    arp_op m_op;
public:
    explicit PktBuilder(arp_op op);
    PktBuilder& set_hrd(const uint16_t hrd);
    PktBuilder& set_pro(const uint16_t pro);
    PktBuilder& set_hln(const uint8_t hln);
    PktBuilder& set_pln(const uint8_t pln);
    PktBuilder& set_op(const uint16_t op);
    PktBuilder& set_sha(const uint8_t* sha);
    PktBuilder& set_spa(const uint32_t spa);
    PktBuilder& set_tha(const uint8_t* tha);
    PktBuilder& set_tpa(const uint32_t tpa);
    const uint8_t* packet() const;
    size_t size() const;
};