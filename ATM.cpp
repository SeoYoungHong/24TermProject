#include "ATM.h"
#include "Bank.h"  // Bank 클래스가 정의된 헤더 파일을 포함
#include "MoneyDict.h"  // MoneyDict 클래스가 정의된 헤더 파일을 포함
#include "Session.h"  // Session 클래스가 정의된 헤더 파일을 포함

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

int ATM::serial_counter = 1;


// 생성자 정의
ATM::ATM(Bank* bank, bool is_single, bool is_unilingual)
    : primery_bank(bank), is_single_bank_atm(is_single),
    is_unilingual_atm(is_unilingual), language_state(0),
    present_session(nullptr) {
    string serial_num = to_string(serial_counter);
    serial_num = string(6 - serial_num.length(), '0') + serial_num;  // 12자리로 맞추기
    serial_counter++;  //
    serial_number = serial_num;
    cout << "[ATM 생성 완료] 시리얼 번호 : " << serial_number << endl;  // Serial Number 출력
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

void ATM::reset_slot_money(){
    delete slot_money;
    delete input_fee;
    input_fee = new MoneyDict();
    slot_money = new MoneyDict(); 
}
