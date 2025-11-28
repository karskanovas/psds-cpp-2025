#include <cstdint>
#include <iostream>


enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

void PrintCheckFlags(CheckFlags flags) {
    uint8_t value = static_cast<uint8_t>(flags);
    uint8_t all = static_cast<uint8_t>(CheckFlags::ALL);
    if ((value & ~all) != 0) {
        return;  }
    if (value == 0) {
        std::cout << "[]";
        return;}
    std::cout << "[";
    bool first = true;
    auto print_flag = [&](CheckFlags f, const char* name) {
        if (value & static_cast<uint8_t>(f)) {
            if (!first) std::cout << ",";
            std::cout << name;
            first = false;}
    };
    print_flag(CheckFlags::TIME, "TIME");
    print_flag(CheckFlags::DATE, "DATE");
    print_flag(CheckFlags::USER, "USER");
    print_flag(CheckFlags::CERT, "CERT");
    print_flag(CheckFlags::KEYS, "KEYS");
    print_flag(CheckFlags::DEST, "DEST");
    std::cout << "]";
}
