#include <gtest/gtest.h>
#include "../src/library_item.h"
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/reference_book.h"

class LibraryItemTest : public ::testing::Test
{
protected:
    Book *a = new Book(5001, "Sherlock Holmes Series", "Arthur Conan Doyle");
    Book *b = new Book(5002, "Harry Potter", "J. K. Rowling");
    EBook *c = new EBook(6001, "Signals Systems and Transforms fifth edition", "Charles L. Phillips; John M. Parr; Eve A. Riskin");
    EBook *d = new EBook(6002, "Power Systems Analysis second edition", "Arthur R.Bergen; Vijay Vittal");
    ReferenceBook *e = new ReferenceBook(7001, "Essential Calculus 2nd Edition", "James Stewart");
    ReferenceBook *f = new ReferenceBook(7002, "Advanced Engineering Mathematics", "Peter V. O'Neil");
    void TearDown() override
    {
        delete a;
        delete b;
        delete c;
        delete d;
        delete e;
        delete f;
    };
};
TEST_F(LibraryItemTest, GetId)
{
    EXPECT_EQ(a->get_unique_id(), 5001);
    EXPECT_EQ(b->get_unique_id(), 5002);
    EXPECT_EQ(c->get_unique_id(), 6001);
    EXPECT_EQ(d->get_unique_id(), 6002);
    EXPECT_EQ(e->get_unique_id(), 7001);
    EXPECT_EQ(f->get_unique_id(), 7002);
}
TEST_F(LibraryItemTest, GetTitle)
{
    EXPECT_EQ(a->get_title(), "Sherlock Holmes Series");
    EXPECT_EQ(b->get_title(), "Harry Potter");
    EXPECT_EQ(c->get_title(), "Signals Systems and Transforms fifth edition");
    EXPECT_EQ(d->get_title(), "Power Systems Analysis second edition");
    EXPECT_EQ(e->get_title(), "Essential Calculus 2nd Edition");
    EXPECT_EQ(f->get_title(), "Advanced Engineering Mathematics");
}
TEST_F(LibraryItemTest, GetAuthor)
{
    EXPECT_EQ(a->get_author(), "Arthur Conan Doyle");
    EXPECT_EQ(b->get_author(), "J. K. Rowling");
    EXPECT_EQ(c->get_author(), "Charles L. Phillips; John M. Parr; Eve A. Riskin");
    EXPECT_EQ(d->get_author(), "Arthur R.Bergen; Vijay Vittal");
    EXPECT_EQ(e->get_author(), "James Stewart");
    EXPECT_EQ(f->get_author(), "Peter V. O'Neil");
}
TEST_F(LibraryItemTest, TestPolymorphism)
{
    std::vector<LibraryItem *> items;
    items.push_back(new Book(100, "The Lord of the Rings", "J.R.R. Tolkien"));
    items.push_back(new EBook(200, "Dune", "Frank Herbert"));
    items.push_back(new ReferenceBook(300, "Code Complete", "Steve McConnell"));
    EXPECT_EQ("Book", items[0]->get_type());
    EXPECT_EQ("EBook", items[1]->get_type());
    EXPECT_EQ("ReferenceBook", items[2]->get_type());
    EXPECT_EQ("Book: The Lord of the Rings by J.R.R. Tolkien", items[0]->to_string());
    EXPECT_EQ("EBook: Dune by Frank Herbert", items[1]->to_string());
    EXPECT_EQ("ReferenceBook: Code Complete by Steve McConnell", items[2]->to_string());
    for (LibraryItem *item : items)
    {
        delete item;
    }
}