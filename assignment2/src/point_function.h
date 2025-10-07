#ifndef POINT_FUNCTION_H
#define POINT_FUNCTION_H

#include <string>
#include "point.h"

double get_euclidean_distance(Point p, Point q);

std::string get_quadrant(Point p);

bool is_collinear(Point p, Point q, Point r);

Point get_midpoint(Point p, Point q);

#endif