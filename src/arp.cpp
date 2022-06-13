#include <iostream>
#ifdef __APPLE__
#include <net/ethernet.h>
#endif

#include "arp.h"
#include "eth.h"

struct arphdr* arp_hdr(struct eth_frame* eth) {
    return reinterpret_cast<arphdr *>(eth->payload);
}

PktBuilder::PktBuilder(arp_op op):m_op(op) {
    memset(raw_pkt, 0, sizeof(raw_pkt));
    eth_pkt = eth_hdr(raw_pkt);
    eth_pkt->type = htons(ETHERTYPE_ARP);
    arp_pkt = arp_hdr(eth_pkt);
}

PktBuilder& PktBuilder::set_hrd(uint16_t hrd) {
    arp_pkt->hrd = htons(hrd);
    return *this;
}

PktBuilder& PktBuilder::set_pro(uint16_t pro) {
    arp_pkt->pro = htons(pro);
    return *this;
}

PktBuilder& PktBuilder::set_hln(uint8_t hln) {
    arp_pkt->hln = hln;
    return *this;
}

PktBuilder& PktBuilder::set_pln(uint8_t pln) {
    arp_pkt->pln = pln;
    return *this;
}

PktBuilder& PktBuilder::set_op(uint16_t op) {
    arp_pkt->op = htons(op);
    return *this;
}

PktBuilder& PktBuilder::set_sha(uint8_t* sha) {
    memcpy(arp_pkt->sha, sha, ETHER_ADDR_LEN);
    memcpy(eth_pkt->smac, sha, ETHER_ADDR_LEN);
    return *this;
}

PktBuilder& PktBuilder::set_spa(uint32_t spa) {
    arp_pkt->spa = htonl(spa);
    return *this;
}

PktBuilder& PktBuilder::set_tha(uint8_t* tha) {
    memcpy(eth_pkt->dmac, tha, ETHER_ADDR_LEN);
    if (m_op == arp_op::request) {
        memset(arp_pkt->tha, 0, ETHER_ADDR_LEN);
    } else {
        memcpy(arp_pkt->tha, tha, ETHER_ADDR_LEN);
    }   
    return *this;
}

PktBuilder& PktBuilder::set_tpa(uint32_t tpa) {
    arp_pkt->tpa = htonl(tpa);
    return *this;
}

const uint8_t* PktBuilder::packet() const {
    return raw_pkt;
}

size_t PktBuilder::size() const {
    return sizeof(raw_pkt);
}



