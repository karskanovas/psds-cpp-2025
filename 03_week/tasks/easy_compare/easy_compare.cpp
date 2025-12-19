#include <tuple>
#include <stdexcept>

struct Date {
    unsigned year = 0;
    unsigned month = 0;
    unsigned day = 0;
    Date() = default;
    Date(unsigned y, unsigned m, unsigned d)
        : year(y), month(m), day(d) {}};
bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) ==
           std::tie(rhs.year, rhs.month, rhs.day);}
bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);}
bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) <
           std::tie(rhs.year, rhs.month, rhs.day);}
bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);}
bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;}
bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);}
struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;};
bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark &&
           lhs.score == rhs.score;}
bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);}
bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    if (lhs.mark != rhs.mark)
        return lhs.mark > rhs.mark;         
    if (lhs.score != rhs.score)
        return lhs.score < rhs.score;        
    if (lhs.course != rhs.course)
        return lhs.course > rhs.course;      
    if (lhs.birth_date != rhs.birth_date)
        return lhs.birth_date < rhs.birth_date; 
    return false;
}
