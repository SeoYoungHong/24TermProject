#include "Card.h"
#include "Account.h"  // Account 클래스의 정의를 포함

// 생성자 정의
Card::Card(Account* account, bool is_admin, const std::string& card_number, const std::string& password)
    : p_account(account), p_is_admin(is_admin), p_card_number(card_number), p_password(password) {}

// 소멸자 정의
Card::~Card() {
    // p_account에 대한 메모리 해제를 해야 하는 경우, 이곳에서 처리
    // 예: delete p_account; (p_account가 Card의 소유자라면)
}

// 복사 생성자 정의
Card::Card(const Card& other)
    : p_account(other.p_account), p_is_admin(other.p_is_admin),
      p_card_number(other.p_card_number), p_password(other.p_password) {}

// 복사 대입 연산자 정의
Card& Card::operator=(const Card& other) {
    if (this != &other) {
        p_account = other.p_account;
        p_is_admin = other.p_is_admin;
        p_card_number = other.p_card_number;
        p_password = other.p_password;
    }
    return *this;
}
