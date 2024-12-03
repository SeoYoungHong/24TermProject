// Bank.cpp
#include "Bank.h"
using namespace std;
// ������
Bank::Bank(const std::string& name) : bank_name(name) {}

// �Ҹ���
Bank::~Bank() {
    std::cout << bank_name << "�� �����Ǿ����ϴ�.\n";
}

// ���� �̸� ������
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
            return card; // ��ġ�ϴ� ������ ��ȯ
        }
    }
    return nullptr; // ��ġ�ϴ� ������ ã�� ���� ���
}

Card* Bank::find_card_by_number(const std::string& cardnum) {
    for (const auto& card : user_card_list) {
        if (card->get_card_num() == cardnum) { // ī�� ��ȣ ��
            return card;
        }
    }
    return nullptr; // ��ġ�ϴ� ī�尡 ���� ���
}
Account* Bank::find_account_by_number(const std::string& account_num) {
    for (const auto& account : user_account_list) {
        if (account->get_account_number() == account_num) { // ī�� ��ȣ ��
            return account;
        }
    }
    return nullptr; // ��ġ�ϴ� ī�尡 ���� ���
}