#include "../src/point.h"
#include "../src/triangle.h"
#include "../src/circle.h"
#include "../src/shape.h"
#include "../src/convex_polygon.h"
#include "../src/save_shape.h"
#include "../src/compound_shape.h"
#include "../src/ext_amoeba.h"
#include "../src/amoeba.h"
#include <gtest/gtest.h>
#include <cmath>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <vector>
#include <memory>

TEST(ShapeTest, Point)
{
    Point p{0.0, 0.0};
    // Point p;
    // p.x = 0.0;
    // p.y = 0.0;
    EXPECT_EQ(0.0, p.x);
    EXPECT_EQ(0.0, p.y);
}

TEST(PointTest, DistanceBetweenTwoPoints)
{
    Point p{0.0, 0.0}; // List initializer
    Point q{1.0, 1.0};

    EXPECT_NEAR(std::sqrt(2.0), distance(p, q), 0.001);
}

TEST(ShapeTest, TriangleAreaTest)
{
    Point p{0.0, 0.0};
    Point q{3.0, 0.0};
    Point r{0.0, 4.0};

    Triangle t{p, q, r}; // Aggregate initializer

    int x = 365;

    EXPECT_NEAR(6.0, t.area(), 0.001);
}

TEST(ShapeTest, CircleTest)
{
    Point center{0.0, 0.0};
    Circle c{center, 5.0};

    Circle c2(center, 5.0);

    int i{100}; // best
    int j = 100;
    int k(100);

    EXPECT_NEAR(78.54, c.area(), 0.01);
}

TEST(ShapeTest, SortIntegers)
{
    std::vector<int> v{4, 2, 5, 1, 3}; // vector is a container
    std::sort(v.begin(), v.end());
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
    EXPECT_EQ(4, v[3]);
    EXPECT_EQ(5, v[4]);
}

TEST(ShapeTest, SortIntegersInArray)
{
    int a[]{4, 2, 5, 1, 3};
    std::sort(a, a + 5);
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
    EXPECT_EQ(3, a[2]);
    EXPECT_EQ(4, a[3]);
    EXPECT_EQ(5, a[4]);
}

bool integer_greater_than(int a, int b)
{
    return a > b;
}

bool integer_less_than(int a, int b)
{
    return a < b;
}

// typedef bool (*Comparator)(int, int); //worse

using Comparator = bool (*)(int, int); // better

TEST(ShapeTest, SortIntegersInArrayWithDescending)
{
    int a[]{4, 2, 5, 1, 3};
    Comparator comp = integer_greater_than;
    std::sort(a, a + 5, comp);
    // std::sort(a, a+5, integer_greater_than);
    // std::sort(a, a+5, [](int a, int b){
    // return a > b;
    // });
    EXPECT_EQ(5, a[0]);
    EXPECT_EQ(4, a[1]);
    EXPECT_EQ(3, a[2]);
    EXPECT_EQ(2, a[3]);
    EXPECT_EQ(1, a[4]);

    comp = integer_less_than;
    std::sort(a, a + 5, comp);
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
    EXPECT_EQ(3, a[2]);
    EXPECT_EQ(4, a[3]);
    EXPECT_EQ(5, a[4]);
}

class MyComparator
{
public:
    bool operator()(int a, int b)
    {
        return a > b;
    }
};
TEST(ShapeTest, SortIntegersInArrayWithClass)
{
    int a[]{4, 2, 5, 1, 3};
    MyComparator comp;
    std::sort(a, a + 5, comp);

    EXPECT_EQ(5, a[0]);
    EXPECT_EQ(4, a[1]);
    EXPECT_EQ(3, a[2]);
    EXPECT_EQ(2, a[3]);
    EXPECT_EQ(1, a[4]);
}

TEST(ShapeTest, SortShapesByArea)
{
    Point center{0.0, 0.0};
    Circle c{center, 5.0};

    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Triangle t{p1, p2, p3};

    std::vector<Shape *> shapes;
    shapes.push_back(&c);
    shapes.push_back(&t);

    std::sort(shapes.begin(), shapes.end(), [](Shape *a, Shape *b)
              { return a->area() < b->area(); });

    EXPECT_NEAR(6.0, shapes[0]->area(), 0.001);
    EXPECT_NEAR(78.54, shapes[1]->area(), 0.001);
}

