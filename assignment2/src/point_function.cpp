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
        return "first";
    else if (p.x < 0 && p.y > 0)
        return "second";
    else if (p.x < 0 && p.y < 0)
        return "third";
    else if (p.x > 0 && p.y < 0)
        return "fourth";
    else
        return "not in any quadrant";
}
Point get_midpoint(Point p, Point q)
{
    Point midpoint;
    midpoint.x = (p.x + q.x) / 2.0;
    midpoint.y = (p.y + q.y) / 2.0;
    return midpoint;
}