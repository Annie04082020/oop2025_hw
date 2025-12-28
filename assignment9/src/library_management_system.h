#ifndef LIBRARY_MANAGEMENT_SYSTEM_H
#define LIBRARY_MANAGEMENT_SYSTEM_H

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>

#include "library_item.h"

class LibraryManagementSystem
{
private:
    std::unordered_map<long, LibraryItem *> libitems;
    long id_counter = 1;
    std::unordered_set<long> checkedoutTokens;

public:
    LibraryManagementSystem();

    LibraryItem::Ticket add_item(LibraryItem *item);
    bool remove_item(const LibraryItem::Ticket &ticket);

    bool checkout(const LibraryItem::Ticket &ticket);
    bool return_item(const LibraryItem::Ticket &ticket);
    bool is_available(const LibraryItem::Ticket &ticket);

    int get_total_items();
    int get_available_items();

    void clear();
};

#endif // LIBRARY_MANAGEMENT_SYSTEM_H
