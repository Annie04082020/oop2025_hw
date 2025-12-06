#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <vector>
#include <filesystem>
#include "transaction.h"

class BankAccount
{
private:
    // Attributes
    static long id_counter;
    long id;
    std::string owner;
    std::string bank_code;
    double balance;
    std::vector<Transaction *> history;

public:
    // Constructor
    BankAccount(const std::string &owner, const std::string &bank_code);
    // Rule of three:
    // 1. Copy constructor
    BankAccount(const BankAccount &other);
    // 2. Copy assignment operator
    BankAccount &operator=(const BankAccount &other);
    // 3. Destructor
    ~BankAccount();
    // Overloaded operator +=,  // receive double and return address
    // operator(double amount);
    BankAccount &operator+(double amount);

    long get_id() const;
    std::string get_owner() const;
    std::string get_bank_code() const;
    double get_balance() const;
    std::vector<Transaction *> get_history() const;

    void deposit(const double amount);
    void withdraw(const double amount);

    void export_to_csv(const std::filesystem::path &folder_path) const;
};

#endif // BANK_ACCOUNT_H