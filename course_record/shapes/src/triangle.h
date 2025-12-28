#include "point.h"
#include "shape.h"

class Triangle : public Shape{
public:
    Point p;
    Point q;
    Point r;

    //Constructor with member initializer list
    Triangle(Point p1, Point p2, Point p3);
    double area() const override;
    double perimeter() const override;
    std::string to_string() const override;
};