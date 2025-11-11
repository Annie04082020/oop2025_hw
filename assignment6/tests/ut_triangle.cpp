#include <gtest/gtest.h>
#include <cmath>
#include <string>
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
    // Not a Triangle (Overlapping Points)
    Point p_ovlap = {0.0, 0.0};
    Point q_ovlap = {0.0, 0.0};
    Point r_ovlap = {0.0, 0.0};
    // Not a Triangle (Overlapping 2 Points)
    Point p_2ovlap = {0.0, 0.0};
    Point q_2ovlap = {0.0, 0.0};
    Point r_2ovlap = {1.0, 0.0};
};
TEST_F(TriangleFunctionTest, UnitTrianglePerimeter)
{
    Triangle a = {p, q, r};
    double perimeter = a.perimeter();
    double ans = 2 + std::sqrt(2);
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, UnitTriangleArea)
{
    Triangle a = {p, q, r};
    double area = a.area();
    double ans = 0.5;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, EqualTrianglePerimeter)
{
    Triangle a = {p_eq, q_eq, r_eq};
    double perimeter = a.perimeter();
    double ans = 3;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, EqualTriangleArea)
{
    Triangle a = {p_eq, q_eq, r_eq};
    double area = a.area();
    double ans = 0.25 * sqrt(3);
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigEqualTrianglePerimeter)
{
    Triangle a = {p_exb_eq, q_exb_eq, r_exb_eq};
    double perimeter = a.perimeter();
    double ans = 3 * 1e9;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigEqualTriangleArea)
{
    Triangle a = {p_exb_eq, q_exb_eq, r_exb_eq};
    double area = a.area();
    double ans = 0.25e18 * sqrt(3);
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeSmallEqualTrianglePerimeter)
{
    Triangle a = {p_exs_eq, q_exs_eq, r_exs_eq};
    double perimeter = a.perimeter();
    double ans = 3 * 1e-6;
    EXPECT_NEAR(perimeter, ans, 1e-12);
}
TEST_F(TriangleFunctionTest, ExtremeSmallEqualTriangleArea)
{
    Triangle a = {p_exs_eq, q_exs_eq, r_exs_eq};
    double area = a.area();
    double ans = 0.25e-12 * sqrt(3);
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, RightTrianglePerimeter)
{
    Triangle a = {p_rt, q_rt, r_rt};
    double perimeter = a.perimeter();
    double ans = 12;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, RightTriangleArea)
{
    Triangle a = {p_rt, q_rt, r_rt};
    double area = a.area();
    double ans = 6;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigRightTrianglePerimeter)
{
    Triangle a = {p_exb_rt, q_exb_rt, r_exb_rt};
    double perimeter = a.perimeter();
    double ans = 12 * 1e9;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeBigRightTriangleArea)
{
    Triangle a = {p_exb_rt, q_exb_rt, r_exb_rt};
    double area = a.area();
    double ans = 6e18;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ExtremeSmallRightTrianglePerimeter)
{
    Triangle a = {p_exs_rt, q_exs_rt, r_exs_rt};
    double perimeter = a.perimeter();
    double ans = 12 * 1e-6;
    EXPECT_NEAR(perimeter, ans, 1e-12);
}
TEST_F(TriangleFunctionTest, ExtremeSmallRightTriangleArea)
{
    Triangle a = {p_exs_rt, q_exs_rt, r_exs_rt};
    double area = a.area();
    double ans = 6e-12;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, NotTrianglePerimeter)
{
    Triangle a = {p_col, q_col, r_col};
    double perimeter = a.perimeter();
    double ans = 4.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, NotTriangleArea)
{
    Triangle a = {p_col, q_col, r_col};
    double area = a.area();
    double ans = 0;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, OverlapPointsPerimeter)
{
    Triangle a = {p_ovlap, q_ovlap, r_ovlap};
    double perimeter = a.perimeter();
    double ans = 0.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, OverlapPointsArea)
{
    Triangle a = {p_ovlap, q_ovlap, r_ovlap};
    double area = a.area();
    double ans = 0;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, Overlap2PointsPerimeter)
{
    Triangle a = {p_2ovlap, q_2ovlap, r_2ovlap};
    double perimeter = a.perimeter();
    double ans = 2.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, Overlap2PointsArea)
{
    Triangle a = {p_2ovlap, q_2ovlap, r_2ovlap};
    double area = a.area();
    double ans = 0;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(TriangleFunctionTest, ToStringTest)
{

    Triangle a = {p, q, r};
    Triangle b = {p_eq, q_eq, r_eq};
    Triangle c = {p_exb_eq, q_exb_eq, r_exb_eq};
    Triangle d = {p_rt, q_rt, r_rt};
    Triangle e = {p_col, q_col, r_col};
    Triangle f = {p_ovlap, q_ovlap, r_ovlap};
    Triangle g = {p_2ovlap, q_2ovlap, r_2ovlap};
    Triangle h = {p_exb_eq, q_exb_eq, r_exb_eq};
    std::string stra = a.to_string();
    std::string ansa = "Triangle";
    std::string strb = b.to_string();
    std::string ansb = "Triangle";
    std::string strc = c.to_string();
    std::string ansc = "Triangle";
    std::string strd = d.to_string();
    std::string ansd = "Triangle";
    std::string stre = e.to_string();
    std::string anse = "Triangle";
    std::string strf = f.to_string();
    std::string ansf = "Triangle";
    std::string strg = g.to_string();
    std::string ansg = "Triangle";
    std::string strh = h.to_string();
    std::string ansh = "Triangle";
    EXPECT_EQ(stra, ansa);
    EXPECT_EQ(strb, ansb);
    EXPECT_EQ(strc, ansc);
    EXPECT_EQ(strd, ansd);
    EXPECT_EQ(stre, anse);
    EXPECT_EQ(strf, ansf);
    EXPECT_EQ(strg, ansg);
}