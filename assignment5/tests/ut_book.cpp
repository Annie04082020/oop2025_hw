#include <gtest/gtest.h>
#include "../src/book.h"
#include "../src/library_item.h"

class BookItemTest : public ::testing::Test
{
protected:
    Book *a = new Book{5001, "Sherlock Holmes Series", "Arthur Conan Doyle"};
    Book *b = new Book{5002, "Harry Potter", "J. K. Rowling"};
    void TearDown() override
    {
        delete a;
        delete b;
    };
};

TEST_F(BookItemTest, GetType)
{
    EXPECT_EQ(a->get_type(), "Book");
}
TEST_F(BookItemTest, GetInfo)
{
    EXPECT_EQ(a->to_string(), "Book: Sherlock Holmes Series by Arthur Conan Doyle");
}
TEST_F(BookItemTest, GetType2)
{
    EXPECT_EQ(b->get_type(), "Book");
}
TEST_F(BookItemTest, GetInfo2)
{
    EXPECT_EQ(b->to_string(), "Book: Harry Potter by J. K. Rowling");
}