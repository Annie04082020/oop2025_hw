# Object-Oriented Programming 2025 Fall Assignment

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100
* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

**!! Important !!**
**Please use `git pull` command to pull the latest code of your homework repository before starting your assignment.**
**!! Important !!**

## Assignment 7
In this assignment, you will need to finish the following tasks:
1. Ensure your Jenkins setting (10%).
2. Correct the program you implemented in Midterm 2(90%).

### Deadline: 2025/12/7 (Sun.) 23:59 PM

### Task 1: Jenkins Setting (10%)
Ensure your Jenkins job is triggered automatically when you push code to your GitLab repository.
If your Jenkins is set up correctly, you will see the following image in your Jenkins job page:
![Pass Criteria](./automatic_trigger.png)

**If you see the message "started by GitLab push by ...", your Jenkins job is set up correctly. If not, please check your GitLab configuration.**

### Task 2: Midterm 2 Correction (90%)

For this assignment, you need to write a bank system which has the following features:
- Deposit money
- Withdraw money
- Record the transaction history
- Export the transaction history to a csv file (output)
- Create a new account by copying an existing account (copy constructor)
- Assign an existing account to another account (copy assignment operator)
- Clean up any dynamically allocated memory when an account is destroyed (destructor)
- Sort elements with the bubble sort (template function)

### Part 1: Bank System Implementation (60%)
To implement the system, you need classes called `BankAccount` and `Transaction`.

#### Class: Transaction (5%)
The class `Transaction` has the following attributes:
- `type` (string): the type of transaction, which can be `"Deposit"` or `"Withdraw"`.
- `amount` (double): the amount of money involved in the transaction.
- `balance_after` (double): the balance of the account after the transaction.

Please implement and test the following methods for `Transaction`:
- getters:
    - `get_type`
        - Returns the type of the transaction.
    - `get_amount`
        - Returns the amount of money involved in the transaction.
    - `get_balance_after`
        - Returns the balance of the account after the transaction.

#### Class: BankAccount (55%)
The class `BankAccount` has the following attributes:
- `id` (long): the account ID. The ID should be positive and unique for each account.
- `owner` (string): the account owner's name.
- `bank_code` (string): the bank code.
- `balance` (double): the balance of the account.
- `history` (vector<Transaction*>): the history of transactions.

Please implement and test the following methods for `BankAccount`:
- getters: (5%)
    - `get_id`
        - Returns the ID of the account.
    - `get_owner`
        - Returns the name of the account owner.
    - `get_bank_code`
        - Returns the bank code of the account.
    - `get_balance`
        - Returns the current balance of the account.
    - `get_history`
        - Returns the history of transactions.

- `deposit` (10%)
    - Deposits a specific amount into the account.
    - If the deposit is successful, do not throw any exception.
    - If the deposit amount is not positive, throws invalid_argument exception with the message `"Must deposit a positive amount."`.

- `withdraw` (10%)
    - Withdraws a specific amount from the account.
    - If the withdrawal is successful, do not throw any exception.
    - If the withdrawal amount is not positive, throws invalid_argument exception with the message `"Must withdraw a positive amount."`.
    - If the balance is not enough for the withdrawal, throws invalid_argument exception with the message `"Insufficient balance."`.

- `operator+=` (10%)
    - operator+= accepts a **constant double amount** as parameter, and returns a **reference to the current object**.
    - Overloads the `+=` operator to allow adding a specific amount to the account balance.
    - If the amount is not positive, throws invalid_argument exception with the message `"Must deposit a positive amount."`.

- `history` (10%)
    - Records each transaction (deposit or withdrawal) in the `history` vector.
    - Each transaction should be stored as a `Transaction` object with the appropriate type, amount, and balance after the transaction.

- `export_history_to_csv` (10%)
    - Exports the transaction history to a CSV file.
    - The CSV file should have the following columns: `Type`, `Amount`, `Balance After`.
    - Export the transaction history to the **specified folder path**.
    - The filename should be in the format `history_{id}_{owner}_{bank_code}.csv`, where `{id}` is the account ID, `{owner}` is the account owner's name, and `{bank_code}` is the bank code.
    - Each row in the CSV file represents a transaction in the history. The values should be separated by commas. **The amount and balance after should be formatted to two decimal places.**
    - For example:
        ```
        Type,Amount,Balance After
        Deposit,100.00,100.00
        Withdraw,50.00,50.00
        ```

(For those methods, you have to write at least one test for yourself.)

