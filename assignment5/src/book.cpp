#include <string>
#include <sstream>
#include "book.h"
#include "library_item.h"

Book::Book(long unique_id, std::string title, std::string author) : LibraryItem(unique_id, title, author) {}

std::string Book::get_type()
{
    return "Book";
};

std::string Book::to_string()
{
    std::ostringstream oss;
    oss << "Book: " << this->get_title() << " by " << this->get_author();
    std::string s = oss.str();
    return s;
};
