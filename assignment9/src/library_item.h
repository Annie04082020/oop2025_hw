#ifndef LIBRARY_ITEM_H
#define LIBRARY_ITEM_H

#include <string>

class LibraryItem {
public:
    // Inner class Ticket for managing library items
    class Ticket {
    private:
        long token;

    public:
        Ticket(long token);
        long get_token() const;
    };

protected:
    std::string title;
    std::string author;

public:
    LibraryItem(std::string title, std::string author);

    std::string get_title();
    std::string get_author();

    virtual std::string get_type() = 0;
    virtual std::string to_string() = 0;
};

#endif // LIBRARY_ITEM_H
