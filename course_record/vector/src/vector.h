#pragma once

#include <iostream>
double innerProduct(double u[], int uSize, double v[], int vSize) {
    if (uSize != vSize) {
        throw "size not equal";
    }
    
    double result = 0;
    for (int i = 0; i < uSize; i++) {
        result += u[i] * v[i];
    }
    return result;
}

class Vector {
private:
    int _dim;
    double * _component;
public:
    Vector (double* data, int size): _dim(size) {
        _component = new double[_dim]; // allocate memory for _component
        for (int i = 0; i < _dim; i++) {
            _component[i] = data[i];
        }
    }

    // copy constructor; deep copy
    Vector(const Vector& other) {
        _dim = other._dim;
        _component = new double[_dim];
        
        for (int i = 0; i < _dim; i++) {
            _component[i] = other._component[i];
        }
    }
    // This is what C++ gives you: memberwise copy; shallow copy
    // Vector(const Vector& other) {
    //     _dim = other._dim;
    //     _component = other._component;
    // }
    
    // copy assignment operator
    
    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        
        delete[] _component;
        _dim = other._dim;
        _component = new double[_dim];
        
        for (int i = 0; i < _dim; i++) {
            _component[i] = other._component[i];
        }
        
        return *this;
    }

    double get(int i) const{
        return _component[i];
    }

    void print() {
        for (int i = 0; i < _dim; i++) {
            std::cout << _component[i] << " ";
        }
        std::cout << std::endl;
    }


    ~Vector() {
        std::cout << "~Vector() called" << std::endl; // "destructor called" will be printed when the destructor is called
        delete[] _component; // deallocate memory for _component
    }
};

void call_by_value(Vector v) {
    v.print();
}