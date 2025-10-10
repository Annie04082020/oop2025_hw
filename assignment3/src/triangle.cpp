#include <cmath>
#include <algorithm>
#include "triangle.h"
#include "point.h"

void Triangle::get_sides(double &a, double &b, double &c) const
{
    a = this->p.get_euclidean_distance(q);
    b = this->q.get_euclidean_distance(r);
    c = this->r.get_euclidean_distance(p);
}
double Triangle::perimeter() const
{
    double a, b, c;
    this->get_sides(a, b, c);
    return a + b + c;
}

bool Triangle::is_equilateral() const
{
    double a, b, c;
    this->get_sides(a, b, c);
    bool a_eq_b = std::abs(a - b) < 1e-9;
    bool b_eq_c = std::abs(b - c) < 1e-9;
    bool a_eq_c = std::abs(a - c) < 1e-9;
    return a_eq_b && b_eq_c && a_eq_c;
}

bool Triangle::is_right() const
{
    double a, b, c;
    this->get_sides(a, b, c);
    double max_side_sqr = std::max({a * a, b * b, c * c});
    double sum_sqr = a * a + b * b + c * c;
    double other_sum_sqr = sum_sqr - max_side_sqr;
    return std::abs(other_sum_sqr - max_side_sqr) < 1e-9;
}
