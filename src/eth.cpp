#include "eth.h"

struct eth_frame* eth_hdr(void* buf) {
    return reinterpret_cast<eth_frame*>(buf);
}