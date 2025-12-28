#include <string>
#include "library_item.h"

LibraryItem::Ticket::Ticket(long token) : token(token)
{
}

long LibraryItem::Ticket::get_token() const
{
    return this->token;
}

LibraryItem::LibraryItem(std::string title, std::string author) : title(title), author(author) {}

std::string LibraryItem::get_title()
{
    return this->title;
}
std::string LibraryItem::get_author()
{
    return this->author;
}
