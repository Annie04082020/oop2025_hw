# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100
* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 6

### Deadline: 2025/11/17 (Mon.) 23:59

### Purpose of this assignment:
Let students practice implementing file I/O operations, command-line argument handling, and geometric shape processing in C++20.
You will implement a complete geometric shape processing system with input/output functionality and a main function that can sort and process different types of shapes.

### Problems:
For this assignment, you need to implement the following core functionalities:

#### Main Requirements:

1. **Main Function Implementation**
   - Command-line argument parsing for geometric shape processing
   - Usage: `./geo <input_file> <output_file> <property> <order>`
   - Support for sorting by area or perimeter in ascending/descending order

2. **File I/O Operations**
   - Read geometric shapes from input files (Triangle, Circle, ConvexPolygon)
   - Write sorted results to output files
   - Handle various file formats and error cases

3. **Shape Processing System**
   - Process multiple shape types: Triangle, Circle, ConvexPolygon
   - Sort shapes by area or perimeter
   - Support both ascending and descending order

You must implement the following components:

### Core Components

#### 1. Main Function (`main.cpp`)
- **Command-line Interface**: Parse arguments for input file, output file, sorting property, and order
- **Input Validation**: Validate command-line arguments and file accessibility
- **Coordinate Processing**: Integrate all components to provide complete functionality

#### 2. File I/O Utilities (`geo_utils.h/cpp`)
- **`read_shapes_from_file()`**: Parse geometric shapes from input files
  - Support Triangle format: `Triangle x1 y1 x2 y2 x3 y3`
  - Support Circle format: `Circle x y radius`
  - Support ConvexPolygon format: `ConvexPolygon x1 y1 x2 y2 ... xn yn`
- **`write_shapes_to_file()`**: Output sorted shapes to file. The format should match the input format with 2 decimal precision.
- **`sort_shapes_by_property()`**: Sort shapes by area or perimeter with the specified order (ascending/descending). **You need to ensure that the sorting is stable.**

#### 3. Shape Classes
- **Triangle**: Implements area, perimeter, and string representation
- **Circle**: Implements area, perimeter, and string representation
- **ConvexPolygon**: Implements area, perimeter, and string representation

#### 4. Input/Output Format
- **Input File Example**:
  ```
  Triangle 0 0 3 0 0 4
  Circle 1 1 2
  ConvexPolygon 0 0 2 0 2 2 0 2
  ```
- **Output File**: Contains sorted shapes in their string representation format

### Repository Structure
```
. (oop2025f_{student ID}_hw6)
├── .gitignore
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── geo_utils.h
│   ├── geo_utils.cpp
│   ├── point.h
│   ├── point.cpp
│   ├── shape.h
│   ├── triangle.h
│   ├── triangle.cpp
│   ├── circle.h
│   ├── circle.cpp
│   ├── convex_polygon.h
│   └── convex_polygon.cpp
├── tests/
│   ├── ut_triangle.cpp
│   ├── ut_circle.cpp
│   ├── ut_convex_polygon.cpp
│   └── ut_geo_utils.cpp
└── build/
    └── geo
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
```

#### Run Unit Tests
```bash
$ ./unit_tests
```

#### Run Main Program
```bash
$ ./geo <input_file> <output_file> <property> <order>

# Examples:
$ ./geo input.txt output.txt area inc
$ ./geo input.txt output.txt perimeter dec
```

#### Usage Parameters:
- **input_file**: Path to input file containing shape definitions
- **output_file**: Path to output file for sorted results
- **property**: `area` or `perimeter` - property to sort by
- **order**: `inc` (ascending) or `dec` (descending) - sort order

### Score

1. Implementation and tests by yourself (40%)
  1. Implementation and tests of `read_shapes_from_file` method (15%)
  2. Implementation and tests of `write_shapes_to_file` method (15%)
  3. Implementation and tests of `sort_shapes_by_property` method (10%)

2. Memory management: 10%
  1. **Proper memory allocation and deallocation (10%)**: In the test and the main program, you need to ensure that all dynamically allocated memory is properly released to avoid memory leaks.

3. Tests by TA (50%)
  1. Tests of `read_shapes_from_file` method with various polygons (15%)
  2. Tests of `write_shapes_to_file` method with various polygons (15%)
  3. Main function tests including command-line argument handling and file I/O (20%)

Total: 100%

### Notes
1. **Ensure that the program does not cause memory leaks.**
2. You can use C++20 features.
3. The Shoelace formula should work for any convex polygon (triangle, square, pentagon, hexagon, octagon, etc.).
4. Implement proper convexity validation to reject concave polygons.
5. TA will use the `_TA` project in Jenkins to test your program.