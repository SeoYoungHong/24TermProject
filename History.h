#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include "Account.h"  // Account Ŭ������ ������ �ʿ��մϴ�.

// ���� ����
class Session;

// HistoryData ����ü ����
struct HistoryData {
    std::string transaction_id;           // �ŷ��� ���� ID
    std::string transaction_type;         // �ŷ� ����
    int amount;                           // �ŷ� �ݾ�
    Account* account;                     // �ŷ��� ���õ� ����
    Session* session;                     // �ŷ��� ���� ����
    std::string additional_information;   // �߰� ����
};

// History Ŭ���� ����
class History {
private:
    std::string transaction_id;           // �ŷ��� ���� ID
    std::string transaction_type;         // �ŷ� ���� (��: �Ա�, ���, ��ü)
    int amount;                           // �ŷ� �ݾ�
    Account* account;                     // �ŷ��� ���õ� ����
    Session* session;                     // �ŷ��� ���� ����
    std::string additional_information;   // �߰� ����

public:
    // ������
    History(const std::string& trans_id, const std::string& trans_type, int amt,
        Account* acc, Session* sess, const std::string& info);

    // �Ҹ���
    ~History();

    // getHistory �޼���: ��� ��� ������ �����ϴ� ����ü�� ��ȯ
    HistoryData getHistory() const;

    // ������ �޼��� (Update ��� �߰�)
    void setTransactionType(const std::string& type);
    void setAmount(int amt);
    void setAdditionalInformation(const std::string& info);
};

#endif // HISTORY_H
