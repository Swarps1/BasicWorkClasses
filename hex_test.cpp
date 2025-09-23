#include <gtest/gtest.h>
#include "hex.hpp"

TEST(HexTest, DefaultConstructor)
{
    Hex h;
    EXPECT_EQ(h.toString(), "0");
    EXPECT_EQ(h.getSize(), 1);
}

TEST(HexTest, StringConstructorValid)
{
    Hex h("1A3F");
    EXPECT_EQ(h.toString(), "1A3F");
    EXPECT_EQ(h.getSize(), 4);
}

TEST(HexTest, StringConstructorInvalid)
{
    EXPECT_THROW(Hex("1G3F"), std::invalid_argument);
    EXPECT_THROW(Hex(""), std::invalid_argument);
}

TEST(HexTest, ArrayConstructorValid)
{
    unsigned char arr[] = {15, 3, 10, 1};
    Hex h(arr, 4);
    EXPECT_EQ(h.toString(), "1A3F");
    EXPECT_EQ(h.getSize(), 4);
}

TEST(HexTest, ArrayConstructorInvalid)
{
    unsigned char arr[] = {16};
    EXPECT_THROW(Hex(arr, 1), std::invalid_argument);
    EXPECT_THROW(Hex(nullptr, 0), std::invalid_argument);
}

TEST(HexTest, CopyConstructor)
{
    Hex h("1A3F");
    Hex copy(h);
    EXPECT_EQ(copy.toString(), "1A3F");
    EXPECT_EQ(copy.getSize(), 4);
}

TEST(HexTest, Add)
{
    Hex a("1A3F");
    Hex b("FF");
    Hex sum = a.add(b);
    EXPECT_EQ(sum.toString(), "1B3E");
    EXPECT_EQ(a.toString(), "1A3F");
    EXPECT_EQ(b.toString(), "FF");
}

TEST(HexTest, SubtractValid)
{
    Hex a("1A3F");
    Hex b("FF");
    Hex diff = a.subtract(b);
    EXPECT_EQ(diff.toString(), "1940");
}

TEST(HexTest, SubtractInvalid)
{
    Hex a("FF");
    Hex b("1A3F");
    EXPECT_THROW(a.subtract(b), std::runtime_error);
}

TEST(HexTest, Comparisons)
{
    Hex a("1A3F");
    Hex b("FF");
    Hex c("1A3F");
    EXPECT_TRUE(a.isGreater(b));
    EXPECT_TRUE(b.isLess(a));
    EXPECT_TRUE(a.isEqual(c));
    EXPECT_FALSE(a.isEqual(b));
}

TEST(HexTest, TrimLeadingZeros)
{
    Hex h("0001A3F");
    EXPECT_EQ(h.toString(), "1A3F");
    EXPECT_EQ(h.getSize(), 4);
    Hex zero("0000");
    EXPECT_EQ(zero.toString(), "0");
    EXPECT_EQ(zero.getSize(), 1);
}

TEST(HexTest, LargeNumbers)
{
    Hex large("FFFFFFFFFFFFFFFF");
    Hex one("1");
    Hex sum = large.add(one);
    EXPECT_EQ(sum.toString(), "10000000000000000");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}