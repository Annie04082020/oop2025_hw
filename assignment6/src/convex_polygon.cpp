#include "point.h"
#include "convex_polygon.h"
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <stdexcept>
#include <iostream>

bool ConvexPolygon::ConvexCheck(std::vector<Point *> vertices)
{
    if (vertices.size() < 3)
    {
        std::cerr << "A polygon must have at least 3 vertices to check convexity." << std::endl;
        return false;
    }
    bool is_convex = true;
    int n = vertices.size();
    int sign = 0;
    double first_cross_product = 0.0;
    for (int i = 0; i < n; i++)
    {
        Point *p1 = vertices[(i + n - 1) % n];
        Point *p2 = vertices[i];
        Point *p3 = vertices[(i + 1) % n];
        std::tuple<double, double> v1 = std::make_tuple(p2->x - p1->x, p2->y - p1->y);
        std::tuple<double, double> v2 = std::make_tuple(p3->x - p2->x, p3->y - p2->y);
        double cross_product = (std::get<0>(v1) * std::get<1>(v2)) - (std::get<1>(v1) * std::get<0>(v2));
        if (cross_product != 0)
        {
            if (first_cross_product == 0.0)
            {
                first_cross_product = cross_product;
            }
            else if (cross_product * first_cross_product < 0)
            {
                is_convex = false;
                break;
            }
        }
    }
    return is_convex;
}

ConvexPolygon::ConvexPolygon() {}
ConvexPolygon::ConvexPolygon(std::vector<Point *> vertices)
{
    if (!ConvexCheck(vertices))
    {
        throw std::runtime_error("Polygon is concave");
    }
    for (Point *p : vertices)
    {
        if (p != nullptr)
        {
            this->vertices_.push_back(new Point(*p));
        };
    }
}
ConvexPolygon::ConvexPolygon(const ConvexPolygon &other)
{
    for (const Point *other_point : other.vertices_)
    {
        this->vertices_.push_back(new Point(*other_point));
    }
}
ConvexPolygon::~ConvexPolygon()
{
    for (Point *p : vertices_)
    {
        delete p;
    }
    vertices_.clear();
}
ConvexPolygon &ConvexPolygon::operator=(const ConvexPolygon &other)
{
    if (this != &other)
    {
        for (Point *p : vertices_)
        {
            delete p;
        }
        vertices_.clear();
        for (const Point *other_point : other.vertices_)
        {
            this->vertices_.push_back(new Point(*other_point));
        }
    }
    return *this;
}
double ConvexPolygon::area() const
{
    double area = 0.0;
    int n = vertices_.size();
    if (n < 3)
    {
        return 0.0;
    }
    for (int i = 0; i < n; i++)
    {
        Point *current = vertices_[i];
        Point *next = vertices_[(i + 1) % n];
        area += (current->x * next->y) - (next->x * current->y);
    }
    return std::abs(area) / 2.0;
}
double ConvexPolygon::perimeter() const
{
    double perimeter = 0.0;
    int n = vertices_.size();
    if (n < 2)
    {
        return 0.0;
    }
    for (int i = 0; i < n; i++)
    {
        Point *current = vertices_[i];
        Point *next = vertices_[(i + 1) % n];
        double length = distance(*current, *next);
        perimeter += length;
    }
    return perimeter;
}
std::string ConvexPolygon::to_string() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "ConvexPolygon";
    for (const Point *p : vertices_)
    {
        ss << " " << p->x << " " << p->y;
    }
    return ss.str();
}
