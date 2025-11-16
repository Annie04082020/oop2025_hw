#include "point.h"
#include "triangle.h"
#include <cmath>
#include <string>
#include <iomanip>
#include <sstream>

Triangle::Triangle(Point p1, Point p2, Point p3) : p(p1), q(p2), r(p3) {}
std::tuple<double, double, double> get_sides(Triangle x)
{
    double a = distance(x.p, x.q);
    double b = distance(x.q, x.r);
    double c = distance(x.r, x.p);
    return std::make_tuple(a, b, c);
}
double Triangle::area() const
{
    std::tuple<double, double, double> sides = get_sides(*this);
    double a = std::get<0>(sides);
    double b = std::get<1>(sides);
    double c = std::get<2>(sides);
    double s = (a + b + c) / 2.0;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}
double Triangle::perimeter() const
{
    std::tuple<double, double, double> sides = get_sides(*this);
    return std::get<0>(sides) + std::get<1>(sides) + std::get<2>(sides);
}
std::string Triangle::to_string() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Triangle " << p.x << " " << p.y << " " << q.x << " " << q.y << " " << r.x << " " << r.y;
    return ss.str();
}