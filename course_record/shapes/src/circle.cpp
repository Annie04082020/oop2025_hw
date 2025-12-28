#include "circle.h"

Circle* Circle::make_circle(const Point& center, const double radius){
    if(radius < 0){
        return nullptr;
    }
    return new Circle(center, radius);
}

double Circle::area() const{
    return M_PI * radius * radius;
}

double Circle::perimeter() const{
    return 2*M_PI*radius;
}

// Circle& Circle::operator = (const Circle& rhs) {
//     if (&rhs == this) {
//         return *this;
//     }
//     center = rhs.center;
//     radius = rhs.radius;
//     return *this;
// }