### Part 2: Rules of Three Implementation (25%)
Please **Write the method interface by yourself** and implement the Rule of Three for the `BankAccount` class:
- Copy Constructor (10%)
    - Copy constructor accepts a **constant reference to another BankAccount object** as parameter.
    - Creates a new `BankAccount` object as a copy of an existing one.
    - **Only copies `owner` and `bank_code`. Do not copy `id`, `balance` and `history`.**
    - **The new account should have a different ID, a balance of 0, and an empty history.**
    - **Make sure to handle deep copy for any dynamically allocated memory.**

- Copy Assignment Operator (10%)
    - Copy assignment operator accepts a **constant reference to another BankAccount object** as parameter and returns a **reference to the current object**.
    - Assigns the values of one `BankAccount` object to another.
    - **Handles self-assignment and copies all attributes.**
    - **Release any dynamically allocated memory properly.**

- Destructor (5%)
    - Cleans up any dynamically allocated memory when a `BankAccount` object is destroyed.

(For those methods, you have to write at least one test for yourself **except for the destructor**.)

### Part 3: Template Function Implementation (15%)
Please implement a template function `bubble_sort` that sorts elements in a vector based on a given comparison function. You can refer the bubble sort algorithm below.

Example Code of the `bubble_sort` algorithm in c:
```c
void bubble_sort(int arr[], int n, Compare comp) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(arr[j + 1], arr[j])) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
```

**The `bubble_sort` function should be implemented as a template to support random access iterators.**
Please implement the following methods:
- `void bubble_sort(RandomIt first, RandomIt last)`
    - Takes two iterators (or pointers) as input, representing the beginning and end of the array or the vector.
    - Sorts the elements in the vector in-place **with the ascending order**.

- `void bubble_sort(RandomIt first, RandomIt last, Compare comp)`
    - Similar to the previous function, but it accepts an additional parameter `comp`, which is the comparison function.
    - The comparison function should take two elements as input and return a boolean value indicating whether the first element should be ordered before the second element.
    - Sorts the elements in the vector based on **the provided comparison function**.

**You should implement the `bubble_sort` function in the `utils.h` file directly, not in the `.cpp` file.**

(For this method, you have to write **at least four tests** for yourself: **two tests for the first function and two tests for the second function**.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Class Declaration
- src/bank_account.h
```c++
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>
#include <filesystem>
#include "transaction.h"

class BankAccount {
private:
    // Attributes

public:
    BankAccount(const std::string& owner, const std::string& bank_code);
    // Copy constructor
    // Copy assignment
    // Destructor

    // Overloaded operator +=

    long get_id() const;
    std::string get_owner() const;
    std::string get_bank_code() const;
    double get_balance() const;
    std::vector<Transaction*> get_history() const;

    void deposit(double amount);
    void withdraw(double amount);
    
    void export_to_csv(const std::filesystem::path& folder_path) const;
};

#endif // BANK_ACCOUNT_H
```

- src/transaction.h
```c++
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    // Attributes

public:
    Transaction(const std::string& type, double amount, double balance_after);
    std::string get_type() const;
    double get_amount() const;
    double get_balance_after() const;
};

#endif // TRANSACTION_H
```

- src/utils.h
```c++
#ifndef UTILS_H
#define UTILS_H

#include <vector>

template <typename RandomIt>
void bubble_sort(RandomIt first, RandomIt last) {
    // Implementation
}

template <typename RandomIt, typename Compare>
void bubble_sort(RandomIt first, RandomIt last, Compare comp) {
    // Implementation
}

#endif // UTILS_H
```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── src
│   ├── bank_account.cpp
│   ├── bank_account.h (provided by TA)
│   ├── transaction.cpp
│   ├── transaction.h (provided by TA)
│   └── utils.h (provided by TA)
└── tests
    ├── ut_bank_account.cpp
    ├── ut_bank_account_rule_of_three.cpp
    └── ut_utils.cpp
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Jenkins Setting (10%)
1. Implementation and tests by yourself (45%)
2. Tests by TA (45%)

Total: 100%

### References you can use:
- [Generating unique IDs with a static counter in C++](https://cplusplus.com/forum/beginner/265627/)

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPECT, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the float number.
3. You should use `EXPECT_STREQ(EXPECT, ACTUAL)` instead of `EXPECT_EQ(EXPECT, ACTUAL)` for testing the message from exception.
4. TA will use the `_TA` project in Jenkins to test your program.