#include <cstddef>
#include <stdexcept>

char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    if (!begin || !end || begin >= end) {
        count = 0;
        return nullptr; }
    char* max_start = begin;
    size_t max_len = 1;
    char* current_start = begin;
    size_t current_len = 1;
    for (char* ptr = begin + 1; ptr < end; ++ptr) {
        if (*ptr == *(ptr - 1)) {
            ++current_len;} 
            else {
            if (current_len > max_len) {
                max_len = current_len;
                max_start = current_start;
            }
            current_start = ptr;
            current_len = 1;}
    }
    if (current_len > max_len) {
        max_len = current_len;
        max_start = current_start;}
    count = max_len;
    return max_start;
}

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) { //из за ошибки про то, что ожидается изменяемый массив 
    return FindLongestSubsequence(const_cast<char*>(begin), const_cast<char*>(end), count);
}
