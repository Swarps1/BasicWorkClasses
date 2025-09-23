#pragma once

#include <stdexcept>
#include <string>

class Hex
{
public:
    // Конструктор по умолчанию (ноль)
    Hex();

    // Конструктор из строки
    explicit Hex(const std::string &hexStr);

    // Конструктор из массива цифр
    Hex(const unsigned char *digits, size_t size);

    // Конструктор копирования
    Hex(const Hex &other);

    // Деструктор
    ~Hex();

    // Арифметические операции
    Hex add(const Hex &other) const;      // Сложение
    Hex subtract(const Hex &other) const; // Вычитание
    Hex copy() const;                     // Копия объекта

    // Операции сравнения
    bool isEqual(const Hex &other) const;   // Равно
    bool isGreater(const Hex &other) const; // Больше
    bool isLess(const Hex &other) const;    // Меньше

    // Получение строкового представления числа
    std::string toString() const;

    // Получение размера числа
    size_t getSize() const;

private:
    unsigned char *data; // Динамический массив цифр
    size_t length;       // Текущая длина
    size_t capacity;     // Выделенная память

    // Увеличение
    void resize(size_t newCapacity);

    // Удаление ведущих нулей
    void trimLeadingZeros();

    // функция для проверки корректности символа
    static unsigned char charToHexDigit(char c);

    // функция для преобразования цифры в символ
    static char hexDigitToChar(unsigned char digit);
};
