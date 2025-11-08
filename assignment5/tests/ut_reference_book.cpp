#include <gtest/gtest.h>
#include "../src/reference_book.h"
#include "../src/library_item.h"

class ReferenceBookItemTest : public ::testing::Test
{
protected:
    ReferenceBook *a = new ReferenceBook{7001, "Essential Calculus 2nd Edition", "James Stewart"};
    ReferenceBook *b = new ReferenceBook{7002, "Advanced Engineering Mathematics", "Peter V. O'Neil"};
    void TearDown() override
    {
        delete a;
        delete b;
    };
};

TEST_F(ReferenceBookItemTest, GetType)
{
    EXPECT_EQ(a->get_type(), "ReferenceBook");
}
TEST_F(ReferenceBookItemTest, GetInfo)
{
    EXPECT_EQ(a->to_string(), "ReferenceBook: Essential Calculus 2nd Edition by James Stewart");
}
TEST_F(ReferenceBookItemTest, GetType2)
{
    EXPECT_EQ(b->get_type(), "ReferenceBook");
}
TEST_F(ReferenceBookItemTest, GetInfo2)
{
    EXPECT_EQ(b->to_string(), "ReferenceBook: Advanced Engineering Mathematics by Peter V. O'Neil");
}