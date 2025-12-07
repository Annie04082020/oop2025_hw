#include <string>
#include <gtest/gtest.h>
#include "../src/transaction.h"
#include "../src/bank_account.h"

class BankSystemRuleofThreeTest : public ::testing::Test
{
protected:
    std::string owner_A = "Robert";
    std::string bank_code_A = "700";
    double balance_A = 500.00;
};

TEST_F(BankSystemRuleofThreeTest, CopyConstructorTest)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(balance_A);
    BankAccount B = A; // 使用複製建構子
    EXPECT_EQ(B.get_owner(), A.get_owner());
    EXPECT_EQ(B.get_bank_code(), A.get_bank_code());
    EXPECT_EQ(B.get_balance(), 0.00);     // 複製建構子應該初始化為0
    EXPECT_NE(B.get_id(), A.get_id());    // ID應該不同
    EXPECT_EQ(B.get_history().size(), 0); // 歷史紀錄應該為空
}
TEST_F(BankSystemRuleofThreeTest, CopyAssignmentOperator)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(500);
    BankAccount B("OldOwner", "999");
    B.deposit(300);
    B = A;
    EXPECT_EQ(B.get_owner(), A.get_owner());
    EXPECT_EQ(B.get_bank_code(), A.get_bank_code());
    EXPECT_EQ(B.get_balance(), A.get_balance());
    ASSERT_EQ(B.get_history().size(), A.get_history().size());
    EXPECT_NE(B.get_history()[0], A.get_history()[0]);
    A.deposit(1000);
    EXPECT_NE(B.get_balance(), A.get_balance());
}
TEST_F(BankSystemRuleofThreeTest, CopyAsssignmentSelfAssign)
{
    BankAccount A(owner_A, bank_code_A);
    A.deposit(500);
    A = A;
    EXPECT_EQ(A.get_balance(), 500);
    EXPECT_EQ(A.get_owner(), "Robert");
    EXPECT_EQ(A.get_bank_code(), "700");
    EXPECT_EQ(A.get_history().size(), 1);
    A.withdraw(200);
    EXPECT_EQ(A.get_balance(), 300);
    EXPECT_EQ(A.get_history().size(), 2);
}
TEST_F(BankSystemRuleofThreeTest, Destructor)
{
    EXPECT_EQ(Transaction::alive_count, 0);
    {
        BankAccount A(owner_A, bank_code_A);
        A += 100;
        EXPECT_EQ(A.get_history().size(), 1);
        EXPECT_EQ(Transaction::alive_count, 1);
        A += 200;
        EXPECT_EQ(A.get_history().size(), 2);
        EXPECT_EQ(Transaction::alive_count, 2);
    }
    EXPECT_EQ(Transaction::alive_count, 0);
}
TEST_F(BankSystemRuleofThreeTest, OverloadOperator)
{
    BankAccount A(owner_A, bank_code_A);
    A += 150.00;
    EXPECT_EQ(A.get_balance(), 150.00);
    A += 350.00;
    EXPECT_EQ(A.get_balance(), 500.00);
    EXPECT_THROW(A += -100.00, std::invalid_argument);
    try
    {
        A += -100.00;
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
    EXPECT_EQ(A.get_balance(), 500.00);
}