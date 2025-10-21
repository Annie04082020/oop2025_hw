#include <gtest/gtest.h>
#include "../src/reference_book.h"
#include "../src/library_item.h"

class ReferenceBookItemTest : public ::testing::Test
{
protected:
    ReferenceBook a = {4001, "Essential Calculus 2nd Edition", "James Stewart"};
    ReferenceBook b = {4002, "Advanced Engineering Mathematics", "Peter V. O'Neil"};
};

TEST_F(ReferenceBookItemTest, GetType)
{
    EXPECT_EQ(a.get_type(), "ReferenceBook");
}
TEST_F(ReferenceBookItemTest, GetInfo)
{
    EXPECT_EQ(a.to_string(), "ReferenceBook: Essential Calculus 2nd Edition by James Stewart");
}
TEST_F(ReferenceBookItemTest, GetType2)
{
    EXPECT_EQ(b.get_type(), "ReferenceBook");
}
TEST_F(ReferenceBookItemTest, GetInfo2)
{
    EXPECT_EQ(b.to_string(), "ReferenceBook: Advanced Engineering Mathematics by Peter V. O'Neil");
}