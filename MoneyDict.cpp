// MoneyDict.cpp
#include "MoneyDict.h"
using namespace std;


MoneyDict::MoneyDict()
    : check_count(0), cash_count(0), total_amount(0), cash_amount(0),isKorean(false) {
    cashes[1000] = 0;
    cashes[5000] = 0;
    cashes[10000] = 0;
    cashes[50000] = 0;
}

void MoneyDict::resetCash() {
    for (auto& pair : cashes) {
        pair.second = 0; // ��� ���� ������ 0���� �ʱ�ȭ
    }
}

void MoneyDict::setLanguageState(bool isKorean) {
    this->isKorean = isKorean;
}


void MoneyDict::addCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        cashes[denomination] += count;
        updateTotals();
    } else {
        std::cerr << (isKorean ? "��ȿ���� ���� ���� �׸鰡:\n" : "Error: Invalid denomination.\n");
        return; // �߰� ó��
    }
}


void MoneyDict::removeCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        if (cashes[denomination] >= count) {
            cashes[denomination] -= count;
            updateTotals();
        } else {
            std::cout << "��ȿ���� ���� ȭ�� �����Դϴ�.\n";
        }
    } else {
        std::cout << "�����Ϸ��� ������ ���� ���� �������� �����ϴ�.\n";
    }
}


int MoneyDict::getCashCount() const {
    return cash_count;
}


int MoneyDict::getCashAmount() const {
    return cash_amount;
}


const std::map<int, int>& MoneyDict::getCashes() const {
    return cashes;
}


void MoneyDict::addCheck(int amount) {
    if (amount >= 100000) {
        checks.push_back(amount);
        check_count++;
        updateTotals();
    } else {
    }
}


void MoneyDict::removeCheck(int index) {
    if (index >= 0 && index < checks.size()) {
        checks.erase(checks.begin() + index);
        check_count--;
        updateTotals();
    } else {
        std::cout << "��ȿ���� ���� ��ǥ �ε����Դϴ�.\n";
    }
}


int MoneyDict::getCheckCount() const {
    return check_count;
}


const std::vector<int>& MoneyDict::getChecks() const {
    return checks;
}


int MoneyDict::getTotalAmount() const {
    return total_amount;
}


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


void MoneyDict::printChecks() const {
    std::cout << "��ǥ ���:\n";
    for (size_t i = 0; i < checks.size(); ++i) {
        std::cout << "[" << i+1 << "] �ݾ�: " << checks[i] << "��\n";
    }
}


void MoneyDict::printCashes() const {
    std::cout << (isKorean ? "���� ���:\n" : "Cash list:\n");
    for (const auto& pair : cashes) {
        std::cout << (isKorean ? "�ݾ�: " : "Denomination: ") 
                << pair.first 
                << (isKorean ? "��, ����: " : " KRW, Count: ") 
                << pair.second << (isKorean ? "��\n" : "\n");
    }
}

MoneyDict MoneyDict::operator+(const MoneyDict& other) const {
    MoneyDict result = *this;

    for (const auto& pair : other.cashes) {
        result.cashes[pair.first] += pair.second;
    }

    result.checks.insert(result.checks.end(), other.checks.begin(), other.checks.end());
    result.updateTotals();
    return result;
}

bool MoneyDict::canPay(int amount) {
    std::map<int, int> temp_cashes = cashes; // ���� cashes�� ����
    int remaining = amount;

    // ū �������� Ȯ��
    for (auto it = temp_cashes.rbegin(); it != temp_cashes.rend(); ++it) {
        int denomination = it->first;
        int& available_count = it->second;

        int needed = remaining / denomination; // �ʿ��� ���� ��
        int to_use = std::min(needed, available_count); // ���� ����� �� �ִ� ���� ��
        remaining -= to_use * denomination; // ���� �ݾ� ����

        if (remaining == 0) break; // �� �̻� ������ �ݾ��� ������ ����
    }

    return (remaining == 0); // ���� �ݾ��� 0�̸� ���� ����
}

MoneyDict MoneyDict::pay(int amount) {
    MoneyDict paid_money; // ��ȯ�� ���޵� �ݾ� ������ ���� ��ü

    if (!canPay(amount)) {
        std::cout << (isKorean ? "������ �� ���� �ݾ��Դϴ�:" : "Cannot pay the amount: ")<< amount<< (isKorean ? "\n" : " \n");
        return paid_money; // �� ��ü ��ȯ
    }

    int remaining = amount;

    // ū �������� ���� ����
    for (auto it = cashes.rbegin(); it != cashes.rend(); ++it) {
        int denomination = it->first;
        int& available_count = it->second;

        int needed = remaining / denomination; // �ʿ��� ���� ��
        int to_use = std::min(needed, available_count); // ���� ����� �� �ִ� ���� ��
        available_count -= to_use; // ���� ���� ����
        remaining -= to_use * denomination; // ���� �ݾ� ����

        // ���޵� ���� paid_money ��ü�� �߰�
        paid_money.addCash(denomination, to_use);

        if (remaining == 0) break; // �� �̻� ������ �ݾ��� ������ ����
    }

    updateTotals(); // �Ѿ� ������Ʈ
    return paid_money; // ���޵� �ݾ� ��ȯ
}

