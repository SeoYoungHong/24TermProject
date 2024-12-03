#include "ATM.h"
#include "Bank.h"  // Bank Ŭ������ ���ǵ� ��� ������ ����
#include "MoneyDict.h"  // MoneyDict Ŭ������ ���ǵ� ��� ������ ����
#include "Session.h"  // Session Ŭ������ ���ǵ� ��� ������ ����

#include <iostream>
#include <random> // ���� ������ ���� ���
#include <string>

using namespace std;

int ATM::serial_counter = 1;


// ������ ����
ATM::ATM(Bank* bank, bool is_single, bool is_unilingual)
    : primery_bank(bank), is_single_bank_atm(is_single),
    is_unilingual_atm(is_unilingual), language_state(0),
    present_session(nullptr) {
    string serial_num = to_string(serial_counter);
    serial_num = string(6 - serial_num.length(), '0') + serial_num;  // 12�ڸ��� ���߱�
    serial_counter++;  //
    serial_number = serial_num;
    cout << "[ATM ���� �Ϸ�] �ø��� ��ȣ : " << serial_number << endl;  // Serial Number ���
    // �ʿ��� �ʱ�ȭ �۾� (�⺻���� �ִٸ�)
}

// �Ҹ��� ����
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

// slot_money ������Ʈ
void ATM::update_slot_money(MoneyDict* input_money) {
    if (slot_money != nullptr) {
        delete slot_money;  // ���� slot_money�� �ִٸ� ����
    }
    slot_money = input_money;  // ���ο� slot_money �Ҵ�
}

// remained_money ������Ʈ
void ATM::update_remained_money(MoneyDict* input_money) {
    if (remained_money != nullptr) {
        delete remained_money;  // ���� remained_money�� �ִٸ� ����
    }
    remained_money = input_money;  // ���ο� remained_money �Ҵ�
}

// ���� ������Ʈ
void ATM::update_session(Session* new_session) {
    if (present_session != nullptr) {
        delete present_session;  // ���� ������ �ִٸ� ����
    }
    present_session = new_session;  // ���ο� ���� �Ҵ�
}

void ATM::reset_slot_money(){
    delete slot_money;
    delete input_fee;
    input_fee = new MoneyDict();
    slot_money = new MoneyDict(); 
}
