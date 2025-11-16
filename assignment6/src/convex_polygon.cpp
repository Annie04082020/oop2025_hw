#include "point.h"
#include "convex_polygon.h"
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

ConvexPolygon::ConvexPolygon() {}
ConvexPolygon::ConvexPolygon(std::vector<Point *> vertices)
{
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
