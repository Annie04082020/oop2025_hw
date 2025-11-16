#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include "../src/point.h"
#include "../src/convex_polygon.h"

class ConvexPolygonFunctionTest : public ::testing::Test
{
protected:
    // Square
    Point s1 = {0.0, 0.0};
    Point s2 = {1.0, 0.0};
    Point s3 = {1.0, 1.0};
    Point s4 = {0.0, 1.0};
    // Rectangle
    Point r1 = {0.0, 0.0};
    Point r2 = {2.0, 0.0};
    Point r3 = {2.0, 1.0};
    Point r4 = {0.0, 1.0};
    // Random Figure
    Point p1 = {0.0, 0.0};
    Point p2 = {4.0, 0.0};
    Point p3 = {4.0, 3.0};
    Point p4 = {2.0, 5.0};
    Point p5 = {0.0, 3.0};
};
TEST_F(ConvexPolygonFunctionTest, SquarePerimeter)
{
    ConvexPolygon square = {std::vector<Point *>{&s1, &s2, &s3, &s4}};
    double perimeter = square.perimeter();
    double ans = 4.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, SquareArea)
{
    ConvexPolygon square = {std::vector<Point *>{&s1, &s2, &s3, &s4}};
    double area = square.area();
    double ans = 1;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, RectanglePerimeter)
{
    ConvexPolygon rect = {std::vector<Point *>{&r1, &r2, &r3, &r4}};
    double perimeter = rect.perimeter();
    double ans = 6.0;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, RectangleArea)
{
    ConvexPolygon rect = {std::vector<Point *>{&r1, &r2, &r3, &r4}};
    double area = rect.area();
    double ans = 2;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, RandomFigurePerimeter)
{
    ConvexPolygon randomfig = {std::vector<Point *>{&p1, &p2, &p3, &p4, &p5}};
    double perimeter = randomfig.perimeter();
    double ans = 4 * sqrt(2) + 10;
    EXPECT_NEAR(perimeter, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, RandomFigureArea)
{
    ConvexPolygon randomfig = {std::vector<Point *>{&p1, &p2, &p3, &p4, &p5}};
    double area = randomfig.area();
    double ans = 16;
    EXPECT_NEAR(area, ans, 1e-9);
}
TEST_F(ConvexPolygonFunctionTest, ToStringTest)
{
    ConvexPolygon square = {std::vector<Point *>{&s1, &s2, &s3, &s4}};
    std::string str = square.to_string();
    EXPECT_EQ(str, "ConvexPolygon 0.00 0.00 1.00 0.00 1.00 1.00 0.00 1.00");
    ConvexPolygon rectangle = {std::vector<Point *>{&r1, &r2, &r3, &r4}};
    std::string str2 = rectangle.to_string();
    EXPECT_EQ(str2, "ConvexPolygon 0.00 0.00 2.00 0.00 2.00 1.00 0.00 1.00");
    ConvexPolygon randomfig = {std::vector<Point *>{&p1, &p2, &p3, &p4, &p5}};
    std::string str3 = randomfig.to_string();
    EXPECT_EQ(str3, "ConvexPolygon 0.00 0.00 4.00 0.00 4.00 3.00 2.00 5.00 0.00 3.00");
}
TEST_F(ConvexPolygonFunctionTest, ConcaveCheckShouldFail)
{
    Point p1{0, 0};
    Point p2{4, 0};
    Point p3{2, 2};
    Point p4{4, 4};
    Point p5{0, 4};
    std::vector<Point *> concave_points = {&p1, &p2, &p3, &p4, &p5};
    EXPECT_FALSE(ConvexPolygon::ConvexCheck(concave_points));
}
TEST_F(ConvexPolygonFunctionTest, ConcavePolygonShouldThrowException)
{
    Point p1{0, 0};
    Point p2{4, 0};
    Point p3{2, 2};
    Point p4{4, 4};
    Point p5{0, 4};
    std::vector<Point *> concave_points = {&p1, &p2, &p3, &p4, &p5};
    EXPECT_THROW(
        new ConvexPolygon(concave_points),
        std::runtime_error);
}