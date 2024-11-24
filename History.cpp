#include "History.h"
#include "Session.h"  // Session 클래스의 구현이 필요합니다
#include "ATM.h"
using namespace std;

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

// 12자리 계좌 번호를 생성하는 함수 정의
string generateTransId() {
    random_device rd;           // 시드 값 생성
    mt19937 gen(rd());          // Mersenne Twister 난수 엔진
    uniform_int_distribution<> dist(0, 9); // 0부터 9까지 균등 분포

    string account_number;
    for (int i = 0; i < 6; ++i) {
        account_number += to_string(dist(gen));
    }
    return account_number;
}

// 생성자 구현
History::History(string trans_type, int amt,
    Account* acc, Session* sess, const string info, ATM* atm)
    : transaction_id(generateTransId()), transaction_type(trans_type), amount(amt),
    additional_information(info) {
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
