#include <cstring>
#include <string>

class CowString
{
private:
    struct Buffer
    {
        char *data;
        size_t size;
        size_t ref_count;

        Buffer(const char *str, size_t len)
            : size(len), ref_count(1)
        {
            data = new char[len + 1];
            if (len > 0)
            {
                std::memcpy(data, str, len);
            }
            data[len] = '\0';
        }

        ~Buffer()
        {
            delete[] data;
        }
    };

    Buffer *buffer_;

    static Buffer *CreateEmptyBuffer()
    {
        return new Buffer("", 0);
    }

    void Release()
    {
        if (buffer_)
        {
            if (--buffer_->ref_count == 0)
            {
                delete buffer_;
            }
        }
    }

    void EnsureUnique()
    {
        if (buffer_->ref_count > 1)
        {
            Buffer *new_buf = new Buffer(buffer_->data, buffer_->size);
            --buffer_->ref_count;
            buffer_ = new_buf;
        }
    }

public:
    static const size_t npos;

    CowString()
        : buffer_(CreateEmptyBuffer()) {}

    CowString(const char *str)
        : buffer_(new Buffer(str, std::strlen(str))) {}

    CowString(const std::string &str)
        : buffer_(new Buffer(str.c_str(), str.size())) {}

    CowString(const CowString &other)
        : buffer_(other.buffer_)
    {
        ++buffer_->ref_count;
    }

    CowString &operator=(const CowString &other)
    {
        if (this != &other)
        {
            Release();
            buffer_ = other.buffer_;
            ++buffer_->ref_count;
        }
        return *this;
    }

    CowString(CowString &&other) noexcept
        : buffer_(other.buffer_)
    {
        other.buffer_ = CreateEmptyBuffer();
    }

    CowString &operator=(CowString &&other) noexcept
    {
        if (this != &other)
        {
            Release();
            buffer_ = other.buffer_;
            other.buffer_ = CreateEmptyBuffer();
        }
        return *this;
    }

    ~CowString()
    {
        Release();
    }

    size_t Size() const
    {
        return buffer_->size;
    }

    bool Empty() const
    {
        return buffer_->size == 0;
    }

    const char *ToCstr() const
    {
        return buffer_->data;
    }

    std::string ToString() const
    {
        return std::string(buffer_->data, buffer_->size);
    }

    const char &operator[](size_t index) const
    {
        return buffer_->data[index];
    }

    operator const char *() const
    {
        return buffer_->data;
    }

    char &operator[](size_t index)
    {
        EnsureUnique();
        return buffer_->data[index];
    }

    CowString &Append(const char *str)
    {
        size_t add_len = std::strlen(str);
        if (add_len == 0)
        {
            return *this;
        }

        EnsureUnique();

        size_t new_size = buffer_->size + add_len;
        char *new_data = new char[new_size + 1];

        std::memcpy(new_data, buffer_->data, buffer_->size);
        std::memcpy(new_data + buffer_->size, str, add_len);
        new_data[new_size] = '\0';

        delete[] buffer_->data;
        buffer_->data = new_data;
        buffer_->size = new_size;

        return *this;
    }

    CowString &Append(const std::string &str)
    {
        return Append(str.c_str());
    }

    CowString Substr(size_t pos = 0, size_t len = npos) const
    {
        if (pos >= buffer_->size)
        {
            return CowString();
        }

        size_t max_len = buffer_->size - pos;
        size_t real_len = (len == npos || len > max_len)
                              ? max_len
                              : len;

        return CowString(std::string(buffer_->data + pos, real_len));
    }

    void Clear()
    {
        if (buffer_->size == 0 && buffer_->ref_count == 1)
        {
            return;
        }

        EnsureUnique();

        delete[] buffer_->data;
        buffer_->data = new char[1];
        buffer_->data[0] = '\0';
        buffer_->size = 0;
    }

    size_t Find(const char *str) const
    {
        if (std::strlen(str) == 0)
        {
            return 0;
        }

        const char *found = std::strstr(buffer_->data, str);
        if (!found)
        {
            return npos;
        }

        return static_cast<size_t>(found - buffer_->data);
    }

    size_t Find(char ch) const
    {
        const char *found = std::strchr(buffer_->data, ch);
        if (!found)
        {
            return npos;
        }

        return static_cast<size_t>(found - buffer_->data);
    }
};

const size_t CowString::npos = static_cast<size_t>(-1);
