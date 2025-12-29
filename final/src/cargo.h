#ifndef CARGO_H
#define CARGO_H

class Cargo {
public:
    virtual void add(Cargo* cargo) = 0;
    virtual double get_weight() const = 0;

    virtual int count_total_items() const = 0;
    virtual bool is_dangerous() const = 0;

    virtual ~Cargo() = default;
};

#endif // CARGO_H
