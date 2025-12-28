# Problem Statement

A simple geometry application called _geo_ is needed to sort shapes such as triangles, circles, rectangles and others, for example, a compound shape made of a circle and triangle to represent as exclamation sign (!). As a command line application, _geo_ reads shapes from an input file, sorts the shapes by area or perimeter in increasing order or decreasing order, and write the result to an output file. 

# Features and Tasks
- [ ] F1: Read input file
- [ ] F2: Write output file
    - [x] T2.1: Convert triangle to a string
    - [ ] T2.2: Convert circle to a string
    - [ ] T2.3: Convert rectangle to a string
    - [ ] T2.4: Convert convex polygon to a string
    - [x] T2.5: Output a vector of shapes to a file
- [ ] F3: Shapes representation & computation
    - [x] T3.1: point 
    - [x] T3.2: triangles
    - [x] T3.3: circle
    - [ ] T3.4: rectangles
    - [x] T3.5: convex polygon
    - [x] T3.6: learn constructors, member initializer list, and list initialization
    - [x] T3.7: learn destructors to release memory correctly; rule of three
    - [x] T3.8: compound shape: for example, exclamation made of a triangle and a circle
    - [x] T3.9: redesign compoundShape to avoid returning raw pointer to shapes
    - [ ] T3.10: sum of areas of all triangles of a compound
- [ ] F4: Sorting by area or perimeter
    - [x] T4.1: Learn how to sort integers with standard library
    - [x] T4.2: Sort shapes by area by increasing order
    - [ ] T4.3: Sort shapes by area by decreasing order
    - [x] T4.4: Sort shapes by perimeter by increasing order
    - [ ] T4.5: Sort shapes by perimeter by decreasing order
- [ ] F5: Command line argument processing
