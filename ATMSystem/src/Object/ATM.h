#ifndef ATM_H
#define ATM_H

#include <string>
#include <Bank.h>
#include <MoneyDict.h>

using namespace std;

// 전방 선언
class Bank;
class MoneyDict;
class Session;

class ATM {
public:
    Bank* primery_bank;
    string serial_number;
    bool is_single_bank_atm;
    bool is_unilingual_atm;
    int language_state;
    MoneyDict* remained_money = nullptr;
    MoneyDict* slot_money = nullptr;
    const int cash_maximum = 50;
    const int check_maximum = 30;
    int input_fee = 0;
    const int withdraw_amount_max = 50000;
    Session* present_session = nullptr;

    // 생성자 (public)
    ATM(Bank* bank, string serial_num, bool is_single, bool is_unilingual);

    // 소멸자 (public)
    ~ATM();

    // 업데이트 함수들
    void update_slot_money(MoneyDict* input_money);
    void update_remained_money(MoneyDict* input_money);
    void update_session(Session* new_session);
    void update_input_fee(int update_input_fee);
};

#endif // ATM_H
