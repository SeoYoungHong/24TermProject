// Bank.h
#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>
#include <vector>
#include "Account.h"
#include "Card.h"

using namespace std;

class Bank {
private:
    string bank_name;
    vector<Account*> user_account_list;
    vector<Card*> user_card_list;

public:
    Bank(const std::string& name);
    ~Bank();
    std::string getBankName() const;
    void setBankName(const std::string& name);
    void append_user_card(Card* card);
    void append_user_account(Account* account);
    Card* find_card(string input_id,string input_pw);
    Card* find_card_by_number(const std::string& cardnum);
    Account* find_account_by_number(const std::string& account_num);
};


#endif // BANK_H