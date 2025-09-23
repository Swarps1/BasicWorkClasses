#include "../include/hex.hpp"
#include <algorithm>
#include <cctype>
#include <cstring>

Hex::Hex() : data(new unsigned char[1]), length(1), capacity(1)
{
    data[0] = 0;
}

Hex::Hex(const std::string &hexStr) : data(nullptr), length(0), capacity(0)
{
    if (hexStr.empty())
    {
        throw std::invalid_argument("Пустая строка");
    }

    size_t strLen = hexStr.length();
    capacity = strLen;
    data = new unsigned char[capacity];

    // Парсим строку с конца
    size_t idx = 0;
    for (auto it = hexStr.rbegin(); it != hexStr.rend(); ++it)
    {
        char c = *it;
        if (!std::isxdigit(c))
        {
            delete[] data;
            throw std::invalid_argument("Недопустимый символ");
        }
        data[idx++] = charToHexDigit(c);
    }
    length = idx;
    trimLeadingZeros();
    if (length == 0)
    {
        delete[] data;
        data = new unsigned char[1];
        data[0] = 0;
        length = 1;
        capacity = 1;
    }
}

Hex::Hex(const unsigned char *digits, size_t size) : data(nullptr), length(0), capacity(0)
{
    if (size == 0)
    {
        throw std::invalid_argument("Пустая строка");
    }
    capacity = size;
    data = new unsigned char[capacity];
    for (size_t i = 0; i < size; ++i)
    {
        if (digits[i] > 15)
        {
            delete[] data;
            throw std::invalid_argument("Недопустимый символ");
        }
        data[i] = digits[i];
    }
    length = size;
    trimLeadingZeros();
    if (length == 0)
    {
        delete[] data;
        data = new unsigned char[1];
        data[0] = 0;
        length = 1;
        capacity = 1;
    }
}

Hex::Hex(const Hex &other) : data(new unsigned char[other.capacity]), length(other.length), capacity(other.capacity)
{
    std::memcpy(data, other.data, length * sizeof(unsigned char));
}

Hex::~Hex()
{
    delete[] data;
}

Hex Hex::add(const Hex &other) const
{
    size_t maxSize = std::max(length, other.length);
    unsigned char *resultData = new unsigned char[maxSize + 1];
    unsigned int carry = 0;
    size_t resLen = 0;

    for (size_t i = 0; i < maxSize; ++i)
    {
        unsigned int sum = carry;
        if (i < length)
            sum += data[i];
        if (i < other.length)
            sum += other.data[i];
        resultData[resLen++] = sum % 16;
        carry = sum / 16;
    }
    if (carry)
    {
        resultData[resLen++] = carry;
    }

    Hex result(resultData, resLen);
    delete[] resultData;
    return result;
}

Hex Hex::subtract(const Hex &other) const
{
    if (isLess(other))
    {
        throw std::runtime_error("Отрицательный результат");
    }

    unsigned char *resultData = new unsigned char[length];
    int borrow = 0;
    size_t resLen = 0;

    for (size_t i = 0; i < length; ++i)
    {
        int current = data[i] - borrow;
        if (i < other.length)
            current -= other.data[i];
        if (current < 0)
        {
            current += 16;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        resultData[resLen++] = current;
    }

    Hex resultHex(resultData, resLen);
    delete[] resultData;
    resultHex.trimLeadingZeros();
    return resultHex;
}

// Копия
Hex Hex::copy() const
{
    return Hex(*this);
}

bool Hex::isEqual(const Hex &other) const
{
    if (length != other.length)
        return false;
    for (size_t i = 0; i < length; ++i)
    {
        if (data[i] != other.data[i])
            return false;
    }
    return true;
}

bool Hex::isGreater(const Hex &other) const
{
    if (length != other.length)
    {
        return length > other.length;
    }
    for (size_t i = length; i > 0; --i)
    {
        size_t idx = i - 1;
        if (data[idx] != other.data[idx])
        {
            return data[idx] > other.data[idx];
        }
    }
    return false;
}

bool Hex::isLess(const Hex &other) const
{
    return !isGreater(other) && !isEqual(other);
}

std::string Hex::toString() const
{
    if (length == 1 && data[0] == 0)
    {
        return "0";
    }
    std::string result;
    for (size_t i = length; i > 0; --i)
    {
        result += hexDigitToChar(data[i - 1]);
    }
    return result;
}

size_t Hex::getSize() const
{
    return length;
}

void Hex::resize(size_t newCapacity)
{
    if (newCapacity <= capacity)
        return;
    unsigned char *newData = new unsigned char[newCapacity];
    std::memcpy(newData, data, length * sizeof(unsigned char));
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void Hex::trimLeadingZeros()
{
    while (length > 1 && data[length - 1] == 0)
    {
        --length;
    }
}

unsigned char Hex::charToHexDigit(char c)
{
    c = std::toupper(c);
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    throw std::invalid_argument("Недопустимый символ");
}

char Hex::hexDigitToChar(unsigned char digit)
{
    if (digit < 10)
        return '0' + digit;
    return 'A' + (digit - 10);
}