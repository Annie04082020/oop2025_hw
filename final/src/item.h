#ifndef ITEM_H
#define ITEM_H

#include "cargo.h"

class Item : public Cargo {
private: 
    double weight;
    bool is_flammable;
    Item(double weight,bool is_flammable);

public:
    static Item* make_item(double weight, bool is_flammable);

    void add(Cargo* cargo) override;
    double get_weight() const override;
    
    int count_total_items() const override;
    bool is_dangerous() const override;
};

#endif // ITEM_H
