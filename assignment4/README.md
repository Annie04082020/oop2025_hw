# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 4

### Deadline: 2025/10/26 (Sun.) 23:59

### Purpose of this assignment:
Let students practice the constructors, inheritance, and polymorphism in C++17.

### Problems:
For this assignment, you need to write a new `LibraryManagementSystem` that manages `Book`, `ReferenceBook`, and `EBook` classes. These classes are inherited from a base class `LibraryItem`. The `LibraryManagementSystem` should be able to add books and search for books by title or author in the library.

Please implement and test the following classes and methods:

#### Base Class `LibraryItem`:
- **Constructor**: `LibraryItem(long unique_id, std::string title, std::string author)`
- **Methods**:
  - `get_unique_id()` - Returns the unique ID of the item
  - `get_title()` - Returns the title of the item
  - `get_author()` - Returns the author of the item  
  - `get_type()` - Returns the type of item (pure virtual)
  - `to_string()` - Returns string representation of the item (pure virtual)

#### Derived Class `Book`:
- **Constructor**: `Book(long unique_id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns "Book"
  - `to_string()` - Returns formatted string with book details
    - Format: "Book: {title} by {author}"

#### Derived Class `ReferenceBook`:
- **Constructor**: `ReferenceBook(long unique_id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns "ReferenceBook"
  - `to_string()` - Returns formatted string with reference book details
    - Format: "ReferenceBook: {title} by {author}"

#### Derived Class `EBook`:
- **Constructor**: `EBook(long unique_id, std::string title, std::string author)`
- **Methods**:
  - `get_type()` - Returns "EBook"
  - `to_string()` - Returns formatted string with EBook details
    - Format: "EBook: {title} by {author}"

#### `LibraryManagementSystem` Class:
- **Methods**:
  - `add_item(LibraryItem* item)` - Adds an item to the library
  - `search_by_title(std::string title)` - Returns `std::vector<LibraryItem*>` containing items matching the title
  - `search_by_author(std::string author)` - Returns `std::vector<LibraryItem*>` containing items by the author
  - `get_total_items()` - Returns the total number of items

(For these methods, you have to write at least one test for yourself.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Class Declaration
**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**
**The sample code only contains public class declarations. You can add the private members and methods as required according to the requirement.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src/
│   ├── library_item.h (provided by TA)
│   ├── library_item.cpp
│   ├── book.h (provided by TA)
│   ├── book.cpp
│   ├── reference_book.h (provided by TA)
│   ├── reference_book.cpp
│   ├── ebook.h (provided by TA)
│   ├── ebook.cpp
│   ├── library_management_system.h (provided by TA)
│   └── library_management_system.cpp
└── tests/
    ├── ut_book.cpp
    ├── ut_ebook.cpp
    ├── ut_library_item.cpp
    ├── ut_library.cpp
    └── ut_reference_book.cpp
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
    1. Implementation and tests of `LibraryItem` base class (10%)
    2. Implementation and tests of `Book` class (10%)
    3. Implementation and tests of `ReferenceBook` class (10%)
    4. Implementation and tests of `EBook` class (10%)
    5. Implementation and tests of `LibraryManagementSystem` class (10%)
2. Tests by TA (50%)
    1. Tests of `LibraryItem` inheritance and polymorphism (10%)
    2. Tests of `Book` functionality (10%)
    3. Tests of `ReferenceBook` functionality (10%)
    4. Tests of `EBook` functionality (10%)
    5. Tests of `LibraryManagementSystem` operations (10%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. Please use the C++17 standard for your implementation. C++20 features are not supported yet in Jenkins.
3. TA will use the `_TA` project in Jenkins to test your program.