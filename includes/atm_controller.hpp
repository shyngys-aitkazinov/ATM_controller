#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <curses.h>
#include <vector>
#include <stdexcept>
#include <utility>

/**
 * @brief the structure that is responsible for the bank account
 * @author Shyngys Aitkazinov
 */
struct Account
{
    Account(std::string acc_num_val, u_long pin_val);
    std::string account_number;
    u_long pin_code;
    unsigned long long int balance;  
};

enum customer_state{
    CARD_OUT,
    CARD_IN,
    ACCOUNT_MENU
};

class AtmController
{

public:

    /**
     * @brief car insertion and validation
     * @return true if successful
     */
    bool InsertAndValidateCard();

    /**
     * @brief registers new account
     * @return void
     */
    void RegisterAccount();

    /**
     * @brief logins to existing account
     * @return true if successful
     */
    bool AccountLogin();

    /**
     * @brief do operations with account
     * @param amount to deposit or withdraw
     * @param type 0 for deposit, 1 for withdraw, else for see balance
     * @return void
     */
    void HandleTransaction(u_long amount, int type);


    /**
     * @brief starts the atm controller
     * @return void
     */
    void Run();



private:

    // stores the accounts
    std::unordered_map<std::string, Account> m_accounts;
    std::string m_welcoming_message = "Hello Dear Customer,\
this is simple ATM controller\n\
For:\n\
    -card insertion press C and Enter\n\
    -program termination press T and Enter\n";
    std::string m_menu = "Operations: \n \
    -register new user - press N and Enter\n\
    -login to account - press L and Enter\n\
    -card removal - press C and Enter\n";
    std::string m_acccount_menu = "Operations: \n\
    -withdraw money - enter W and Amount (e.g. W 200) and Enter\n\
    -deposit money- enter D and Amount (e.g. D 300) and Enter\n\
    -show balance  - enter B and Enter\n\
    -account logout - enter L and Enter\n";

    
    std::pair<u_long,int> m_parse_transaction(std::string &input);

    std::string m_current_account;
    // state of the ATM controller
    enum customer_state m_state = CARD_OUT;

    
};

