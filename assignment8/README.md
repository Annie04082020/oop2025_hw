# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100
* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Assignment 8
In this assignment, you will implement a simplified version of the C++ standard library's std::shared_ptr using class templates. This exercise is designed to reinforce core Object-Oriented Programming (OOP) concepts, including:

- Encapsulation
- Polymorphism
- Resource Acquisition Is Initialization (RAII) principles
- Correct Copy Semantics (Constructors and Assignment)
- Dynamic Memory Handling
- Basic Smart Pointer Design

### Deadline: 2025/12/15 (Mon.) 23:59 PM

## Requirements
The SharedPtr<T> class must manage a dynamically allocated object of type T and maintain a shared reference count among all copies. The managed object must be automatically deleted when the last SharedPtr owning it is destroyed or reset.

### SharedPtr()
**Default constructor.** Initializes an empty `SharedPtr` that does not own any object.

### explicit SharedPtr(T* rawPtr)
**Construct from raw pointer.** Constructs a `SharedPtr` that takes ownership of the raw pointer `rawPtr`.

### SharedPtr(const SharedPtr<T>& other)
**Copy constructor.** Creates a new `SharedPtr` that shares ownership with `other`.

### SharedPtr<T>& operator=(const SharedPtr<T>& other)
**Copy assignment operator.** Releases ownership of the currently managed object (if any). Then, it shares ownership with `other`. Returns a reference to the current `SharedPtr` object.

### ~SharedPtr()
**Destructor.** Releases ownership of the currently managed object (if any) and deallocate resources it manages (including any dynamically allocated space) if this is the last `SharedPtr` instance owning the object.

### T& operator*() const
**Dereference operator.** Returns a reference to the managed object. If the `SharedPtr` does not own any object, throw an exception.

### int reference_count() const
**Return reference count.** Returns the current number of `SharedPtr` instances that share ownership of the managed object.

### void reset()
**Release ownership.** Releases ownership of the currently managed object (if any) and deallocate resources it manages (including any dynamically allocated space) if this is the last `SharedPtr` instance owning the object.

## Example header file
```c++
template <typename T>
class SharedPtr {
public:

    // --- Constructors ---
    SharedPtr();                           // Default constructor
    explicit SharedPtr(T* rawPtr);         // Construct from raw pointer
    SharedPtr(const SharedPtr<T>& other);  // Copy constructor

    // --- Assignment ---
    SharedPtr<T>& operator=(const SharedPtr<T>& other); // Copy assignment

    // --- Destructor ---
    ~SharedPtr();

    // --- Observers ---
    T& operator*() const;                  // Dereference operator
    int reference_count() const;                 // Return reference count

    // --- Modifiers ---
    void reset();                          // Release ownership

private:
    //helper functions and data members go here
};
```

## Example Test Cases

### Test 1: Create SharedPtr
**Objective:** Verify the basic creation of a `SharedPtr` from a raw pointer and confirm its initial reference count and dereferenced value.
**Expected Behavior:** A `SharedPtr` initialized with `new int(1)` should have a reference count of 1 and dereference to the value 1.

### Test 2: Share after creation
**Objective:** Test the copy constructor and copy assignment operator to ensure correct sharing of ownership and modification of the managed object.
**Expected Behavior:** Copying a `SharedPtr` should increment the reference count. Both the original and the copied `SharedPtr` should point to the same object, allowing modifications through either to be reflected in the other.

### Test 3: Share and reset after creation
**Objective:** Verify the `reset()` functionality and its impact on shared ownership and object deallocation.
**Expected Behavior:** After copying a `SharedPtr`, resetting one instance should decrement the reference count. If an instance is reset and no other `SharedPtr`s own the object, attempting to dereference it should throw an exception. The underlying resource should be released when the last `SharedPtr` is reset or destroyed.

### Test 4: Try to reset an already reset pointer
**Objective:** Ensure that calling `reset()` on an already reset or empty `SharedPtr` does not cause issues.
**Expected Behavior:** Repeated calls to `reset()` on the same `SharedPtr` instance should be idempotent and not affect other `SharedPtr` instances sharing ownership, nor should it lead to errors.

### Test 5: Assignment chain (a = b = c)
**Objective:** Test complex assignment chains to confirm correct reference counting and ownership transfer.
**Expected Behavior:** In an assignment chain like `a = b = c`, all `SharedPtr`s (`a`, `b`, and `c`) should correctly share ownership, leading to an incremented reference count for the object originally owned by `c`. The `SharedPtr` `d` should retain its separate ownership.

## Bonus: Thread Safety

### Why is Thread Safety Important?
In a multithreaded environment, multiple threads might attempt to copy, assign, or destroy `SharedPtr` instances that share ownership of the same object. Without proper synchronization, this can lead to race conditions when modifying the reference count. For example, if two threads read the reference count simultaneously, increment it, and then write it back, one of the increments could be lost. Such race conditions can cause the reference count to become incorrect, leading to premature deallocation (dangling pointers) or memory leaks (resource never deallocated).

### Requirement
To ensure the `SharedPtr` is thread-safe, access to the reference count must be protected by a synchronization mechanism like a `std::mutex`. This guarantees that increments and decrements to the reference count are protected from race conditions, ensuring the managed object's lifetime is correctly handled across all threads. You can achieve this by using `std::mutex` to guard access to the reference counter.

### Example testcase: Race condition
**Objective:** Verify thread-safe reference counting when multiple threads access and copy `SharedPtr` instances concurrently.
**Expected Behavior:** When multiple threads concurrently copy a `SharedPtr`, the atomic reference counter should correctly reflect the total number of `SharedPtr` instances sharing ownership, demonstrating thread-safety.
Here's an example of how to test the race condition.
```c++
    std::vector<std::thread> threads;
    Share_ptr<int> ptr6(new int(1));
    std::vector<Share_ptr<int>> vec(10);
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&vec, i, ptr6](){vec[i]=ptr6;});
    }

    for (auto& t : threads) {
        t.join();
    }
    assert(ptr6.reference_count()==11);
```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src
│   └── shared_ptr.h (provided by TA)
└── tests
    └── ut_shared_ptr.cpp
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
3. Bonus: Thread Safety (30%)

Total: 130%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPECT, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the float number.
3. You should use `EXPECT_STREQ(EXPECT, ACTUAL)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the message from exception.
4. TA will use the `_TA` project in Jenkins to test your program.