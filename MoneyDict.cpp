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
    std::map<int, int> temp_cashes = cashes; // 원본 cashes를 보존
    int remaining = amount;

    // 큰 단위부터 확인
    for (auto it = temp_cashes.rbegin(); it != temp_cashes.rend(); ++it) {
        int denomination = it->first;
        int& available_count = it->second;

        int needed = remaining / denomination; // 필요한 지폐 수
        int to_use = std::min(needed, available_count); // 실제 사용할 수 있는 지폐 수
        remaining -= to_use * denomination; // 남은 금액 갱신

        if (remaining == 0) break; // 더 이상 지불할 금액이 없으면 종료
    }

    return (remaining == 0); // 남은 금액이 0이면 지급 가능
}

MoneyDict MoneyDict::pay(int amount) {
    MoneyDict paid_money; // 반환할 지급된 금액 정보를 담을 객체

    if (!canPay(amount)) {
        std::cout << "Cannot pay the amount: " << amount << "\n";
        return paid_money; // 빈 객체 반환
    }

    int remaining = amount;

    // 큰 단위부터 실제 차감
    for (auto it = cashes.rbegin(); it != cashes.rend(); ++it) {
        int denomination = it->first;
        int& available_count = it->second;

        int needed = remaining / denomination; // 필요한 지폐 수
        int to_use = std::min(needed, available_count); // 실제 사용할 수 있는 지폐 수
        available_count -= to_use; // 실제 지폐 차감
        remaining -= to_use * denomination; // 남은 금액 갱신

        // 지급된 지폐를 paid_money 객체에 추가
        paid_money.addCash(denomination, to_use);

        if (remaining == 0) break; // 더 이상 지불할 금액이 없으면 종료
    }

    updateTotals(); // 총액 업데이트
    std::cout << "Paid " << amount << " successfully.\n";
    return paid_money; // 지급된 금액 반환
}

