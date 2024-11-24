#include "History.h"
#include "Session.h"  // Session 클래스의 구현이 필요합니다
#include "ATM.h"
using namespace std;

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

int History::history_counter = 1;


// 생성자 구현
History::History(string trans_type, int amt,
    Account* acc, Session* sess, const string info, ATM* atm)
    :transaction_type(trans_type), amount(amt),
    additional_information(info) {
        string serial_num = to_string(history_counter);
        serial_num = string(6 - serial_num.length(), '0') + serial_num;  // 12자리로 맞추기
        history_counter++; 
        transaction_id = serial_num;
        session_id = sess->getSessionID();
        account_num = acc->get_account_number();
        int remain_money = acc->get_amount();
        atm_serial_num = atm->serial_number;


    }

// 소멸자 구현
History::~History() {}

// getHistory 메서드 구현
HistoryData History::getHistory() const {
    HistoryData data;
    data.transaction_id = transaction_id;
    data.transaction_type = transaction_type;
    data.amount = amount;
    data.account_num = account_num;
    data.session_id = session_id;
    data.additional_information = additional_information;
    data.atm_serial_num = atm_serial_num;
    return data;
}

void History::printHistory() {
    HistoryData data = getHistory();
    std::cout << "Transaction ID: " << data.transaction_id << std::endl;
    std::cout << "Transaction Type: " << data.transaction_type << std::endl;
    std::cout << "Amount: " << data.amount << std::endl;
    std::cout << "Account Number: " << data.account_num << std::endl;
    std::cout << "Session ID: " << data.session_id << std::endl;
    std::cout << "Additional Information: " << data.additional_information << std::endl;
}

void History::printHistoryToFile(std::ofstream& outFile) {
    outFile << "Transaction ID: " << transaction_id << std::endl;
    outFile << "Transaction Type: " << transaction_type << std::endl;
    outFile << "Amount: " << amount << std::endl;
    outFile << "Account Number: " << account_num << std::endl;
    outFile << "Session ID: " << session_id << std::endl;
    outFile << "Additional Information: " << additional_information << std::endl;
}

// 수정자 메서드 구현
void History::setTransactionType(const string& type) {
    transaction_type = type;
}

void History::setAmount(int amt) {
    amount = amt;
}

void History::setAdditionalInformation(const string& info) {
    additional_information = info;
}
