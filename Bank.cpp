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
    // cout << "user account appended, card num: "<<endl;
    return user_card_list.push_back(card);
}


void Bank::append_user_account(Account* account){
    // cout << "user account appended, acount num: "<<endl;
    return user_account_list.push_back(account);
}

Card* Bank::find_card(string input_id,string input_pw)  {
    for (const auto& card : user_card_list) {
        if (card->match_credentials(input_id, input_pw)) {
            return card; // 일치하는 계정을 반환
        }
    }
    return nullptr; // 일치하는 계정을 찾지 못한 경우
}

Card* Bank::find_card_by_number(const std::string& cardnum) {
    for (const auto& card : user_card_list) {
        if (card->get_card_num() == cardnum) { // 카드 번호 비교
            return card;
        }
    }
    return nullptr; // 일치하는 카드가 없는 경우
}
Account* Bank::find_account_by_number(const std::string& account_num) {
    for (const auto& account : user_account_list) {
        if (account->get_account_number() == account_num) { // 카드 번호 비교
            return account;
        }
    }
    return nullptr; // 일치하는 카드가 없는 경우
}