#ifndef BOOK_H
#define BOOK_H

#include <string>

#include "library_item.h"

class Book : public LibraryItem {
private:
    Book(std::string title, std::string author);

public:
    static LibraryItem* make_book(std::string title, std::string author);
    std::string get_type() override;
    std::string to_string() override;
};

#endif // BOOK_H
