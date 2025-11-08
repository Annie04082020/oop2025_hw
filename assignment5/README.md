# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100
* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080
* [Assignment 4](http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment4): http://140.124.181.100/course/oop2025f_assignment/-/tree/assignment4

## Assignment 5

### Deadline: 2025/11/09 (Sun.) 23:59

### Purpose of this assignment:
Let students practice file input/output and memory-safe management of dynamically allocated objects in C++20.
You will extend the `LibraryManagementSystem` implemented in Assignment 4 to support saving and loading library data from text files.

### Problems:
For this assignment, you will enhance your previous library system to support persistent storage using text files.
Specifically, you need to **save** all library items to a file and **load** them back when restarting the system.

You must implement the following new functionalities:

### Updates to Existing Classes

#### Class `LibraryManagementSystem`
Add the following new methods:

- **Methods**:
  - `bool remove_item(long id)`  
    Removes the library item with the specified ID from the system.  
    Ensure proper memory management when removing items.
    Returns `true` if the item was found and removed, `false` otherwise.

  - `void clear()`  
    Clears all library items from the system, ensuring no memory leaks.
  
  - `void save_to_file(const std::filesystem::path& output_path)`  
    Saves all current library items to the specified text file.  
    Each line should contain the type, title, and author separated by commas.  
    Example output line:  
    ```
    Book,The C++ Programming Language,Bjarne Stroustrup
    ```
  - `void load_from_file(const std::filesystem::path& input_path)`  
    Clears the current items and loads new items from the specified file.  
    Each line corresponds to a library item.  
    Use the second field (type) to determine which derived class to instantiate (`Book`, `ReferenceBook`, or `EBook`).
    Skip any malformed lines.

#### File Format
Each item should be stored in one line with the following format:
```
<unique_id>,<type>,<title>,<author>
```
Example file content:
```
1,Book,The Pragmatic Programmer,Andrew Hunt
2,ReferenceBook,Design Patterns,Erich Gamma
3,EBook,Clean Code,Robert C. Martin
```

### Repository Structure
```
. (oop2025f_{student ID}_hw5)
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
    ├── ut_reference_book.cpp
    └── ut_file_io.cpp
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
  1. Implementation and tests of `remove_item` (15%)
  2. Implementation and tests of file writing (`save_to_file`) (15%)
  3. Implementation and tests of file reading (`load_from_file`) (15%)
  4. Implementation and tests of `clear()` function (5%)

2. Tests by TA (50%)
  1. Tests of `remove_item` (15%)
  2. Tests of file writing (`save_to_file`) (15%)
  3. Tests of file reading (`load_from_file`) (15%)
  4. Tests of `clear()` function (5%)

Total: 100%

### Notes
1. Ensure that the program does not cause memory leaks.  
2. You can use C++20 features.
3. Follow the file format exactly. TA tests will depend on it.
4. TA will use the `_TA` project in Jenkins to test your program.
