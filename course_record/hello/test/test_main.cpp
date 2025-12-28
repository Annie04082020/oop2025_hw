#include <gtest/gtest.h>
#include "generate_greeting_test.h"

int main(int argc, char * argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}