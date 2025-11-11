#ifndef GEO_UTILS_H
#define GEO_UTILS_H

#include <vector>
#include <string>
#include <filesystem>
#include "shape.h"

// 從文件讀取形狀的函數
std::vector<Shape*> read_shapes_from_file(const std::filesystem::path& filename);

// 將形狀寫入文件的函數
void write_shapes_to_file(const std::vector<Shape*>& shapes, const std::filesystem::path& filename);

// 根據屬性和順序排序形狀的函數
void sort_shapes_by_property(std::vector<Shape*>& shapes, const std::string& property, const std::string& order);

#endif // GEO_UTILS_H
