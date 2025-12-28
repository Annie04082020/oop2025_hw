# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100
* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080
* [Assignment 4](http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment4): http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment4
* [Assignment 5](http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment5): http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment5

## Assignment 9

### Deadline: 2025/12/22 (Mon.) 23:59

### Purpose of this assignment:
Let students practice Object-Oriented Programming concepts including inner classes and the Simple Factory pattern in C++.

### Problems:
For this assignment, you will implement a library management system with the following features:
- **Inner Class**: `Ticket` class inside `LibraryItem`
- **Simple Factory Pattern**: Static factory methods for creating objects

### Class Definitions

#### Class `LibraryItem`
Abstract base class for all library items.

- **Inner Class `Ticket`**:
  - `Ticket(long token)`: Constructor
  - `long get_token() const`: Returns the token value (-1 indicates invalid ticket)

- **Protected Members**:
  - `std::string title`
  - `std::string author`

- **Public Methods**:
  - `LibraryItem(std::string title, std::string author)`: Constructor
  - `std::string get_title()`: Returns the title
  - `std::string get_author()`: Returns the author
  - `virtual std::string get_type() = 0`: Pure virtual, returns item type
  - `virtual std::string to_string() = 0`: Pure virtual, returns string representation

#### Class `Book` (extends `LibraryItem`)
- **Private Constructor**: `Book(std::string title, std::string author)`
- **Static Factory Method**: `static LibraryItem* make_book(std::string title, std::string author)`
  - Returns `nullptr` if title or author is empty
- **Methods**:
  - `std::string get_type() override`: Returns `"Book"`
  - `std::string to_string() override`: Returns `"Book: <title> by <author>"`

#### Class `ReferenceBook` (extends `LibraryItem`)
- **Private Constructor**: `ReferenceBook(std::string title, std::string author)`
- **Static Factory Method**: `static LibraryItem* make_reference_book(std::string title, std::string author)`
  - Returns `nullptr` if title or author is empty
- **Methods**:
  - `std::string get_type() override`: Returns `"ReferenceBook"`
  - `std::string to_string() override`: Returns `"ReferenceBook: <title> by <author>"`

#### Class `LibraryManagementSystem`
Manages library items with checkout/return functionality.

- **Public Methods**:
  - `LibraryManagementSystem()`: Constructor
  - `LibraryItem::Ticket add_item(LibraryItem* item)`: Adds an item to the library
    - Returns a `Ticket` that can be used to reference the item
    - If `item` is `nullptr`, returns an invalid ticket with token = -1
    - Each successful add generates a unique token starting from 1
  - `bool remove_item(const LibraryItem::Ticket& ticket)`: Removes an item from the library
    - Returns `true` if the item was successfully removed
    - Returns `false` if:
      - The ticket is invalid (token = -1)
      - The item does not exist in the library
      - The item is currently checked out
  - `bool checkout(const LibraryItem::Ticket& ticket)`: Checks out an item
    - Returns `true` if the item was successfully checked out
    - Returns `false` if:
      - The ticket is invalid (token = -1)
      - The item does not exist in the library
      - The item is already checked out
  - `bool return_item(const LibraryItem::Ticket& ticket)`: Returns a checked out item
    - Returns `true` if the item was successfully returned
    - Returns `false` if:
      - The ticket is invalid (token = -1)
      - The item does not exist in the library
      - The item is not currently checked out
  - `bool is_available(const LibraryItem::Ticket& ticket)`: Checks if an item is available
    - Returns `true` if the item exists and is not checked out
    - Returns `false` if:
      - The ticket is invalid (token = -1)
      - The item does not exist in the library
      - The item is currently checked out
  - `int get_total_items()`: Returns the total number of items in the library
  - `int get_available_items()`: Returns the number of items that are not checked out
  - `void clear()`: Removes all items and clears all checkout records

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
│   ├── library_management_system.h (provided by TA)
│   └── library_management_system.cpp
└── tests/
    ├── ut_book.cpp
    ├── ut_library_item.cpp
    ├── ut_library_management_system.cpp
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
2. Tests by TA (50%)

Total: 100%

### Notes
1. **Ensure that the program does not cause memory leaks.**
2. You can use C++20 features.
3. Constructors for `Book` and `ReferenceBook` must be private - use factory methods only.
4. Factory methods must return `nullptr` when title or author is empty.
5. Checked out items cannot be removed - must be returned first.
6. TA will use the `_TA` project in Jenkins to test your program.
