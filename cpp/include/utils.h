#pragma once

#include <type_traits>
#include <bitset>

#define DEBUG

#ifdef DEBUG
#define debug(a) {std::cout << #a << " is " << (a) << '\n';}
#else
#define debug(a)
#endif

// Ensure that T is an integral type
template<typename T>
std::enable_if_t<std::is_integral_v<T>, std::string> get_bit_string(T t) {
    // Get the number of bits in the type T
    constexpr size_t num_bits = sizeof(T) * 8;
    // Create a bitset from the value t
    std::bitset<num_bits> bitset(t);
    // Convert the bitset to string
    return bitset.to_string();
}