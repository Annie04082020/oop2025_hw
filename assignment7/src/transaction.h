#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction
{
private:
    // Attributes
    const std::string &type;
    double amount;
    double balance_after;

public:
    static int alive_count;
    Transaction(const std::string &type, double amount, double balance_after);
    std::string get_type() const;
    double get_amount() const;
    double get_balance_after() const;

    Transaction(const Transaction &other);
    ~Transaction();
};

#endif // TRANSACTION_H