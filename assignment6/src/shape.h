#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <vector>


class Shape {
public:
    virtual double area() const = 0; // area declared but not defined
    virtual double perimeter() const = 0; // pure virtual
    virtual std::string to_string() const {return "Shape";}
    virtual ~Shape() {}
};



#endif // SHAPE_H