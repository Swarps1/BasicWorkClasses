#include "hex.hpp"
#include <iostream>
int main()
{
    try
    {
        Hex x("1A3F");
        Hex y("FF");
        std::cout << "a=" << x.str() << '\n'
                  << "b=" << y.str() << '\n';
        Hex s = x.add(y);
        std::cout << "a+b=" << s.str() << '\n';
        Hex d = x.sub(y);
        std::cout << "a-b=" << d.str() << '\n';
        Hex c = x.cpy();
        std::cout << "copy=" << c.str() << '\n';
        std::cout << "a==b:" << (x.eq(y) ? "yes" : "no") << '\n';
        std::cout << "a>b:" << (x.gt(y) ? "yes" : "no") << '\n';
        std::cout << "a<b:" << (x.lt(y) ? "yes" : "no") << '\n';
    }
    catch (std::exception &e)
    {
        std::cerr << "err:" << e.what() << '\n';
    }
    return 0;
}