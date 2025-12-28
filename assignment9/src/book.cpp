#include <iostream>
#include "book.h"
#include "library_item.h"

Book::Book(std::string title, std::string author) : LibraryItem(title, author) {}

LibraryItem *Book::make_book(std::string title, std::string author)
{
    if (title.empty() || author.empty())
    {
        return nullptr;
    }

    return new Book(title, author);
}

std::string Book::get_type()
{
    return "Book";
}
std::string Book::to_string()
{
    return "Book: " + this->get_title() + " by " + this->get_author();
}