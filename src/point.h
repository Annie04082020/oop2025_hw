#ifndef POINT_H
#define POINT_H

#include <string>
class Point
{
public:
    double x;
    double y;

    double get_euclidean_distance(const Point &other) const;

    std::string get_quadrant() const;

    bool is_collinear(const Point &other1, const Point &other2) const;

    Point get_midpoint(const Point &other) const;
};
#endif