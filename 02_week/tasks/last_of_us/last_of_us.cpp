#include <stdexcept>

const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    if (!begin || !end || begin > end) {
        return end;}
    const int* result = end;
    for (const int* ptr = begin; ptr < end; ++ptr) {
        if (predicate(*ptr)) {
            result = ptr;}
    }
    return result;
}
