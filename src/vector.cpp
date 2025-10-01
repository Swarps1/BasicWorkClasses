#include "vector.hpp"

template <typename T>
Vector<T>::Vector() : data(new T[1]), length(1), capacity(1)
{
    data[0] = T();
}

template <typename T>
Vector<T>::Vector(size_t sz) : data(new T[sz]), length(sz), capacity(sz)
{
    for (size_t i = 0; i < sz; ++i)
    {
        data[i] = T();
    }
}

template <typename T>
Vector<T>::Vector(const T *arr, size_t sz) : data(new T[sz]), length(sz), capacity(sz)
{
    memcpy(data, arr, sz * sizeof(T));
}

template <typename T>
Vector<T>::Vector(const Vector &other) : data(new T[other.capacity]), length(other.length), capacity(other.capacity)
{
    memcpy(data, other.data, length * sizeof(T));
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

template <typename T>
void Vector<T>::grow(size_t newCap)
{
    if (newCap <= capacity)
        return;
    T *newData = new T[newCap];
    memcpy(newData, data, length * sizeof(T));
    delete[] data;
    data = newData;
    capacity = newCap;
}

template <typename T>
T &Vector<T>::operator[](size_t index)
{
    if (index >= length)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T &Vector<T>::operator[](size_t index) const
{
    if (index >= length)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
void Vector<T>::push_back(const T &value)
{
    if (length == capacity)
    {
        grow(capacity * 2);
    }
    data[length++] = value;
}

template <typename T>
size_t Vector<T>::size() const
{
    return length;
}

template <typename T>
size_t Vector<T>::cap() const
{
    return capacity;
}

template <typename T>
T *Vector<T>::getData() const
{
    return data;
}

template <typename T>
void Vector<T>::resize(size_t newSize)
{
    if (newSize > capacity)
        grow(newSize);
    length = newSize;
}

template class Vector<unsigned char>;