#include <vector>

void Filter(std::vector<int>& v, bool (*pred)(int)) {
    if (pred == nullptr) {
        return;}
    size_t write = 0;
    for (size_t read = 0; read < v.size(); ++read) {
        if (pred(v[read])) {
            v[write] = v[read];
            ++write;}
    }
    v.resize(write);
}
