#ifndef AMOEBA_H
#define AMOEBA_H

#include "ext_amoeba.h"
#include "shape.h"

class Amoeba : public Shape {
private:
    ExtAmoeba* _ea;
public:
    Amoeba(ExtAmoeba* ea): _ea(ea) {}
    double area() const override {
        return _ea->aarea();
    }

    double perimeter() const override {
        return _ea->aperimeter();
    }
};

class Amoeba2 : public Shape, private ExtAmoeba {
public:
    double area() const override {
        // return aarea();
        return const_cast<ExtAmoeba*>(static_cast<const ExtAmoeba*>(this))->aarea();
    }

    double perimeter() const override {
        // return aperimeter();
        return const_cast<ExtAmoeba*>(static_cast<const ExtAmoeba*>(this))->aperimeter();
    }
};

#endif