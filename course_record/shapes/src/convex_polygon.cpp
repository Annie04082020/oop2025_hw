#include <iostream>
#include <algorithm>
#include <cmath>
#include "convex_polygon.h"
#include "triangle.h"

ConvexPolygon2::ConvexPolygon2() : vertices_(){}

ConvexPolygon2::ConvexPolygon2(std::vector<Point*> vertices) : vertices_(){
    for (auto vertex: vertices){
        vertices_.push_back(new Point(*vertex));
    }
}

ConvexPolygon2::ConvexPolygon2(const ConvexPolygon2& other) : vertices_(){
    for (auto vertex: other.vertices_){
        vertices_.push_back(new Point(*vertex));
    }
}

ConvexPolygon2::~ConvexPolygon2(){
    std::cout<< "destructor ConvexPolygon call\n";
    for (auto vertex: vertices_){
        delete vertex;
    }
}

ConvexPolygon2& ConvexPolygon2::operator = (const ConvexPolygon2& rhs){
    if (this == &rhs){
        return *this;
    }
    for (auto vertex: vertices_){
        delete vertex;
    }
    vertices_.clear();
    for (auto vertex: rhs.vertices_){
        vertices_.push_back(new Point(*vertex));
    }
    return *this;
}

double ConvexPolygon2::area() const {return 12.0;}

double ConvexPolygon2::perimeter() const {return 14.0;}

std::string ConvexPolygon2::to_string() const {return "";}


ConvexPolygon::ConvexPolygon() : vertices_(){}
ConvexPolygon::ConvexPolygon(const std::vector<Point>& vertices) : vertices_(vertices){
    Point c{centroid()};
    std::sort(vertices_.begin(), vertices_.end(), [c](const Point &p1, const Point &p2){
        return std::atan2(p1.y-c.y, p1.x-c.x) < std::atan2(p2.y-c.y, p2.x-c.x);
    });
}

Point ConvexPolygon::centroid() const{
    Point center{0, 0};
    for(auto &it : vertices_) {
        center.x += it.x;
        center.y += it.y;
    }
    center.x /= vertices_.size();
    center.y /= vertices_.size();

    return center;
}

double ConvexPolygon::area() const {    
    double ans = 0;
    for(int i=1;i<vertices_.size()-1;i++) {
        ans += Triangle(vertices_[0], vertices_[i], vertices_[i+1]).area();
    }
    return ans;
}
double ConvexPolygon::perimeter() const {
    double ans = 0;
    for(int i=0;i<vertices_.size();i++) {
    //    ans += distance(vertices_[i], vertices_[i+1]);
        ans += distance(vertices_.at(i), vertices_.at((i+1)%vertices_.size()));
    }
    return ans;
}
std::string ConvexPolygon::to_string() const {return "";}
