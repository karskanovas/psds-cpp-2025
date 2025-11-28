#include <cstddef>  
#include <cmath>    
#include <stdexcept>

double CalculateRMS(double values[], size_t size) {
    if (size == 0) return 0.0;
    if (values == nullptr) return 0.0;  
    double sum_squares = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum_squares += values[i] * values[i];
    }
    return std::sqrt(sum_squares / static_cast<double>(size));
}
