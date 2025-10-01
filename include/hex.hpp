#pragma once

#include <string>
#include <stdexcept>
#include "vector.hpp"

class Hex
{
public:
    Hex();
    explicit Hex(std::string str);
    Hex(const unsigned char *arr, size_t sz);
    Hex(const Hex &o);
    ~Hex();

    Hex add(const Hex &o) const;
    Hex sub(const Hex &o) const;
    Hex cpy() const;
    bool eq(const Hex &o) const;
    bool gt(const Hex &o) const;
    bool lt(const Hex &o) const;
    std::string str() const;
    size_t sz() const;

private:
    Vector<unsigned char> digits;
    void trim();
    static unsigned char c2h(char c);
    static char h2c(unsigned char d);
};