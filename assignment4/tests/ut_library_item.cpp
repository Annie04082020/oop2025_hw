#include <gtest/gtest.h>
#include "../src/library_item.h"
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/reference_book.h"

class LibraryItemTest : public ::testing::Test
{
protected:
    Book a = {5001, "Sherlock Holmes Series", "Arthur Conan Doyle"};
    Book b = {5002, "Harry Potter", "J. K. Rowling"};
    EBook c = {6001, "Signals, Systems, and Transforms fifth edition", "Charles L. Phillips, John M. Parr, Eve A. Riskin"};
    EBook d = {6002, "Power Systems Analysis second edition", "Arthur R.Bergen, Vijay Vittal"};
    ReferenceBook e = {7001, "Essential Calculus 2nd Edition", "James Stewart"};
    ReferenceBook f = {7002, "Advanced Engineering Mathematics", "Peter V. O'Neil"};
};
TEST_F(LibraryItemTest, GetId)
{
    EXPECT_EQ(a.get_unique_id(), 5001);
    EXPECT_EQ(b.get_unique_id(), 5002);
    EXPECT_EQ(c.get_unique_id(), 6001);
    EXPECT_EQ(d.get_unique_id(), 6002);
    EXPECT_EQ(e.get_unique_id(), 7001);
    EXPECT_EQ(f.get_unique_id(), 7002);
}
TEST_F(LibraryItemTest, GetTitle)
{
    EXPECT_EQ(a.get_title(), "Sherlock Holmes Series");
    EXPECT_EQ(b.get_title(), "Harry Potter");
    EXPECT_EQ(c.get_title(), "Signals, Systems, and Transforms fifth edition");
    EXPECT_EQ(d.get_title(), "Power Systems Analysis second edition");
    EXPECT_EQ(e.get_title(), "Essential Calculus 2nd Edition");
    EXPECT_EQ(f.get_title(), "Advanced Engineering Mathematics");
}
TEST_F(LibraryItemTest, GetAuthor)
{
    EXPECT_EQ(a.get_author(), "Arthur Conan Doyle");
    EXPECT_EQ(b.get_author(), "J. K. Rowling");
    EXPECT_EQ(c.get_author(), "Charles L. Phillips, John M. Parr, Eve A. Riskin");
    EXPECT_EQ(d.get_author(), "Arthur R.Bergen, Vijay Vittal");
    EXPECT_EQ(e.get_author(), "James Stewart");
    EXPECT_EQ(f.get_author(), "Peter V. O'Neil");
}
