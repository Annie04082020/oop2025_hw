#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>
#include <vector>

#include "library_item.h"
#include "library_management_system.h"

LibraryManagementSystem::LibraryManagementSystem()
{
}

LibraryItem::Ticket LibraryManagementSystem::add_item(LibraryItem *item)
{
    if (item == nullptr)
    {
        return LibraryItem::Ticket(-1);
    }
    this->libitems[this->id_counter] = item;
    long currentID = this->id_counter;
    this->id_counter++;
    return LibraryItem::Ticket(currentID);
}
bool LibraryManagementSystem::remove_item(const LibraryItem::Ticket &ticket)
{
    if (!this->is_available(ticket))
    {
        return false;
    }
    auto find_lib = this->libitems.find(ticket.get_token());
    // first means token, second means the library item pointer
    delete find_lib->second;
    // sending iterator is quicker than token
    this->libitems.erase(find_lib);
    return true;
}
bool LibraryManagementSystem::checkout(const LibraryItem::Ticket &ticket)
{
    if (!this->is_available(ticket))
    {
        return false;
    }
    this->checkedoutTokens.insert(ticket.get_token());
    return true;
}
bool LibraryManagementSystem::return_item(const LibraryItem::Ticket &ticket)
{
    long ticket_token = ticket.get_token();
    auto find_lib = this->libitems.find(ticket_token);
    auto find_checkedout = this->checkedoutTokens.find(ticket_token);
    if (ticket_token == -1)
    {
        return false;
    }
    else if (find_lib == this->libitems.end())
    {
        return false;
    }
    else if (find_checkedout == this->checkedoutTokens.end())
    {
        return false;
    }
    this->checkedoutTokens.erase(find_checkedout);
    return true;
}
bool LibraryManagementSystem::is_available(const LibraryItem::Ticket &ticket)
{
    long ticket_token = ticket.get_token();
    // std::unordered_map<long, LibraryItem *>::const_iterator find_lib = this->libitems.find(ticket_token);
    auto find_lib = this->libitems.find(ticket_token);
    // std::unordered_set<long>::const_iterator find_checkedout = this->checkedoutTokens.find(ticket_token);
    auto find_checkedout = this->checkedoutTokens.find(ticket_token);
    if (ticket_token == -1)
    {
        return false;
    }
    else if (find_lib == this->libitems.end())
    {
        return false;
    }
    else if (find_checkedout != this->checkedoutTokens.end())
    {
        return false;
    }
    return true;
}

int LibraryManagementSystem::get_total_items()
{
    return this->libitems.size();
}
int LibraryManagementSystem::get_available_items()
{
    return this->libitems.size() - this->checkedoutTokens.size();
}

void LibraryManagementSystem::clear()
{
    for (auto &[id, book_ptr] : this->libitems)
    {
        delete book_ptr;
    }
    this->libitems.clear();
    this->checkedoutTokens.clear();
    this->id_counter = 1;
}
