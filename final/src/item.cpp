#include "cargo.h"
#include "item.h"
#include "exceptions.h"
#include <iostream>

Item::Item(double weight, bool is_flammable) : weight(weight), is_flammable(is_flammable) {}
Item *Item::make_item(double weight, bool is_flammable)
{
    if (weight < 0)
    {
        return nullptr;
    }
    return new Item(weight, is_flammable);
}
void Item::add(Cargo *cargo)
{
    throw UnsupportedOperationException("Cannot add cargo to an Item.");
}
double Item::get_weight() const
{
    return this->weight;
}
int Item::count_total_items() const
{
    return 1;
}
bool Item::is_dangerous() const
{
    return this->is_flammable;
}
