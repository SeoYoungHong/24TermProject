#include "Account.h"
#include "Bank.h" 
#include "Card.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;
class Card;
int Account::account_counter = 1;

Account::Account(Bank* bank, const std::string& user_name)
    : p_bank(bank), user_name(user_name), amount(0), bank_name(bank->getBankName()) { // 은행 이름 초기화
    std::string serial_num;

    while (true) { // 계좌 번호 입력 루프
        std::cout << "생성할 계좌번호를 입력하세요.(12자리): " << std::endl;
        std::cin >> serial_num;

        // 계좌 번호 길이 확인
        if (serial_num.length() == 12) {
            break; // 유효한 입력
        } else {
            std::cout << "계좌 번호는 반드시 12자리여야 합니다. 다시 입력해주세요." << std::endl;
        }
    }

    account_counter++;
    p_account_number = serial_num;
    bank->append_user_account(this);

    std::cout << "생성된 계좌의 초기 금액을 입력하세요(KRW): " << std::endl;
    std::cin >> amount;

    std::cout << "계좌 생성 완료." << std::endl;
    std::cout << "은행 이름: " << bank_name 
              << ", 계좌 번호: " << p_account_number 
              << ", 초기 금액: " << amount 
              << "KRW, 사용자 이름: " << user_name << std::endl;
}


// 소멸자 정의
Account::~Account() {
    cout << "[Destruct] destruct account, account_number: " << p_account_number << endl;
    // p_bank에 대한 메모리 해제를 해야 하는 경우, 이곳에서 처리 (필요시)
    // 예: delete p_bank; (만약 Account가 Bank의 소유자라면)
}

string Account::get_user_name() const {
    return user_name;
}

std::string Account::get_bank_name() const { // 지금 수정한 부분: 은행 이름 반환
    return bank_name;
}

// 잔액 업데이트 함수 정의
void Account::update_amount(int changed_amount) {
    amount = changed_amount;
}

// 잔액 업데이트 함수 정의
string Account::get_account_number() {
    return p_account_number;
}
int Account::get_amount(){
    return amount;
}

void Account::append_user_card(Card* card) {
    // 기존 코드에서 user_card_list에 카드 객체를 저장하던 부분을 카드 번호만 저장하도록 수정
    // user_card_list.push_back(card); -> 제거
    p_bank->append_user_card(card); // 기존 로직 유지
    user_card_list.push_back(card->get_card_num()); // 카드 번호만 리스트에 추가
}

Bank* Account::get_bank(){
    return p_bank;
}