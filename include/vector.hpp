#pragma once

#include <stdexcept>
#include <cstring>

template <typename T>
class Vector
{
private:
    T *data;
    size_t length;
    size_t capacity;

    void grow(size_t newCap);

public:
    Vector();
    explicit Vector(size_t sz);
    Vector(const T *arr, size_t sz);
    Vector(const Vector &other);
    ~Vector();

    T &operator[](size_t index);
    const T &operator[](size_t index) const;

    void push_back(const T &value);
    size_t size() const;
    size_t cap() const;
    T *getData() const;
    void resize(size_t newSize);
};