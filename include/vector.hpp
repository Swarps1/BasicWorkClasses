#pragma once

#include <cstddef>
#include <stdexcept>

class MyVector
{
public:
    MyVector();
    explicit MyVector(size_t size);
    MyVector(const MyVector &other);
    MyVector(MyVector &&other) noexcept;
    MyVector &operator=(const MyVector &other);
    MyVector &operator=(MyVector &&other) noexcept;
    ~MyVector();

    void push_back(unsigned char value);
    unsigned char &at(size_t index);
    const unsigned char &at(size_t index) const;
    size_t size() const;
    size_t capacity() const;

private:
    unsigned char *data_;
    size_t size_;
    size_t capacity_;
};