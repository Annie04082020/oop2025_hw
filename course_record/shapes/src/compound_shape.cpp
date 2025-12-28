#include "compound_shape.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

CompoundShape::CompoundShape(std::vector<Shape *> components) : _components(components) {}

CompoundShape::~CompoundShape()
{
    for (auto shape : _components)
    {
        delete shape;
    }
}

double CompoundShape::area() const
{
    double result = 0.0;
    for (auto component : _components)
    {
        result += component->area();
    }
    return result;
}

double CompoundShape::perimeter() const
{
    double result = 0.0;
    for (auto component : _components)
    {
        result += component->perimeter();
    }
    return result;
}

CompoundShapeUnique::CompoundShapeUnique(std::vector<std::unique_ptr<Shape>> components) : _components(std::move(components)) {}

double CompoundShapeUnique::area() const
{
    double result = 0.0;
    for (const std::unique_ptr<Shape> &component : _components)
    {
        result += component->area();
    }
    return result;
}

double CompoundShapeUnique::perimeter() const
{
    double result = 0.0;
    for (const std::unique_ptr<Shape> &component : _components)
    {
        result += component->perimeter();
    }
    return result;
}

Shape *CompoundShapeUnique::add(std::unique_ptr<Shape> shape)
{
    Shape *returnPtr = shape.get(); // get raw pointer
    _components.push_back(std::move(shape));
    return returnPtr;
}
void CompoundShapeUnique::remove(Shape *shape)
{
    auto it = std::remove_if(_components.begin(), _components.end(), [shape](const std::unique_ptr<Shape> &it)
                             { return shape == it.get(); });

    if (it != _components.end())
    {
        _components.erase(it, _components.end());
    }
}

CompoundShapeSafe::Handle CompoundShapeSafe::add(std::unique_ptr<Shape> shape)
{
    if(shape == nullptr){
        return -1;
    }
    // std::pair<Handle, std::unique_ptr<Shape>> newShape =
    //     std::pair(_currentIndex, std::move(shape));
    _components[_currentIndex] = std::move(shape);
    return _currentIndex++;
}

void CompoundShapeSafe::remove(Handle handle)
{
    auto it = _components.find(handle);
    if (it == _components.end())
    {
        return;
    }
    _components.erase(it);
}
double CompoundShapeSafe::area() const
{
    double result = 0.0;
    for (auto &component : _components)
    {
        result += component.second->area();
    }
    return result;
}

double CompoundShapeSafe::perimeter() const
{
    double result = 0.0;
    for (auto &component : _components)
    {
        result += component.second->perimeter();
    }
    return result;
}

Shape &CompoundShapeSafe::get(Handle handle) const
{
    auto it = _components.find(handle);
    if (it == _components.end())
    {
        throw std::invalid_argument("handle not found");
    }
    return *it->second;
}

double CompoundShapeSafe::find_area(const char* shapeType) const {
    double returnArea = 0.0;

    for(const auto & component: _components) {
        if (component.second->to_string().find(shapeType) != std::string::npos) {
            returnArea += component.second->area();
        }
        // else if (component.second->to_string().find("CompoundShape") != std::string::npos) {
        //     std::cout << "work" << std::endl;
        //     // CompoundShapeSafe *c = static_cast<CompoundShapeSafe*>(component.second.get());
        //     CompoundShapeSafe *c = dynamic_cast<CompoundShapeSafe*>(component.second.get());
        //     if (c) {
        //         returnArea += c->find_area(shapeType);
        //     }
        // }
        else {
            CompoundShapeSafe *c = dynamic_cast<CompoundShapeSafe*>(component.second.get());
            if (c) {
                returnArea += c->find_area(shapeType);
            }
        }
    }

    return returnArea;
}

double CompoundShapeSafe::find_area(Shape *shape) const {
    double returnArea = 0.0;

    for (const auto &component: _components) {
        if (typeid(*component.second.get()) == typeid(*shape)) {
            returnArea += component.second->area();
        }
        else {
            CompoundShapeSafe *c = dynamic_cast<CompoundShapeSafe*>(component.second.get());
            if (c) {
                returnArea += c->find_area(shape);
            }
        }
    }

    return returnArea;
}