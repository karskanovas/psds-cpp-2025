#include <string>
#include <utility>

class UniquePtr
{
private:
    std::string *ptr_;

public:
    UniquePtr() : ptr_(nullptr) {}
    explicit UniquePtr(std::string *ptr) : ptr_(ptr) {}
    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;
    UniquePtr(UniquePtr &&other) noexcept : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }
    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    ~UniquePtr()
    {
        delete ptr_;
    }
    std::string &operator*() const
    {
        return *ptr_;
    }
    std::string *operator->() const
    {
        return ptr_;
    }
    std::string *Get() const
    {
        return ptr_;
    }
    std::string *Release()
    {
        std::string *temp = ptr_;
        ptr_ = nullptr;
        return temp;
    }
    void Reset(std::string *new_ptr = nullptr)
    {
        if (ptr_ != new_ptr)
        {
            delete ptr_;
            ptr_ = new_ptr;
        }
    }
    void Swap(UniquePtr &other)
    {
        std::swap(ptr_, other.ptr_);
    }
    explicit operator bool() const
    {
        return ptr_ != nullptr;
    }
};
template <typename T>
UniquePtr MakeUnique(T &&value)
{
    return UniquePtr(new std::string(std::forward<T>(value)));
}
void Swap(UniquePtr &lhs, UniquePtr &rhs)
{
    lhs.Swap(rhs);
}