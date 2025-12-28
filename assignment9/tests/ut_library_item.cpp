#include <gtest/gtest.h>
#include <vector>
#include "../src/library_item.h"
#include "../src/reference_book.h"
#include "../src/book.h"

class LibraryItemTest : public ::testing::Test
{
protected:
    LibraryItem *new_book = Book::make_book("Test Book Title", "Test Book Author");
    LibraryItem *new_reference_book = ReferenceBook::make_reference_book("Test Reference Book Title", "Test Reference Book Author");
    void TearDown() override
    {
        delete new_reference_book;
        delete new_book;
    };
};
TEST_F(LibraryItemTest, makeLibraryItems)
{
    ASSERT_NE(new_book, nullptr);
    ASSERT_NE(new_reference_book, nullptr);
    EXPECT_EQ(new_book->get_title(), "Test Book Title");
    EXPECT_EQ(new_reference_book->get_title(), "Test Reference Book Title");
    EXPECT_EQ(new_book->get_author(), "Test Book Author");
    EXPECT_EQ(new_reference_book->get_author(), "Test Reference Book Author");
}
TEST_F(LibraryItemTest, getType)
{
    EXPECT_EQ(new_reference_book->get_type(), "ReferenceBook");
    EXPECT_EQ(new_book->get_type(), "Book");
}
TEST_F(LibraryItemTest, getToken)
{
    LibraryItem::Ticket ticket1(12345);
    LibraryItem::Ticket ticket2(67890);

    EXPECT_EQ(ticket1.get_token(), 12345);
    EXPECT_EQ(ticket2.get_token(), 67890);
}