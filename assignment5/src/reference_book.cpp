#include <string>
#include <sstream>
#include "reference_book.h"
#include "library_item.h"

ReferenceBook::ReferenceBook(long unique_id, std::string title, std::string author) : LibraryItem(unique_id, title, author) {}

std::string ReferenceBook::get_type()
{
    return "ReferenceBook";
};

std::string ReferenceBook::to_string()
{
    std::ostringstream oss;
    oss << "ReferenceBook: " << get_title() << " by " << get_author();
    std::string s = oss.str();
    return s;
};