TEST(ShapeTest, CircleAsShape)
{
    Point center{0.0, 0.0};
    Circle c{center, 5.0};

    Shape *s = &c; // Upcasting

    EXPECT_NEAR(78.54, s->area(), 0.01);

    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Triangle t{p1, p2, p3};

    s = &t; // Upcasting

    EXPECT_NEAR(6.0, s->area(), 0.001);
}

// 直角三角形 邊長3 4 5
// TEST(ShapeTest, Triangle345Case){

// }

TEST(ShapeTest, SortShapesByPerimeter)
{
    Point center{0.0, 0.0};
    Circle c{center, 5.0};

    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Triangle t{p1, p2, p3};

    std::vector<Shape *> shapes;
    shapes.push_back(&c);
    shapes.push_back(&t);

    std::sort(shapes.begin(), shapes.end(), [](Shape *a, Shape *b)
              { return a->perimeter() < b->perimeter(); });

    EXPECT_NEAR(12.0, shapes[0]->perimeter(), 0.01);
    EXPECT_NEAR(31.41, shapes[1]->perimeter(), 0.01);
}

TEST(ShapeTest, ConvertTriangle)
{
    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Triangle t{p1, p2, p3};

    EXPECT_EQ("Triangle 0.0000 0.0000 3.0000 0.0000 3.0000 4.0000", t.to_string());
}

TEST(ShapeTest, OutputTriangle)
{
    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Triangle t1{p1, p2, p3};

    Point q1{0.0, 0.0};
    Point q2{2.0, 0.0};
    Point q3{3.0, 4.0};
    Triangle t2{q1, q2, q3};

    std::vector<Shape *> shapes{&t1, &t2};
    std::filesystem::path dir = "./";
    std::filesystem::path filename = dir / "sorted_shapes.txt";

    save_shapes_to_file(shapes, filename.string());

    std::ifstream ifs(filename);
    std::string expectedString1 = "Triangle 0.0000 0.0000 3.0000 0.0000 3.0000 4.0000";
    std::string expectedString2 = "Triangle 0.0000 0.0000 2.0000 0.0000 3.0000 4.0000";
    std::string actualString1;
    std::string actualString2;

    std::getline(ifs, actualString1);
    std::getline(ifs, actualString2);
    EXPECT_EQ(expectedString1, actualString1);
    EXPECT_EQ(expectedString2, actualString2);

    std::filesystem::remove(filename);
}

TEST(ShapeTest, OutputTrianglePointers)
{
    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};

    Point q1{0.0, 0.0};
    Point q2{2.0, 0.0};
    Point q3{3.0, 4.0};

    std::vector<Shape *> shapes{new Triangle(p1, p2, p3), new Triangle(q1, q2, q3)};
    std::filesystem::path dir = "./";
    std::filesystem::path filename = dir / "sorted_shapes.txt";

    save_shapes_to_file(shapes, filename.string());

    std::ifstream ifs(filename);
    std::string expectedString1 = "Triangle 0.0000 0.0000 3.0000 0.0000 3.0000 4.0000";
    std::string expectedString2 = "Triangle 0.0000 0.0000 2.0000 0.0000 3.0000 4.0000";
    std::string actualString1;
    std::string actualString2;

    std::getline(ifs, actualString1);
    std::getline(ifs, actualString2);
    EXPECT_EQ(expectedString1, actualString1);
    EXPECT_EQ(expectedString2, actualString2);

    std::filesystem::remove(filename);
    delete shapes[0];
    delete shapes[1];
}

TEST(ShapeTest, ConvexPolygon2)
{
    Point p1{0.0, 0.0};
    Point p2{3.0, 0.0};
    Point p3{3.0, 4.0};
    Point p4{0.0, 4.0};
    std::vector<Point *> vertices{
        new Point{0.0, 0.0},
        new Point{3.0, 0.0},
        new Point{3.0, 4.0},
        new Point{0.0, 4.0}};
    ConvexPolygon2 cp1(vertices);
    ConvexPolygon2 cp2(cp1); // copy constructor: bitwise copy
    ConvexPolygon2 cp3;      // default constructor
    // cp3 = cp1;  // shallow copy assignment
    // cp3 = cp3;
    (cp3 = cp2) = cp1;

    EXPECT_NEAR(12.0, cp1.area(), 0.01);
    EXPECT_NEAR(14.0, cp1.perimeter(), 0.01);
}

