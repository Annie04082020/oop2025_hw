#include <string>
#include <cmath>
#include "point.h"

double Point::get_euclidean_distance(const Point &other) const
{
    double dx = other.x - this->x;
    double dy = other.y - this->y;
    return std::abs(std::sqrt(dx * dx + dy * dy));
}

bool Point::is_collinear(const Point &other1, const Point &other2) const
{
    // Cross product will be zero if any two vectors are collinear
    double cross_product = (other1.x - this->x) * (other2.y - this->y) - (other1.y - this->y) * (other2.x - this->x);
    return std::abs(cross_product) < 1e-9;
}
std::string Point::get_quadrant() const
{
    if (this->x > 0 && this->y > 0)
        return "first";
    else if (this->x < 0 && this->y > 0)
        return "second";
    else if (this->x < 0 && this->y < 0)
        return "third";
    else if (this->x > 0 && this->y < 0)
        return "fourth";
    else
        return "not in any quadrant";
}
Point Point::get_midpoint(const Point &other) const
{
    Point midpoint;
    midpoint.x = (this->x + other.x) / 2.0;
    midpoint.y = (this->y + other.y) / 2.0;
    return midpoint;
}