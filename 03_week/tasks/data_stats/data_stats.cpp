#include <vector>
#include <cmath>

struct DataStats {
    double avg;
    double sd;};

DataStats CalculateDataStats(const std::vector<int>& data) {
    if (data.empty()) {
        return {0.0, 0.0};}
    double sum = 0.0;
    for (int x : data) {
        sum += x;}
    double mean = sum / data.size();
    double variance_sum = 0.0;
    for (int x : data) {
        variance_sum += (x - mean) * (x - mean);}
    double variance = variance_sum / data.size();
    double stddev = std::sqrt(variance);
    return {mean, stddev};
}
