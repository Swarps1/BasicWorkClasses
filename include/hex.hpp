#pragma once

#include <string>
#include <stdexcept>

class Hex
{
public:
    Hex();
    explicit Hex(const std::string &str);
    Hex(const unsigned char *d, size_t s);
    Hex(const Hex &oth);
    ~Hex();
    Hex add(const Hex &oth) const;
    Hex subtract(const Hex &oth) const;
    Hex copy() const;
    bool isEqual(const Hex &oth) const;
    bool isGreater(const Hex &oth) const;
    bool isLess(const Hex &oth) const;
    std::string toString() const;
    size_t getSize() const;

private:
    unsigned char *d;
    size_t len, cap;
    void resize(size_t newCap);
    void trimZeros();
    static unsigned char c2h(char c);
    static char h2c(unsigned char d);
};