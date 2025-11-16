#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "geo_utils.h"
#include "shape.h"
#include "point.h"
#include "circle.h"
#include "triangle.h"
#include "convex_polygon.h"

Shape *create_shape_from_string(const std::string &line)
{
    std::stringstream ss(line);
    std::string shape_type;
    ss >> shape_type;
    if (shape_type == "Circle")
    {
        double x, y, r;
        ss >> x >> y >> r;
        Point center{x, y};
        return new Circle(center, r);
    }
    else if (shape_type == "Triangle")
    {
        double x1, y1, x2, y2, x3, y3;
        ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        Point p{x1, y1};
        Point q{x2, y2};
        Point r{x3, y3};
        return new Triangle(p, q, r);
    }
    else if (shape_type == "ConvexPolygon")
    {
        std::vector<Point *> vertices;
        for (double x, y; ss >> x >> y;)
        {
            vertices.push_back(new Point{x, y});
        }
        return new ConvexPolygon(vertices);
    }
    else
    {
        throw std::runtime_error("Unknown shape type: " + shape_type);
    }
}
std::vector<Shape *> read_shapes_from_file(const std::filesystem::path &filename)
{
    std::ifstream input_file(filename);
    if (!input_file.is_open())
    {
        throw std::runtime_error("Could not open file for reading: " + filename.string());
    }
    std::vector<Shape *> shapes;
    std::string line;
    while (std::getline(input_file, line))
    {
        if (line.empty())
            continue;
        Shape *shape = nullptr;
        std::stringstream ss(line);
        try
        {
            shape = create_shape_from_string(line);
            shapes.push_back(shape);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Warning: Skipping malformed line: " << line << " (" << e.what() << ")" << std::endl;
            continue;
        }
    }
    return shapes;
}
void write_shapes_to_file(const std::vector<Shape *> &shapes, const std::filesystem::path &filename)
{
    std::ofstream output_file(filename);
    if (!output_file.is_open())
    {
        throw std::runtime_error("Could not open file for writing: " + filename.string());
        return;
    }
    for (const auto &item : shapes)
    {
        if (item)
        {
            output_file << item->to_string() << "\n";
        }
    }
}
void sort_shapes_by_property(std::vector<Shape *> &shapes, const std::string &property, const std::string &order)
{
    auto compare_area_inc = [](Shape *a, Shape *b)
    { return a->area() < b->area(); };
    auto compare_area_dec = [](Shape *a, Shape *b)
    { return a->area() > b->area(); };
    auto compare_perimeter_inc = [](Shape *a, Shape *b)
    { return a->perimeter() < b->perimeter(); };
    auto compare_perimeter_dec = [](Shape *a, Shape *b)
    { return a->perimeter() > b->perimeter(); };
    if (property.compare("perimeter") == 0 && order.compare("inc") == 0)
    {
        std::stable_sort(shapes.begin(), shapes.end(), compare_perimeter_inc);
    }
    else if (property.compare("perimeter") == 0 && order.compare("inc") == 0)
    {
        std::stable_sort(shapes.begin(), shapes.end(), compare_perimeter_inc);
    }
    else if (property.compare("area") == 0 && order.compare("inc") == 0)
    {
        std::stable_sort(shapes.begin(), shapes.end(), compare_area_inc);
    }
    else if (property.compare("area") == 0 && order.compare("dec") == 0)
    {
        std::stable_sort(shapes.begin(), shapes.end(), compare_area_dec);
    }
    else
    {
        std::cerr << "Neither area nor perimeter" << std::endl;
        return;
    }
}
void cleanup_shapes(std::vector<Shape *> &shapes)
{
    for (Shape *shape : shapes)
    {
        delete shape;
    }
    shapes.clear();
}