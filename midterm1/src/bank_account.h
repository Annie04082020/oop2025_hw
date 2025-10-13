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