TEST(ShapeTest, ConvexPolygon)
{
    // std::vector<Point> vertices{
    //     Point{0.0, 0.0},
    //     Point{3.0, 0.0},
    //     Point{3.0, 4.0},
    //     Point{0.0, 4.0}
    // };
    std::vector<Point> vertices{
        Point{1.0, 1.0},
        Point{4.0, 1.0},
        Point{4.0, 5.0},
        Point{1.0, 5.0}};
    ConvexPolygon cp1(vertices);
    ConvexPolygon cp2(cp1); // copy constructor: bitwise copy
    ConvexPolygon cp3;      // default constructor
    cp3 = cp1;              // shallow copy assignment
    cp3 = cp3;
    (cp3 = cp2) = cp1;

    EXPECT_NEAR(12.0, cp1.area(), 0.01);
    EXPECT_NEAR(14.0, cp1.perimeter(), 0.01);
}
TEST(ShapeTest, ConvexPolygon_VerticesNotOrder)
{
    std::vector<Point> vertices{
        Point{0.0, 0.0},
        Point{3.0, 4.0},
        Point{0.0, 4.0},
        Point{3.0, 0.0}};
    ConvexPolygon cp1(vertices);

    EXPECT_NEAR(12.0, cp1.area(), 0.01);
    EXPECT_NEAR(14.0, cp1.perimeter(), 0.01);
}

TEST(ShapeTest, ConvexPolygonCentroid)
{
    std::vector<Point> vertices{
        Point{0.0, 0.0},
        Point{3.0, 4.0},
        Point{0.0, 4.0},
        Point{3.0, 0.0}};
    ConvexPolygon cp(vertices);

    EXPECT_NEAR(1.5, cp.centroid().x, 0.001);
    EXPECT_NEAR(2.0, cp.centroid().y, 0.001);
}

// TEST(ShapeTest, ConvexPolygonAsShape){
//     Point p1{0.0, 0.0};
//     Point p2{3.0, 0.0};
//     Point p3{3.0, 4.0};
//     Point p4{0.0, 4.0};
//     std::vector<Point*> vertices{&p1, &p2, &p3, &p4};

//     Shape *polygon1 = new ConvexPolygon(vertices);
//     Shape *polygon2 = new ConvexPolygon(*polygon1);

//     // EXPECT_NEAR(12.0, cp.area(), 0.01);
//     // EXPECT_NEAR(14.0, cp.perimeter(), 0.01);
// }

template <typename T>
void my_swap(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

TEST(ShapeTest, MySwapOnInt)
{
    int a = 3, b = 4;
    my_swap(a, b); // instantiate my_swap(int &, int &)
    EXPECT_EQ(4, a);
    EXPECT_EQ(3, b);
}

TEST(ShapeTest, MySwapOnCircle)
{
    Circle c1{Point{0.0, 0.0}, 1.0};
    Circle c2{Point{1.0, 1.0}, 2.0};
    my_swap(c1, c2); // instantiate my_swap(Circle &, Circle &); now my_swap is overloaded
    // EXPECT_EQ("Circle 1.0000 1.0000 2.0000", c1.to_string());
    // EXPECT_EQ("Circle 0.0000 0.0000 1.0000", c2.to_string());
    EXPECT_NEAR(2.0, c1.get_radius(), 0.001);
    EXPECT_NEAR(1.0, c2.get_radius(), 0.001);
}

TEST(ShapeTest, CircleGetterTest)
{
    Circle c{Point{0.0, 1.0}, 3.0};

    EXPECT_NEAR(3.0, c.get_radius(), 0.001);
    EXPECT_NEAR(0.0, c.get_center().x, 0.001);
    EXPECT_NEAR(1.0, c.get_center().y, 0.001);
}

TEST(ShapeTest, CircleWithNegativeRadiusTest)
{
    EXPECT_THROW((Circle{Point{0.0, 1.0}, -3.0}), std::invalid_argument);
}

TEST(ShapeTest, CompoundShapeExclamationTest)
{
    Triangle t{Point{0.0, 0.0}, Point{-1.0, 3.0}, Point{1.0, 3.0}};
    Circle c{Point{0.0, -1.0}, 0.5};
    std::vector<Shape *> input{&t, &c};
    Shape *exclamation = new CompoundShape{input};
    EXPECT_NEAR(t.area() + c.area(), exclamation->area(), 0.001);
    EXPECT_NEAR(t.perimeter() + c.perimeter(), exclamation->perimeter(), 0.001);
    // delete exclamation;
}
TEST(ShapeTest, CompoundShapeExclamationWithUniquePtrTest)
{
    Shape *t = new Triangle{Point{0.0, 0.0}, Point{-1.0, 3.0}, Point{1.0, 3.0}};
    Shape *c = new Circle{Point{0.0, -1.0}, 0.5};

    std::vector<std::unique_ptr<Shape>> input;
    input.push_back(std::make_unique<Triangle>(
        Point{0.0, 0.0}, Point{-1.0, 3.0}, Point{1.0, 3.0}));
    input.push_back(std::make_unique<Circle>(
        Point{0.0, -1.0}, 0.5));

    Shape *exclamation = new CompoundShapeUnique(std::move(input));
    EXPECT_NEAR(t->area() + c->area(), exclamation->area(), 0.001);
    EXPECT_NEAR(t->perimeter() + c->perimeter(), exclamation->perimeter(), 0.001);
    delete exclamation;
}

TEST(ShapeTest, CompoundShapeWheelSetTest)
{
    Circle c1{Point{0.0, 0.0}, 0.5};
    Circle c2{Point{0.0, 4.0}, 0.5};
    Circle c3{Point{3.0, 0.0}, 0.5};
    Circle c4{Point{3.0, 4.0}, 0.5};
    Shape *compound1 = new CompoundShape{{&c1, &c2}};
    Shape *wheel_set = new CompoundShape{{compound1, &c3, &c4}};
    EXPECT_NEAR(c1.area() * 4, wheel_set->area(), 0.001);
    EXPECT_NEAR(c1.perimeter() * 4, wheel_set->perimeter(), 0.001);
}

TEST(ShapeTest, CompoundShapeUniqueAddTest)
{
    CompoundShapeUnique compoundShape;
    Shape *c = compoundShape.add(std::make_unique<Circle>(Point{0.0, 0.0}, 3.0));
    Shape *t = compoundShape.add(std::make_unique<Triangle>(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0}));

    EXPECT_NEAR(c->area() + t->area(), compoundShape.area(), 0.01);
    compoundShape.remove(c);
    EXPECT_NEAR(t->area(), compoundShape.area(), 0.01);

    // c is a dangling reference
    // delete c;
    // c->area();
}

