#include <string>
#include <utility>
#include <stdexcept>

class SimpleList
{
private:
    struct Node
    {
        std::string value;
        Node *prev;
        Node *next;

        Node(const std::string &v) : value(v), prev(nullptr), next(nullptr) {}
        Node(std::string &&v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };
    Node *head_;
    Node *tail_;
    size_t size_;

private:
    void Link(Node *position, Node *newNode)
    {
        newNode->next = position;
        newNode->prev = position->prev;
        if (position->prev)
            position->prev->next = newNode;
        else
            head_ = newNode;

        position->prev = newNode;
        ++size_;
    }
    void Unlink(Node *node)
    {
        if (!node)
            return;

        if (node->prev)
            node->prev->next = node->next;
        else
            head_ = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail_ = node->prev;

        delete node;
        --size_;
    }

public:
    SimpleList() : head_(nullptr), tail_(nullptr), size_(0) {}
    SimpleList(const SimpleList &other) : head_(nullptr), tail_(nullptr), size_(0)
    {
        Node *current = other.head_;
        while (current)
        {
            PushBack(current->value);
            current = current->next;
        }
    }
    SimpleList(SimpleList &&other) noexcept : head_(nullptr), tail_(nullptr), size_(0)
    {
        Swap(other);
    }
    ~SimpleList()
    {
        Clear();
    }
    void Swap(SimpleList &other) noexcept
    {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
    size_t Size() const { return size_; }
    bool Empty() const { return size_ == 0; }
    void PushBack(const std::string &value)
    {
        Node *node = new Node(value);
        if (!tail_)
            head_ = tail_ = node;
        else
        {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }
    void PushBack(std::string &&value)
    {
        Node *node = new Node(std::move(value));
        if (!tail_)
            head_ = tail_ = node;
        else
        {
            node->prev = tail_;
            tail_->next = node;
            tail_ = node;
        }
        ++size_;
    }
    void PushFront(const std::string &value)
    {
        Node *node = new Node(value);
        if (!head_)
            head_ = tail_ = node;
        else
        {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }
    void PushFront(std::string &&value)
    {
        Node *node = new Node(std::move(value));
        if (!head_)
            head_ = tail_ = node;
        else
        {
            node->next = head_;
            head_->prev = node;
            head_ = node;
        }
        ++size_;
    }
    void PopBack()
    {
        if (!Empty())
            Unlink(tail_);
    }
    void PopFront()
    {
        if (!Empty())
            Unlink(head_);
    }
    std::string &Back()
    {
        if (Empty())
            throw std::out_of_range("List is empty");
        return tail_->value;
    }
    const std::string &Back() const
    {
        if (Empty())
            throw std::out_of_range("List is empty");
        return tail_->value;
    }
    std::string &Front()
    {
        if (Empty())
            throw std::out_of_range("List is empty");
        return head_->value;
    }
    const std::string &Front() const
    {
        if (Empty())
            throw std::out_of_range("List is empty");
        return head_->value;
    }
    void Clear()
    {
        while (!Empty())
            PopFront();
    }
    SimpleList &operator=(const SimpleList &other)
    {
        if (this != &other)
        {
            SimpleList tmp(other);
            Swap(tmp);
        }
        return *this;
    }
    SimpleList &operator=(SimpleList &&other) noexcept
    {
        if (this != &other)
        {
            Clear();
            Swap(other);
        }
        return *this;
    }
};

inline void Swap(SimpleList &a, SimpleList &b) noexcept
{
    a.Swap(b);
}