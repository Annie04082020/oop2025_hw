#include <gtest/gtest.h>
#include "../src/library_management_system.h"
#include "../src/library_item.h"
#include "../src/book.h"
#include "../src/ebook.h"
#include "../src/reference_book.h"
#include <filesystem>
#include <stdexcept>
#include <fstream>
class FileIOTest : public ::testing::Test
{
protected:
    LibraryManagementSystem LibSys;
    std::filesystem::path test_file_path = "test_library_data.txt";
    void SetUp() override
    {
        // 1. **在 SetUp 中使用 new 創建物件 (動態分配)**
        Book *a = new Book(5001, "Sherlock Holmes Series", "Arthur Conan Doyle");
        Book *b = new Book(5002, "Harry Potter", "J. K. Rowling");
        EBook *c = new EBook(6001, "Signals Systems and Transforms fifth edition", "Charles L. Phillips; John M. Parr; Eve A. Riskin");
        EBook *d = new EBook(6002, "Power Systems Analysis second edition", "Arthur R.Bergen; Vijay Vittal");
        ReferenceBook *e = new ReferenceBook(7001, "Essential Calculus 2nd Edition", "James Stewart");
        ReferenceBook *f = new ReferenceBook(7002, "Advanced Engineering Mathematics", "Peter V. O'Neil");
        // 2. 將 new 出來的指標加入 LibSys
        LibSys.add_item(a);
        LibSys.add_item(b);
        LibSys.add_item(c);
        LibSys.add_item(d);
        LibSys.add_item(e);
        LibSys.add_item(f);
    }
    void TearDown() override
    {
        // 確保在每次測試後，測試檔案都被刪除
        if (std::filesystem::exists(test_file_path))
        {
            std::filesystem::remove(test_file_path);
        }
        LibSys.clear();
    }
};
TEST_F(FileIOTest, SaveAndLoadFromFile)
{
    // Save to file
    LibSys.save_to_file(test_file_path);
    // Clear the current library
    LibSys.clear();
    EXPECT_EQ(LibSys.get_total_items(), 0);
    // Load from file
    LibSys.load_from_file(test_file_path);
    // Verify the total number of items after loading
    EXPECT_EQ(LibSys.get_total_items(), 6);
    // Clean up the test file
    std::filesystem::remove(test_file_path);
};
TEST_F(FileIOTest, LoadFromNonExistentFile)
{
    // Attempt to load from a non-existent file
    std::filesystem::path non_existent_file = "non_existent_file.txt";
    EXPECT_THROW(
        LibSys.load_from_file(non_existent_file), std::runtime_error);
    // Verify that no items were loaded
    EXPECT_EQ(LibSys.get_total_items(), 0);
}
TEST_F(FileIOTest, LoadFromMalformedFile)
{
    // Create a malformed test file
    std::ofstream malformed_file(test_file_path);
    malformed_file << "5001,Book,Sherlock Holmes Series\n";                                                                         // Missing author
    malformed_file << "6001,EBook,Signals Systems and Transforms fifth edition,Charles L. Phillips; John M. Parr; Eve A. Riskin\n"; // Correct line
    malformed_file << "7001,ReferenceBook,Essential Calculus 2nd Edition,James Stewart,ExtraField\n";                               // Extra field
    malformed_file << "InvalidLineWithoutCommas\n";                                                                                 // Completely invalid line
    malformed_file.close();
    // Attempt to load from the malformed file
    EXPECT_NO_THROW(
        LibSys.load_from_file(test_file_path));
    // Verify that only the correctly formed line was loaded
    EXPECT_EQ(LibSys.get_total_items(), 1);
    // Clean up the test file
    std::filesystem::remove(test_file_path);
};