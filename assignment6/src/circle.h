#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "shape.h"

class Circle : public Shape{
public:
    const Point center;
    double radius;

    Circle(Point c, double r);

    double area() const override;
    double perimeter() const override;
    std::string to_string() const override;
};

#endif // CIRCLE_H