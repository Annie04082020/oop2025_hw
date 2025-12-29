#include <gtest/gtest.h>
#include "../src/item.h"
#include "../src/box.h"
#include "../src/cargo.h"
#include "../src/exceptions.h"

class BoxTest : public ::testing::Test
{
protected:
};

TEST_F(BoxTest, makeEmptyBox)
{
    Box *a = Box::make_box(10, 100);
    EXPECT_EQ(a->get_weight(), 10);
    EXPECT_EQ(a->is_dangerous(), false);
    delete a;
}
TEST_F(BoxTest, makeBoxWithItem)
{
    Box *a = Box::make_box(10, 100);
    Item *item1 = Item::make_item(50, true);
    a->add(item1);
    EXPECT_EQ(a->get_weight(), 60);
    EXPECT_NE(a->get_weight(), 10);
    EXPECT_EQ(a->is_dangerous(), true);
    delete a;
}
TEST_F(BoxTest, BoxOverWeight)
{
    Box *a = Box::make_box(10, 30);
    Item *item1 = Item::make_item(50, true);
    EXPECT_THROW(a->add(item1), WeightLimitExceeded);
    EXPECT_EQ(a->count_total_items(), 0);
    delete a;
    delete item1;
}
TEST_F(BoxTest, BoxInsertingBox)
{
    Box *big = Box::make_box(10, 100);
    Box *small = Box::make_box(10, 50);
    Item *item1 = Item::make_item(10, true);
    EXPECT_NO_THROW(
        small->add(item1);
        big->add(small););
    EXPECT_EQ(small->count_total_items(), 1);
    EXPECT_EQ(big->count_total_items(), 1);
    EXPECT_EQ(small->is_dangerous(), true);
    EXPECT_EQ(big->is_dangerous(), true);
    EXPECT_EQ(small->get_weight(), 20);
    EXPECT_EQ(big->get_weight(), 30);
    delete big;
}
TEST_F(BoxTest, BoxSortItemOnly)
{
    Box *big = Box::make_box(1, 151);
    Item *item50 = Item::make_item(50, true);
    Item *item40 = Item::make_item(40, true);
    Item *item30 = Item::make_item(30, true);
    Item *item20 = Item::make_item(20, true);
    Item *item10 = Item::make_item(10, true);
    big->add(item10);
    big->add(item40);
    big->add(item30);
    big->add(item20);
    big->add(item50);
    EXPECT_EQ(big->get_weight(), 151);
    EXPECT_EQ(big->count_total_items(), 5);
    const std::vector<Cargo *> &contents = big->get_contents();
    EXPECT_EQ(contents[0]->get_weight(), 10);
    EXPECT_EQ(contents[1]->get_weight(), 40);
    EXPECT_EQ(contents[2]->get_weight(), 30);
    EXPECT_EQ(contents[3]->get_weight(), 20);
    EXPECT_EQ(contents[4]->get_weight(), 50);
    big->sort_contents();
    EXPECT_EQ(contents[0]->get_weight(), 50);
    EXPECT_EQ(contents[1]->get_weight(), 40);
    EXPECT_EQ(contents[2]->get_weight(), 30);
    EXPECT_EQ(contents[3]->get_weight(), 20);
    EXPECT_EQ(contents[4]->get_weight(), 10);
    delete big;
}