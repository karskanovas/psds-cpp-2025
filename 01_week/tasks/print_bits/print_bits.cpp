#include <cstddef>
#include <iostream>


void PrintBits(long long value, size_t bytes) {
    if (bytes == 0 || bytes > 8)
        return;
    std::cout << "0b";
    size_t total_bits = bytes * 8;
    for (size_t i = 0; i < total_bits; ++i) {
        size_t bit_index = total_bits - 1 - i;
        bool bit = (value >> bit_index) & 1;
        std::cout << (bit ? '1' : '0');
        if (i % 4 == 3 && i + 1 < total_bits)
            std::cout << "'"; }
    std::cout << "\n";
}