#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include "Bank.h"
#include "Card.h"
#include <vector>

class Bank;
using namespace std;

class Account {
private:
    static int account_counter;
    string p_account_number;
    Bank* p_bank;
    std::vector<std::string> user_card_list; // ī�� ��ȣ(���ڿ�)�� ����
    int amount;
    string user_name; // ���� �̸� �߰�
    std::string bank_name; // ���� ������ �κ�: ���� �̸� �߰�
public:
    // ������ (public)
    Account(Bank* bank, const string& user_name);

    // �Ҹ��� (public)
    ~Account();

    // �ܾ� ������Ʈ �Լ� (��Ÿ ����: unpdate -> update)
    void update_amount(int changed_amount);
    string get_account_number();
    void append_user_card(Card* card);
    int get_amount();
    Bank* get_bank();
    string get_user_name() const; // ���� �̸� ��ȯ �Լ� �߰�
    std::string get_bank_name() const; // ���� ������ �κ�: ���� �̸� ��ȯ
};

#endif // ACCOUNT_H
