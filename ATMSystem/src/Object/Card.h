#ifndef CARD_H
#define CARD_H

#include <string>

// Account 클래스의 전방 선언
class Account;

class Card {
public:
    // 멤버 변수
    Account* p_account;
    bool p_is_admin;
    std::string p_card_number;
    std::string p_password;

    // 생성자
    Card(Account* account, bool is_admin, const std::string& card_number, const std::string& password);

    // 소멸자
    ~Card();

    // 복사 생성자 및 복사 대입 연산자
    Card(const Card& other);
    Card& operator=(const Card& other);

private:
    // private 멤버 함수 및 변수 필요 시 정의 가능
};

#endif // CARD_H
