#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "../src/inner_product.h"

TEST(InnerProductTest, NormalCaseTwoDimension) {
    // 3A
    // Arrange: prepare data
    double u[] = {1.0, 1.0};
    double v[] = {0.0, 1.0};
    int u_dim = 2;
    int v_dim = 2;
    double expected_result = 1.0;
    // Act: call the function with testing
    double actual_result = inner_product(u, v, u_dim, v_dim);
    // Assert: check the result
    EXPECT_EQ(expected_result, actual_result);
}
TEST(InnerProductTest, NormalCaseZeroDimension) {
    // 3A
    // Arrange: prepare data
    double u[] = {};
    double v[] = {};
    int u_dim = 0;
    int v_dim = 0;
    double expected_result = 0.0;
    // Act: call the function with testing
    double actual_result = inner_product(u, v, u_dim, v_dim);
    // Assert: check the result
    EXPECT_EQ(expected_result, actual_result);
}
TEST(InnerProductTest, ExceptionCaseUnequalDimension) {
    // 3A
    // Arrange: prepare data
    double u[] = {1.0, 1.0};
    double v[] = {0.0, 1.0, 2.0};
    int u_dim = 2;
    int v_dim = 3;
    // Act: call the function with testing
    double actual_result = inner_product(u, v, u_dim, v_dim);
    // Assert: check the result
    EXPECT_TRUE(std::isnan(actual_result));
}

TEST(InnerProductTest, NormalCaseTwoArrays) {
    // 3A
    // Arrange: prepare data
    std::vector<double> u = {1.0, 1.0};
    std::vector<double> v = {0.0, 1.0};
    
    // Act: call the function with testing
    double actual_result = inner_product(u, v);
    // Assert: check the result
    double expected_result = 1.0;
    EXPECT_EQ(expected_result, actual_result);
}