TEST(ShapeTest, MoveSemanticsTest)
{
    std::unique_ptr<Shape> c = std::make_unique<Circle>(Point{0.0, 0.0}, 5.0);
    std::unique_ptr<Shape> t = std::make_unique<Triangle>(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0});
    EXPECT_NEAR(78.54, c->area(), 0.01);
    EXPECT_NEAR(6.0, t->area(), 0.001);
    EXPECT_NEAR(78.54, (*c).area(), 0.01);
    EXPECT_NEAR(6.0, (*t).area(), 0.001);
    // std::unique_ptr<Shape> x = c;
    Shape *pt = t.get();
    std::unique_ptr<Shape> x(std::move(t));
    EXPECT_EQ(nullptr, t);
    // the raw pointer still points to the triangle object
    EXPECT_NEAR(6.0, pt->area(), 0.001);
    // deleting it crashes the program
    // delete pt;
    // EXPECT_EQ(nullptr, t->get());
    x = std::move(c);
    EXPECT_EQ(nullptr, c);
}

TEST(ShapeTest, MoveSemanticsInitializationTest)
{
    std::unique_ptr<Shape> c = std::make_unique<Circle>(Point{0.0, 0.0}, 5.0);
    std::unique_ptr<Shape> t = std::make_unique<Triangle>(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0});
    // initialize notation does not work because unique_ptr's cannot be copied ...
    // std::vector <std::unique_ptr<Shape>> shapes{std::move(c), std::move(t)};
    // ... so you push_back after moving
    double result = c->area() + t->area();
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::move(c));
    shapes.push_back(std::move(t));

    // vector shapes giving up ownership when constructing CompoundShapeUnique...
    // check out the initializer_list that moves the ownership of the unique_ptrs
    CompoundShapeUnique compoundShape(std::move(shapes));
    EXPECT_EQ(0, shapes.size());
    EXPECT_NEAR(result, compoundShape.area(), 0.01);
}

