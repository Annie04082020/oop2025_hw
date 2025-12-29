#ifndef BOX_H
#define BOX_H

#include "cargo.h"
#include <vector>

class Box : public Cargo {
private:
    double empty_weight;
    double max_weight;
    std::vector<Cargo*>& items;
    Box(double empty_weight, double max_weight);

public:
    static Box* make_box(double empty_weight, double max_weight);
    
    void add(Cargo* cargo) override;
    double get_weight() const override;
    
    int count_total_items() const override;
    bool is_dangerous() const override;
    
    void sort_contents();
    const std::vector<Cargo*>& get_contents() const;
    
    ~Box();
};

#endif // BOX_H
