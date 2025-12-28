#include <gtest/gtest.h>
#include <vector>
#include "../src/book.h"
#include "../src/library_item.h"

class BookItemTest : public ::testing::Test
{
protected:
    LibraryItem *new_book = Book::make_book("Test Title", "Test Author");
    void TearDown() override
    {
        delete new_book;
    };
};

TEST_F(BookItemTest, MakeABook)
{
    ASSERT_NE(new_book, nullptr);
    EXPECT_EQ(new_book->get_title(), "Test Title");
    EXPECT_EQ(new_book->get_author(), "Test Author");
}
TEST_F(BookItemTest, getType)
{
    EXPECT_EQ(new_book->get_type(), "Book");
}
TEST_F(BookItemTest, exportString)
{
    EXPECT_EQ(new_book->to_string(), "Book: Test Title by Test Author");
}
TEST_F(BookItemTest, InvalidTitle)
{
    LibraryItem *no_title_book = Book::make_book("", "Test Author");
    EXPECT_EQ(no_title_book, nullptr);
}
TEST_F(BookItemTest, InvalidAuthor)
{
    LibraryItem *no_author_book = Book::make_book("Test Title", "");
    EXPECT_EQ(no_author_book, nullptr);
}
