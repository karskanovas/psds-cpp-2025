
#include <initializer_list>
#include <algorithm>

class SimpleVector
{
private:
    int *data_;
    size_t size_;
    size_t capacity_;

    void Reallocate(size_t new_capacity)
    {
        int *new_data = new int[new_capacity];
        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    SimpleVector()
        : data_(nullptr), size_(0), capacity_(0) {}

    explicit SimpleVector(size_t size)
        : data_(new int[size]()), size_(size), capacity_(size) {}

    SimpleVector(size_t size, int value)
        : data_(new int[size]), size_(size), capacity_(size)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = value;
        }
    }

    SimpleVector(std::initializer_list<int> init)
        : data_(new int[init.size()]), size_(init.size()), capacity_(init.size())
    {
        std::copy(init.begin(), init.end(), data_);
    }

    SimpleVector(const SimpleVector &other)
        : data_(new int[other.size_]), size_(other.size_), capacity_(other.size_)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }
    SimpleVector(SimpleVector &&other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    SimpleVector &operator=(const SimpleVector &other)
    {
        if (this != &other)
        {
            SimpleVector temp(other);
            Swap(temp);
        }
        return *this;
    }
    SimpleVector &operator=(SimpleVector &&other) noexcept
    {
        if (this != &other)
        {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }
    ~SimpleVector()
    {
        delete[] data_;
    }
    void Swap(SimpleVector &other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
    friend void swap(SimpleVector &lhs, SimpleVector &rhs) noexcept
    {
        lhs.Swap(rhs);
    }
    int &operator[](size_t index) { return data_[index]; }
    const int &operator[](size_t index) const { return data_[index]; }
    size_t Size() const { return size_; }
    size_t Capacity() const { return capacity_; }
    bool Empty() const { return size_ == 0; }
    const int *Data() const { return data_; }
    void PushBack(int value)
    {
        if (size_ == capacity_)
        {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Reallocate(new_capacity);
        }
        data_[size_++] = value;
    }
    void PopBack()
    {
        if (size_ > 0)
            --size_;
    }
    int *Insert(const int *pos, int value)
    {
        if (pos < data_ || pos > data_ + size_)
            return data_ + size_;

        size_t index = pos - data_;
        if (size_ == capacity_)
        {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            Reallocate(new_capacity);
        }

        for (size_t i = size_; i > index; --i)
            data_[i] = data_[i - 1];

        data_[index] = value;
        ++size_;
        return data_ + index;
    }
    int *Erase(const int *pos)
    {
        if (pos < data_ || pos >= data_ + size_)
            return data_ + size_;

        size_t index = pos - data_;
        for (size_t i = index; i + 1 < size_; ++i)
            data_[i] = data_[i + 1];

        --size_;
        return data_ + index;
    }
    void Clear() { size_ = 0; }
    void Resize(size_t new_size, int value = 0)
    {
        if (new_size <= size_)
        {
            size_ = new_size;
            return;
        }
        if (new_size > capacity_)
            Reallocate(new_size);

        for (size_t i = size_; i < new_size; ++i)
            data_[i] = value;

        size_ = new_size;
    }
    void Reserve(size_t new_capacity)
    {
        if (new_capacity > capacity_)
            Reallocate(new_capacity);
    }
    int *begin() { return data_; }
    int *end() { return data_ + size_; }
    const int *begin() const { return data_; }
    const int *end() const { return data_ + size_; }
    bool operator==(const SimpleVector &other) const
    {
        if (size_ != other.size_)
            return false;
        for (size_t i = 0; i < size_; ++i)
            if (data_[i] != other.data_[i])
                return false;
        return true;
    }

    bool operator!=(const SimpleVector &other) const
    {
        return !(*this == other);
    }


