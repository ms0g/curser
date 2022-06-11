#pragma once
#include <cstdint>

struct eth_frame {
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t type;
    uint8_t payload[];
} __attribute__((packed));

struct eth_frame* eth_hdr(void *buf);
