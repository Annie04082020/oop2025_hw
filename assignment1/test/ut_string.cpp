#include <gtest/gtest.h>
#include <iostream>
#include <string>

TEST(StringFuncTest, length)
{
    std::string str = "";
    for (int i = 1; i <= 20; i++)
    {
        str.append(1u, '.');
        ASSERT_EQ(i, str.length());
    }
}
TEST(StringFuncTest, empty)
{
    std::string str = "";
    ASSERT_TRUE(str.empty());
    str.append(1u, '.');
    ASSERT_FALSE(str.empty());
    str.clear();
    ASSERT_TRUE(str.empty());
}
TEST(StringFuncTest, clear)
{
    std::string str = "";
    for (int i = 1; i <= 20; i++)
    {
        str.append(i, '.');
        ASSERT_FALSE(str.empty());
        str.clear();
        ASSERT_TRUE(str.empty());
        ASSERT_EQ(0, str.length());
    }
}
TEST(StringFuncTest, insert)
{
    std::string str_a = "0123456789";
    std::string str_b = "ABC";
    std::string empty_str = "";
    // insert pos 0
    str_a.insert(0, str_b);
    ASSERT_EQ("ABC0123456789", str_a);
    // insert pos mid
    str_a = "0123456789";
    str_a.insert(5, str_b);
    ASSERT_EQ("01234ABC56789", str_a);
    // insert pos end
    str_a = "0123456789";
    str_a.insert(str_a.length(), str_b);
    ASSERT_EQ("0123456789ABC", str_a);
    // insert to empty string
    empty_str.insert(0, str_b);
    ASSERT_EQ("ABC", empty_str);
}
TEST(StringFuncTest, copy)
{
    // Normal case
    char copied[10] = {0};
    std::string str = "01234";
    std::size_t length = str.copy(copied, 3, 0);
    copied[length] = '\0';
    ASSERT_EQ(3, length);
    ASSERT_EQ("012", std::string(copied));
    // copy more than length
    length = str.copy(copied, 3, 5);
    copied[length] = '\0';
    ASSERT_EQ(0, length);
    ASSERT_EQ("", std::string(copied));
}
TEST(StringFuncTest, compare)
{
    // Equal
    std::string str = "cdefg";
    std::string str_equal = str;
    ASSERT_EQ(0, str.compare(str_equal));
    // a smaller than b
    std::string str_greater_order = "defgh";
    std::string str_longer = "cdefgh";
    ASSERT_LT(str.compare(str_greater_order), 0);
    ASSERT_LT(str.compare(str_longer), 0);
    // a greater than b
    std::string str_smaller_order = "bcdef";
    std::string str_shorter = "cdef";
    ASSERT_GT(str.compare(str_smaller_order), 0);
    ASSERT_GT(str.compare(str_shorter), 0);
}
TEST(StringFuncTest, swap)
{
    std::string str_a = "aaa";
    std::string str_b = "bbb";
    str_a.swap(str_b);
    ASSERT_EQ("aaa", str_b);
    ASSERT_EQ("bbb", str_a);
    str_b.swap(str_a);
    ASSERT_EQ("aaa", str_a);
    ASSERT_EQ("bbb", str_b);
}
TEST(StringFuncTest, find)
{
    std::string str_text = "assignment";
    std::string str_find_exist = "ment";
    std::string str_find_not_exist = "hw";
    // find exist
    ASSERT_EQ(6, str_text.find(str_find_exist));
    ASSERT_EQ(4, str_text.find('g'));
    // find not exist
    ASSERT_EQ(std::string::npos, str_text.find(str_find_not_exist));
    ASSERT_EQ(std::string::npos, str_text.find('z'));
}