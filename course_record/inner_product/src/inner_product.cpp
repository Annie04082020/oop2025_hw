#include <cmath>
#include <array>
#include "inner_product.h"

double inner_product(double u[], double v[], int u_dim, int v_dim){
    if(u_dim != v_dim){
        return std::nan("");
    }
    double result = 0.0;
    for (int i = 0; i < u_dim; i++){
        result += u[i] * v[i];
    }
    return result;
}

double inner_product(std::vector<double> u, std::vector<double> v){
    
    double result = 0.0;
    for (int i = 0; i < u.size(); i++){
        result += u[i] * v[i];
    }
    return result;
}