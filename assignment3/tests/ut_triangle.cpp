#include <gtest/gtest.h>
#include <cmath>
#include "../src/point.h"
#include "../src/triangle.h"
class TriangleFunctionTest : public ::testing::Test
{
protected:
    // Unit Triangle
    Point p = {0.0, 0.0};
    Point q = {1.0, 0.0};
    Point r = {0.0, 1.0};
    // Equilateral Triangle
    Point p_eq = {0.0, 0.0};
    Point q_eq = {1.0, 0.0};
    Point r_eq = {0.5, std::sqrt(3) / 2};
    // Extreme big Equilateral Triangle
    Point p_exb_eq = {0.0, 0.0};
    Point q_exb_eq = {1e9, 0.0};
    Point r_exb_eq = {0.5 * 1e9, 1e9 * std::sqrt(3) / 2};
    // Extreme small Equilateral Triangle
    Point p_exs_eq = {0.0, 0.0};
    Point q_exs_eq = {1e-6, 0.0};
    Point r_exs_eq = {0.5 * 1e-6, 1e-6 * std::sqrt(3) / 2};
    // Right Triangle
    Point p_rt = {0.0, 0.0};
    Point q_rt = {3.0, 0.0};
    Point r_rt = {0.0, 4.0};
    // Extreme big Right Triangle
    Point p_exb_rt = {0.0, 0.0};
    Point q_exb_rt = {3 * 1e9, 0.0};
    Point r_exb_rt = {0.0, 4 * 1e9};
    // Extreme small Right Triangle
    Point p_exs_rt = {0.0, 0.0};
    Point q_exs_rt = {3 * 1e-6, 0.0};
    Point r_exs_rt = {0.0, 4 * 1e-6};
    // Not a Triangle (Collinear)
    Point p_col = {0.0, 0.0};
    Point q_col = {1.0, 0.0};
    Point r_col = {2.0, 0.0};
};
TEST_F(TriangleFunctionTest, UnitTrianglePerimeter)
{
    Triangle a = {p, q, r};
    double perimeter = a.perimeter();
    double ans = 2 + std::sqrt(2);
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, UnitTriangleEquilateral)
{
    Triangle a = {p, q, r};
    EXPECT_FALSE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, UnitTriangleRightorNot)
{
    Triangle a = {p, q, r};
    EXPECT_TRUE(a.is_right());
}
TEST_F(TriangleFunctionTest, EqualTrianglePerimeter)
{
    Triangle a = {p_eq, q_eq, r_eq};
    double perimeter = a.perimeter();
    double ans = 3;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, EqualTriangleEquilateral)
{
    Triangle a = {p_eq, q_eq, r_eq};
    EXPECT_TRUE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, EqualTriangleRightorNot)
{
    Triangle a = {p_eq, q_eq, r_eq};
    EXPECT_FALSE(a.is_right());
}
TEST_F(TriangleFunctionTest, ExtremeBigEqualTrianglePerimeter)
{
    Triangle a = {p_exb_eq, q_exb_eq, r_exb_eq};
    double perimeter = a.perimeter();
    double ans = 3 * 1e9;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigEqualTriangleEquilateral)
{
    Triangle a = {p_exb_eq, q_exb_eq, r_exb_eq};
    EXPECT_TRUE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, ExtremeBigEqualTriangleRightorNot)
{
    Triangle a = {p_exb_eq, q_exb_eq, r_exb_eq};
    EXPECT_FALSE(a.is_right());
}
TEST_F(TriangleFunctionTest, ExtremeSmallEqualTrianglePerimeter)
{
    Triangle a = {p_exs_eq, q_exs_eq, r_exs_eq};
    double perimeter = a.perimeter();
    double ans = 3 * 1e-6;
    EXPECT_NEAR(perimeter, ans, 1e-12);
}
TEST_F(TriangleFunctionTest, ExtremeSmallEqualTriangleEquilateral)
{
    Triangle a = {p_exs_eq, q_exs_eq, r_exs_eq};
    EXPECT_TRUE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, ExtremeSmallEqualTriangleRightorNot)
{
    Triangle a = {p_exs_eq, q_exs_eq, r_exs_eq};
    EXPECT_FALSE(a.is_right());
}

TEST_F(TriangleFunctionTest, RightTrianglePerimeter)
{
    Triangle a = {p_rt, q_rt, r_rt};
    double perimeter = a.perimeter();
    double ans = 12;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, RightTriangleEquilateral)
{
    Triangle a = {p_rt, q_rt, r_rt};
    EXPECT_FALSE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, RightTriangleRightorNot)
{
    Triangle a = {p_rt, q_rt, r_rt};
    EXPECT_TRUE(a.is_right());
}
TEST_F(TriangleFunctionTest, ExtremeBigRightTrianglePerimeter)
{
    Triangle a = {p_exb_rt, q_exb_rt, r_exb_rt};
    double perimeter = a.perimeter();
    double ans = 12 * 1e9;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigRightTriangleEquilateral)
{
    Triangle a = {p_exb_rt, q_exb_rt, r_exb_rt};
    EXPECT_FALSE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, ExtremeBigRightTriangleRightorNot)
{
    Triangle a = {p_exb_rt, q_exb_rt, r_exb_rt};
    EXPECT_TRUE(a.is_right());
}
TEST_F(TriangleFunctionTest, ExtremeSmallRightTrianglePerimeter)
{
    Triangle a = {p_exs_rt, q_exs_rt, r_exs_rt};
    double perimeter = a.perimeter();
    double ans = 12 * 1e-6;
    EXPECT_NEAR(perimeter, ans, 1e-12);
}
TEST_F(TriangleFunctionTest, ExtremeSmallRightTriangleEquilateral)
{
    Triangle a = {p_exs_rt, q_exs_rt, r_exs_rt};
    EXPECT_FALSE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, ExtremeSmallRightTriangleRightorNot)
{
    Triangle a = {p_exs_rt, q_exs_rt, r_exs_rt};
    EXPECT_TRUE(a.is_right());
}
TEST_F(TriangleFunctionTest, NotTrianglePerimeter)
{
    Triangle a = {p_col, q_col, r_col};
    double perimeter = a.perimeter();
    double ans = 4.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, NotTriangleEquilateral)
{
    Triangle a = {p_col, q_col, r_col};
    EXPECT_FALSE(a.is_equilateral());
}
TEST_F(TriangleFunctionTest, NotTriangleRightorNot)
{
    Triangle a = {p_col, q_col, r_col};
    EXPECT_FALSE(a.is_right());
}