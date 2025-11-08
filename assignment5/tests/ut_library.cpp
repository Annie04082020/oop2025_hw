#include <gtest/gtest.h>
#include "../src/library_item.h"
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/reference_book.h"
#include "../src/library_management_system.h"

class LibraryTest : public ::testing::Test
{
protected:
    LibraryManagementSystem LibSys;
    std::filesystem::path test_file_path = "test_library_data.txt";
    // 1. **在 SetUp 中使用 new 創建物件 (動態分配)**
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
TEST_F(LibraryTest, AddBookItem)
{
    auto result_before_add = LibSys.search_by_author("Arthur Conan Doyle");
    EXPECT_EQ(result_before_add.size(), 0);
    LibSys.add_item(a);
    auto result_after_add = LibSys.search_by_author("Arthur Conan Doyle");
    EXPECT_EQ(result_after_add.size(), 1);
    EXPECT_EQ(LibSys.get_total_items(), 1);
    EXPECT_EQ(result_after_add[0]->get_author(), "Arthur Conan Doyle");
    EXPECT_EQ(result_after_add[0]->get_title(), "Sherlock Holmes Series");
    EXPECT_EQ(result_after_add[0]->get_unique_id(), 5001);
    EXPECT_EQ(result_after_add[0]->get_type(), "Book");
    EXPECT_EQ(result_after_add[0]->to_string(), "Book: Sherlock Holmes Series by Arthur Conan Doyle");
    LibSys.clear();
}
TEST_F(LibraryTest, AddEBookItem)
{
    auto result_before_add = LibSys.search_by_author("Arthur R.Bergen; Vijay Vittal");
    EXPECT_EQ(result_before_add.size(), 0);
    LibSys.add_item(d);
    auto result_after_add = LibSys.search_by_author("Arthur R.Bergen; Vijay Vittal");
    EXPECT_EQ(result_after_add.size(), 1);
    EXPECT_EQ(LibSys.get_total_items(), 1);
    EXPECT_EQ(result_after_add[0]->get_author(), "Arthur R.Bergen; Vijay Vittal");
    EXPECT_EQ(result_after_add[0]->get_title(), "Power Systems Analysis second edition");
    EXPECT_EQ(result_after_add[0]->get_unique_id(), 6002);
    EXPECT_EQ(result_after_add[0]->get_type(), "EBook");
    EXPECT_EQ(result_after_add[0]->to_string(), "EBook: Power Systems Analysis second edition by Arthur R.Bergen; Vijay Vittal");
    LibSys.clear();
}
TEST_F(LibraryTest, AddReferenceBookItem)
{
    auto result_before_add = LibSys.search_by_author("James Stewart");
    EXPECT_EQ(result_before_add.size(), 0);
    LibSys.add_item(e);
    auto result_after_add = LibSys.search_by_author("James Stewart");
    EXPECT_EQ(result_after_add.size(), 1);
    EXPECT_EQ(LibSys.get_total_items(), 1);
    EXPECT_EQ(result_after_add[0]->get_author(), "James Stewart");
    EXPECT_EQ(result_after_add[0]->get_title(), "Essential Calculus 2nd Edition");
    EXPECT_EQ(result_after_add[0]->get_unique_id(), 7001);
    EXPECT_EQ(result_after_add[0]->get_type(), "ReferenceBook");
    EXPECT_EQ(result_after_add[0]->to_string(), "ReferenceBook: Essential Calculus 2nd Edition by James Stewart");
    LibSys.clear();
}
TEST_F(LibraryTest, SearchByTitle)
{
    LibSys.add_item(a);
    LibSys.add_item(b);
    LibSys.add_item(c);
    LibSys.add_item(d);
    LibSys.add_item(e);
    LibSys.add_item(f);

    auto result = LibSys.search_by_title("Harry Potter");
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->get_author(), "J. K. Rowling");
    EXPECT_EQ(result[0]->get_unique_id(), 5002);
    EXPECT_EQ(result[0]->get_type(), "Book");
    EXPECT_EQ(result[0]->to_string(), "Book: Harry Potter by J. K. Rowling");
    LibSys.clear();
}
TEST_F(LibraryTest, SearchByAuthor)
{
    LibSys.add_item(a);
    LibSys.add_item(b);
    LibSys.add_item(c);
    LibSys.add_item(d);
    LibSys.add_item(e);
    LibSys.add_item(f);
    auto result = LibSys.search_by_author("Charles L. Phillips; John M. Parr; Eve A. Riskin");
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->get_title(), "Signals Systems and Transforms fifth edition");
    EXPECT_EQ(result[0]->get_unique_id(), 6001);
    EXPECT_EQ(result[0]->get_type(), "EBook");
    EXPECT_EQ(result[0]->to_string(), "EBook: Signals Systems and Transforms fifth edition by Charles L. Phillips; John M. Parr; Eve A. Riskin");
    LibSys.clear();
}
TEST_F(LibraryTest, TotalItems)
{
    EXPECT_EQ(LibSys.get_total_items(), 0);
    LibSys.add_item(a);
    EXPECT_EQ(LibSys.get_total_items(), 1);
    LibSys.add_item(b);
    EXPECT_EQ(LibSys.get_total_items(), 2);
    LibSys.add_item(c);
    EXPECT_EQ(LibSys.get_total_items(), 3);
    LibSys.add_item(d);
    EXPECT_EQ(LibSys.get_total_items(), 4);
    LibSys.add_item(e);
    EXPECT_EQ(LibSys.get_total_items(), 5);
    LibSys.add_item(f);
    EXPECT_EQ(LibSys.get_total_items(), 6);
    LibSys.clear();
    EXPECT_EQ(LibSys.get_total_items(), 0);
}
TEST_F(LibraryTest, SearchNonExistentItem)
{
    LibSys.add_item(a);
    LibSys.add_item(b);
    auto result_by_title = LibSys.search_by_title("Non Existent Title");
    EXPECT_EQ(result_by_title.size(), 0);
    auto result_by_author = LibSys.search_by_author("Non Existent Author");
    EXPECT_EQ(result_by_author.size(), 0);
    LibSys.clear();
}
TEST_F(LibraryTest, DynamicObjectMethod)
{
    Book *book_ptr = new Book(8001, "Dynamic Book", "Dynamic Author");
    LibSys.add_item(book_ptr);
    auto result = LibSys.search_by_title("Dynamic Book");
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0]->get_type(), "Book");
    EXPECT_EQ(result[0]->to_string(), "Book: Dynamic Book by Dynamic Author");
    LibSys.add_item(new EBook(8002, "Dynamic EBook", "Dynamic EAuthor"));
    auto result_ebook = LibSys.search_by_title("Dynamic EBook");
    EXPECT_EQ(result_ebook.size(), 1);
    EXPECT_EQ(result_ebook[0]->get_type(), "EBook");
    EXPECT_EQ(result_ebook[0]->to_string(), "EBook: Dynamic EBook by Dynamic EAuthor");
    LibSys.clear();
}
TEST_F(LibraryTest, ClearLibrary)
{
    LibSys.add_item(a);
    LibSys.add_item(b);
    LibSys.add_item(c);
    EXPECT_EQ(LibSys.get_total_items(), 3);
    LibSys.clear();
    EXPECT_EQ(LibSys.get_total_items(), 0);
    auto result = LibSys.search_by_title("Sherlock Holmes Series");
    EXPECT_EQ(result.size(), 0);
}
TEST_F(LibraryTest, RemoveItem)
{
    LibSys.add_item(a);
    LibSys.add_item(b);
    LibSys.add_item(c);
    EXPECT_EQ(LibSys.get_total_items(), 3);
    bool removed = LibSys.remove_item(5002); // Remove "Harry Potter"
    EXPECT_TRUE(removed);
    EXPECT_EQ(LibSys.get_total_items(), 2);
    auto result = LibSys.search_by_title("Harry Potter");
    EXPECT_EQ(result.size(), 0);
    // Attempt to remove a non-existent item
    bool removed_non_existent = LibSys.remove_item(9999);
    EXPECT_FALSE(removed_non_existent);
    EXPECT_EQ(LibSys.get_total_items(), 2);
    LibSys.clear();
}