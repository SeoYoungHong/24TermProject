#include "Account.h"
#include "Bank.h" 
#include "Card.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;
class Card;
int Account::account_counter = 1;


// 생성자 정의
Account::Account(Bank* bank)
    : p_bank(bank), amount(0) {
    string serial_num = to_string(account_counter);
    serial_num = string(12 - serial_num.length(), '0') + serial_num;  // 12자리로 맞추기
    account_counter++;
    p_account_number =serial_num;
    bank->append_user_account(this);
    amount=0;
    cout << "[Construct] create account, account_number: " << p_account_number << endl;
}

// 소멸자 정의
Account::~Account() {
    cout << "[Destruct] destruct account, account_number: " << p_account_number << endl;
    // p_bank에 대한 메모리 해제를 해야 하는 경우, 이곳에서 처리 (필요시)
    // 예: delete p_bank; (만약 Account가 Bank의 소유자라면)
}

// 잔액 업데이트 함수 정의
void Account::update_amount(int changed_amount) {
    amount = changed_amount;
    cout << "Updated amount: " << amount << endl;
}

// 잔액 업데이트 함수 정의
string Account::get_account_number() {
    return p_account_number;
}
int Account::get_amount(){
    return amount;
}

void Account::append_user_card(Card* card){
    cout << "user account appended, card num: "<<endl;
    p_bank->append_user_card(card);
    user_card_list.push_back(card);
}

Bank* Account::get_bank(){
    return p_bank;
}