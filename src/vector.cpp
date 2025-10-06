#include "vector.hpp"

MyVector::MyVector() : data_(nullptr), size_(0), capacity_(0) {}

MyVector::MyVector(size_t size) : size_(size), capacity_(size)
{
    if (size == 0)
    {
        data_ = nullptr;
        return;
    }
    data_ = new unsigned char[size];
    for (size_t i = 0; i < size; ++i)
    {
        data_[i] = 0;
    }
}

MyVector::MyVector(const MyVector &other) : size_(other.size_), capacity_(other.capacity_)
{
    if (size_ == 0)
    {
        data_ = nullptr;
        return;
    }
    data_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

MyVector::MyVector(MyVector &&other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

MyVector &MyVector::operator=(const MyVector &other)
{
    if (this != &other)
    {
        unsigned char *new_data = nullptr;
        if (other.size_ > 0)
        {
            new_data = new unsigned char[other.size_];
            for (size_t i = 0; i < other.size_; ++i)
            {
                new_data[i] = other.data_[i];
            }
        }
        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.size_;
    }
    return *this;
}

MyVector &MyVector::operator=(MyVector &&other) noexcept
{
    if (this != &other)
    {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

MyVector::~MyVector()
{
    delete[] data_;
}

void MyVector::push_back(unsigned char value)
{
    if (size_ == capacity_)
    {
        size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
        unsigned char *new_data = new unsigned char[new_capacity];
        for (size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_++] = value;
}

unsigned char &MyVector::at(size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

const unsigned char &MyVector::at(size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

size_t MyVector::size() const
{
    return size_;
}

size_t MyVector::capacity() const
{
    return capacity_;
}