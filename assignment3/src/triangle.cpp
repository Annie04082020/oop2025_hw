#include <cmath>
#include <algorithm>
#include <tuple>
#include "triangle.h"
#include "point.h"

std::tuple<double, double, double> get_sides(Triangle x)
{
    double a = x.p.get_euclidean_distance(x.q);
    double b = x.q.get_euclidean_distance(x.r);
    double c = x.r.get_euclidean_distance(x.p);
    return std::make_tuple(a, b, c);
}
double Triangle::perimeter() const
{
    std::tuple<double, double, double> sides = get_sides(*this);
    return std::get<0>(sides) + std::get<1>(sides) + std::get<2>(sides);
}

bool Triangle::is_equilateral() const
{
    auto [a, b, c] = get_sides(*this);
    bool a_eq_b = std::abs(a - b) < 1e-12;
    bool b_eq_c = std::abs(b - c) < 1e-12;
    bool a_eq_c = std::abs(a - c) < 1e-12;
    return a_eq_b && b_eq_c && a_eq_c;
}

bool Triangle::is_right() const
{
    auto [a, b, c] = get_sides(*this);
    double max_side_sqr = std::max({a * a, b * b, c * c});
    double sum_sqr = a * a + b * b + c * c;
    double other_sum_sqr = sum_sqr - max_side_sqr;
    return std::abs(other_sum_sqr - max_side_sqr) < 1e-12;
}
