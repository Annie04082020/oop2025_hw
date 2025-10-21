#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>

class LibraryItem
{
protected:
    long unique_id;
    std::string title;
    std::string author;

public:
    LibraryItem(long unique_id, std::string title, std::string author);

    virtual ~LibraryItem() = default;

    long get_unique_id();
    std::string get_title();
    std::string get_author();

    virtual std::string get_type() = 0;
    virtual std::string to_string() = 0;
};

#endif // LIBRARY_ITEM_H
