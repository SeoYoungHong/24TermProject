// MoneyDict.cpp
#include "MoneyDict.h"

// 생성자
MoneyDict::MoneyDict()
    : check_count(0), cash_count(0), total_amount(0), cash_amount(0) {
    // 화폐 단위 초기화
    cashes[1000] = 0;
    cashes[5000] = 0;
    cashes[10000] = 0;
    cashes[50000] = 0;
}

// 현금 추가
void MoneyDict::addCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        cashes[denomination] += count;
        updateTotals();
    } else {
        std::cout << "유효하지 않은 화폐 단위입니다.\n";
    }
}

// 현금 제거
void MoneyDict::removeCash(int denomination, int count) {
    if (cashes.find(denomination) != cashes.end()) {
        if (cashes[denomination] >= count) {
            cashes[denomination] -= count;
            updateTotals();
        } else {
            std::cout << "제거하려는 수량이 현재 보유 수량보다 많습니다.\n";
        }
    } else {
        std::cout << "유효하지 않은 화폐 단위입니다.\n";
    }
}

// 현금 개수 반환
int MoneyDict::getCashCount() const {
    return cash_count;
}

// 현금 총액 반환
int MoneyDict::getCashAmount() const {
    return cash_amount;
}

// 현금 정보 반환
const std::map<int, int>& MoneyDict::getCashes() const {
    return cashes;
}

// 수표 추가
void MoneyDict::addCheck(int amount) {
    if (amount >= 100000) {
        checks.push_back(amount);
        check_count++;
        updateTotals();
    } else {
        std::cout << "유효하지 않은 수표 금액입니다. 100,000원 이상이어야 합니다.\n";
    }
}

// 수표 제거
void MoneyDict::removeCheck(int index) {
    if (index >= 0 && index < checks.size()) {
        checks.erase(checks.begin() + index);
        check_count--;
        updateTotals();
    } else {
        std::cout << "유효하지 않은 수표 인덱스입니다.\n";
    }
}

// 수표 개수 반환
int MoneyDict::getCheckCount() const {
    return check_count;
}

// 수표 목록 반환
const std::vector<int>& MoneyDict::getChecks() const {
    return checks;
}

// 총액 반환
int MoneyDict::getTotalAmount() const {
    return total_amount;
}

// 합계 업데이트
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

// 수표 목록 출력 함수 추가
void MoneyDict::printChecks() const {
    std::cout << "수표 목록:\n";
    for (size_t i = 0; i < checks.size(); ++i) {
        std::cout << "[" << i + 1 << "] 금액: " << checks[i] << "원\n";
    }
}

// 현금 정보 출력 함수 추가
void MoneyDict::printCashes() const {
    std::cout << "현금 목록:\n";
    for (const auto& pair : cashes) {
        std::cout << "금액: " << pair.first << "원, 개수: " << pair.second << "장\n";
    }
}
