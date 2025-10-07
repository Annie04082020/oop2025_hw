#include <gtest/gtest.h>
#include <string>
#include <random>
#include "../src/point.h"
#include "../src/point_function.h"

TEST(PointFunctionTest, DistanceNormalCase)
{
    Point a = {0, 0};
    Point b = {1, 1};
    EXPECT_NEAR(get_euclidean_distance(a, b), std::sqrt(2), 1e-9);
}
TEST(PointFunctionTest, DistanceOnXaxis)
{
    Point a = {0, 0};
    Point b = {1, 0};
    EXPECT_NEAR(get_euclidean_distance(a, b), 1.0, 1e-9);
}
TEST(PointFunctionTest, DistanceOnYaxis)
{
    Point a = {0, 0};
    Point b = {0, 1};
    EXPECT_NEAR(get_euclidean_distance(a, b), 1.0, 1e-9);
}
TEST(PointFunctionTest, DistanceZero)
{
    Point a = {1, 1};
    Point b = {1, 1};
    EXPECT_NEAR(get_euclidean_distance(a, b), 0.0, 1e-9);
}
TEST(PointFunctionTest, DistanceNegativeCoordinates)
{
    Point a = {-1, -1};
    Point b = {1, 1};
    EXPECT_NEAR(get_euclidean_distance(a, b), 2 * std::sqrt(2), 1e-9);
}
TEST(PointFunctionTest, DistanceLargeCoordinates)
{
    Point a = {1e6, 1e6};
    Point b = {2e6, 2e6};
    EXPECT_NEAR(get_euclidean_distance(a, b), 1e6 * std::sqrt(2), 1e-6);
}
TEST(PointFunctionTest, CollinearityDiffPointFalse)
{
    Point a = {0, 0};
    Point b = {1, 0};
    Point c = {0, 1};
    EXPECT_FALSE(is_collinear(a, b, c));
}
TEST(PointFunctionTest, CollinearityDiffPointTrue)
{
    Point a = {0, 0};
    Point b = {1, 1};
    Point c = {2, 2};
    EXPECT_TRUE(is_collinear(a, b, c));
}
TEST(PointFunctionTest, CollinearityVertical)
{
    Point a = {1, 0};
    Point b = {1, 1};
    Point c = {1, 2};
    EXPECT_TRUE(is_collinear(a, b, c));
}

TEST(PointFunctionTest, CollinearityHorizontal)
{
    Point a = {0, 1};
    Point b = {1, 1};
    Point c = {2, 1};
    EXPECT_TRUE(is_collinear(a, b, c));
}

TEST(PointFunctionTest, CollinearityTwoPointsSame)
{
    Point a = {0, 0};
    Point b = {0, 0};
    Point c = {1, 1};
    EXPECT_TRUE(is_collinear(a, b, c));
}
TEST(PointFunctionTest, CollinearitySamePoint)
{
    Point a = {1, 1};
    Point b = a;
    Point c = a;
    EXPECT_TRUE(is_collinear(a, b, c));
}
TEST(PointFunctionTest, CollinearityLargeCoordinates)
{
    Point a = {1e6, 1e6};
    Point b = {2e6, 2e6};
    Point c = {3e6, 3e6};
    EXPECT_TRUE(is_collinear(a, b, c));
}
TEST(PointFunctionTest, IdentifyQuadrant1)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, random};
    EXPECT_EQ(get_quadrant(a), "Quadrant 1");
}
TEST(PointFunctionTest, IdentifyQuadrant2)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {-random, random};
    EXPECT_EQ(get_quadrant(a), "Quadrant 2");
}
TEST(PointFunctionTest, IdentifyQuadrant3)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {-random, -random};
    EXPECT_EQ(get_quadrant(a), "Quadrant 3");
}
TEST(PointFunctionTest, IdentifyQuadrant4)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, -random};
    EXPECT_EQ(get_quadrant(a), "Quadrant 4");
}
TEST(PointFunctionTest, IdentifyQuadrantXaxis)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, 0};
    EXPECT_EQ(get_quadrant(a), "On X axis");
}
TEST(PointFunctionTest, IdentifyQuadrantYaxis)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {0, random};
    EXPECT_EQ(get_quadrant(a), "On Y axis");
}
TEST(PointFunctionTest, IdentifyQuadrantOrigin)
{
    Point a = {0, 0};
    EXPECT_EQ(get_quadrant(a), "Origin");
}
TEST(PointFunctionTest, MidPointNormalCase)
{ // Single unit
    Point a = {0, 0};
    Point b = {1, 1};
    Point MidPoint = get_midpoint(a, b);
    EXPECT_NEAR(MidPoint.x, 0.5, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.5, 1e-9);
    EXPECT_EQ(get_euclidean_distance(a, MidPoint), get_euclidean_distance(b, MidPoint));
}
TEST(PointFunctionTest, MidPointOnXaxis)
{ // On X axis
    Point a = {0, 0};
    Point b = {1, 0};
    Point MidPoint = get_midpoint(a, b);
    EXPECT_NEAR(MidPoint.x, 0.5, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.0, 1e-9);
    EXPECT_EQ(get_euclidean_distance(a, MidPoint), get_euclidean_distance(b, MidPoint));
}
TEST(PointFunctionTest, MidPointOnYaxis)
{ // On Y axis
    Point a = {0, 0};
    Point b = {0, 1};
    Point MidPoint = get_midpoint(a, b);
    EXPECT_NEAR(MidPoint.x, 0.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.5, 1e-9);
    EXPECT_EQ(get_euclidean_distance(a, MidPoint), get_euclidean_distance(b, MidPoint));
}
TEST(PointFunctionTest, MidPointSamePoint)
{ // Same point
    Point a = {1, 1};
    Point b = {1, 1};
    Point MidPoint = get_midpoint(a, b);
    EXPECT_NEAR(MidPoint.x, 1.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 1.0, 1e-9);
    EXPECT_EQ(get_euclidean_distance(a, MidPoint), get_euclidean_distance(b, MidPoint));
}
TEST(PointFunctionTest, MidPointNegativeCoordinates)
{
    Point a = {-1, -1};
    Point b = {1, 1};
    Point MidPoint = get_midpoint(a, b);
    EXPECT_NEAR(MidPoint.x, 0.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.0, 1e-9);
    EXPECT_EQ(get_euclidean_distance(a, MidPoint), get_euclidean_distance(b, MidPoint));
}