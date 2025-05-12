#include "ethernet.h"

eth_frame* eth_hdr(void* buf) {
    return static_cast<eth_frame*>(buf);
}