#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"
#include "shape.h"
#include <cmath>
#include <stdexcept>

class Circle : public Shape {
private:
    // const Point center;
    Point center; // constant remove: because we need to overload copy assignment
    double radius;

public:
    static Circle* make_circle(const Point& center, const double radius); // simple factory
    // Constructor with member initializer list
    Circle(Point c, double r) : Shape(), center(c), radius(r) { // can be make protected or private
        if(r<0) {   // class invariant
            throw std::invalid_argument("A circle cannot have negative radius.");
        }
    }
    // Circle& operator = (const Circle&);

    const Point get_center() const { return center; }
    const double get_radius() const { return radius; }

    double area() const override;
    double perimeter() const override;

    
};

#endif // CIRCLE_H
