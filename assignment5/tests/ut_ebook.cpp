#include <gtest/gtest.h>
#include "../src/ebook.h"
#include "../src/library_item.h"

class EBookItemTest : public ::testing::Test
{
protected:
    EBook a = {6001, "Signals, Systems, and Transforms fifth edition", "Charles L. Phillips, John M. Parr, Eve A. Riskin"};
    EBook b = {6002, "Power Systems Analysis second edition", "Arthur R.Bergen, Vijay Vittal"};
};

TEST_F(EBookItemTest, GetType)
{
    EXPECT_EQ(a.get_type(), "EBook");
}
TEST_F(EBookItemTest, GetInfo)
{
    EXPECT_EQ(a.to_string(), "EBook: Signals, Systems, and Transforms fifth edition by Charles L. Phillips, John M. Parr, Eve A. Riskin");
}
TEST_F(EBookItemTest, GetType2)
{
    EXPECT_EQ(b.get_type(), "EBook");
}
TEST_F(EBookItemTest, GetInfo2)
{
    EXPECT_EQ(b.to_string(), "EBook: Power Systems Analysis second edition by Arthur R.Bergen, Vijay Vittal");
}