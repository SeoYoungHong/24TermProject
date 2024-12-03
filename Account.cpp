#include "Account.h"
#include "Bank.h" 
#include "Card.h"

#include <iostream>
#include <random> // ���� ������ ���� ���
#include <string>

using namespace std;
class Card;
int Account::account_counter = 1;

Account::Account(Bank* bank, const std::string& user_name)
    : p_bank(bank), user_name(user_name), amount(0), bank_name(bank->getBankName()) { // ���� �̸� �ʱ�ȭ
    std::string serial_num;

    while (true) { // ���� ��ȣ �Է� ����
        std::cout << "������ ���¹�ȣ�� �Է��ϼ���.(12�ڸ�): " << std::endl;
        std::cin >> serial_num;

        // ���� ��ȣ ���� Ȯ��
        if (serial_num.length() == 12) {
            break; // ��ȿ�� �Է�
        } else {
            std::cout << "���� ��ȣ�� �ݵ�� 12�ڸ����� �մϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
    }

    account_counter++;
    p_account_number = serial_num;
    bank->append_user_account(this);

    std::cout << "������ ������ �ʱ� �ݾ��� �Է��ϼ���(KRW): " << std::endl;
    std::cin >> amount;

    std::cout << "���� ���� �Ϸ�." << std::endl;
    std::cout << "���� �̸�: " << bank_name 
              << ", ���� ��ȣ: " << p_account_number 
              << ", �ʱ� �ݾ�: " << amount 
              << "KRW, ����� �̸�: " << user_name << std::endl;
}


// �Ҹ��� ����
Account::~Account() {
    cout << "[Destruct] destruct account, account_number: " << p_account_number << endl;
    // p_bank�� ���� �޸� ������ �ؾ� �ϴ� ���, �̰����� ó�� (�ʿ��)
    // ��: delete p_bank; (���� Account�� Bank�� �����ڶ��)
}

string Account::get_user_name() const {
    return user_name;
}

std::string Account::get_bank_name() const { // ���� ������ �κ�: ���� �̸� ��ȯ
    return bank_name;
}

// �ܾ� ������Ʈ �Լ� ����
void Account::update_amount(int changed_amount) {
    amount = changed_amount;
}

// �ܾ� ������Ʈ �Լ� ����
string Account::get_account_number() {
    return p_account_number;
}
int Account::get_amount(){
    return amount;
}

void Account::append_user_card(Card* card) {
    // ���� �ڵ忡�� user_card_list�� ī�� ��ü�� �����ϴ� �κ��� ī�� ��ȣ�� �����ϵ��� ����
    // user_card_list.push_back(card); -> ����
    p_bank->append_user_card(card); // ���� ���� ����
    user_card_list.push_back(card->get_card_num()); // ī�� ��ȣ�� ����Ʈ�� �߰�
}

Bank* Account::get_bank(){
    return p_bank;
}