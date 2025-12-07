#include <string>
#include "transaction.h"

int Transaction::alive_count = 0;
Transaction::Transaction(const std::string &type, double amount, double balance_after)
    : type(type), amount(amount), balance_after(balance_after)
{
    alive_count++;
}
Transaction::Transaction(const Transaction &other)
    : type(other.type), amount(other.amount), balance_after(other.balance_after)
{
    alive_count++; 
}
Transaction::~Transaction()
{
    alive_count--;
}

std::string Transaction::get_type() const
{
    return this->type;
}
double Transaction::get_amount() const
{
    return this->amount;
}
double Transaction::get_balance_after() const
{
    return this->balance_after;
}