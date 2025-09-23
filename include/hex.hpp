#pragma once

#include <stdexcept>
#include <string>

class Hex
{
public:
    Hex();

    explicit Hex(const std::string &hexStr);

    Hex(const unsigned char *digits, size_t size);

    Hex(const Hex &other);

    ~Hex();

    Hex add(const Hex &other) const;
    Hex subtract(const Hex &other) const;
    Hex copy() const;

    bool isEqual(const Hex &other) const;
    bool isGreater(const Hex &other) const;
    bool isLess(const Hex &other) const;

    std::string toString() const;

    size_t getSize() const;

private:
    unsigned char *data;
    size_t length;
    size_t capacity;

    // Увеличение
    void resize(size_t newCapacity);

    void trimLeadingZeros();

    static unsigned char charToHexDigit(char c);

    static char hexDigitToChar(unsigned char digit);
};
