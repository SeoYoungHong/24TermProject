#include "Account.h"
#include "Bank.h" 
#include "Card.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;
class Card;
// 12자리 계좌 번호를 생성하는 함수 정의
string generateAccountNumber() {
    random_device rd;           // 시드 값 생성
    mt19937 gen(rd());          // Mersenne Twister 난수 엔진
    uniform_int_distribution<> dist(0, 9); // 0부터 9까지 균등 분포

    string account_number;
    for (int i = 0; i < 12; ++i) {
        account_number += to_string(dist(gen));
    }
    return account_number;
}

// 생성자 정의
Account::Account(Bank* bank)
    : p_account_number(generateAccountNumber()), p_bank(bank), amount(0) {
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