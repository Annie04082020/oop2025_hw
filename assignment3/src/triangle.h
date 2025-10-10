#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle
{
public:
    Point p;
    Point q;
    Point r;

    void get_sides(double& a, double& b, double& c) const;
    double perimeter() const;
    bool is_equilateral() const;
    bool is_right() const;
};
#endif