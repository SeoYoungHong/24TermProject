// MoneyDict.cpp
#include "MoneyDict.h"
using namespace std;
MoneyDict::MoneyDict()
    : check_count(0), cash_count(0), total_amount(0), cash_amount(0) {
    // ȭ�� ���� �ʱ�ȭ
    cashes[1000] = 0;
    cashes[5000] = 0;
    cashes[10000] = 0;
    cashes[50000] = 0;
}

// ���� �߰�
void MoneyDict::addCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        cashes[denomination] += count;
        updateTotals();
    } else {
        std::cerr << "Error: Invalid denomination.\n";
        return; // 추가 처리
    }
}

// ���� ����
void MoneyDict::removeCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        if (cashes[denomination] >= count) {
            cashes[denomination] -= count;
            updateTotals();
        } else {
            std::cout << "�����Ϸ��� ������ ���� ���� �������� �����ϴ�.\n";
        }
    } else {
        std::cout << "��ȿ���� ���� ȭ�� �����Դϴ�.\n";
    }
}

// ���� ���� ��ȯ
int MoneyDict::getCashCount() const {
    return cash_count;
}

// ���� �Ѿ� ��ȯ
int MoneyDict::getCashAmount() const {
    return cash_amount;
}

// ���� ���� ��ȯ
const std::map<int, int>& MoneyDict::getCashes() const {
    return cashes;
}

// ��ǥ �߰�
void MoneyDict::addCheck(int amount) {
    if (amount >= 100000) {
        checks.push_back(amount);
        check_count++;
        updateTotals();
    } else {
        std::cout << "��ȿ���� ���� ��ǥ �ݾ��Դϴ�. 100,000�� �̻��̾�� �մϴ�.\n";
    }
}

// ��ǥ ����
void MoneyDict::removeCheck(int index) {
    if (index >= 0 && index < checks.size()) {
        checks.erase(checks.begin() + index);
        check_count--;
        updateTotals();
    } else {
        std::cout << "��ȿ���� ���� ��ǥ �ε����Դϴ�.\n";
    }
}

// ��ǥ ���� ��ȯ
int MoneyDict::getCheckCount() const {
    return check_count;
}

// ��ǥ ��� ��ȯ
const std::vector<int>& MoneyDict::getChecks() const {
    return checks;
}

// �Ѿ� ��ȯ
int MoneyDict::getTotalAmount() const {
    return total_amount;
}

// �հ� ������Ʈ
void MoneyDict::updateTotals() {
    cash_count = 0;
    cash_amount = 0;
    for (const auto& pair : cashes) {
        int denomination = pair.first;
        int count = pair.second;
        cash_count += count;
        cash_amount += denomination * count;
    }

    total_amount = cash_amount;
    for (const int& check_amount : checks) {
        total_amount += check_amount;
    }
}

// ��ǥ ��� ��� �Լ� �߰�
void MoneyDict::printChecks() const {
    std::cout << "��ǥ ���:\n";
    for (size_t i = 0; i < checks.size(); ++i) {
        std::cout << "[" << i + 1 << "] �ݾ�: " << checks[i] << "��\n";
    }
}

// ���� ���� ��� �Լ� �߰�
void MoneyDict::printCashes() const {
    std::cout << "���� ���:\n";
    for (const auto& pair : cashes) {
        std::cout << "�ݾ�: " << pair.first << "��, ����: " << pair.second << "��\n";
    }
}