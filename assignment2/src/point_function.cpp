#include <string>
#include <cmath>
#include "point.h"
#include "point_function.h"

double get_euclidean_distance(Point p, Point q)
{
    double dx = q.x - p.x;
    double dy = q.y - p.y;
    return std::sqrt(dx * dx + dy * dy);
}

bool is_collinear(Point p, Point q, Point r)
{
    return (q.y - p.y) * (r.x - q.x) == (r.y - q.y) * (q.x - p.x);
}
Point get_midpoint(Point p, Point q)
{
    Point midpoint;
    midpoint.x = (p.x + q.x) / 2.0;
    midpoint.y = (p.y + q.y) / 2.0;
    return midpoint;
}