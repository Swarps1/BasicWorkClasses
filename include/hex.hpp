#pragma once

#include "vector.hpp"
#include <stdexcept>
#include <string>

class Hex
{
public:
    Hex();
    explicit Hex(const char *str);
    Hex(const unsigned char *arr, size_t size);
    Hex(const Hex &other);
    Hex(Hex &&other) noexcept;
    Hex &operator=(const Hex &other);
    Hex &operator=(Hex &&other) noexcept;
    ~Hex();

    Hex add(const Hex &other) const;
    Hex sub(const Hex &other) const;
    Hex cpy() const;
    bool gt(const Hex &other) const;
    bool lt(const Hex &other) const;
    bool eq(const Hex &other) const;

    std::string str() const;
    size_t sz() const;

private:
    MyVector digits_;
};