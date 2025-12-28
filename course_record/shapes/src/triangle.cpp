#include "triangle.h"
#include "shape.h"
#include "point.h"
#include <cmath>
#include <sstream>
#include <iomanip>

Triangle::Triangle(Point p1, Point p2, Point p3): Shape(), p(p1), q(p2), r(p3) {}

double Triangle::area() const{ // Triangle:: prefix
    double a = distance(p, q);
    double b = distance(q, r);
    double c = distance(r, p);

    double s = (a + b + c) / 2;

    return std::sqrt(s * (s-a) * (s-b) * (s-c));
}

double Triangle::perimeter() const{

    double a = distance(p, q);
    double b = distance(q, r);
    double c = distance(r, p);

    return a+b+c;
}

std::string Triangle::to_string() const{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(4);
    oss << "Triangle " << p.x << " " << p.y << " " << q.x << " " << q.y << " " << r.x << " " << r.y;
    return oss.str();
}