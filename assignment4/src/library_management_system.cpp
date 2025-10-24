#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
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
    std::string search_title = title;
    std::transform(search_title.begin(), search_title.end(), search_title.begin(), ::tolower);
    for (auto item : library)
    {
        std::string item_title = item->get_title();
        std::transform(item_title.begin(), item_title.end(), item_title.begin(), ::tolower);
        if (item_title.find(search_title) != std::string::npos)
        {
            result.push_back(item);
        };
    }
    return result;
};
std::vector<LibraryItem *> LibraryManagementSystem::search_by_author(std::string author)
{
    std::vector<LibraryItem *> result;
    std::string search_author = author;
    std::transform(search_author.begin(), search_author.end(), search_author.begin(), ::tolower);
    for (auto item : library)
    {
        std::string item_author = item->get_author();
        std::transform(item_author.begin(), item_author.end(), item_author.begin(), ::tolower);
        if (item_author.find(search_author) != std::string::npos)
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
