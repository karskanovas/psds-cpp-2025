#include <vector>
#include <utility>
#include <stdexcept>

auto MinMax(const std::vector<int>& v) {
    if (v.empty()) {
        return std::make_pair(v.end(), v.end());}
    auto min_it = v.begin();
    auto max_it = v.begin();
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it < *min_it) {
            min_it = it;}
        if (*it >= *max_it) {
            max_it = it;}
    }
    return std::make_pair(min_it, max_it);
}
