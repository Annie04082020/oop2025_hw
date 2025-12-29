#include <gtest/gtest.h>
#include "../src/item.h"
#include "../src/box.h"
#include "../src/cargo.h"
#include "../src/exceptions.h"

class BoxTest : public ::testing::Test
{
protected:

};

TEST_F(BoxTest,makeBox){
    Box *a = Box::make_box(10,100);
    EXPECT_EQ(a->get_weight(),10);
    EXPECT_EQ(a->is_dangerous(),false);
    // delete a;
}