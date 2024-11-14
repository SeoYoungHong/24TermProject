// main.cpp
#include <iostream>
#include "Bank.h"
#include "MoneyDict.h"

int main() {
    // 테스트 코드

    // 은행 생성
    Bank* bank = new Bank("Kakao Bank");
    std::cout << bank->getBankName() << std::endl;

    // 은행명 변경
    bank->setBankName("KB Bank");
    std::cout << bank->getBankName() << std::endl;

    // MoneyDict 객체 생성
    MoneyDict atm_cash;

    // 현금 추가
    atm_cash.addCash(50000, 10);
    atm_cash.addCash(10000, 20);

    // 수표 추가
    atm_cash.addCheck(200000);
    atm_cash.addCheck(150000);

    // 정보 출력
    std::cout << "ATM 현금 총액: " << atm_cash.getCashAmount() << "원\n";
    std::cout << "ATM 총액: " << atm_cash.getTotalAmount() << "원\n";

    // 수표 목록 출력
    atm_cash.printChecks();

    // 현금 목록 출력
    atm_cash.printCashes();

    // 메모리 해제
    delete bank;

    return 0;
}
