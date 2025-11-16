#include <iostream>
#include <filesystem>
#include "geo_utils.h"
#include "shape.h"
#include "shape.h"
#include "circle.h"
#include "triangle.h"
#include "convex_polygon.h"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file> <property> <order>" << std::endl;
        std::cerr << "Example: " << argv[0] << " input.txt output.txt area inc" << std::endl;
        return 1;
    }
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    std::string property = argv[3];
    std::string order = argv[4];
    std::vector<Shape *> shapes;
    try
    {
        shapes = read_shapes_from_file(input_file);
        sort_shapes_by_property(shapes, property, order);
        write_shapes_to_file(shapes, output_file);
        std::cout << "Successfully processed " << shapes.size() << " shapes." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        // (在清理記憶體後返回錯誤)
    }
    for (Shape *shape : shapes)
    {
        delete shape;
    }
    shapes.clear();

    return 0;
}
