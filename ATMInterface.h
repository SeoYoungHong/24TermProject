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
    
    History* p_history;
    Card* p_card;
    MoneyDict* money_slot= new MoneyDict();
    vector<Bank*> bank_list;
    vector<History*> history_list;
    vector<Account*> user_account_list;
    vector<Card*> user_card_list;
    vector<ATM*> atm_list;
    
public:
    ATM* p_atm;
    const vector<Bank*>& getBankList() const {return bank_list;}
    const std::vector<ATM*>& getATMList() const;  // atm_list ��ȯ
    const std::vector<Account*>& getAccountList() const;  // atm_list ��ȯ
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
    void transfer(Account* target_account, int amount);
    void changeLanguage();
    // void performTransaction(int option);
    void depositCash();
    void withdrawCash();
    void checkFeeDetails();
    void append_user_card(Card* card);
    void append_user_account(Account* account);
    void update_card(Card* card);
    Bank* choiceBank(bool is_single, Bank* bank);
    Bank* choiceBanking(bool is_single, Bank* bank);
    Card* choiceCard();
    Account* choiceAccount();
    Account* createAccount();
    Card* matchcard(Bank* bank, string card_numm, string pw);
    int insert_cach(MoneyDict* moneydictm, bool is_initial);
    int insert_cache(MoneyDict* moneydictm, bool is_initial);
    void insert_check();
    void atm_to_account();
    int withdraw();
    bool account_to_account();
    bool slot_to_account();
    Account* check_account_num();
    void append_history(History* new_history);
    void print_by_session(Session* session);
    void print_by_atm();
    void export_by_atm();
    int append_bank(string bank_name);
    ATM* append_ATM();
};

#endif 
