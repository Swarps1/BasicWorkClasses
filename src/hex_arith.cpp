#include "hex.hpp"

Hex Hex::add(const Hex &o) const
{
    size_t maxLen = digits.size() > o.digits.size() ? digits.size() : o.digits.size();
    Vector<unsigned char> result(maxLen + 1);

    int carry = 0;
    size_t k = 0;
    for (size_t i = 0; i < maxLen; i++)
    {
        int sum = carry;
        if (i < digits.size())
            sum += digits[i];
        if (i < o.digits.size())
            sum += o.digits[i];
        result[i] = sum % 16;
        carry = sum / 16;
        k++;
    }
    if (carry)
        result[k++] = carry;

    Hex h(result.getData(), k);
    return h;
}

Hex Hex::sub(const Hex &o) const
{
    if (lt(o))
        throw std::runtime_error("negative");

    Vector<unsigned char> result(digits.size());
    int borrow = 0;
    size_t k = 0;
    for (size_t i = 0; i < digits.size(); i++)
    {
        int val = digits[i] - borrow;
        if (i < o.digits.size())
            val -= o.digits[i];
        if (val < 0)
        {
            val += 16;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result[i] = val;
        k++;
    }

    Hex h(result.getData(), k);
    h.trim();
    return h;
}

Hex Hex::cpy() const
{
    return Hex(*this);
}

bool Hex::eq(const Hex &o) const
{
    if (digits.size() != o.digits.size())
        return false;
    for (size_t i = 0; i < digits.size(); i++)
    {
        if (digits[i] != o.digits[i])
            return false;
    }
    return true;
}

bool Hex::gt(const Hex &o) const
{
    if (digits.size() != o.digits.size())
        return digits.size() > o.digits.size();
    for (int i = digits.size() - 1; i >= 0; i--)
    {
        if (digits[i] != o.digits[i])
            return digits[i] > o.digits[i];
    }
    return false;
}

bool Hex::lt(const Hex &o) const
{
    return !gt(o) && !eq(o);
}

std::string Hex::str() const
{
    if (digits.size() == 1 && digits[0] == 0)
        return "0";
    std::string s;
    for (int i = digits.size() - 1; i >= 0; i--)
    {
        s += h2c(digits[i]);
    }
    return s;
}

size_t Hex::sz() const
{
    return digits.size();
}