#include <vector>


std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> result;
    if (step == 0) {
        return result;}
    if ((from < to && step < 0) || (from > to && step > 0)) {
        return result;}
    int count = 0;
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            ++count;}
    } else {
        for (int i = from; i > to; i += step) {
            ++count;}
    }
    result.reserve(count);
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            result.push_back(i);}
    } else {
        for (int i = from; i > to; i += step) {
            result.push_back(i);}
    }
    return result;
}
