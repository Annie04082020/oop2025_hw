#include <string>
#include <gtest/gtest.h>
#include "../src/utils.h"

class BubbleSortTest : public ::testing::Test
{
protected:
    std::vector<int> int_unsort = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> int_sorted_asc = {11, 12, 22, 25, 34, 64, 90};
    std::vector<int> int_sorted_dec = {90, 64, 34, 25, 22, 12, 11};
    std::vector<std::string> str_unsort = {"banana", "apple", "cherry", "date"};
    std::vector<std::string> str_sorted_asc = {"apple", "banana", "cherry", "date"};
    std::vector<std::string> str_sorted_dec = {"date", "cherry", "banana", "apple"};
    std::vector<long> long_unsort = {5000L, 100L, 3000L, 200L, 4000L};
    std::vector<long> long_sorted_asc = {100L, 200L, 3000L, 4000L, 5000L};
    std::vector<long> long_sorted_dec = {5000L, 4000L, 3000L, 200L, 100L};
};

TEST_F(BubbleSortTest, SortIntegerDecending)
{
    auto descending = [](int a, int b)
    { return a > b; };
    bubble_sort(int_unsort.begin(), int_unsort.end(), descending);
    EXPECT_EQ(int_unsort, int_sorted_dec);
}
TEST_F(BubbleSortTest, SortIntegerAscending)
{
    auto ascending = [](int a, int b)
    { return a < b; };
    bubble_sort(int_unsort.begin(), int_unsort.end(), ascending);
    EXPECT_EQ(int_unsort, int_sorted_asc);
}
TEST_F(BubbleSortTest, SortLongDecending)
{
    auto descending = [](long a, long b)
    { return a > b; };
    bubble_sort(long_unsort.begin(), long_unsort.end(), descending);
    EXPECT_EQ(long_unsort, long_sorted_dec);
}
TEST_F(BubbleSortTest, SortLongAscending)
{
    auto ascending = [](long a, long b)
    { return a < b; };
    bubble_sort(long_unsort.begin(), long_unsort.end(), ascending);
    EXPECT_EQ(long_unsort, long_sorted_asc);
}
TEST_F(BubbleSortTest, SortStringDecending)
{
    auto descending = [](std::string a, std::string b)
    { return a > b; };
    bubble_sort(str_unsort.begin(), str_unsort.end(), descending);
    EXPECT_EQ(str_unsort, str_sorted_dec);
}
TEST_F(BubbleSortTest, SortStringAscending)
{
    auto ascending = [](std::string a, std::string b)
    { return a < b; };
    bubble_sort(str_unsort.begin(), str_unsort.end(), ascending);
    EXPECT_EQ(str_unsort, str_sorted_asc);
}

TEST_F(BubbleSortTest, SortIntergerDefault)
{
    bubble_sort(int_unsort.begin(), int_unsort.end());
    EXPECT_EQ(int_unsort, int_sorted_asc);
}
TEST_F(BubbleSortTest, SortLongDefault)
{
    bubble_sort(long_unsort.begin(), long_unsort.end());
    EXPECT_EQ(long_unsort, long_sorted_asc);
}
TEST_F(BubbleSortTest, SortStringDefault)
{
    bubble_sort(str_unsort.begin(), str_unsort.end());
    EXPECT_EQ(str_unsort, str_sorted_asc);
}