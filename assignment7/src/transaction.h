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