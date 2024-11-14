// MoneyDict.h
#ifndef MONEYDICT_H
#define MONEYDICT_H

#include <iostream>
#include <map>
#include <vector>

class MoneyDict {
private:
    // ȭ�� ������ ������ �����ϴ� ��
    std::map<int, int> cashes; // Ű: ȭ�� ���� (1000, 5000, 10000, 50000), ��: ����
    std::vector<int> checks;   // ��ǥ �ݾ� ���
    int check_count;
    int cash_count;
    int total_amount;
    int cash_amount;

public:
    // ������
    MoneyDict();

    // ���� �߰�
    void addCash(int denomination, int count);

    // ���� ����
    void removeCash(int denomination, int count);

    // ���� ���� ��ȯ
    int getCashCount() const;

    // ���� �Ѿ� ��ȯ
    int getCashAmount() const;

    // ���� ���� ��ȯ
    const std::map<int, int>& getCashes() const;

    // ��ǥ �߰�
    void addCheck(int amount);

    // ��ǥ ����
    void removeCheck(int index);

    // ��ǥ ���� ��ȯ
    int getCheckCount() const;

    // ��ǥ ��� ��ȯ
    const std::vector<int>& getChecks() const;

    // �Ѿ� ��ȯ
    int getTotalAmount() const;

    // �հ� ������Ʈ
    void updateTotals();

    // ��ǥ ��� ��� �Լ� �߰�
    void printChecks() const;

    // ���� ���� ��� �Լ� �߰�
    void printCashes() const;
};

#endif // MONEYDICT_H