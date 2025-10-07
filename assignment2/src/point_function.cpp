#include <string>
#include <cmath>
#include "point.h"
#include "point_function.h"

double get_euclidean_distance(Point p, Point q)
{
    double dx = q.x - p.x;
    double dy = q.y - p.y;
    return std::abs(std::sqrt(dx * dx + dy * dy));
}

bool is_collinear(Point p, Point q, Point r)
{
    // Cross product will be zero if any two vectors are collinear
    double cross_product = (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
    return std::abs(cross_product) < 1e-9;
}
std::string get_quadrant(Point p)
{
    if (p.x > 0 && p.y > 0)
        return "Quadrant 1";
    else if (p.x < 0 && p.y > 0)
        return "Quadrant 2";
    else if (p.x < 0 && p.y < 0)
        return "Quadrant 3";
    else if (p.x > 0 && p.y < 0)
        return "Quadrant 4";
    else if (p.x == 0 && p.y != 0)
        return "On Y axis";
    else if (p.y == 0 && p.x != 0)
        return "On X axis";
    else
        return "Origin";
}
Point get_midpoint(Point p, Point q)
{
    Point midpoint;
    midpoint.x = (p.x + q.x) / 2.0;
    midpoint.y = (p.y + q.y) / 2.0;
    return midpoint;
}