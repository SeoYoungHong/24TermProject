#include "ATM.h"
#include "Bank.h"  // Bank 클래스가 정의된 헤더 파일을 포함
#include "MoneyDict.h"  // MoneyDict 클래스가 정의된 헤더 파일을 포함
#include "Session.h"  // Session 클래스가 정의된 헤더 파일을 포함

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

// 12자리 계좌 번호를 생성하는 함수 정의
string generateSerialNumber() {
    random_device rd;           // 시드 값 생성
    mt19937 gen(rd());          // Mersenne Twister 난수 엔진
    uniform_int_distribution<> dist(0, 9); // 0부터 9까지 균등 분포

    string account_number;
    for (int i = 0; i < 6; ++i) {
        account_number += to_string(dist(gen));
    }
    return account_number;
}

// 생성자 정의
ATM::ATM(Bank* bank, bool is_single, bool is_unilingual)
    : primery_bank(bank), serial_number(generateSerialNumber()), is_single_bank_atm(is_single),
      is_unilingual_atm(is_unilingual), language_state(0),
      present_session(nullptr) {
    // 필요한 초기화 작업 (기본값이 있다면)
}

// 소멸자 정의
ATM::~ATM() {
    if (remained_money != nullptr) {
        delete remained_money;
        remained_money = nullptr;
    }
    if (slot_money != nullptr) {
        delete slot_money;
        slot_money = nullptr;
    }
    if (present_session != nullptr) {
        delete present_session;
        present_session = nullptr;
    }
}

// slot_money 업데이트
void ATM::update_slot_money(MoneyDict* input_money) {
    if (slot_money != nullptr) {
        delete slot_money;  // 기존 slot_money가 있다면 삭제
    }
    slot_money = input_money;  // 새로운 slot_money 할당
}

// remained_money 업데이트
void ATM::update_remained_money(MoneyDict* input_money) {
    if (remained_money != nullptr) {
        delete remained_money;  // 기존 remained_money가 있다면 삭제
    }
    remained_money = input_money;  // 새로운 remained_money 할당
}

// 세션 업데이트
void ATM::update_session(Session* new_session) {
    if (present_session != nullptr) {
        delete present_session;  // 기존 세션이 있다면 삭제
    }
    present_session = new_session;  // 새로운 세션 할당
}
