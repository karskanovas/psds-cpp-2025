#include <initializer_list>
#include <cstddef>
#include <utility>

template <class T, size_t N>
class Array
{
private:
    T data_[N];

public:
    Array() = default;
    Array(std::initializer_list<T> init)
    {
        size_t i = 0;
        for (const auto &v : init)
        {
            if (i < N)
                data_[i++] = v;
        }
    }
    Array(const Array &other)
    {
        for (size_t i = 0; i < N; ++i)
            data_[i] = other.data_[i];
    }
    Array(Array &&other) noexcept
    {
        for (size_t i = 0; i < N; ++i)
            data_[i] = std::move(other.data_[i]);
    }
    Array &operator=(const Array &other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < N; ++i)
                data_[i] = other.data_[i];
        }
        return *this;
    }
    Array &operator=(Array &&other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < N; ++i)
                data_[i] = std::move(other.data_[i]);
        }
        return *this;
    }
    ~Array() = default;
    T &operator[](size_t i) { return data_[i]; }
    const T &operator[](size_t i) const { return data_[i]; }
    T &Front() { return data_[0]; }
    const T &Front() const { return data_[0]; }
    T &Back() { return data_[N - 1]; }
    const T &Back() const { return data_[N - 1]; }
    T *Data() { return data_; }
    const T *Data() const { return data_; }
    bool Empty() const { return N == 0; }
    size_t Size() const { return N; }
    void Fill(const T &value)
    {
        for (size_t i = 0; i < N; ++i)
            data_[i] = value;
    }
    void Swap(Array &other)
    {
        for (size_t i = 0; i < N; ++i)
            std::swap(data_[i], other.data_[i]);
    }
    T *begin() { return data_; }
    T *end() { return data_ + N; }
    const T *begin() const { return data_; }
    const T *end() const { return data_ + N; }
    const T *cbegin() const { return data_; }
    const T *cend() const { return data_ + N; }
};
template <class T, size_t N>
void swap(Array<T, N> &a, Array<T, N> &b)
{
    a.Swap(b);
}
template <class T, size_t N>
bool operator==(const Array<T, N> &a, const Array<T, N> &b)
{
    for (size_t i = 0; i < N; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}
template <class T, size_t N>
bool operator!=(const Array<T, N> &a, const Array<T, N> &b)
{
    return !(a == b);
}
template <class T, size_t N>
bool operator<(const Array<T, N> &a, const Array<T, N> &b)
{
    for (size_t i = 0; i < N; ++i)
    {
        if (a[i] < b[i])
            return true;
        if (b[i] < a[i])
            return false;
    }
    return false;
}
template <class T, size_t N>
bool operator>(const Array<T, N> &a, const Array<T, N> &b) { return b < a; }
template <class T, size_t N>
bool operator<=(const Array<T, N> &a, const Array<T, N> &b) { return !(b < a); }
template <class T, size_t N>
bool operator>=(const Array<T, N> &a, const Array<T, N> &b) { return !(a < b); }
template <size_t I, class T, size_t N>
T &get(Array<T, N> &arr) { return arr[I]; }
template <size_t I, class T, size_t N>
const T &get(const Array<T, N> &arr) { return arr[I]; }
template <size_t I, class T, size_t N>
T &&get(Array<T, N> &&arr) { return std::move(arr[I]); }