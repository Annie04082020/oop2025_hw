#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "geo_utils.h"
#include "shape.h"

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
    auto compare_perimeter_inc = [](Shape *a, Shape *b)
    { return a->perimeter() < b->perimeter(); };
    if (property.compare("area") == 0)
    {
        std::sort(shapes.begin(), shapes.end(), compare_area_inc);
    }
    else if (property.compare("perimeter") == 0)
    {
        std::sort(shapes.begin(), shapes.end(), compare_perimeter_inc);
    }
    else
    {
        std::cerr << "Neither area nor perimeter" << std::endl;
        return;
    }
    if (order.compare("desc") == 0)
    {
        std::reverse(shapes.begin(), shapes.end());
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