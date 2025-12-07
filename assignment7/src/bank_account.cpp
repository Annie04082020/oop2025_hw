#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include "bank_account.h"
#include "transaction.h"

long BankAccount::id_counter = 1;

// Constructor (bankaccount initialization)
BankAccount::BankAccount(const std::string &owner, const std::string &bank_code) : owner(owner), bank_code(bank_code), balance(0)
{
    this->id = id_counter++;
}
// Copy Constructor
BankAccount::BankAccount(const BankAccount &other)
{
    this->owner = other.owner;
    this->bank_code = other.bank_code;
    this->id = id_counter++;
    this->balance = 0;
    this->history.clear();
}
// Copy Assignment Operator
BankAccount &BankAccount::operator=(const BankAccount &other)
{
    if (this != &other)
    {
        for (Transaction *p : this->history)
        {
            delete p;
        }
        this->history.clear();
        this->owner = other.owner;
        this->bank_code = other.bank_code;
        this->id = other.id;
        this->balance = other.balance;
        for (const Transaction *other_history : other.history)
        {
            this->history.push_back(new Transaction(*other_history));
        }
    }
    return *this;
}
// Destructor
BankAccount::~BankAccount()
{
    for (Transaction *p : history)
    {
        delete p;
    }
    history.clear();
}
// Overloaded operator +=
BankAccount &BankAccount::operator+=(double amount)
{
    this->deposit(amount);
    return *this;
}

long BankAccount::get_id() const
{
    return this->id;
}
std::string BankAccount::get_owner() const
{
    return this->owner;
}
std::string BankAccount::get_bank_code() const
{
    return this->bank_code;
}
double BankAccount::get_balance() const
{
    return this->balance;
}
std::vector<Transaction *> BankAccount::get_history() const
{
    return this->history;
}
void BankAccount::deposit(double amount)
{
    // this->balance+=amount;
    if (amount <= 0)
    {
        throw std::invalid_argument("Must deposit a positive amount.");
    }
    else
    {
        this->balance += amount;
        static const std::string type = "Deposit";
        Transaction *deposit = new Transaction{type, amount, this->balance};
        this->history.push_back(deposit);
    };
}
void BankAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        throw std::invalid_argument("Must withdraw a positive amount.");
    }
    else if (amount > this->balance)
    {
        throw std::invalid_argument("Insufficient balance");
    }
    else
    {
        this->balance -= amount;
        static const std::string type = "Withdraw";
        Transaction *withdraw = new Transaction{type, amount, this->balance};
        this->history.push_back(withdraw);
        return;
    };
}
void BankAccount::export_to_csv(const std::filesystem::path &folder_path) const
{
    if (!std::filesystem::exists(folder_path))
    {
        std::filesystem::create_directories(folder_path);
    }
    std::string filename = "history_" + std::to_string(this->id) + "_" + this->owner + "_" + this->bank_code + ".csv";
    std::filesystem::path full_path = folder_path / filename;
    std::ofstream output_file(full_path);
    if (!output_file.is_open())
    {
        throw std::invalid_argument("Could not open file for writing: " + folder_path.string());
    }
    output_file << "Transaction Type,Amount,Balance After" << "\n";

    for (const auto &item : this->get_history())
    {
        if (item != nullptr)
        {
            output_file << item->get_type() << ","
                        << std::fixed << std::setprecision(2) << item->get_amount() << ","
                        << std::fixed << std::setprecision(2) << item->get_balance_after() << "\n";
        }
    }
}