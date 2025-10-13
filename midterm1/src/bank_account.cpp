#include <string>
#include <vector>
#include "bank_account.h"

std::string BankAccount::get_owner()
{
    return this->owner;
}
std::string BankAccount::get_bank_code()
{
    return this->bank_code;
}
double BankAccount::get_balance()
{
    return this->balance;
}
std::vector<std::string> BankAccount::get_history()
{
    return this->history;
}
std::string BankAccount::deposit(double amount)
{
    if (amount <= 0)
    {
        return "Must deposit a positive amount.";
    }
    else
    {
        this->balance += amount;
        std::string add_history = "Deposit: ";
        std::string amount_to_string = std::to_string(amount);
        int i;
        for (i = 0; i < 4; i++)
        {
            amount_to_string.pop_back();
        };
        add_history += amount_to_string;
        add_history += ". New balance: ";
        std::string new_balance = std::to_string(this->balance);
        i = 0;
        for (i = 0; i < 4; i++)
        {
            new_balance.pop_back();
        };
        add_history += new_balance;
        this->history.push_back(add_history);
        return "";
    };
}
std::string BankAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        return "Must withdraw a positive amount.";
    }
    else
    {
        if (this->balance < amount)
        {
            return "Insufficient balance.";
        }
        else
        {
            this->balance -= amount;
            std::string add_history = "Withdraw: ";
            std::string amount_to_string = std::to_string(amount);
            int i;
            for (i = 0; i < 4; i++)
            {
                amount_to_string.pop_back();
            };
            add_history += amount_to_string;
            add_history += ". New balance: ";
            std::string new_balance = std::to_string(this->balance);
            i = 0;
            for (i = 0; i < 4; i++)
            {
                new_balance.pop_back();
            };
            add_history += new_balance;
            this->history.push_back(add_history);
            return "";
        };
    };
}
std::string BankAccount::transfer(BankAccount &account_to, double amount)
{
    int fee = 0;
    if (account_to.bank_code == this->bank_code)
    {
        fee = 0;
    }
    else
    {
        fee = 15;
    };
    if (amount <= 0)
    {
        return "Must transfer a positive amount.";
    }
    else
    {
        if (this->balance < (amount + fee))
        {
            return "Insufficient balance.";
        }
        if ((account_to.owner == this->owner) && (account_to.bank_code == this->bank_code))
        {
            return "Cannot transfer to the same account.";
        }
        else
        {
            this->balance -= (fee + amount);
            account_to.balance += amount;
            std::string add_history = "Transfer: ";
            std::string amount_to_string = std::to_string(amount);
            int i;
            for (i = 0; i < 4; i++)
            {
                amount_to_string.pop_back();
            };
            add_history += amount_to_string;
            add_history += " to [";
            add_history += account_to.bank_code;
            add_history += "] ";
            add_history += account_to.owner;
            add_history += ". New balance: ";
            std::string new_balance = std::to_string(this->balance);
            i = 0;
            for (i = 0; i < 4; i++)
            {
                new_balance.pop_back();
            };
            add_history += new_balance;
            if (fee != 0)
            {
                add_history += " (fee ";
                std::string fee_to_string = std::to_string(fee);
                for (int i = 0; i++; i < 6)
                {
                    fee_to_string.pop_back();
                };
                add_history += fee_to_string;
                add_history += ")";
            };
            this->history.push_back(add_history);

            std::string receive_history = "Receive: ";
            std::string receive_amount_to_string = std::to_string(amount);
            i = 0;
            for (i = 0; i < 4; i++)
            {
                receive_amount_to_string.pop_back();
            };
            receive_history += receive_amount_to_string;
            receive_history += " from [";
            receive_history += this->bank_code;
            receive_history += "] ";
            receive_history += this->owner;
            receive_history += ". New balance: ";
            std::string new_receive_balance = std::to_string(this->balance);
            i = 0;
            for (i = 0; i < 4; i++)
            {
                new_receive_balance.pop_back();
            };
            receive_history += new_receive_balance;
            account_to.history.push_back(receive_history);
            return "";
        };
    };
}