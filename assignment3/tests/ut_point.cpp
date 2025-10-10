#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <random>
#include "../src/point.h"
class PointFunctionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        gen.seed(3); // 固定種子
    }
    std::mt19937 gen; // 共享的隨機數生成器
};
TEST_F(PointFunctionTest, DistanceNormalCase)
{
    Point a = {0, 0};
    Point b = {1, 1};
    EXPECT_NEAR(a.get_euclidean_distance(b), std::sqrt(2), 1e-9);
}
TEST_F(PointFunctionTest, DistanceOnXaxis)
{
    Point a = {0, 0};
    Point b = {1, 0};
    EXPECT_NEAR(a.get_euclidean_distance(b), 1.0, 1e-9);
}
TEST_F(PointFunctionTest, DistanceOnYaxis)
{
    Point a = {0, 0};
    Point b = {0, 1};
    EXPECT_NEAR(a.get_euclidean_distance(b), 1.0, 1e-9);
}
TEST_F(PointFunctionTest, DistanceZero)
{
    Point a = {1, 1};
    Point b = {1, 1};
    EXPECT_NEAR(a.get_euclidean_distance(b), 0.0, 1e-9);
}
TEST_F(PointFunctionTest, DistanceNegativeCoordinates)
{
    Point a = {-1, -1};
    Point b = {1, 1};
    EXPECT_NEAR(a.get_euclidean_distance(b), 2 * std::sqrt(2), 1e-9);
}
TEST_F(PointFunctionTest, DistanceLargeCoordinates)
{
    Point a = {1e6, 1e6};
    Point b = {2e6, 2e6};
    EXPECT_NEAR(a.get_euclidean_distance(b), 1e6 * std::sqrt(2), 1e-6);
}
TEST_F(PointFunctionTest, DistanceNonInteger)
{
    Point a = {0.6, 0.6};
    Point b = {1.6, 1.6};
    EXPECT_NEAR(a.get_euclidean_distance(b), std::sqrt(2), 1e-9);
}

TEST_F(PointFunctionTest, CollinearityDiffPointFalse)
{
    Point a = {0, 0};
    Point b = {1, 0};
    Point c = {0, 1};
    EXPECT_FALSE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearityDiffPointTrue)
{
    Point a = {0, 0};
    Point b = {1, 1};
    Point c = {2, 2};
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearityVertical)
{
    Point a = {1, 0};
    Point b = {1, 1};
    Point c = {1, 2};
    EXPECT_TRUE(a.is_collinear(b, c));
}

TEST_F(PointFunctionTest, CollinearityHorizontal)
{
    Point a = {0, 1};
    Point b = {1, 1};
    Point c = {2, 1};
    EXPECT_TRUE(a.is_collinear(b, c));
}

TEST_F(PointFunctionTest, CollinearityTwoPointsSame)
{
    Point a = {0, 0};
    Point b = {0, 0};
    Point c = {1, 1};
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearitySamePoint)
{
    Point a = {1, 1};
    Point b = a;
    Point c = a;
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearityLargeCoordinates)
{
    Point a = {1e6, 1e6};
    Point b = {2e6, 2e6};
    Point c = {3e6, 3e6};
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearityNonInteger)
{
    Point a = {0.0, 0.0};
    Point b = {1.5, 1.5};
    Point c = {3.0, 3.0};
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, CollinearityNearPoints)
{
    Point a = {0, 0};
    Point b = {1, 1};
    Point c = {2 + 1e-10, 2 + 1e-10};
    EXPECT_TRUE(a.is_collinear(b, c));
}
TEST_F(PointFunctionTest, IdentifyQuadrant1)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, random};
    EXPECT_EQ(a.get_quadrant(), "first");
}
TEST_F(PointFunctionTest, IdentifyQuadrant2)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {-random, random};
    EXPECT_EQ(a.get_quadrant(), "second");
}
TEST_F(PointFunctionTest, IdentifyQuadrant3)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {-random, -random};
    EXPECT_EQ(a.get_quadrant(), "third");
}
TEST_F(PointFunctionTest, IdentifyQuadrant4)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, -random};
    EXPECT_EQ(a.get_quadrant(), "fourth");
}
TEST_F(PointFunctionTest, IdentifyQuadrantXaxis)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {random, 0};
    EXPECT_EQ(a.get_quadrant(), "not in any quadrant");
}
TEST_F(PointFunctionTest, IdentifyQuadrantYaxis)
{
    std::mt19937 gen(3);
    std::uniform_real_distribution<double> dis(1.0, 100.0);
    double random = dis(gen);
    Point a = {0, random};
    EXPECT_EQ(a.get_quadrant(), "not in any quadrant");
}
TEST_F(PointFunctionTest, IdentifyQuadrantOrigin)
{
    Point a = {0, 0};
    EXPECT_EQ(a.get_quadrant(), "not in any quadrant");
}
TEST_F(PointFunctionTest, MidPointNormalCase)
{ // Single unit
    Point a = {0, 0};
    Point b = {1, 1};
    Point MidPoint = a.get_midpoint(b);
    EXPECT_NEAR(MidPoint.x, 0.5, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.5, 1e-9);
    EXPECT_EQ(a.get_euclidean_distance(MidPoint), b.get_euclidean_distance(MidPoint));
}
TEST_F(PointFunctionTest, MidPointOnXaxis)
{ // On X axis
    Point a = {0, 0};
    Point b = {1, 0};
    Point MidPoint = a.get_midpoint(b);
    EXPECT_NEAR(MidPoint.x, 0.5, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.0, 1e-9);
    EXPECT_EQ(a.get_euclidean_distance(MidPoint), b.get_euclidean_distance(MidPoint));
}
TEST_F(PointFunctionTest, MidPointOnYaxis)
{ // On Y axis
    Point a = {0, 0};
    Point b = {0, 1};
    Point MidPoint = a.get_midpoint(b);
    EXPECT_NEAR(MidPoint.x, 0.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.5, 1e-9);
    EXPECT_EQ(a.get_euclidean_distance(MidPoint), b.get_euclidean_distance(MidPoint));
}
TEST_F(PointFunctionTest, MidPointSamePoint)
{ // Same point
    Point a = {1, 1};
    Point b = {1, 1};
    Point MidPoint = a.get_midpoint(b);
    EXPECT_NEAR(MidPoint.x, 1.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 1.0, 1e-9);
    EXPECT_EQ(a.get_euclidean_distance(MidPoint), b.get_euclidean_distance(MidPoint));
}
TEST_F(PointFunctionTest, MidPointNegativeCoordinates)
{
    Point a = {-1, -1};
    Point b = {1, 1};
    Point MidPoint = a.get_midpoint(b);
    EXPECT_NEAR(MidPoint.x, 0.0, 1e-9);
    EXPECT_NEAR(MidPoint.y, 0.0, 1e-9);
    EXPECT_EQ(a.get_euclidean_distance(MidPoint), b.get_euclidean_distance(MidPoint));
}