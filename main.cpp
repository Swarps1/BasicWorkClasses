#include "hex.hpp"
#include <iostream>

int main()
{
    try
    {

        Hex a("1A3F");
        Hex b("FF");

        std::cout << "a = " << a.toString() << std::endl;
        std::cout << "b = " << b.toString() << std::endl;

        Hex sum = a.add(b);
        std::cout << "a + b = " << sum.toString() << std::endl;

        Hex diff = a.subtract(b);
        std::cout << "a - b = " << diff.toString() << std::endl;

        Hex copy = a.copy();
        std::cout << "Copy of a = " << copy.toString() << std::endl;

        std::cout << "a == b: " << (a.isEqual(b) ? "true" : "false") << std::endl;
        std::cout << "a > b: " << (a.isGreater(b) ? "true" : "false") << std::endl;
        std::cout << "a < b: " << (a.isLess(b) ? "true" : "false") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}