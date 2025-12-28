#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include "point.h"
#include "shape.h"
#include <vector>

class ConvexPolygon2 : public Shape{
private:
    std::vector<Point*> vertices_;

public:
    ConvexPolygon2();
    ConvexPolygon2(std::vector<Point*>);
    // rule of three
    ConvexPolygon2(const ConvexPolygon2&);
    ~ConvexPolygon2();
    ConvexPolygon2& operator = (const ConvexPolygon2&);
    double area() const override;
    double perimeter() const override;
    std::string to_string() const override;

};

class ConvexPolygon : public Shape{
private:
    std::vector<Point> vertices_;

public:
    ConvexPolygon();
    ConvexPolygon(const std::vector<Point>&);
    // rule of three -> rule of zero
    // ~ConvexPolygon() = default;
    // ConvexPolygon& operator = (const ConvexPolygon&);
    // ConvexPolygon(const ConvexPolygon&);

    Point centroid() const;

    double area() const override;
    double perimeter() const override;
    std::string to_string() const override;

};

#endif
