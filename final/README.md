# Object-Oriented Programming 2025 Fall Final Exam

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Final Exam
- There are only five websites allowed to visit:
  1. [cppreference.com](https://en.cppreference.com/w/)
  2. [cplusplus.com](https://cplusplus.com/)
  3. [cambridge dictionary](https://dictionary.cambridge.org/zht/)
  4. [code in class](http://140.124.181.100/yccheng/oop2025f)
  5. [Jenkins](http://140.124.181.97:8080/)
  6. your homework repository.
- **!! Important !! You will be considered as cheating if you visit other websites not listed above. !! Important !!**

### Deadline: 2025/12/29 (Mon.) 12:10 PM

For this exam, you need to write a logistics cargo system. Please implement the features in the following suggested order:
1.  **Construction**: Implement factories to create valid objects.
2.  **Structure**: Build the composite structure (boxes inside boxes).
3.  **Recursion**: Implement recursive counting and weight tracking.
4.  **Logic**: Implement recursive safety checks.
5.  **Sorting**: Sort items inside a box.

### Part 1: Cargo System Implementation (90%)

To implement the system, you need classes called `Item`, `Box`, and `Cargo`.

#### Step 1: Cargo Construction (Factory Methods) (15%)
Since the constructors of `Item` and `Box` might be private or require validation, you must implement static factory methods first to create objects for testing.

- **`Item::make_item(double weight, bool is_flammable)`**:
    - Creates and returns a new `Item` object.
    - **Validation**: If `weight` is negative, return `nullptr`.
- **`Box::make_box(double empty_weight, double max_weight)`**:
    - Creates and returns a new `Box` object.
    - **Validation**: If any weight is negative, or if `empty_weight > max_weight`, return `nullptr`.

#### Step 2: Composite Pattern (Structure & Weight) (25%)
Implement the core structure to allow nesting items and boxes.

- **`Cargo` Interface**:
    - `add(Cargo* cargo)`
    - `get_weight()`
- **`Item` Implementation**:
    - `add`: Throws `UnsupportedOperationException` with message `"Cannot add cargo to an Item."`.
    - `get_weight`: Returns the item's weight.
- **`Box` Implementation**:
    - `add`: Adds a cargo to the box. If adding the cargo would exceed `max_weight`, throw a `WeightLimitExceeded` exception with message `"Cannot add cargo. Exceeds max weight."`.
    - `get_weight`: Recursively calculates and returns `empty_weight` + total weight of all contents.

#### Step 3: Item Counting (Recursive) (20%)
Implement the logic to count how many leaf items are in the structure.

- **`Cargo` Interface**: `count_total_items()`
- **`Item` Implementation**: Returns `1`.
- **`Box` Implementation**: Recursively sums up the `count_total_items()` of all its contents.

#### Step 4: Safety Check (Recursive) (20%)
Implement the logic to determine if a cargo is dangerous.

- **`Cargo` Interface**: `is_dangerous()`
- **`Item` Implementation**: Returns `true` if the item is flammable (`is_flammable` is true), otherwise `false`.
- **`Box` Implementation**: Returns `true` if **any** cargo inside the box is dangerous (Recursive OR logic).

#### Step 5: Sorting (10%)
Implement the functionality to organize contents.

- **`Box` Implementation**:
    - `sortContents()`: Sorts the contents in **ascending order** based on their weight using `std::sort`.
    - `getContents()`: Returns the const reference to the contents vector.

### Part 2: Memory Management (10%)
Since we are using raw pointers, you must handle memory manually to prevent leaks.
- **Destructor**:
    - Implement the destructor for `Box`.
    - It must **recursively delete** all `Cargo*` pointers stored in `contents`.

(For the destructor, you do not need to write a test case, but you should ensure your other tests pass without memory errors.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Class Declaration
- src/cargo.h
```c++
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
```

- src/item.h
```c++
#ifndef ITEM_H
#define ITEM_H

#include "cargo.h"

class Item : public Cargo {
public:
    static Item* make_item(double weight, bool is_flammable);

    void add(Cargo* cargo) override;
    double get_weight() const override;

    int count_total_items() const override;
    bool is_dangerous() const override;
};

#endif // ITEM_H
```

- src/box.h
```c++
#ifndef BOX_H
#define BOX_H

#include "cargo.h"
#include <vector>

class Box : public Cargo {
public:
    static Box* make_box(double empty_weight, double max_weight);
    
    void add(Cargo* cargo) override;
    double get_weight() const override;
    
    int count_total_items() const override;
    bool is_dangerous() const override;
    
    void sortContents();
    const std::vector<Cargo*>& getContents() const;
    
    ~Box();
};

#endif // BOX_H

```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src
│   ├── box.cpp
│   ├── box.h (provided by TA)
│   ├── cargo.h (provided by TA)
│   ├── exceptions.h (provided by TA)
│   ├── item.cpp
│   └── item.h (provided by TA)
└── tests
    ├── ut_box.cpp
    ├── ut_cargo.cpp
    └── ut_item.cpp
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Implementation and tests by yourself (50%)
2. Tests by TA (50%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPECT, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the float number.
3. You should use `EXPECT_STREQ(EXPECT, ACTUAL)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the message from exception.
4. TA will use the `_TA` project in Jenkins to test your program.
