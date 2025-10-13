# Object-Oriented Programming 2025 Fall Midterm 1

### Important Links

* [Gitlab](http://140.124.181.100): http://140.124.181.100

* [Jenkins](http://140.124.181.97:8080): http://140.124.181.97:8080

## Midterm 1
In this midterm, you have two problems to solve. The first problem is implementing a bank system with a class `BankAccount`. The second problem is hand-writing questions.

- There are only five websites allowed to visit:
  1. [cppreference.com](https://en.cppreference.com/w/)
  2. [cplusplus.com](https://cplusplus.com/)
  3. [cambridge dictionary](https://dictionary.cambridge.org/zht/)
  4. [code in class](http://140.124.181.100/yccheng/oop2025f)
  5. [Jenkins](http://140.124.181.97:8080/)
  6. your homework repo.
- You will be considered as cheating if you visit other websites.

### Deadline: 2025/10/13 (Mon.) 12:10

### Problem 1: Bank System (80%)
For this assignment, you need to write a bank system to deposit, withdraw, or transfer money. To implement the system, you need a class called `BankAccount`.

The class `BankAccount` has the following attributes:
- `owner` (string): the account owner's name.
- `bank_code` (string): the bank code.
- `balance` (double): the balance of the account.
- `history` (vector<string>): the history of transactions.

Please implement and test the following methods for `BankAccount`:
- getters: (5%)
    - `get_owner`
        - Returns the name of the account owner.
    - `get_bank_code`
        - Returns the bank code of the account.
    - `get_balance`
        - Returns the current balance of the account.
    - `get_history`
        - Returns the history of transactions.

- `deposit` (15%)
    - Deposits a specific amount into the account.
    - If the deposit is successful, returns `""`.
    - If the deposit amount is not positive, returns `"Must deposit a positive amount."`.

- `withdraw` (15%)
    - Withdraws a specific amount from the account.
    - If the withdrawal is successful, returns `""`.
    - If the withdrawal amount is not positive, returns `"Must withdraw a positive amount."`.
    - If the balance is not enough for the withdrawal, returns `"Insufficient balance."`.

- `transfer` (20%)
    - Transfers a specific amount from the current account to another account.
    - $0 fee if transfer to the same bank code.
    - $15 fee if transfer to a different bank code.
        - For example, if you transfer \$100 to an account with a different bank code, your balance will decrease by \$115, and the other account's balance will increase by \$100.
    - If the transfer is successful, returns `""`.
    - If the transfer amount is not positive, returns `"Must transfer a positive amount."`.
    - If the balance is not enough for the transfer and fee, returns `"Insufficient balance."`.
    - If the current and target accounts are the same (two accounts are the same if the owner and bank code are the same), returns `"Cannot transfer to the same account."`.

- `History` (25%)
    - For each successful transaction (deposit, withdraw, transfer), a record should be added to the history in the following format:
        - Deposit: `"Deposit: {amount}. New balance: {new_balance}"`
        - Withdraw: `"Withdraw: {amount}. New balance: {new_balance}"`
        - Transfer:
            - For the account that makes the transfer, add: 
                - No fee: `"Transfer: {amount} to [{bank_code}] {owner}. New balance: {new_balance}"`
                - With fee: `"Transfer: {amount} to [{bank_code}] {owner}. New balance: {new_balance} (fee {fee})"`
            - For the account that receives the transfer, add: 
                - `"Receive: {amount} from [{bank_code}] {owner}. New balance: {new_balance}"`
    - Here, `{amount}` is the transaction amount formatted to 2 decimal places, `{bank_code}` is the bank code involved in the transaction, `{owner}` is the owner of the target account in a transfer, and `{new_balance}` is the account's balance after the transaction, also formatted to 2 decimal places.
        - For example, If Alice with bank code "700" has a balance of $100.00:
            - When deposits $100 into her account, the history should include: `"Deposit: 100.00. New balance: 200.00"`.
            - When withdraws $50 from her account, the history should include: `"Withdraw: 50.00. New balance: 50.00"`.
            - When transfers $100 to Bob with bank code "700", the history should include: `"Transfer: 100.00 to [700] Bob. New balance: 50.00"`, and Bob's history should include: `"Receive: 100.00 from [700] Alice. New balance: 100.00"`.
            - When transfers $100 to Charlie with bank code "800", the history should include: `"Transfer: 100.00 to [800] Charlie. New balance: 35.00 (fee 15.00)"`, and Charlie's history should include: `"Receive: 100.00 from [700] Alice. New balance: 100.00"`.
    - If the operation does not succeed, **do not add any record to the history**.
    - You can use `std::to_string(value)` to convert a number to a string, but it may not format the number to 2 decimal places. You need to handle the formatting yourself.

(For those methods, you have to write at least one test for yourself.)

Please follow the declaration and write the implementation in the corresponding `.cpp` files.

### Problem 2: Hand-writing Questions (20%)
1. What are the four steps of How-to-Solve-It? (10%)
2. What are the three steps of TDD? (10%)

**Please write your answer in the hand_writing_answer.txt.**

### Class Declaration
- src/bank_account.h
```c++
#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>

class BankAccount {
public:
    std::string owner;
    std::string bank_code;
    double balance;
    std::vector<std::string> history;

    std::string get_owner();
    std::string get_bank_code();
    double get_balance();
    std::vector<std::string> get_history();

    std::string deposit(double amount);
    std::string withdraw(double amount);
    std::string transfer(BankAccount& account_to, double amount);
};

#endif // BANK_ACCOUNT_H
```

**Please download the files in the `sample_code` folder and follow the repository structure to put the files in your repository.**

### Repository Structure
```
. (oop2025f_{student ID}_hw)
├── .gitignore (provided by TA)
├── CMakeLists.txt (provided by TA)
├── hand_writing_answer.txt
├── src
│   ├── bank_account.cpp
│   └── bank_account.h (provided by TA)
└── tests
    └── ut_bank_account.cpp
```

### Commands to Execute the Program

```bash
$ cd build
$ cmake ..
$ make
$ ./unit_tests
```

### Score

1. Implementation and tests by yourself (40%)

2. Tests by TA (40%)

3. Hand-writing questions (20%)

Total: 100%

### Notes
1. Please implement your test cases reasonably; otherwise, you will get no points for that sub-problem.
2. You should use `EXPECT_NEAR(EXPCET, ACTUAL, ALPHA)` instead of `EXPECT_EQ(EXPCET, ACTUAL)` for testing the float number.
3. TA will use the `_TA` project in Jenkins to test your program.
