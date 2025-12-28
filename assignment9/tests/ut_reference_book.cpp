#include <gtest/gtest.h>
#include <vector>
#include "../src/reference_book.h"

class ReferenceBookItemTest : public ::testing::Test
{
protected:
    LibraryItem *new_reference_book = ReferenceBook::make_reference_book("Test Title", "Test Author");
    void TearDown() override
    {
        delete new_reference_book;
    };
};

TEST_F(ReferenceBookItemTest, MakeAReferenceBook)
{
    ASSERT_NE(new_reference_book, nullptr);
    EXPECT_EQ(new_reference_book->get_title(), "Test Title");
    EXPECT_EQ(new_reference_book->get_author(), "Test Author");
}
TEST_F(ReferenceBookItemTest, getType)
{
    EXPECT_EQ(new_reference_book->get_type(), "ReferenceBook");
}
TEST_F(ReferenceBookItemTest, exportString)
{
    EXPECT_EQ(new_reference_book->to_string(), "ReferenceBook: Test Title by Test Author");
}
TEST_F(ReferenceBookItemTest, InvalidTitle)
{
    LibraryItem *no_title_book = ReferenceBook::make_reference_book("", "Test Author");
    EXPECT_EQ(no_title_book, nullptr);
}
TEST_F(ReferenceBookItemTest, InvalidAuthor)
{
    LibraryItem *no_author_book = ReferenceBook::make_reference_book("Test Title", "");
    EXPECT_EQ(no_author_book, nullptr);
}