#ifndef SAVE_SHAPE_H
#define SAVE_SHAPE_H
#include "shape.h"
#include <fstream>

void save_shapes_to_file(std::vector<Shape*> &shapes, std::string filename){
    std::ofstream ofs (filename);
    for(auto shape : shapes){
        ofs << shape->to_string() << std::endl;
    }
    ofs.close();
}

#endif
