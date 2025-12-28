#include <iostream>
#include "reference_book.h"
#include "library_item.h"

ReferenceBook::ReferenceBook(std::string title, std::string author) : LibraryItem(title, author) {}

LibraryItem *ReferenceBook::make_reference_book(std::string title, std::string author)
{
    if (title.empty() || author.empty())
    {
        return nullptr;
    }

    return new ReferenceBook(title, author);
}

std::string ReferenceBook::get_type()
{
    return "ReferenceBook";
}
std::string ReferenceBook::to_string()
{
    return "ReferenceBook: " + this->get_title() + " by " + this->get_author();
}