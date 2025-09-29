#include <gtest/gtest.h>
#include "hex.hpp"
TEST(Hex, T1)
{
    Hex h;
    ASSERT_EQ(h.str(), "0");
    ASSERT_EQ(h.sz(), 1);
}
TEST(Hex, T2)
{
    Hex h("1A3F");
    ASSERT_EQ(h.str(), "1A3F");
    ASSERT_EQ(h.sz(), 4);
}
TEST(Hex, T3)
{
    ASSERT_THROW(Hex("1G3F"), std::invalid_argument);
    ASSERT_THROW(Hex(""), std::invalid_argument);
}
TEST(Hex, T4)
{
    unsigned char a[] = {15, 3, 10, 1};
    Hex h(a, 4);
    ASSERT_EQ(h.str(), "1A3F");
    ASSERT_EQ(h.sz(), 4);
}
TEST(Hex, T5)
{
    unsigned char a[] = {16};
    ASSERT_THROW(Hex(a, 1), std::invalid_argument);
    ASSERT_THROW(Hex(0, 0), std::invalid_argument);
}
TEST(Hex, T6)
{
    Hex h("1A3F");
    Hex c(h);
    ASSERT_EQ(c.str(), "1A3F");
    ASSERT_EQ(c.sz(), 4);
}
TEST(Hex, T7)
{
    Hex x("1A3F"), y("FF");
    Hex s = x.add(y);
    ASSERT_EQ(s.str(), "1B3E");
    ASSERT_EQ(x.str(), "1A3F");
    ASSERT_EQ(y.str(), "FF");
}
TEST(Hex, T8)
{
    Hex x("1A3F"), y("FF");
    Hex d = x.sub(y);
    ASSERT_EQ(d.str(), "1940");
}
TEST(Hex, T9)
{
    Hex x("FF"), y("1A3F");
    ASSERT_THROW(x.sub(y), std::runtime_error);
}
TEST(Hex, T10)
{
    Hex x("1A3F"), y("FF"), z("1A3F");
    ASSERT_TRUE(x.gt(y));
    ASSERT_TRUE(y.lt(x));
    ASSERT_TRUE(x.eq(z));
    ASSERT_FALSE(x.eq(y));
}
TEST(Hex, T11)
{
    Hex h("0001A3F");
    ASSERT_EQ(h.str(), "1A3F");
    ASSERT_EQ(h.sz(), 4);
    Hex z("0000");
    ASSERT_EQ(z.str(), "0");
    ASSERT_EQ(z.sz(), 1);
}
TEST(Hex, T12)
{
    Hex big("FFFFFFFFFFFFFFFF"), one("1");
    Hex s = big.add(one);
    ASSERT_EQ(s.str(), "10000000000000000");
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}