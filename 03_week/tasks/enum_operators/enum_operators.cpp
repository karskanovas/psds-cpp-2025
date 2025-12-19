#include <cstdint>
#include <ostream>
#include <vector>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL  = TIME | DATE | USER | CERT | KEYS | DEST};
CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result =
        static_cast<uint8_t>(lhs) |
        static_cast<uint8_t>(rhs);
    result &= static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(result);}
bool operator&(CheckFlags lhs, CheckFlags rhs) {
    uint8_t l = static_cast<uint8_t>(lhs) &
                static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t r = static_cast<uint8_t>(rhs) &
                static_cast<uint8_t>(CheckFlags::ALL);
    if (l == 0 || r == 0) {
        return false; }
    uint8_t inter = l & r;
    return inter == l || inter == r;}
CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    uint8_t result =
        static_cast<uint8_t>(lhs) ^
        static_cast<uint8_t>(rhs);

    result &= static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(result);}
CheckFlags operator~(CheckFlags f) {
    uint8_t result = ~static_cast<uint8_t>(f);
    result &= static_cast<uint8_t>(CheckFlags::ALL);
    return static_cast<CheckFlags>(result);}
std::ostream& operator<<(std::ostream& os, CheckFlags f) {
    uint8_t mask = static_cast<uint8_t>(f) &
                   static_cast<uint8_t>(CheckFlags::ALL);
    if (mask == 0) {
        os << "NONE";
        return os;}
    struct FlagName {
        CheckFlags flag;
        const char* name;};
    static const std::vector<FlagName> flags = {
        {CheckFlags::TIME, "TIME"},
        {CheckFlags::DATE, "DATE"},
        {CheckFlags::USER, "USER"},
        {CheckFlags::CERT, "CERT"},
        {CheckFlags::KEYS, "KEYS"},
        {CheckFlags::DEST, "DEST"}};
    bool first = true;
    for (const auto& fn : flags) {
        if (mask & static_cast<uint8_t>(fn.flag)) {
            if (!first) {
                os << ", ";
            }
            os << fn.name;
            first = false;}
    }
    return os;
}
