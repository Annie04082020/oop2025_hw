#include "point.h"
#include "circle.h"
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>
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
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Circle " << center.x << " " << center.y << " " << radius;
    return ss.str();
}