#include <cstdint>

constexpr long double operator"" _ft_to_m(long double v) {
    return static_cast<double>(v * 0.3048L);
}

constexpr long double operator"" _ft_to_in(long double v) {
    return static_cast<double>(v * 12.0L);
}

constexpr long double operator"" _ft_to_cm(long double v) {
    return static_cast<double>(v * 30.48L);
}

constexpr long double operator"" _in_to_ft(long double v) {
    return static_cast<double>(v / 12.0L);
}

constexpr long double operator"" _in_to_m(long double v) {
    return static_cast<double>(v * 0.0254L);
}

constexpr long double operator"" _in_to_cm(long double v) {
    return static_cast<double>(v * 2.54L);
}

constexpr long double operator"" _cm_to_in(long double v) {
    return static_cast<double>(v / 2.54L);
}

constexpr long double operator"" _cm_to_ft(long double v) {
    return static_cast<double>(v / 30.48L);
}

constexpr long double operator"" _cm_to_m(long double v) {
    return static_cast<double>(v / 100.0L);
}

constexpr long double operator"" _m_to_cm(long double v) {
    return static_cast<double>(v * 100.0L);
}

constexpr long double operator"" _m_to_in(long double v) {
    return static_cast<double>(v / 0.0254L);
}

constexpr long double operator"" _m_to_ft(long double v) {
    return static_cast<double>(v / 0.3048L);
}
