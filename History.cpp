#include "Account.h"
#include "ATM.h" 
#include "Bank.h" // Bank 클래스 포함 필요
#include "History.h"
#include "Session.h"  // Session 클래스의 구현이 필요합니다
// Bank 클래스를 포함해야 합니다
using namespace std;

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

int History::history_counter = 1;

// 생성자 구현
History::History(TransactionType trans_type, int amt, Account* acc, Session* sess, const std::string info_key,const std::string info_value, ATM* atm, Bank* bank)
    : transaction_type(trans_type), amount(amt), additional_information_key(info_key),additional_information_value(info_value), bank(bank) {  // bank를 초기화
    // Transaction ID 생성 로직 수정
    transaction_id = std::string(6 - std::to_string(history_counter).length(), '0') + std::to_string(history_counter);
    history_counter++;

    session_id = sess->getSessionID();
    account_num = acc->get_account_number();
    atm_serial_num = atm->serial_number;
}

// 소멸자 구현
History::~History() {}

// getHistory 메서드 구현
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
            return isKorean ? "입금" : "Deposit";
        case TransactionType::Withdrawal:
            return isKorean ? "출금" : "Withdrawal";
        case TransactionType::Transfer:
            return isKorean ? "송금" : "Transfer";
        default:
            return isKorean ? "알 수 없음" : "Unknown";
    }
}

std::string History::getAdditionalInformation(bool isKorean) const {
    if (additional_information_key == "balance_after_transaction") {
        return isKorean ? "거래 후 잔액: " + additional_information_value + "원" 
                        : "Balance after transaction: " + additional_information_value + " KRW";
    } else if (additional_information_key == "target_account") {
        return isKorean ? "상대 계좌 번호: " + additional_information_value 
                        : "Target account number: " + additional_information_value;
    }
    return isKorean ? "추가 정보 없음" : "No additional information";
}

void History::printHistory(const ATM* atm, Bank* bank) const { // 지금 수정한 부분
    bool isKorean = atm->language_state == 1;
    std::cout << (isKorean ? "세션 ID: " : "Session ID: ") << session_id << std::endl;
    std::cout << (isKorean ? "거래 ID: " : "Transaction ID: ") << transaction_id << std::endl;
    std::cout << (isKorean ? "은행이름: " : "Bank Name: ") << getBankName() << std::endl;
    std::cout << (isKorean ? "계좌 번호: " : "Account Number: ") << account_num << std::endl;
    std::cout << (isKorean ? "거래 유형: " : "Transaction Type: ") << getTransactionType(isKorean) << std::endl;
    std::cout << (isKorean ? "금액: " : "Amount: ") << amount << std::endl;
    std::cout << (isKorean ? "추가정보: " : "Additional information: ") << getAdditionalInformation(isKorean)<< std::endl;
      // bank 정보 출력
}

void History::printHistoryToFile(std::ofstream& outFile, const ATM* atm, Bank* bank) const { // 지금 수정한 부분
    bool isKorean = atm->language_state == 1;
    outFile << (isKorean ? "세션 ID: " : "Session ID: ") << session_id << std::endl;
    outFile << (isKorean ? "거래 ID: " : "Transaction ID: ") << transaction_id << std::endl;
    outFile << (isKorean ? "은행이름: " : "Bank Name: ") << getBankName() << std::endl;
    outFile << (isKorean ? "계좌 번호: " : "Account Number: ") << account_num << std::endl;
    outFile << (isKorean ? "거래 유형: " : "Transaction Type: ") << getTransactionType(isKorean) << std::endl;
    outFile << (isKorean ? "금액: " : "Amount: ") << amount << std::endl;
    outFile << (isKorean ? "추가정보: " : "Additional information: ") << getAdditionalInformation(isKorean)<< std::endl;
    
    
     // bank 정보 출력
}

// 수정자 메서드 구현
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
    return bank ? bank->getBankName() : "Unknown Bank"; // 은행 이름 반환, nullptr 처리 포함
}
