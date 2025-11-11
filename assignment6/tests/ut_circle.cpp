#include "gtest/gtest.h"
#include "../src/circle.h"
#include "../src/point.h"
#include <cmath>
#include <string>
#define _USE_MATH_DEFINES

class CircleFunctionTest : public ::testing::Test
{
protected:
    Point center = {0.0, 0.0};
    double radius_normal = 5.0;
    double radius_extreme_big = 5e9;
    double radius_extreme_small = 5e-6;
};
TEST_F(CircleFunctionTest, NormalCirclePerimeter)
{
    Circle c = {center, radius_normal};
    double perimeter = c.perimeter();
    double ans = 10 * M_PI;
    EXPECT_NEAR(perimeter, ans, 1e-6);
}
TEST_F(CircleFunctionTest, NormalCircleArea)
{
    Circle c = {center, radius_normal};
    double area = c.area();
    double ans = M_PI * 25;
    EXPECT_NEAR(area, ans, 1e-6);
}
TEST_F(CircleFunctionTest, ExtremeBigCirclePerimeter)
{
    Circle c = {center, radius_extreme_big};
    double perimeter = c.perimeter();
    double ans = M_PI * 10e9;
    EXPECT_NEAR(perimeter, ans, 1e-6);
}
TEST_F(CircleFunctionTest, ExtremeBigCircleArea)
{
    Circle c = {center, radius_extreme_big};
    double area = c.area();
    double ans = M_PI * 25e18;
    EXPECT_NEAR(area, ans, 1e-6);
}
TEST_F(CircleFunctionTest, ExtremeSmallCirclePerimeter)
{
    Circle c = {center, radius_extreme_small};
    double perimeter = c.perimeter();
    double ans = M_PI * 10e-6;
    EXPECT_NEAR(perimeter, ans, 1e-6);
}
TEST_F(CircleFunctionTest, ExtremeSmallCircleArea)
{
    Circle c = {center, radius_extreme_small};
    double area = c.area();
    double ans = M_PI * 25e-12;
    EXPECT_NEAR(area, ans, 1e-6);
}
TEST_F(CircleFunctionTest, ZeroRadiusCirclePerimeter)
{
    Circle c = {center, 0.0};
    double perimeter = c.perimeter();
    double ans = 0.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(CircleFunctionTest, ZeroRadiusCircleArea)
{
    Circle c = {center, 0.0};
    double area = c.area();
    double ans = 0.0;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(CircleFunctionTest, ToStringTest)
{
    Circle c = {center, radius_normal};
    Circle c2 = {center, radius_extreme_big};
    Circle c3 = {center, radius_extreme_small};
    std::string str = c.to_string();
    std::string str2 = c2.to_string();
    std::string str3 = c3.to_string();
    EXPECT_EQ(str, "Circle");
    EXPECT_EQ(str2, "Circle");
    EXPECT_EQ(str3, "Circle");
}