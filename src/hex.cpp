#include "hex.hpp"

Hex::Hex() : digits_(MyVector(1))
{
    digits_.at(0) = 0;
}

Hex::Hex(const char *str)
{
    if (!str || !str[0])
    {
        throw std::invalid_argument("Invalid string");
    }
    size_t len = 0;
    while (str[len])
        ++len;
    digits_ = MyVector(len);
    for (size_t i = 0; i < len; ++i)
    {
        char c = str[len - 1 - i];
        if ((c >= '0' && c <= '9'))
        {
            digits_.at(i) = c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            digits_.at(i) = c - 'A' + 10;
        }
        else if (c >= 'a' && c <= 'f')
        {
            digits_.at(i) = c - 'a' + 10;
        }
        else
        {
            throw std::invalid_argument("Invalid hex character");
        }
    }
    while (len > 1 && digits_.at(len - 1) == 0)
    {
        MyVector temp(len - 1);
        for (size_t i = 0; i < len - 1; ++i)
        {
            temp.at(i) = digits_.at(i);
        }
        digits_ = std::move(temp);
        --len;
    }
}

Hex::Hex(const unsigned char *arr, size_t size)
{
    if (size == 0)
    {
        throw std::invalid_argument("Empty array");
    }
    for (size_t i = 0; i < size; ++i)
    {
        if (arr[i] > 15)
        {
            throw std::invalid_argument("Invalid hex digit");
        }
    }
    digits_ = MyVector(size);
    for (size_t i = 0; i < size; ++i)
    {
        digits_.at(i) = arr[i];
    }
    while (size > 1 && digits_.at(size - 1) == 0)
    {
        MyVector temp(size - 1);
        for (size_t i = 0; i < size - 1; ++i)
        {
            temp.at(i) = digits_.at(i);
        }
        digits_ = std::move(temp);
        --size;
    }
}

Hex::Hex(const Hex &other) : digits_(other.digits_) {}

Hex::Hex(Hex &&other) noexcept : digits_(std::move(other.digits_)) {}

Hex &Hex::operator=(const Hex &other)
{
    if (this != &other)
    {
        digits_ = other.digits_;
    }
    return *this;
}

Hex &Hex::operator=(Hex &&other) noexcept
{
    if (this != &other)
    {
        digits_ = std::move(other.digits_);
    }
    return *this;
}

Hex::~Hex() {}

Hex Hex::add(const Hex &other) const
{
    Hex result;
    size_t max_size = std::max(digits_.size(), other.digits_.size());
    result.digits_ = MyVector(max_size);
    unsigned char carry = 0;
    for (size_t i = 0; i < max_size; ++i)
    {
        unsigned char a = (i < digits_.size()) ? digits_.at(i) : 0;
        unsigned char b = (i < other.digits_.size()) ? other.digits_.at(i) : 0;
        unsigned char sum = a + b + carry;
        carry = sum / 16;
        result.digits_.at(i) = sum % 16;
    }
    if (carry)
    {
        result.digits_.push_back(carry);
    }
    return result;
}

Hex Hex::sub(const Hex &other) const
{
    if (lt(other))
    {
        throw std::runtime_error("Result would be negative");
    }
    Hex result;
    size_t max_size = digits_.size();
    result.digits_ = MyVector(max_size);
    unsigned char borrow = 0;
    for (size_t i = 0; i < max_size; ++i)
    {
        unsigned char a = digits_.at(i);
        unsigned char b = (i < other.digits_.size()) ? other.digits_.at(i) : 0;
        if (a < b + borrow)
        {
            result.digits_.at(i) = a + 16 - b - borrow;
            borrow = 1;
        }
        else
        {
            result.digits_.at(i) = a - b - borrow;
            borrow = 0;
        }
    }
    while (result.digits_.size() > 1 && result.digits_.at(result.digits_.size() - 1) == 0)
    {
        MyVector temp(result.digits_.size() - 1);
        for (size_t i = 0; i < temp.size(); ++i)
        {
            temp.at(i) = result.digits_.at(i);
        }
        result.digits_ = std::move(temp);
    }
    return result;
}

Hex Hex::cpy() const
{
    return Hex(*this);
}

bool Hex::gt(const Hex &other) const
{
    if (digits_.size() != other.digits_.size())
    {
        return digits_.size() > other.digits_.size();
    }
    for (size_t i = digits_.size(); i > 0; --i)
    {
        if (digits_.at(i - 1) != other.digits_.at(i - 1))
        {
            return digits_.at(i - 1) > other.digits_.at(i - 1);
        }
    }
    return false;
}

bool Hex::lt(const Hex &other) const
{
    if (digits_.size() != other.digits_.size())
    {
        return digits_.size() < other.digits_.size();
    }
    for (size_t i = digits_.size(); i > 0; --i)
    {
        if (digits_.at(i - 1) != other.digits_.at(i - 1))
        {
            return digits_.at(i - 1) < other.digits_.at(i - 1);
        }
    }
    return false;
}

bool Hex::eq(const Hex &other) const
{
    if (digits_.size() != other.digits_.size())
    {
        return false;
    }
    for (size_t i = 0; i < digits_.size(); ++i)
    {
        if (digits_.at(i) != other.digits_.at(i))
        {
            return false;
        }
    }
    return true;
}

std::string Hex::str() const
{
    if (digits_.size() == 0)
    {
        return "0";
    }
    std::string result;
    for (size_t i = digits_.size(); i > 0; --i)
    {
        unsigned char digit = digits_.at(i - 1);
        if (digit < 10)
        {
            result += static_cast<char>('0' + digit);
        }
        else
        {
            result += static_cast<char>('A' + digit - 10);
        }
    }
    return result;
}

size_t Hex::sz() const
{
    return digits_.size();
}