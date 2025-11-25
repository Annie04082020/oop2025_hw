#include <gtest/gtest.h>
#include <cmath>
#include "../src/bank_account.h"
class BankSystemTest : public ::testing::Test{
    protected:
        const std::string& type1 = "Deposit";
        long id_A = 111 ;
        const std::string& owner_A = "Robert";
        std::string bank_code_A = "700";
        double balance_A = 500.00;
        Transaction*  history_A = new Transaction{type1,100.00,100.00};
        long id_B = 222 ;
        const std::string& owner_B = "Alex";
        std::string bank_code_B = "700";
        double balance_B = 700.00;
        Transaction*  history_B = new Transaction{type1,100.00,100.00};  
        long id_C = 333 ;
        const std::string& owner_C = "Felix";
        std::string bank_code_C = "500";
        double balance_C = 300.00;
        Transaction*  history_C = new Transaction{type1,100.00,100.00};
};
// TEST_F(BankSystemTest,GetOwner){    
//     BankAccount A = new BankAccount{id_A, owner_A, bank_code_A, balance_A, history_A};
//     std::string owner = A.get_owner();
//     EXPECT_EQ(owner, "Robert");
// }
// TEST_F(BankSystemTest,GetBankCode){
//     BankAccount A = {id_A,owner_A,bank_code_A,balance_A,history_A};
//     std::string bank_code = A.get_bank_code();
//     EXPECT_EQ(bank_code, "700");
// }
// TEST_F(BankSystemTest,GetBalance){
//     BankAccount A = {id_A,owner_A,bank_code_A,balance_A,history_A};
//     double balance = A.get_balance();
//     EXPECT_EQ(balance, 500.00);
// }


