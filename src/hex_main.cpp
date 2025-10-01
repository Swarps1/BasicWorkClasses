#include "hex.hpp"
#include <cctype>

Hex::Hex() : digits()
{
    digits[0] = 0;
}

Hex::Hex(std::string str) : digits(str.size())
{
    if (!str.size())
        throw std::invalid_argument("Пусто");

    size_t pos = 0;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (!isxdigit(str[i]))
        {
            throw std::invalid_argument("Ошибка");
        }
        digits[pos++] = c2h(str[i]);
    }
    trim();
    if (digits.size() == 0)
    {
        digits.resize(1);
        digits[0] = 0;
    }
}

Hex::Hex(const unsigned char *arr, size_t sz) : digits(sz)
{
    if (!sz)
        throw std::invalid_argument("Пусто");

    for (size_t i = 0; i < sz; i++)
    {
        if (arr[i] > 15)
        {
            throw std::invalid_argument("Ошибка");
        }
        digits[i] = arr[i];
    }
    trim();
    if (digits.size() == 0)
    {
        digits.resize(1);
        digits[0] = 0;
    }
}

Hex::Hex(const Hex &o) : digits(o.digits) {}

Hex::~Hex() {}

void Hex::trim()
{
    while (digits.size() > 1 && digits[digits.size() - 1] == 0)
    {
        digits.resize(digits.size() - 1);
    }
}

unsigned char Hex::c2h(char c)
{
    c = toupper(c);
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    throw std::invalid_argument("Ошибка");
}

char Hex::h2c(unsigned char d)
{
    if (d < 10)
        return '0' + d;
    return 'A' + (d - 10);
}