#include <string>
#include "library_item.h"

LibraryItem::LibraryItem(long unique_id, std::string title, std::string author) : unique_id(unique_id), title(title), author(author) {};

long LibraryItem::get_unique_id()
{
    return this->unique_id;
}
std::string LibraryItem::get_title()
{
    return this->title;
}
std::string LibraryItem::get_author()
{
    return this->author;
}