TEST(ShapeTest, CompoundShapeSafeWithHandleTest)
{
    double ca = Circle{Point{0.0, 0.0}, 3}.area();
    double ta = Triangle{Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0}}.area();
    CompoundShapeSafe compoundShape;
    CompoundShapeSafe::Handle c = compoundShape.add(std::make_unique<Circle>(Point{0.0, 0.0}, 3.0));
    CompoundShapeSafe::Handle t = compoundShape.add(std::make_unique<Triangle>(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0}));

    EXPECT_NEAR(ca + ta, compoundShape.area(), 0.001);
    compoundShape.remove(c);
    EXPECT_NEAR(ta, compoundShape.area(), 0.001);

    Shape &shape = compoundShape.get(t);
    EXPECT_NEAR(ta, shape.area(), 0.001);

    try
    {
        compoundShape.get(c);
        FAIL();
    }
    catch (const std::exception &e)
    {
        EXPECT_STREQ("handle not found", e.what());
    }

    CompoundShapeSafe::Handle t2 = compoundShape.add(
        std::make_unique<Triangle>(
            Triangle{Point{0.0, 0.0}, Point{6.0, 0.0}, Point{0.0, 8.0}}));
    EXPECT_EQ(2, t2);

    CompoundShapeSafe compoundShape2 = std::move(compoundShape); // move constructor
    Shape &shape1 = compoundShape2.get(t2);
    EXPECT_NEAR(24.0, shape1.area(), 0.001);

    CompoundShapeSafe compoundShape3; // default constructor
    compoundShape3 = std::move(compoundShape2); // move assignment
    Shape &shape2 = compoundShape3.get(t2);
    EXPECT_NEAR(24.0, shape2.area(), 0.001);
    EXPECT_NEAR(6.0, compoundShape3.get(t).area(), 0.001);

    EXPECT_NEAR(0.0, compoundShape2.area(), 0.001);

    EXPECT_EQ(3, compoundShape.get_next_handle());
}


TEST(ShapeTest, CircleFactory){
    Circle* c = Circle::make_circle(Point{0.0, 0.0}, -3);
    EXPECT_EQ(nullptr, c); 
    
    Circle *c2 = Circle::make_circle(Point{0.0, 0.0}, 3);
    EXPECT_NEAR(3*3*M_PI, c2->area(), 0.001);
}

TEST(ShapeTest, CompoundShapeSafeAndCircleFactory){
    std::unique_ptr<CompoundShapeSafe> compoundShape = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = compoundShape->add(std::unique_ptr<Circle>(Circle::make_circle(Point{0.0, 0.0}, -3)));
    EXPECT_EQ(-1, c);
    CompoundShapeSafe::Handle t = compoundShape->add(std::make_unique<Triangle>(Point{0.0, 0.0}, Point{3.0, 0.0}, Point{0.0, 4.0}));
    EXPECT_NEAR(6, compoundShape->area(), 0.001);


    CompoundShapeSafe c2;

    CompoundShapeSafe::Handle compound = c2.add(std::move(compoundShape));
    EXPECT_NEAR(6, c2.area(), 0.001);
}

TEST(ShapeTest, AreaOfAllTrianglesInCompound) {
    std::unique_ptr<CompoundShapeSafe> insideCompound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = insideCompound->add(std::make_unique<Circle>(Point{0.0,0.0}, 3.0));
    CompoundShapeSafe::Handle t = insideCompound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{3.0,0.0}, Point{3.0,4.0}));

    EXPECT_NEAR(34.2743, insideCompound->area(), 0.001);

    std::unique_ptr<CompoundShapeSafe> compound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle t2 = compound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{6.0,0.0}, Point{6.0,8.0}));
    CompoundShapeSafe::Handle ic = compound->add(std::move(insideCompound));

    EXPECT_NEAR(34.2743+24.0, compound->area(), 0.001);
    double triangleArea = compound->find_area("Triangle");

    EXPECT_NEAR(24.0+6.0, triangleArea, 0.001);
}

TEST(ShapeTest, AreaOfAllTrianglesInCompoundByTypeId) {
    std::unique_ptr<CompoundShapeSafe> insideCompound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = insideCompound->add(std::make_unique<Circle>(Point{0.0,0.0}, 3.0));
    CompoundShapeSafe::Handle t = insideCompound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{3.0,0.0}, Point{3.0,4.0}));

    EXPECT_NEAR(34.2743, insideCompound->area(), 0.001);

    std::unique_ptr<CompoundShapeSafe> compound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle t2 = compound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{6.0,0.0}, Point{6.0,8.0}));
    CompoundShapeSafe::Handle ic = compound->add(std::move(insideCompound));

    EXPECT_NEAR(34.2743+24.0, compound->area(), 0.001);
    std::unique_ptr<Shape> t3 = std::make_unique<Triangle>(Point{0.0,0.0}, Point{1.0,0.0}, Point{0.0,1.0});
    // query by example
    double triangleArea = compound->find_area(t3.get());

    EXPECT_NEAR(24.0+6.0, triangleArea, 0.001);
}

