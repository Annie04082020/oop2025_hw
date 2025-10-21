#include <vector>
#include <string>
#include <algorithm>
#include "library_item.h"
#include "library_management_system.h"

LibraryManagementSystem::LibraryManagementSystem() {};

void LibraryManagementSystem::add_item(LibraryItem *item)
{
    library.push_back(item);
};
std::vector<LibraryItem *> LibraryManagementSystem::search_by_title(std::string title)
{
    std::vector<LibraryItem *> result;
    for (auto item : library)
    {
        if (item->get_title() == title)
        {
            result.push_back(item);
        };
    }
    return result;
};
std::vector<LibraryItem *> LibraryManagementSystem::search_by_author(std::string author)
{
    std::vector<LibraryItem *> result;
    for (auto item : library)
    {
        if (item->get_author() == author)
        {
            result.push_back(item);
        };
    }
    return result;
};

int LibraryManagementSystem::get_total_items()
{
    return library.size();
};
