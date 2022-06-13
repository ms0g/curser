#pragma once

#include <type_traits>
#include <cstdint>

uint32_t inet_bf(const char* addr);

void getMacAddr(const char* ifname, uint8_t* mac);

template <typename T>
auto as_integer(T const val) {
    return static_cast<std::underlying_type_t<T>>(val);
}