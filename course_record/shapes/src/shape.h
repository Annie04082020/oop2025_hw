#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <typeinfo>

class Shape {
public:
    virtual double area() const = 0; // area declared but not defined
    virtual double perimeter() const = 0; // pure virtual
    virtual std::string to_string() const {return "Shape";}
    virtual double find_area(Shape* shape) const{
        return typeid(*shape) == typeid(*this) ? this->area() : 0;
    }
    virtual ~Shape() {}
};



#endif // SHAPE_H