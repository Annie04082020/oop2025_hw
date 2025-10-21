#include <string>
#include <sstream>
#include "ebook.h"
#include "library_item.h"

EBook::EBook(long unique_id, std::string title, std::string author) : LibraryItem(unique_id, title, author) {}

std::string EBook::get_type()
{
    return "EBook";
}

std::string EBook::to_string()
{
    std::ostringstream oss;
    oss << "EBook: " << this->title << " by " << this->author;
    std::string s = oss.str();
    return s;
}
