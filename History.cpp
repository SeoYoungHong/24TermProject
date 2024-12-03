#include "Account.h"
#include "ATM.h" 
#include "Bank.h" // Bank Ŭ���� ���� �ʿ�
#include "History.h"
#include "Session.h"  // Session Ŭ������ ������ �ʿ��մϴ�
// Bank Ŭ������ �����ؾ� �մϴ�
using namespace std;

#include <iostream>
#include <random> // ���� ������ ���� ���
#include <string>

using namespace std;

int History::history_counter = 1;

// ������ ����
History::History(TransactionType trans_type, int amt, Account* acc, Session* sess, const std::string info_key,const std::string info_value, ATM* atm, Bank* bank)
    : transaction_type(trans_type), amount(amt), additional_information_key(info_key),additional_information_value(info_value), bank(bank) {  // bank�� �ʱ�ȭ
    // Transaction ID ���� ���� ����
    transaction_id = std::string(6 - std::to_string(history_counter).length(), '0') + std::to_string(history_counter);
    history_counter++;

    session_id = sess->getSessionID();
    account_num = acc->get_account_number();
    atm_serial_num = atm->serial_number;
}

// �Ҹ��� ����
History::~History() {}

// getHistory �޼��� ����
HistoryData History::getHistory() const {
    HistoryData data;
    data.transaction_id = transaction_id;
    data.transaction_type = getTransactionType(true);
    data.amount = amount;
    data.account_num = account_num;
    data.session_id = session_id;
    data.additional_information = additional_information;
    data.atm_serial_num = atm_serial_num;
    return data;
}
std::string History::getTransactionType(bool isKorean) const {
    switch (transaction_type) {
        case TransactionType::Deposit:
            return isKorean ? "�Ա�" : "Deposit";
        case TransactionType::Withdrawal:
            return isKorean ? "���" : "Withdrawal";
        case TransactionType::Transfer:
            return isKorean ? "�۱�" : "Transfer";
        default:
            return isKorean ? "�� �� ����" : "Unknown";
    }
}

std::string History::getAdditionalInformation(bool isKorean) const {
    if (additional_information_key == "balance_after_transaction") {
        return isKorean ? "�ŷ� �� �ܾ�: " + additional_information_value + "��" 
                        : "Balance after transaction: " + additional_information_value + " KRW";
    } else if (additional_information_key == "target_account") {
        return isKorean ? "��� ���� ��ȣ: " + additional_information_value 
                        : "Target account number: " + additional_information_value;
    }
    return isKorean ? "�߰� ���� ����" : "No additional information";
}

void History::printHistory(const ATM* atm, Bank* bank) const { // ���� ������ �κ�
    bool isKorean = atm->language_state == 1;
    std::cout << (isKorean ? "���� ID: " : "Session ID: ") << session_id << std::endl;
    std::cout << (isKorean ? "�ŷ� ID: " : "Transaction ID: ") << transaction_id << std::endl;
    std::cout << (isKorean ? "�����̸�: " : "Bank Name: ") << getBankName() << std::endl;
    std::cout << (isKorean ? "���� ��ȣ: " : "Account Number: ") << account_num << std::endl;
    std::cout << (isKorean ? "�ŷ� ����: " : "Transaction Type: ") << getTransactionType(isKorean) << std::endl;
    std::cout << (isKorean ? "�ݾ�: " : "Amount: ") << amount << std::endl;
    std::cout << (isKorean ? "�߰�����: " : "Additional information: ") << getAdditionalInformation(isKorean)<< std::endl;
      // bank ���� ���
}

void History::printHistoryToFile(std::ofstream& outFile, const ATM* atm, Bank* bank) const { // ���� ������ �κ�
    bool isKorean = atm->language_state == 1;
    outFile << (isKorean ? "���� ID: " : "Session ID: ") << session_id << std::endl;
    outFile << (isKorean ? "�ŷ� ID: " : "Transaction ID: ") << transaction_id << std::endl;
    outFile << (isKorean ? "�����̸�: " : "Bank Name: ") << getBankName() << std::endl;
    outFile << (isKorean ? "���� ��ȣ: " : "Account Number: ") << account_num << std::endl;
    outFile << (isKorean ? "�ŷ� ����: " : "Transaction Type: ") << getTransactionType(isKorean) << std::endl;
    outFile << (isKorean ? "�ݾ�: " : "Amount: ") << amount << std::endl;
    outFile << (isKorean ? "�߰�����: " : "Additional information: ") << getAdditionalInformation(isKorean)<< std::endl;
    
    
     // bank ���� ���
}

// ������ �޼��� ����
void History::setTransactionType(TransactionType type) {
    transaction_type = type;
}

void History::setAmount(int amt) {
    amount = amt;
}

void History::setAdditionalInformation(const string& info) {
    additional_information = info;
}
std::string History::getBankName() const {
    return bank ? bank->getBankName() : "Unknown Bank"; // ���� �̸� ��ȯ, nullptr ó�� ����
}
