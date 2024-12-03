#ifndef CARD_H
#define CARD_H

#include <string>

class Account; // ���� �������� ��ȯ ���� ����

class Card {
public:
    // ��� ����
    Account* p_account;
    bool p_is_admin;
    std::string p_card_number;
    std::string p_password;

    // ������
    Card(Account* account, bool is_admin, const std::string& card_number, const std::string& password);

    // �Ҹ���
    ~Card();

    // ��� �Լ�
    Account* getAccount();
    std::string get_card_num();
    bool match_credentials(std::string card_num, std::string input_pw);
};

#endif // CARD_H
