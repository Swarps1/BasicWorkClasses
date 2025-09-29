#include "../include/hex.hpp"
#include <cstring>
#include <cctype>

Hex::Hex() : d(new unsigned char[1]), len(1), cap(1)
{
    d[0] = 0;
}

Hex::Hex(std::string str) : d(0), len(0), cap(0)
{
    if (!str.size())
        throw std::invalid_argument("empty");
    cap = str.size();
    d = new unsigned char[cap];
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (!isxdigit(str[i]))
        {
            delete[] d;
            throw std::invalid_argument("bad char");
        }
        d[len++] = c2h(str[i]);
    }
    trim();
    if (!len)
    {
        delete[] d;
        d = new unsigned char[1];
        d[0] = 0;
        len = 1;
        cap = 1;
    }
}

Hex::Hex(const unsigned char *arr, size_t sz) : d(0), len(0), cap(0)
{
    if (!sz)
        throw std::invalid_argument("empty");
    cap = sz;
    d = new unsigned char[cap];
    for (size_t i = 0; i < sz; i++)
    {
        if (arr[i] > 15)
        {
            delete[] d;
            throw std::invalid_argument("bad digit");
        }
        d[i] = arr[i];
    }
    len = sz;
    trim();
    if (!len)
    {
        delete[] d;
        d = new unsigned char[1];
        d[0] = 0;
        len = 1;
        cap = 1;
    }
}

Hex::Hex(const Hex &o) : d(new unsigned char[o.cap]), len(o.len), cap(o.cap)
{
    memcpy(d, o.d, len);
}

Hex::~Hex() { delete[] d; }

void Hex::grow(size_t newCap)
{
    if (newCap <= cap)
        return;
    unsigned char *t = new unsigned char[newCap];
    memcpy(t, d, len);
    delete[] d;
    d = t;
    cap = newCap;
}

Hex Hex::add(const Hex &o) const
{
    size_t m = len > o.len ? len : o.len;
    unsigned char *r = new unsigned char[m + 1];
    int c = 0, k = 0;
    for (size_t i = 0; i < m; i++)
    {
        int s = c;
        if (i < len)
            s += d[i];
        if (i < o.len)
            s += o.d[i];
        r[k++] = s % 16;
        c = s / 16;
    }
    if (c)
        r[k++] = c;
    Hex h(r, k);
    delete[] r;
    return h;
}

Hex Hex::sub(const Hex &o) const
{
    if (lt(o))
        throw std::runtime_error("negative");
    unsigned char *r = new unsigned char[len];
    int b = 0, k = 0;
    for (size_t i = 0; i < len; i++)
    {
        int v = d[i] - b;
        if (i < o.len)
            v -= o.d[i];
        if (v < 0)
        {
            v += 16;
            b = 1;
        }
        else
            b = 0;
        r[k++] = v;
    }
    Hex h(r, k);
    delete[] r;
    h.trim();
    return h;
}

Hex Hex::cpy() const
{
    Hex h(*this);
    return h;
}

bool Hex::eq(const Hex &o) const
{
    if (len != o.len)
        return false;
    for (size_t i = 0; i < len; i++)
        if (d[i] != o.d[i])
            return false;
    return true;
}

bool Hex::gt(const Hex &o) const
{
    if (len != o.len)
        return len > o.len;
    for (int i = len - 1; i >= 0; i--)
        if (d[i] != o.d[i])
            return d[i] > o.d[i];
    return false;
}

bool Hex::lt(const Hex &o) const
{
    return !gt(o) && !eq(o);
}

std::string Hex::str() const
{
    if (len == 1 && d[0] == 0)
        return "0";
    std::string s;
    for (int i = len - 1; i >= 0; i--)
        s += h2c(d[i]);
    return s;
}

size_t Hex::sz() const { return len; }

void Hex::trim()
{
    while (len > 1 && d[len - 1] == 0)
        len--;
}

unsigned char Hex::c2h(char c)
{
    c = toupper(c);
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    throw std::invalid_argument("bad char");
}

char Hex::h2c(unsigned char d)
{
    if (d < 10)
        return '0' + d;
    return 'A' + (d - 10);
}