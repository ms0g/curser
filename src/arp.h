#pragma once

#include <cstddef>
#include <cstdint>

enum class arp_op : uint16_t {
    request = 0x0001,
    reply = 0x0002,
};

struct eth_frame;

struct arphdr {
    uint16_t hrd; /* Hardware type */
    uint16_t pro; /* Protocol type */
    uint8_t hln; /* Hardware Address Length */
    uint8_t pln; /* Protocol Address Length */
    uint16_t op; /* Opcode */
    uint8_t sha[6]; /* Sender Hardware Address */
    uint32_t spa; /* Sender Protocol Address */
    uint8_t tha[6]; /* Target Hardware Address */
    uint32_t tpa; /* Target Protocol Address */
} __attribute__((packed));

arphdr* arp_hdr(const eth_frame* eth);

class PktBuilder {
public:
    explicit PktBuilder(arp_op op);

    [[nodiscard]] const uint8_t* packet() const;

    [[nodiscard]] size_t size() const;

    PktBuilder& set_hrd(uint16_t hrd);

    PktBuilder& set_pro(uint16_t pro);

    PktBuilder& set_hln(uint8_t hln);

    PktBuilder& set_pln(uint8_t pln);

    PktBuilder& set_op(uint16_t op);

    PktBuilder& set_sha(const uint8_t* sha);

    PktBuilder& set_spa(uint32_t spa);

    PktBuilder& set_tha(const uint8_t* tha);

    PktBuilder& set_tpa(uint32_t tpa);

private:
    uint8_t raw_pkt[46]{};
    arphdr* arp_pkt;
    eth_frame* eth_pkt{};
    arp_op m_op;
};
