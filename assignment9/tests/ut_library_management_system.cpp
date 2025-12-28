#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../src/library_management_system.h"
#include "../src/library_item.h"
#include "../src/book.h"
#include "../src/reference_book.h"

class LibraryManagementSystemTest : public ::testing::Test
{
protected:
    LibraryManagementSystem sys;

    void TearDown() override
    {
        sys.clear();
    }
};

// Purpose: Verify the system starts with zero items
TEST_F(LibraryManagementSystemTest, VerifySystemInitialization)
{
    EXPECT_EQ(sys.get_total_items(), 0);
    EXPECT_EQ(sys.get_available_items(), 0);
}

// Purpose: Verify adding items increases count and assigns tokens
TEST_F(LibraryManagementSystemTest, AddBooksAndVerifyTokens)
{
    auto t1 = sys.add_item(Book::make_book("B1", "A1"));
    auto t2 = sys.add_item(ReferenceBook::make_reference_book("R1", "A2"));

    EXPECT_EQ(t1.get_token(), 1);
    EXPECT_EQ(t2.get_token(), 2);
    EXPECT_NE(t1.get_token(), t2.get_token());
    EXPECT_EQ(sys.get_total_items(), 2);
}

// Purpose: Verify adding a nullptr returns an invalid ticket
TEST_F(LibraryManagementSystemTest, AddNullptrReturnsInvalid)
{
    auto ticket = sys.add_item(nullptr);
    EXPECT_EQ(ticket.get_token(), -1);
    EXPECT_EQ(sys.get_total_items(), 0);
}

// Purpose: Verify basic removal functionality
TEST_F(LibraryManagementSystemTest, RemoveItemSuccess)
{
    auto t1 = sys.add_item(Book::make_book("B1", "A1"));
    EXPECT_EQ(sys.get_total_items(), 1);

    EXPECT_TRUE(sys.remove_item(t1));
    EXPECT_EQ(sys.get_total_items(), 0);
}

// Purpose: Verify removing from an empty library fails
TEST_F(LibraryManagementSystemTest, RemoveFromEmptySystem)
{
    LibraryItem::Ticket t(1);
    EXPECT_FALSE(sys.remove_item(t));
}

// Purpose: Verify removing a non-existent token fails
TEST_F(LibraryManagementSystemTest, RemoveNonExistentItem)
{
    sys.add_item(Book::make_book("B1", "A1"));
    LibraryItem::Ticket fake(999);
    EXPECT_FALSE(sys.remove_item(fake));
}

// Purpose: Verify removing all items sequentially works
TEST_F(LibraryManagementSystemTest, RemoveAllItemsSequentially)
{
    auto t1 = sys.add_item(Book::make_book("B1", "A1"));
    auto t2 = sys.add_item(Book::make_book("B2", "A2"));

    EXPECT_TRUE(sys.remove_item(t1));
    EXPECT_TRUE(sys.remove_item(t2));
    EXPECT_EQ(sys.get_total_items(), 0);
}

// Purpose: Verify adding then removing using ticket flow
TEST_F(LibraryManagementSystemTest, AddAndRemoveUsingTickets)
{
    auto t = sys.add_item(Book::make_book("T", "A"));
    EXPECT_EQ(t.get_token(), 1);
    EXPECT_TRUE(sys.remove_item(t));
}

// Purpose: Verify ticket property retrieval
TEST_F(LibraryManagementSystemTest, VerifyTicketProperties)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    long id = t.get_token();
    EXPECT_GT(id, 0);
}

// Purpose: Verify operations with an invalid ticket
TEST_F(LibraryManagementSystemTest, OperationsWithInvalidTicket)
{
    LibraryItem::Ticket invalid(-1);
    EXPECT_FALSE(sys.remove_item(invalid));
    EXPECT_FALSE(sys.checkout(invalid));
    EXPECT_FALSE(sys.return_item(invalid));
    EXPECT_FALSE(sys.is_available(invalid));
}

// Purpose: Verify new items get new IDs even after old ones are removed
TEST_F(LibraryManagementSystemTest, TicketIdIncrementAfterRemoval)
{
    auto t1 = sys.add_item(Book::make_book("B1", "A1"));
    sys.remove_item(t1);

    auto t2 = sys.add_item(Book::make_book("B2", "A2"));
    EXPECT_EQ(t2.get_token(), 2);
}

// Purpose: Verify basic checkout functionality
TEST_F(LibraryManagementSystemTest, CheckoutItemSuccess)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    EXPECT_TRUE(sys.checkout(t));
    EXPECT_FALSE(sys.is_available(t));
}

