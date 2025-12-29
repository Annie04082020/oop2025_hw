#include <gtest/gtest.h>
#include "../src/item.h"
#include "../src/cargo.h"
#include "../src/exceptions.h"

class ItemTest : public ::testing::Test
{
protected:
};

TEST_F(ItemTest, makeItem)
{
    Item *a = Item::make_item(50, false);
    EXPECT_EQ(a->get_weight(), 50);
    EXPECT_EQ(a->is_dangerous(), false);
    delete a;
}
TEST_F(ItemTest, makeInvalidItem)
{
    Item *a = Item::make_item(-10, false);
    Item *b = Item::make_item(-5, false);
    EXPECT_EQ(a, nullptr);
    EXPECT_EQ(b, nullptr);
    delete a;
    delete b;
}
TEST_F(ItemTest, add)
{
    Item *a = Item::make_item(50, false);
    Item *b = Item::make_item(100, true);
    EXPECT_THROW(a->add(b), UnsupportedOperationException);
    delete a;
    delete b;
}
TEST_F(ItemTest, getWeight)
{
    Item *a = Item::make_item(50, false);
    Item *b = Item::make_item(100, true);
    Item *c = Item::make_item(150, false);
    EXPECT_EQ(a->get_weight(), 50);
    EXPECT_EQ(b->get_weight(), 100);
    EXPECT_EQ(c->get_weight(), 150);
    delete a;
    delete b;
    delete c;
}