TEST(ShapeTest, AreaOfAllTrianglesInCompoundByTemplate) {
    std::unique_ptr<CompoundShapeSafe> insideCompound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = insideCompound->add(std::make_unique<Circle>(Point{0.0,0.0}, 3.0));
    CompoundShapeSafe::Handle t = insideCompound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{3.0,0.0}, Point{3.0,4.0}));

    EXPECT_NEAR(34.2743, insideCompound->area(), 0.001);

    std::unique_ptr<CompoundShapeSafe> compound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle t2 = compound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{6.0,0.0}, Point{6.0,8.0}));
    CompoundShapeSafe::Handle ic = compound->add(std::move(insideCompound));

    EXPECT_NEAR(34.2743+24.0, compound->area(), 0.001);
    
    double triangleArea = compound->find_area<Triangle>();

    EXPECT_NEAR(24.0+6.0, triangleArea, 0.001);
}

TEST(ShapeTest, AreaOfAllTrianglesInCompoundByLambda) {
    std::unique_ptr<CompoundShapeSafe> insideCompound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = insideCompound->add(std::make_unique<Circle>(Point{0.0,0.0}, 3.0));
    CompoundShapeSafe::Handle t = insideCompound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{3.0,0.0}, Point{3.0,4.0}));

    EXPECT_NEAR(34.2743, insideCompound->area(), 0.001);

    std::unique_ptr<CompoundShapeSafe> compound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle t2 = compound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{6.0,0.0}, Point{6.0,8.0}));
    CompoundShapeSafe::Handle ic = compound->add(std::move(insideCompound));

    EXPECT_NEAR(34.2743+24.0, compound->area(), 0.001);
    std::unique_ptr<Shape> t3 = std::make_unique<Triangle>(Point{0.0,0.0}, Point{1.0,0.0}, Point{0.0,1.0});
    double triangleArea = compound->find_area([&t3](Shape* shape){ 
        return typeid(*shape) == typeid(*t3.get());
    });

    EXPECT_NEAR(24.0+6.0, triangleArea, 0.001);
}

TEST(ShapeTest, Amoeba) {
    ExtAmoeba* ea = new ExtAmoeba();
    Amoeba amoeba {ea};

    EXPECT_NEAR(0.5, amoeba.area(), 0.001);
    EXPECT_NEAR(0.25, amoeba.perimeter(), 0.001);

    delete ea;
}

// TEST(ShapeTest, Amoeba2) {
//     Amoeba2 amoeba;

//     EXPECT_NEAR(0.5, amoeba.area(), 0.001);
//     EXPECT_NEAR(0.25, amoeba.perimeter(), 0.001);
// }

TEST(ShapeTest, AreaOfAllTrianglesInCompoundSort) {
    std::unique_ptr<CompoundShapeSafe> insideCompound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle c = insideCompound->add(std::make_unique<Circle>(Point{0.0,0.0}, 3.0));
    CompoundShapeSafe::Handle t = insideCompound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{3.0,0.0}, Point{3.0,4.0}));

    EXPECT_NEAR(34.2743, insideCompound->area(), 0.001);

    std::unique_ptr<CompoundShapeSafe> compound = std::make_unique<CompoundShapeSafe>();
    CompoundShapeSafe::Handle t2 = compound->add(std::make_unique<Triangle>(Point{0.0,0.0}, Point{6.0,0.0}, Point{6.0,8.0}));
    CompoundShapeSafe::Handle ic = compound->add(std::move(insideCompound));

    EXPECT_NEAR(34.2743+24.0, compound->area(), 0.001);
    
    Shape* c2 = new Circle{Point{0.0, 0.0}, 1.0};
    Shape* t3 = new Triangle{Point{0.0, 0.0}, Point{1.0, 0.0}, Point{0.0, 1.0}};

    Shape* exampleType = new Triangle{Point{0.0, 0.0}, Point{1.0, 0.0}, Point{0.0, 2.0}};
    std::vector<Shape*> shapes{compound.get(), c2, t3};
    std::sort(shapes.begin(), shapes.end(), [exampleType](Shape* a, Shape* b){
        return a->find_area(exampleType) < b->find_area(exampleType);
    });

    EXPECT_NEAR(0, shapes[0]->find_area(exampleType), 0.001);
    EXPECT_NEAR(0.5, shapes[1]->find_area(exampleType), 0.001);
    EXPECT_NEAR(30, shapes[2]->find_area(exampleType), 0.001);

    delete c2;
    delete t3;
    delete exampleType;

    
}