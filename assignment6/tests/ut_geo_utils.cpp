#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include <string>
#include <filesystem>
#include <stdio.h>
#include "../src/point.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/circle.h"
#include "../src/convex_polygon.h"
#include "../src/geo_utils.h"

class GeoIOTest : public ::testing::Test
{
protected:
    std::filesystem::path test_file = "test_shapes.txt";
    // Rectangle
    Point r1 = {0.0, 0.0};
    Point r2 = {2.0, 0.0};
    Point r3 = {2.0, 1.0};
    Point r4 = {0.0, 1.0};
    ConvexPolygon rect = {std::vector<Point *>{&r1, &r2, &r3, &r4}};
    // Random Figure
    Point p1 = {0.0, 0.0};
    Point p2 = {4.0, 0.0};
    Point p3 = {4.0, 3.0};
    Point p4 = {2.0, 5.0};
    Point p5 = {0.0, 3.0};
    ConvexPolygon randomfig = {std::vector<Point *>{&p1, &p2, &p3, &p4, &p5}};
    // Circle
    Point c1 = {0.0, 0.0};
    Point c2 = {1.0, 1.0};
    double radius1 = 5.0;
    double radius2 = 10.0;
    Circle circle1 = {c1, radius1};
    Circle circle2 = {c2, radius2};
    // Unit Triangle
    Point p = {0.0, 0.0};
    Point q = {1.0, 0.0};
    Point r = {0.0, 1.0};
    Triangle unit_triangle = {p, q, r};
    // Equilateral Triangle
    Point p_eq = {0.0, 0.0};
    Point q_eq = {1.0, 0.0};
    Point r_eq = {0.5, std::sqrt(3) / 2};
    Triangle equal_triangle = {p_eq, q_eq, r_eq};
    // Right Triangle
    Point p_rt = {0.0, 0.0};
    Point q_rt = {3.0, 0.0};
    Point r_rt = {0.0, 4.0};
    Triangle right_triangle = {p_rt, q_rt, r_rt};
};
TEST_F(GeoIOTest, StoringShapes)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    ASSERT_TRUE(std::filesystem::exists(test_file)) << "write_shapes_to_file did not create the file!";
    std::vector<Shape *> shapes;
    EXPECT_NO_THROW(shapes = read_shapes_from_file(test_file));
    EXPECT_EQ(shapes.size(), 7);
    cleanup_shapes(shapes);
    std::filesystem::remove(test_file);
}
TEST_F(GeoIOTest, ReadingTestShapesType)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    // Check types and properties
    EXPECT_TRUE(typeid(*shapes[0]) == typeid(ConvexPolygon));
    EXPECT_TRUE(typeid(*shapes[1]) == typeid(ConvexPolygon));
    EXPECT_TRUE(typeid(*shapes[2]) == typeid(Circle));
    EXPECT_TRUE(typeid(*shapes[3]) == typeid(Circle));
    EXPECT_TRUE(typeid(*shapes[4]) == typeid(Triangle));
    EXPECT_TRUE(typeid(*shapes[5]) == typeid(Triangle));
    EXPECT_TRUE(typeid(*shapes[6]) == typeid(Triangle));
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, ReadingTestShapesArea)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    // Check types and properties
    EXPECT_NEAR(shapes[0]->area(), rect.area(), 1e-2);
    EXPECT_NEAR(shapes[1]->area(), randomfig.area(), 1e-2);
    EXPECT_NEAR(shapes[2]->area(), circle1.area(), 1e-2);
    EXPECT_NEAR(shapes[3]->area(), circle2.area(), 1e-2);
    EXPECT_NEAR(shapes[4]->area(), unit_triangle.area(), 1e-2);
    EXPECT_NEAR(shapes[5]->area(), equal_triangle.area(), 1e-2);
    EXPECT_NEAR(shapes[6]->area(), right_triangle.area(), 1e-2);
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, ReadingTestShapesPerimeter)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    // Check types and properties
    EXPECT_NEAR(shapes[0]->perimeter(), rect.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[1]->perimeter(), randomfig.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[2]->perimeter(), circle1.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[3]->perimeter(), circle2.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[4]->perimeter(), unit_triangle.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[5]->perimeter(), equal_triangle.perimeter(), 1e-2);
    EXPECT_NEAR(shapes[6]->perimeter(), right_triangle.perimeter(), 1e-2);
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, PolymorphismWithStackObjectsTest)
{
    // 1. 在「堆疊 (Stack)」上創建子類別的物件
    Circle stack_circle = circle1;
    Triangle stack_triangle = unit_triangle;
    ConvexPolygon stack_polygon = rect;

    // 2. 宣告「基底類別指標」
    Shape *ptr_to_circle;
    Shape *ptr_to_triangle;
    Shape *ptr_to_polygon;

    // 3. 將「堆疊物件的位址(&)」指派給「基底類別指標」
    //"reference assign給 BaseClass*"
    ptr_to_circle = &stack_circle;
    ptr_to_triangle = &stack_triangle;
    ptr_to_polygon = &stack_polygon;

    // 4. 透過基底類別指標，驗證虛擬函式 (virtual function) 是否能正確運作
    // 檢查 Circle
    EXPECT_EQ(ptr_to_circle->to_string(), "Circle 0.00 0.00 5.00");
    EXPECT_NEAR(ptr_to_circle->area(), circle1.area(), 1e-9);

    // 檢查 Triangle
    EXPECT_EQ(ptr_to_triangle->to_string(), "Triangle 0.00 0.00 1.00 0.00 0.00 1.00");
    EXPECT_NEAR(ptr_to_triangle->area(), unit_triangle.area(), 1e-9);

    // 檢查 ConvexPolygon
    EXPECT_EQ(ptr_to_polygon->to_string(), "ConvexPolygon 0.00 0.00 2.00 0.00 2.00 1.00 0.00 1.00");
    EXPECT_NEAR(ptr_to_polygon->area(), rect.area(), 1e-9);
}
TEST_F(GeoIOTest, SortbyAreaIncreasingTest)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    EXPECT_NO_THROW(sort_shapes_by_property(shapes, "area", "inc"));
    for (size_t i = 1; i < shapes.size(); ++i)
    {
        EXPECT_LE(shapes[i - 1]->area(), shapes[i]->area());
    }
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, SortbyAreaDecreasingTest)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    EXPECT_NO_THROW(sort_shapes_by_property(shapes, "area", "dec"));
    for (size_t i = 1; i < shapes.size(); ++i)
    {
        EXPECT_GE(shapes[i - 1]->area(), shapes[i]->area());
    }
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, SortbyPerimeterIncreasingTest)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    EXPECT_NO_THROW(sort_shapes_by_property(shapes, "perimeter", "inc"));
    for (size_t i = 1; i < shapes.size(); ++i)
    {
        EXPECT_LE(shapes[i - 1]->perimeter(), shapes[i]->perimeter());
    }
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}
TEST_F(GeoIOTest, SortbyPerimeterDecreasingTest)
{
    EXPECT_NO_THROW(
        write_shapes_to_file(std::vector<Shape *>{&rect, &randomfig, &circle1, &circle2, &unit_triangle, &equal_triangle, &right_triangle}, test_file));
    std::vector<Shape *> shapes = read_shapes_from_file("test_shapes.txt");
    EXPECT_NO_THROW(sort_shapes_by_property(shapes, "perimeter", "dec"));
    for (size_t i = 1; i < shapes.size(); ++i)
    {
        EXPECT_GE(shapes[i - 1]->perimeter(), shapes[i]->perimeter());
    }
    // Clean up dynamically allocated shapes
    cleanup_shapes(shapes);
    std::filesystem::remove("test_shapes.txt");
}