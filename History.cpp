#include "History.h"
#include "Session.h"  // Session 클래스의 구현이 필요합니다

using namespace std;

// 생성자 구현
History::History(const string& trans_id, const string& trans_type, int amt,
    Account* acc, Session* sess, const string& info)
    : transaction_id(trans_id), transaction_type(trans_type), amount(amt),
    account(acc), session(sess), additional_information(info) {}

// 소멸자 구현
History::~History() {}

// getHistory 메서드 구현
HistoryData History::getHistory() const {
    HistoryData data;
    data.transaction_id = transaction_id;
    data.transaction_type = transaction_type;
    data.amount = amount;
    data.account = account;
    data.session = session;
    data.additional_information = additional_information;
    return data;
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
