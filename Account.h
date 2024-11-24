#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include "Bank.h"
#include "Card.h"
#include <vector>

class Bank;
using namespace std;

class Account {
private:
    static int account_counter;
    string p_account_number;
    Bank* p_bank;
    vector<Card*> user_card_list;
    int amount;

public:
    // 생성자 (public)
    Account(Bank* bank);

    // 소멸자 (public)
    ~Account();

    // 잔액 업데이트 함수 (오타 수정: unpdate -> update)
    void update_amount(int changed_amount);
    string get_account_number();
    void append_user_card(Card* card);
    int get_amount();
    Bank* get_bank();
};

#endif // ACCOUNT_H
