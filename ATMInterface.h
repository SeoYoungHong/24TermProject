#ifndef ATM_INTERFACE_H
#define ATM_INTERFACE_H

#include <iostream>
#include <string>
#include "ATM.h"
#include "History.h"
#include "Card.h"
#include <vector>



class ATMInterface {
private:
    ATM* p_atm;
    History* p_history;
    Card* p_card;
    MoneyDict* money_slot= new MoneyDict();
    vector<Bank*> bank_list;
    
    vector<Account*> user_account_list;
    vector<Card*> user_card_list;
public:
    bool is_inserted=false;
    bool p_is_admin;
    ATMInterface();
    Card* createCard();
    ATM* createATM();
    void insertCard();
    void reset();
    void printBySession();
    void printByATM();
    void insertMoney();
    void checkFee();
    void transfer();
    void changeLanguage();
    void performTransaction(int option);
    void depositCash();
    void withdrawCash();
    void checkFeeDetails();
    void append_user_card(Card* card);
    void append_user_account(Account* account);
    void update_card(Card* card);
    Bank* choiceBank();
    Card* choiceCard();
    Account* choiceAccount();
    Account* createAccount();
    Card* matchcard(Bank* bank, string card_numm, string pw);
    void insert_cach();
    void insert_check();
    void atm_to_account();
    int withdraw();
    
};

#endif 
