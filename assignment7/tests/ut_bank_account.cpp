#include <gtest/gtest.h>
#include <cmath>
#include <iostream> // 為了使用 std::cout
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
TEST_F(BankSystemTest, CSV)
{
    BankAccount A(owner_A, bank_code_A);
    A += 600.00;
    A.export_to_csv("test");
    std::filesystem::path filepath = "test/" + std::to_string(A.get_id()) + "_" + A.get_owner() + "_" + A.get_bank_code() + ".csv";
    std::cout << "Checking file at: " << filepath << std::endl; // 輸出檔案路徑以便調試
    EXPECT_TRUE(std::filesystem::exists(filepath));
}