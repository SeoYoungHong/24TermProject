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
    std::vector<std::string> user_card_list; // 카드 번호(문자열)만 저장
    int amount;
    string user_name; // 유저 이름 추가
    std::string bank_name; // 지금 수정한 부분: 은행 이름 추가
public:
    // 생성자 (public)
    Account(Bank* bank, const string& user_name);

    // 소멸자 (public)
    ~Account();

    // 잔액 업데이트 함수 (오타 수정: unpdate -> update)
    void update_amount(int changed_amount);
    string get_account_number();
    void append_user_card(Card* card);
    int get_amount();
    Bank* get_bank();
    string get_user_name() const; // 유저 이름 반환 함수 추가
    std::string get_bank_name() const; // 지금 수정한 부분: 은행 이름 반환
};

#endif // ACCOUNT_H
