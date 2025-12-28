#include <gtest/gtest.h>
#include "vector_test.h"

TEST(TestSuite, Test) {
    ASSERT_TRUE(true);
}

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}