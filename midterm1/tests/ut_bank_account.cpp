#include <gtest/gtest.h>
#include <cmath>
#include "../src/bank_account.h"
class BankSystemTest : public ::testing::Test{
    protected:
        std::string owner_A = "Robert";
        std::string bank_code_A = "700";
        double balance_A = 500.00;
        std::vector<std::string> history_A = {};
        std::string owner_B = "Alex";
        std::string bank_code_B = "700";
        double balance_B = 700.00;
        std::vector<std::string> history_B = {};   
        std::string owner_C = "Felix";
        std::string bank_code_C = "500";
        double balance_C = 300.00;
        std::vector<std::string> history_C = {};
};
TEST_F(BankSystemTest,GetOwner){
    BankAccount A = {owner_A, bank_code_A, balance_A, history_A};
    std::string owner = A.get_owner();
    EXPECT_EQ(owner, "Robert");
}
TEST_F(BankSystemTest,GetBankCode){
    BankAccount A = {owner_A,bank_code_A,balance_A,history_A};
    std::string bank_code = A.get_bank_code();
    EXPECT_EQ(bank_code, "700");
}
TEST_F(BankSystemTest,GetBalance){
    BankAccount A = {owner_A,bank_code_A,balance_A,history_A};
    double balance = A.get_balance();
    EXPECT_EQ(balance, 500.00);
}
TEST_F(BankSystemTest,Deposit){
    BankAccount A = {owner_A,bank_code_A,balance_A,history_A};
    A.deposit(500);
    EXPECT_EQ(A.balance,1000);
    EXPECT_EQ(A.history[0],"Deposit: 500.00. New balance: 1000.00");
}
TEST_F(BankSystemTest,Withdraw){
    BankAccount A = {owner_A,bank_code_A,balance_A,history_A};
    A.withdraw(500);
    EXPECT_EQ(A.balance,0);
    EXPECT_EQ(A.history[0],"Withdraw: 500.00. New balance: 0.00");

}

