#include <gtest/gtest.h>
#include <cmath>
#include <filesystem>
#include <fstream>
#include "../src/bank_account.h"
class BankSystemTest : public ::testing::Test
{
protected:
    std::string owner_A = "Robert";
    std::string bank_code_A = "700";
    double balance_A = 500.00;
};
TEST_F(BankSystemTest, GetOwner)
{
    BankAccount A(owner_A, bank_code_A);
    EXPECT_EQ(A.get_owner(), "Robert");
}
TEST_F(BankSystemTest, GetBankCode)
{
    BankAccount A(owner_A, bank_code_A);
    EXPECT_EQ(A.get_bank_code(), "700");
}
TEST_F(BankSystemTest, GetBalance)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(500.00);
    EXPECT_EQ(A.get_balance(), 500.00);
}
TEST_F(BankSystemTest, Deposit)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(300.00);
    EXPECT_EQ(A.get_balance(), 300.00);
}
TEST_F(BankSystemTest, Deposit_NegativeBalance)
{
    BankAccount A(owner_A, bank_code_A);
    EXPECT_THROW(A.deposit(-300.00), std::invalid_argument);
}
TEST_F(BankSystemTest, Withdraw)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(400.00);
    A.withdraw(150.00);
    EXPECT_EQ(A.get_balance(), 250.00);
}
TEST_F(BankSystemTest, Withdraw_NegativeBalance)
{
    BankAccount A(owner_A, bank_code_A);
    EXPECT_THROW(A.withdraw(-300.00), std::invalid_argument);
}
TEST_F(BankSystemTest, Withdraw_InsufficientBalance)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(200.00);
    EXPECT_THROW(A.withdraw(300.00), std::invalid_argument);
}
TEST_F(BankSystemTest, OperatorPlusEqual)
{
    BankAccount A(owner_A, bank_code_A);
    A += 600.00;
    EXPECT_EQ(A.get_balance(), 600.00);
}
TEST_F(BankSystemTest, CSVoutput)
{
    BankAccount A(owner_A, bank_code_A);
    A += 600.00;
    EXPECT_NO_THROW(A.export_to_csv("test"));
    std::filesystem::path filepath = "test/history_" + std::to_string(A.get_id()) + "_" + A.get_owner() + "_" + A.get_bank_code() + ".csv";
    ASSERT_TRUE(std::filesystem::exists(filepath));

    {
        std::ifstream read_output_file(filepath);
        ASSERT_TRUE(read_output_file.is_open());
        std::string line;
        int line_count = 0;
        std::vector<std::string> expected_lines = {
            "Transaction Type,Amount,Balance After",
            "Deposit,600.00,600.00"};
        while (std::getline(read_output_file, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            if (line_count >= expected_lines.size())
            {
                FAIL();
                break;
            }
            EXPECT_EQ(line, expected_lines[line_count]);
            line_count++;
        }
        EXPECT_EQ(line_count, expected_lines.size());
        read_output_file.close();
    }

    std::filesystem::remove_all("test");
    EXPECT_FALSE(std::filesystem::exists(filepath));
}
TEST_F(BankSystemTest, TransactionHistory)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(500.00);
    A.withdraw(200.00);
    A.deposit(300.00);
    std::vector<Transaction *> history = A.get_history();
    ASSERT_EQ(history.size(), 3);
    EXPECT_EQ(history[0]->get_type(), "Deposit");
    EXPECT_DOUBLE_EQ(history[0]->get_amount(), 500.00);
    EXPECT_DOUBLE_EQ(history[0]->get_balance_after(), 500.00);
    EXPECT_EQ(history[1]->get_type(), "Withdraw");
    EXPECT_DOUBLE_EQ(history[1]->get_amount(), 200.00);
    EXPECT_DOUBLE_EQ(history[1]->get_balance_after(), 300.00);
    EXPECT_EQ(history[2]->get_type(), "Deposit");
    EXPECT_DOUBLE_EQ(history[2]->get_amount(), 300.00);
    EXPECT_DOUBLE_EQ(history[2]->get_balance_after(), 600.00);
}
TEST_F(BankSystemTest, DepositNegativeAmount)
{
    BankAccount A(owner_A, bank_code_A);
    try
    {
        A.deposit(-500);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (const std::invalid_argument &e)
    {
        EXPECT_STREQ(e.what(), "Must deposit a positive amount.");
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument, but got different exception";
    }
    EXPECT_THROW(A.deposit(-500), std::invalid_argument);
}
TEST_F(BankSystemTest, WithdrawNegativeAmount)
{
    BankAccount A(owner_A, bank_code_A);
    try
    {
        A.withdraw(-500);
        FAIL() << "Expected std::invalid_argument";
    }
    catch (const std::invalid_argument &e)
    {
        EXPECT_STREQ(e.what(), "Must withdraw a positive amount.");
    }
    catch (...)
    {
        FAIL() << "Expected std::invalid_argument, but got different exception";
    }
    EXPECT_THROW(A.withdraw(-500), std::invalid_argument);
}