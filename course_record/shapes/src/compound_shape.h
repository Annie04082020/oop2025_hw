#ifndef COMPOUND_SHAPE_H
#define COMPOUND_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>
#include <unordered_map>

class CompoundShape : public Shape
{
private:
    std::vector<Shape *> _components;

public:
    // CompoundShape();
    CompoundShape(std::vector<Shape *>);
    ~CompoundShape() override;

    double area() const override;
    double perimeter() const override;
};

class CompoundShapeUnique : public Shape
{
private:
    std::vector<std::unique_ptr<Shape>> _components;

public:
    CompoundShapeUnique() {}
    CompoundShapeUnique(std::vector<std::unique_ptr<Shape>>);
    // Rule of zero from rule of five(three)
    // ~CompoundShapeUnique() = default;
    double area() const override;
    double perimeter() const override;

    Shape *add(std::unique_ptr<Shape>);
    void remove(Shape *);
};

class CompoundShapeSafe : public Shape
{
public:
    using Handle = int;

private:
    std::unordered_map<Handle, std::unique_ptr<Shape>> _components;
    Handle _currentIndex{0};

public:
    double area() const override;
    double perimeter() const override;
    double find_area(const char *) const;
    std::string to_string() const override { return "CompoundShape"; }
    double find_area(Shape*) const override;
    
    template<typename T>
    double find_area() const {
        double returnArea = 0.0;

        for (const auto &component: _components) {
            if (typeid(*component.second.get()) == typeid(T)) {
                returnArea += component.second->area();
            }
            else {
                CompoundShapeSafe *c = dynamic_cast<CompoundShapeSafe*>(component.second.get());
                if (c) {
                    returnArea += c->find_area<T>();
                }
            }
        }

        return returnArea;
    }

    template<typename Predicate>
    double find_area(Predicate p) const {
        double returnArea = 0.0;

        for (const auto &component: _components) {
            if (p(component.second.get())) {
                returnArea += component.second->area();
            }
            else {
                CompoundShapeSafe *c = dynamic_cast<CompoundShapeSafe*>(component.second.get());
                if (c) {
                    returnArea += c->find_area(p);
                } 
            }
        }

        return returnArea;
    }

    Handle add(std::unique_ptr<Shape>);
    void remove(Handle);

    Shape &get(Handle) const;

    Handle get_next_handle() const {return _currentIndex;}
};

#endif
