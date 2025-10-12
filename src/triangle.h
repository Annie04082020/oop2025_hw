#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle
{
public:
    Point p;
    Point q;
    Point r;

    double perimeter() const;

    bool is_equilateral() const;

    bool is_right() const;
};
#endif