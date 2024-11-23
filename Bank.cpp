// Bank.cpp
#include "Bank.h"
using namespace std;
// 생성자
Bank::Bank(const std::string& name) : bank_name(name) {}

// 소멸자
Bank::~Bank() {
    std::cout << bank_name << "가 삭제되었습니다.\n";
}

// 은행 이름 접근자
std::string Bank::getBankName() const {
    return bank_name;
}

void Bank::setBankName(const std::string& name) {
    bank_name = name;
}

void Bank::append_user_card(Card* card){
    cout << "user account appended, card num: "<<endl;
    return user_card_list.push_back(card);
}


void Bank::append_user_account(Account* account){
    cout << "user account appended, acount num: "<<endl;
    return user_account_list.push_back(account);
}