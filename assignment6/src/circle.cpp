#include "point.h"
#include "circle.h"
#include <string>
#include <cmath>
#define _USE_MATH_DEFINES

Circle::Circle(Point c, double r) : center(c), radius(r) {}
double Circle::area() const
{
    return M_PI * radius * radius;
}
double Circle::perimeter() const
{
    return 2 * M_PI * radius;
}
std::string Circle::to_string() const
{
    return "Circle";
}