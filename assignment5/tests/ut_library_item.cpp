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
TEST_F(LibraryItemTest, TestPolymorphism)
{
    // 1. 建立基底類別指標 (LibraryItem*) 的向量，用於儲存子類別物件
    std::vector<LibraryItem *> items;
    // 2. 使用 new 動態創建子類別物件，並將其指標向上轉型存入基底類別向量
    // (確保在測試結束時使用 delete 清理記憶體)
    // Book 向上轉型
    items.push_back(new Book(100, "The Lord of the Rings", "J.R.R. Tolkien"));
    // EBook 向上轉型
    items.push_back(new EBook(200, "Dune", "Frank Herbert"));
    // ReferenceBook 向上轉型
    items.push_back(new ReferenceBook(300, "Code Complete", "Steve McConnell"));
    // 3. 透過基底類別指標 (LibraryItem*) 呼叫虛擬函式
    // 這確保了多型機制能正確地呼叫到子類別覆寫 (override) 的版本
    EXPECT_EQ("Book", items[0]->get_type());
    EXPECT_EQ("EBook", items[1]->get_type());
    EXPECT_EQ("ReferenceBook", items[2]->get_type());
    EXPECT_EQ("Book: The Lord of the Rings by J.R.R. Tolkien", items[0]->to_string());
    EXPECT_EQ("EBook: Dune by Frank Herbert", items[1]->to_string());
    EXPECT_EQ("ReferenceBook: Code Complete by Steve McConnell", items[2]->to_string());
    // 4. 清理記憶體 (釋放動態分配的物件)
    for (LibraryItem *item : items)
    {
        delete item;
    }
}