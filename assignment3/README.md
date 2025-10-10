# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 3

### Deadline: 2025/10/15 (Wed.) 23:59

### Purpose of this assignment:
Let students practice the tests and the use of class methods.

### Problems:
For this assignment, you need to revise functions to methods for `Point`, write methods for `Triangle`, and test them.

Please implement and test the following methods for `Point`:

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

Please implement and test the following methods for `Triangle`:

- `perimeter`
    - Returns the perimeter of the triangle.
    - Reference: https://en.wikipedia.org/wiki/Triangle
- `is_equilateral`
    - Returns whether the triangle is equilateral (all sides are equal).
    - Reference: https://en.wikipedia.org/wiki/Equilateral_triangle
- `is_right`
    - Returns whether the triangle is a right triangle (one angle is 90 degrees).
    - Reference: https://en.wikipedia.org/wiki/Right_triangle

(For those methods, you have to write at least one test for yourself.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Class Declaration
- src/point.h
```c++
#ifndef POINT_H
#define POINT_H

#include <string>
class Point{
public:
    double x;
    double y;
    
    double get_euclidean_distance(Point q);

    std::string get_quadrant();

    bool is_collinear(Point q, Point r);
    
    Point get_midpoint(Point q);
};
#endif
```

- src/triangle.h
```c++
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"

class Triangle{
public:
    Point p;
    Point q;
    Point r;

    double perimeter();

    bool is_equilateral();

    bool is_right();
};
#endif
```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src
│   ├── point.cpp
│   ├── point.h (provided by TA)
│   ├── triangle.cpp
│   └── triangle.h (provided by TA)
└── tests
    ├── ut_point.cpp
    └── ut_triangle.cpp
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
    1. Implementation and tests of `get_euclidean_distance` (5%)
    2. Implementation and tests of `get_quadrant` (5%)
    3. Implementation and tests of `is_collinear` (5%)
    4. Implementation and tests of `get_midpoint` (5%)
    5. Implementation and tests of `perimeter` (10%)
    6. Implementation and tests of `is_equilateral` (10%)
    7. Implementation and tests of `is_right` (10%)
2. Tests by TA (50%)
    1. Tests of `get_euclidean_distance` (5%)
    2. Tests of `get_quadrant` (5%)
    3. Tests of `is_collinear` (5%)
    4. Tests of `get_midpoint` (5%)
    5. Tests of `perimeter` (10%)
    6. Tests of `is_equilateral` (10%)
    7. Tests of `is_right` (10%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPCET, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPCET, ACTUAL)` for testing the float number.
3. TA will use the `_TA` project in Jenkins to test your program.