// Purpose: Verify checking out an already checked out item fails
TEST_F(LibraryManagementSystemTest, CheckoutAlreadyBorrowedItem)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    sys.checkout(t);
    EXPECT_FALSE(sys.checkout(t));
}

// Purpose: Verify checkout fails with invalid ticket
TEST_F(LibraryManagementSystemTest, CheckoutWithInvalidTicket)
{
    LibraryItem::Ticket t(-1);
    EXPECT_FALSE(sys.checkout(t));
}

// Purpose: Verify checkout works for multiple distinct items
TEST_F(LibraryManagementSystemTest, CheckoutMultipleUniqueItems)
{
    auto t1 = sys.add_item(Book::make_book("B1", "A1"));
    auto t2 = sys.add_item(Book::make_book("B2", "A2"));

    EXPECT_TRUE(sys.checkout(t1));
    EXPECT_TRUE(sys.checkout(t2));
    EXPECT_FALSE(sys.is_available(t1));
    EXPECT_FALSE(sys.is_available(t2));
}

// Purpose: Verify basic return functionality
TEST_F(LibraryManagementSystemTest, ReturnItemSuccess)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    sys.checkout(t);
    EXPECT_TRUE(sys.return_item(t));
    EXPECT_TRUE(sys.is_available(t));
}

// Purpose: Verify return fails if item was not checked out
TEST_F(LibraryManagementSystemTest, ReturnItemNotBorrowed)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    EXPECT_FALSE(sys.return_item(t));
}

// Purpose: Verify return fails with invalid ticket
TEST_F(LibraryManagementSystemTest, ReturnWithInvalidTicket)
{
    LibraryItem::Ticket t(-1);
    EXPECT_FALSE(sys.return_item(t));
}

// Purpose: Verify is_available logic for basic item
TEST_F(LibraryManagementSystemTest, CheckAvailabilityStatus)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    EXPECT_TRUE(sys.is_available(t));
    sys.checkout(t);
    EXPECT_FALSE(sys.is_available(t));
}

// Purpose: Verify is_available returns false for invalid ticket
TEST_F(LibraryManagementSystemTest, CheckAvailabilityInvalidTicket)
{
    LibraryItem::Ticket t(-1);
    EXPECT_FALSE(sys.is_available(t));
}

// Purpose: Verify is_available returns false for removed item
TEST_F(LibraryManagementSystemTest, CheckAvailabilityRemovedItem)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    sys.remove_item(t);
    EXPECT_FALSE(sys.is_available(t));
}

// Purpose: Verify checked out item cannot be removed
TEST_F(LibraryManagementSystemTest, RemoveBorrowedItemFailure)
{
    auto t = sys.add_item(Book::make_book("B", "A"));
    sys.checkout(t);
    EXPECT_FALSE(sys.remove_item(t));
    EXPECT_EQ(sys.get_total_items(), 1);
}

// Purpose: Verify available count is zero for empty library
TEST_F(LibraryManagementSystemTest, CountItemsInEmptySystem)
{
    EXPECT_EQ(sys.get_available_items(), 0);
}

// Purpose: Verify available count equals total when nothing borrowed
TEST_F(LibraryManagementSystemTest, CountItemsAllAvailable)
{
    sys.add_item(Book::make_book("B1", "A1"));
    sys.add_item(Book::make_book("B2", "A2"));
    EXPECT_EQ(sys.get_available_items(), 2);
}

// Purpose: Verify available count decreases after checkout
TEST_F(LibraryManagementSystemTest, CountItemsAfterCheckout)
{
    auto t = sys.add_item(Book::make_book("B1", "A1"));
    sys.add_item(Book::make_book("B2", "A2"));

    sys.checkout(t);
    EXPECT_EQ(sys.get_available_items(), 1);
}

// Purpose: Verify available count increases after return
TEST_F(LibraryManagementSystemTest, CountItemsAfterReturn)
{
    auto t = sys.add_item(Book::make_book("B1", "A1"));
    sys.checkout(t);
    EXPECT_EQ(sys.get_available_items(), 0);

    sys.return_item(t);
    EXPECT_EQ(sys.get_available_items(), 1);
}

// Purpose: Verify available count decreases after removal
TEST_F(LibraryManagementSystemTest, CountItemsAfterRemoval)
{
    auto t = sys.add_item(Book::make_book("B1", "A1"));
    sys.add_item(Book::make_book("B2", "A2"));

    sys.remove_item(t);
    EXPECT_EQ(sys.get_available_items(), 1);
}