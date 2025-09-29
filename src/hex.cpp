#include "../include/hex.hpp"
#include <algorithm>
#include <cctype>
#include <cstring>

Hex::Hex() : d(new unsigned char[1]), len(1), cap(1) { d[0] = 0; }

Hex::Hex(const std::string &str) : d(nullptr), len(0), cap(0)
{
    if (str.empty())
        throw std::invalid_argument("Empty hex string");
    cap = str.length();
    d = new unsigned char[cap];
    len = 0;
    for (auto it = str.rbegin(); it != str.rend(); ++it)
    {
        if (!std::isxdigit(*it))
        {
            delete[] d;
            throw std::invalid_argument("Invalid hex character");
        }
        d[len++] = c2h(*it);
    }
    trimZeros();
    if (len == 0)
    {
        delete[] d;
        d = new unsigned char[1];
        d[0] = 0;
        len = 1;
        cap = 1;
    }
}

Hex::Hex(const unsigned char *d, size_t s) : d(nullptr), len(0), cap(0)
{
    if (s == 0)
        throw std::invalid_argument("Empty hex number");
    cap = s;
    this->d = new unsigned char[cap];
    for (size_t i = 0; i < s; ++i)
    {
        if (d[i] > 15)
        {
            delete[] this->d;
            throw std::invalid_argument("Invalid hex digit");
        }
        this->d[i] = d[i];
    }
    len = s;
    trimZeros();
    if (len == 0)
    {
        delete[] this->d;
        this->d = new unsigned char[1];
        this->d[0] = 0;
        len = 1;
        cap = 1;
    }
}

Hex::Hex(const Hex &oth) : d(new unsigned char[oth.cap]), len(oth.len), cap(oth.cap)
{
    std::memcpy(d, oth.d, len * sizeof(unsigned char));
}

Hex::~Hex() { delete[] d; }

void Hex::resize(size_t newCap)
{
    if (newCap <= cap)
        return;
    unsigned char *newD = new unsigned char[newCap];
    std::memcpy(newD, d, len * sizeof(unsigned char));
    delete[] d;
    d = newD;
    cap = newCap;
}

Hex Hex::add(const Hex &oth) const
{
    size_t maxS = std::max(len, oth.len);
    unsigned char *res = new unsigned char[maxS + 1];
    unsigned int c = 0;
    size_t resLen = 0;
    for (size_t i = 0; i < maxS; ++i)
    {
        unsigned int sum = c;
        if (i < len)
            sum += d[i];
        if (i < oth.len)
            sum += oth.d[i];
        res[resLen++] = sum % 16;
        c = sum / 16;
    }
    if (c)
        res[resLen++] = c;
    Hex resHex(res, resLen);
    delete[] res;
    return resHex;
}

Hex Hex::subtract(const Hex &oth) const
{
    if (isLess(oth))
        throw std::runtime_error("Negative result");
    unsigned char *res = new unsigned char[len];
    int b = 0;
    size_t resLen = 0;
    for (size_t i = 0; i < len; ++i)
    {
        int cur = d[i] - b;
        if (i < oth.len)
            cur -= oth.d[i];
        if (cur < 0)
        {
            cur += 16;
            b = 1;
        }
        else
            b = 0;
        res[resLen++] = cur;
    }
    Hex resHex(res, resLen);
    delete[] res;
    resHex.trimZeros();
    return resHex;
}

Hex Hex::copy() const { return Hex(*this); }
bool Hex::isEqual(const Hex &oth) const
{
    if (len != oth.len)
        return false;
    for (size_t i = 0; i < len; ++i)
    {
        if (d[i] != oth.d[i])
            return false;
    }
    return true;
}

bool Hex::isGreater(const Hex &oth) const
{
    if (len != oth.len)
        return len > oth.len;
    for (size_t i = len; i > 0; --i)
    {
        if (d[i - 1] != oth.d[i - 1])
            return d[i - 1] > oth.d[i - 1];
    }
    return false;
}

bool Hex::isLess(const Hex &oth) const { return !isGreater(oth) && !isEqual(oth); }

std::string Hex::toString() const
{
    if (len == 1 && d[0] == 0)
        return "0";
    std::string res;
    for (size_t i = len; i > 0; --i)
        res += h2c(d[i - 1]);
    return res;
}

size_t Hex::getSize() const { return len; }

void Hex::trimZeros()
{
    while (len > 1 && d[len - 1] == 0)
        --len;
}

unsigned char Hex::c2h(char c)
{
    c = std::toupper(c);
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    throw std::invalid_argument("Invalid hex char");
}

char Hex::h2c(unsigned char d)
{
    if (d < 10)
        return '0' + d;
    return 'A' + (d - 10);
}