// main.cpp
#include <iostream>
#include "Bank.h"
#include "MoneyDict.h"

int main() {
    // �׽�Ʈ �ڵ�

    // ���� ����
    Bank* bank = new Bank("Kakao Bank");
    std::cout << bank->getBankName() << std::endl;

    // ����� ����
    bank->setBankName("KB Bank");
    std::cout << bank->getBankName() << std::endl;

    // MoneyDict ��ü ����
    MoneyDict atm_cash;

    // ���� �߰�
    atm_cash.addCash(50000, 10);
    atm_cash.addCash(10000, 20);

    // ��ǥ �߰�
    atm_cash.addCheck(200000);
    atm_cash.addCheck(150000);

    // ���� ���
    std::cout << "ATM ���� �Ѿ�: " << atm_cash.getCashAmount() << "��\n";
    std::cout << "ATM �Ѿ�: " << atm_cash.getTotalAmount() << "��\n";

    // ��ǥ ��� ���
    atm_cash.printChecks();

    // ���� ��� ���
    atm_cash.printCashes();

    // �޸� ����
    delete bank;

    return 0;
}
