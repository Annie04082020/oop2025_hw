#include <vector>
#include <algorithm>
#include "exceptions.h"
#include "box.h"
#include "cargo.h"

// Don't need to initialize the vector
Box::Box(double empty_weight, double max_weight) : empty_weight(empty_weight), max_weight(max_weight)
{
}
Box *Box::make_box(double empty_weight, double max_weight)
{
    if (empty_weight < 0 || max_weight < 0)
    {
        return nullptr;
    }
    else if (empty_weight > max_weight)
    {
        return nullptr;
    }
    return new Box(empty_weight, max_weight);
}
void Box::add(Cargo *cargo)
{
    if (this->get_weight() + cargo->get_weight() > this->max_weight)
    {
        throw WeightLimitExceeded("Cannot add cargo. Exceeds max weight.");
    }
    this->items.push_back(cargo);
}
double Box::get_weight() const
{
    double content_weight = 0;
    if (this->items.size() == 0)
    {
        return empty_weight;
    }
    for (auto item : items)
    {
        content_weight += item->get_weight();
    }
    return this->empty_weight + content_weight;
}
int Box::count_total_items() const
{
    int count_items = 0;
    for (auto item : items)
    {
        count_items += item->count_total_items();
    }
    return count_items;
}
bool Box::is_dangerous() const
{
    bool danger = false;
    for (auto item : items)
    {
        // save the result
        danger = danger || item->is_dangerous();
    }
    return danger;
}
void Box::sort_contents()
{
    // not sorting by any specific criteria as Cargo doesn't have comparable attributes
    std::sort(items.begin(), items.end(), [](Cargo *a, Cargo *b)
              {
                  // Ascending order by weight
                  return a->get_weight() < b->get_weight(); // 比較重量，由小到大
              });
};
const std::vector<Cargo *> &Box::get_contents() const
{
    return this->items;
}
Box::~Box()
{
    for (auto item : items)
    {
        delete item;
    }
}