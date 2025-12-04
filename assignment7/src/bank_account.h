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

    void deposit(const double amount);
    void withdraw(const double amount);
    
    void export_to_csv(const std::filesystem::path& folder_path) const;
};

#endif // BANK_ACCOUNT_H