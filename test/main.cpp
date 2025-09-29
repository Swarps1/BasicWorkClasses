#include "hex.hpp"
#include <iostream>
int main()
{
    try
    {
        Hex a("1A3F"), b("FF");
        std::cout << "a=" << a.toString() << '\n';
        std::cout << "b=" << b.toString() << '\n';
        Hex sum = a.add(b);
        std::cout << "a+b=" << sum.toString() << '\n';
        Hex diff = a.subtract(b);
        std::cout << "a-b=" << diff.toString() << '\n';
        Hex copy = a.copy();
        std::cout << "Copy=" << copy.toString() << '\n';
        std::cout << "a==b:" << (a.isEqual(b) ? "true" : "false") << '\n';
        std::cout << "a>b:" << (a.isGreater(b) ? "true" : "false") << '\n';
        std::cout << "a<b:" << (a.isLess(b) ? "true" : "false") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error:" << e.what() << '\n';
    }
    return 0;
}