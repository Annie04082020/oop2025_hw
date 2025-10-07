# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 2

### Deadline: 2025/10/07 (Tue.) 23:59

### Purpose of this assignment:
Let students practice the tests and the use of basic functions.

### Problems:

In class, you have learned and written the simple class `Point` and function `inner_product`. For this assignment, you have to write some basic functions for `Point`, and test them!

Please implement and test the following functions:

- `get_euclidean_distance`
    - Returns the distance between the two points.
    - Reference: https://en.wikipedia.org/wiki/Euclidean_distance
- `get_quadrant`
    - Returns the quadrant of `first`, `second`, `third`, or `fourth` in which the point is located.
    - Returns `not in any quadrant` if a point is located on the x-axis or the y-axis.
    - Reference: https://en.wikipedia.org/wiki/Quadrant_(plane_geometry)
- `is_collinear`
    - Returns whether the three points are collinear (located on the same line).
    - Reference: https://en.wikipedia.org/wiki/Collinearity
- `get_midpoint`
    - Returns the midpoint of the two points.
    - Reference: https://en.wikipedia.org/wiki/Midpoint

(For those functions, you have to write at least one test for yourself.)

Please follow the function declaration and write the implementation in the corresponding `.cpp` files.

### Function Declaration
- src/point.h
```c++
#ifndef POINT_H
#define POINT_H

class Point{
    public:
        double x;
        double y;
};

#endif
```

- src/point_function.h
```c++
#ifndef POINT_FUNCTION_H
#define POINT_FUNCTION_H

#include <string>
#include "point.h"

double get_euclidean_distance(Point p, Point q);

std::string get_quadrant(Point p);

bool is_collinear(Point p, Point q, Point r);

Point get_midpoint(Point p, Point q);

#endif
```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src
│   ├── point_function.cpp
│   ├── point_function.h (provided by TA)
│   └── point.h (provided by TA)
└── tests
    └── ut_point_function.cpp
```

### Commands to Execute the Program

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Implementation and tests by yourself (50%)
    1. Implementation and tests of `get_euclidean_distance` (12.5%)
    2. Implementation and tests of `get_quadrant` (12.5%)
    3. Implementation and tests of `is_collinear` (12.5%)
    4. Implementation and tests of `get_midpoint` (12.5%)
2. Tests by TA (50%)
    1. Tests of `get_euclidean_distance` (12.5%)
    2. Tests of `get_quadrant` (12.5%)
    3. Tests of `is_collinear` (12.5%)
    4. Tests of `get_midpoint` (12.5%)

Total: 100%

### Notes

1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPCET, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPCET, ACTUAL)` for testing the float number.
3. TA will use the `_TA` project in Jenkins to test your program.
