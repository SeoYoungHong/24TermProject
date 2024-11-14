// MoneyDict.h
#ifndef MONEYDICT_H
#define MONEYDICT_H

#include <iostream>
#include <map>
#include <vector>

class MoneyDict {
private:
    // 화폐 단위별 개수를 저장하는 맵
    std::map<int, int> cashes; // 키: 화폐 단위 (1000, 5000, 10000, 50000), 값: 개수
    std::vector<int> checks;   // 수표 금액 목록
    int check_count;
    int cash_count;
    int total_amount;
    int cash_amount;

public:
    // 생성자
    MoneyDict();

    // 현금 추가
    void addCash(int denomination, int count);

    // 현금 제거
    void removeCash(int denomination, int count);

    // 현금 개수 반환
    int getCashCount() const;

    // 현금 총액 반환
    int getCashAmount() const;

    // 현금 정보 반환
    const std::map<int, int>& getCashes() const;

    // 수표 추가
    void addCheck(int amount);

    // 수표 제거
    void removeCheck(int index);

    // 수표 개수 반환
    int getCheckCount() const;

    // 수표 목록 반환
    const std::vector<int>& getChecks() const;

    // 총액 반환
    int getTotalAmount() const;

    // 합계 업데이트
    void updateTotals();

    // 수표 목록 출력 함수 추가
    void printChecks() const;

    // 현금 정보 출력 함수 추가
    void printCashes() const;
};

#endif // MONEYDICT_H
