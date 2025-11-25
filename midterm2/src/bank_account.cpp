#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <exception>
#include "bank_account.h"
#include "transaction.h"
BankAccount::BankAccount(const std::string& owner, const std::string& bank_code) {}
BankAccount::BankAccount(std::vector<Transaction *> history)
{

    for (Transaction *p : history)
    {
        if (p != nullptr)
        {
            this->history.push_back(new Transaction(*p));
        };
    }
}
BankAccount::BankAccount(const BankAccount &other)
{
    for (const Transaction *other_history : other.history)
    {
        this->history.push_back(new Transaction(*other_history));
    }
}
BankAccount::~BankAccount()
{
    for (Transaction *p : history)
    {
        delete p;
    }
    history.clear();
}
BankAccount &BankAccount::operator+=(double amount)
{   
    return;
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
double BankAccount::get_balance()const
{
    return this->balance;
}
std::vector<Transaction*> BankAccount::get_history()const
{
    return this->history;
}
void BankAccount::deposit(double amount)
{
    // this->balance+=amount;
    if (amount <= 0)
    {
        throw ("Must deposit a positive amount.");
    }
    else
    {
        const std::string& type = "Deposit";
        double balance_after = this->balance+amount;
        Transaction* deposit = new Transaction{type,amount, balance_after};
        this->history.push_back(deposit);
        return;
    };
}
void BankAccount::withdraw(double amount)
{
     if (amount <= 0)
    {
        throw std::invalid_argument("Must withdraw a positive amount.");
    }
    else
    {
        const std::string& type = "Withdraw";
        double balance_after = this->balance+amount;
        Transaction* withdraw =  new Transaction {type, amount, balance_after};
        this->history.push_back(withdraw);
        return;
    };
}
void BankAccount::export_to_csv(const std::filesystem::path& folder_path)const
{

     std::ofstream output_file(folder_path);
    if (!output_file.is_open())
    {
        throw std::invalid_argument("Could not open file for writing: " + folder_path.string());
        return;
    }
    for (const auto &item : this->get_history())
    {
        output_file << "Type,Amount,Balance After" << "\n";
        if (item)
        {
            output_file << item->get_type() << ","<<item->get_amount()<< ","<<item->get_balance_after()<<"\n";
        }
    }


}