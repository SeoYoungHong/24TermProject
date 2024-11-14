#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

// 전방 선언: Bank 클래스
class Bank;

class Account {
public:
    string p_account_number;
    Bank* p_bank;
    int amount;

    // 생성자 (public)
    Account(string account_number, Bank* bank);

    // 소멸자 (public)
    ~Account();

    // 잔액 업데이트 함수 (오타 수정: unpdate -> update)
    void update_amount(int changed_amount);
};

#endif // ACCOUNT_H