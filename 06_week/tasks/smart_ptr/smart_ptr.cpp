#include <string>
#include <utility>
#include <cstddef>

struct Block
{
    std::string *ptr;
    size_t shared_count;
    size_t weak_count;
    explicit Block(std::string *p)
        : ptr(p), shared_count(1), weak_count(0) {}
};
class SharedPtr;
class WeakPtr;
class SharedPtr
{
private:
    std::string *ptr_;
    Block *block_;
    void Release()
    {
        if (!block_)
            return;
        --block_->shared_count;
        if (block_->shared_count == 0)
        {
            delete block_->ptr;
            block_->ptr = nullptr;

            if (block_->weak_count == 0)
                delete block_;
        }
        block_ = nullptr;
        ptr_ = nullptr;
    }

public:
    SharedPtr() : ptr_(nullptr), block_(nullptr) {}
    explicit SharedPtr(std::string *ptr)
        : ptr_(ptr)
    {
        if (ptr)
            block_ = new Block(ptr);
        else
            block_ = nullptr;
    }
    SharedPtr(std::string *ptr, Block *block)
        : ptr_(ptr), block_(block)
    {
        if (block_)
            ++block_->shared_count;
    }
    SharedPtr(const SharedPtr &other)
        : ptr_(other.ptr_), block_(other.block_)
    {
        if (block_)
            ++block_->shared_count;
    }
    SharedPtr(SharedPtr &&other) noexcept
        : ptr_(other.ptr_), block_(other.block_)
    {
        other.ptr_ = nullptr;
        other.block_ = nullptr;
    }
    ~SharedPtr() { Release(); }
    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this != &other)
        {
            Release();
            ptr_ = other.ptr_;
            block_ = other.block_;
            if (block_)
                ++block_->shared_count;
        }
        return *this;
    }
    SharedPtr &operator=(SharedPtr &&other) noexcept
    {
        if (this != &other)
        {
            Release();
            ptr_ = other.ptr_;
            block_ = other.block_;
            other.ptr_ = nullptr;
            other.block_ = nullptr;
        }
        return *this;
    }
    std::string &operator*() const { return *ptr_; }
    std::string *operator->() const { return ptr_; }
    std::string *Get() const { return ptr_; }
    void Reset(std::string *new_ptr = nullptr)
    {
        Release();
        if (new_ptr)
        {
            block_ = new Block(new_ptr);
            ptr_ = new_ptr;
        }
    }
    void Swap(SharedPtr &other)
    {
        std::swap(ptr_, other.ptr_);
        std::swap(block_, other.block_);
    }
    size_t UseCount() const { return block_ ? block_->shared_count : 0; }
    explicit operator bool() const { return ptr_ != nullptr; }
    Block *GetBlock() const { return block_; }
};
class WeakPtr
{
private:
    Block *block_;
    void Release()
    {
        if (!block_)
            return;

        --block_->weak_count;
        if (block_->shared_count == 0 && block_->weak_count == 0)
            delete block_;

        block_ = nullptr;
    }

public:
    WeakPtr() : block_(nullptr) {}
    WeakPtr(const SharedPtr &shared) : block_(shared.GetBlock())
    {
        if (block_)
            ++block_->weak_count;
    }
    WeakPtr(const WeakPtr &other) : block_(other.block_)
    {
        if (block_)
            ++block_->weak_count;
    }
    WeakPtr(WeakPtr &&other) noexcept : block_(other.block_)
    {
        other.block_ = nullptr;
    }
    ~WeakPtr() { Release(); }
    WeakPtr &operator=(const WeakPtr &other)
    {
        if (this != &other)
        {
            Release();
            block_ = other.block_;
            if (block_)
                ++block_->weak_count;
        }
        return *this;
    }
    WeakPtr &operator=(WeakPtr &&other) noexcept
    {
        if (this != &other)
        {
            Release();
            block_ = other.block_;
            other.block_ = nullptr;
        }
        return *this;
    }
    WeakPtr &operator=(const SharedPtr &shared)
    {
        Release();
        block_ = shared.GetBlock();
        if (block_)
            ++block_->weak_count;
        return *this;
    }
    void Reset()
    {
        Release();
    }
    void Swap(WeakPtr &other)
    {
        std::swap(block_, other.block_);
    }
    size_t UseCount() const { return block_ ? block_->shared_count : 0; }
    bool Expired() const { return !block_ || block_->shared_count == 0; }
    SharedPtr Lock() const
    {
        if (Expired())
            return SharedPtr();
        return SharedPtr(block_->ptr, block_);
    }
};
template <typename T>
SharedPtr MakeShared(T &&value)
{
    return SharedPtr(new std::string(std::forward<T>(value)));
}
void Swap(SharedPtr &a, SharedPtr &b) { a.Swap(b); }
void Swap(WeakPtr &a, WeakPtr &b) { a.Swap(b); }