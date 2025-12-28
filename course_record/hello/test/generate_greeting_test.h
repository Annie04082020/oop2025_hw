#include <gtest/gtest.h>
#include "../src/generate_greeting.h"

TEST(HelloSuite, JoeTest) {
    ASSERT_EQ("Hello, Joe, I hope you’re having a wonderful day!", generateGreeting("Joe"));
}