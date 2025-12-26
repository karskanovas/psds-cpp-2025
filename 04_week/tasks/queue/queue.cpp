#include <vector>
#include <stack>
#include <initializer_list>
#include <algorithm> 

class Queue {
private:
    std::vector<int> inStack_;   
    std::vector<int> outStack_;  
    void Transfer() {
        if (outStack_.empty()) {
            while (!inStack_.empty()) {
                outStack_.push_back(inStack_.back());
                inStack_.pop_back();}
        }
    }
public:
    Queue() = default;
    Queue(const std::stack<int>& s) {
        std::stack<int> temp = s;
        while (!temp.empty()) {
            inStack_.push_back(temp.top());
            temp.pop();}
        std::reverse(inStack_.begin(), inStack_.end());}
    Queue(const std::vector<int>& v) : inStack_(v) {}
    Queue(std::initializer_list<int> il) : inStack_(il) {}
    explicit Queue(size_t capacity) {
        inStack_.reserve(capacity);
        outStack_.reserve(capacity);}
    void Push(int value) {
        inStack_.push_back(value);}
    bool Pop() {
        Transfer();
        if (outStack_.empty()) return false;
        outStack_.pop_back();
        return true;}
    int& Front() {
        Transfer();
        return outStack_.back();}
    const int& Front() const {
        return const_cast<Queue*>(this)->Front();}
    int& Back() {
        if (!inStack_.empty()) return inStack_.back();
        Transfer();
        return outStack_.front(); }
    const int& Back() const {
        return const_cast<Queue*>(this)->Back();}
    bool Empty() const {
        return inStack_.empty() && outStack_.empty();}
    size_t Size() const {
        return inStack_.size() + outStack_.size();}
    void Clear() {
        inStack_.clear();
        outStack_.clear();}
    void Swap(Queue& other) {
        std::swap(inStack_, other.inStack_);
        std::swap(outStack_, other.outStack_);}
    bool operator==(const Queue& other) const {
        Queue copy1 = *this;
        Queue copy2 = other;
        while (!copy1.Empty() && !copy2.Empty()) {
            if (copy1.Front() != copy2.Front()) return false;
            copy1.Pop();
            copy2.Pop();}
        return copy1.Empty() && copy2.Empty();}
    bool operator!=(const Queue& other) const {
        return !(*this == other);}
};