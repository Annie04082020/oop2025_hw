#ifndef LIBRARY_MANAGEMENT_SYSTEM_H
#define LIBRARY_MANAGEMENT_SYSTEM_H

#include <vector>
#include <string>

#include "library_item.h"

class LibraryManagementSystem
{
private:
    std::vector<LibraryItem *> library;

public:
    LibraryManagementSystem();

    void add_item(LibraryItem *item);

    std::vector<LibraryItem *> search_by_title(std::string title);
    std::vector<LibraryItem *> search_by_author(std::string author);

    int get_total_items();
};

#endif // LIBRARY_MANAGEMENT_SYSTEM_H
