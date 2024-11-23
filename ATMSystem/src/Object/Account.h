#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <Bank.h>
using namespace std;

class Account {
private:
    string p_account_number;
    Bank* p_bank;
    int amount;

public:
    // 생성자 (public)
    Account(string account_number, Bank* bank);

    // 소멸자 (public)
    ~Account();

    // 잔액 업데이트 함수 (오타 수정: unpdate -> update)
    void update_amount(int changed_amount);
};

#endif // ACCOUNT_H
