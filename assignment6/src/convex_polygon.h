#ifndef CONVEX_POLYGON_H
#define CONVEX_POLYGON_H

#include "point.h"
#include "shape.h"

class ConvexPolygon : public Shape{
private:
    std::vector<Point*> vertices_;

public:
    ConvexPolygon();
    ConvexPolygon(std::vector<Point*>);
    ConvexPolygon(const ConvexPolygon&);
    ~ConvexPolygon();
    ConvexPolygon& operator = (const ConvexPolygon&);
    double area() const override;
    double perimeter() const override;
    std::string to_string() const override;

};

#endif
