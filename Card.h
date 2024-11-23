#ifndef CARD_H
#define CARD_H

#include <string>

class Account; // 전방 선언으로 순환 참조 방지

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

    // 멤버 함수
    Account* getAccount();
    std::string get_card_num();
};

#endif // CARD_H
