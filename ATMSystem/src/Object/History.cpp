#include <iostream>
#include <string>
#include <vector>

// 전방 선언
class Account;
class Session;

// History 클래스 정의
class History {
private:
    std::string transaction_id;           // 거래의 고유 ID
    std::string transaction_type;         // 거래 유형 (예: 입금, 출금, 이체)
    double amount;                        // 거래 금액
    Account* account;                     // 거래와 관련된 계좌
    Session* session;                     // 거래가 속한 세션
    std::string additional_information;   // 추가 정보

public:
    // 생성자
    History(const std::string& trans_id, const std::string& trans_type, double amt,
        Account* acc, Session* sess, const std::string& info)
        : transaction_id(trans_id), transaction_type(trans_type), amount(amt),
        account(acc), session(sess), additional_information(info) {}

    // 소멸자
    ~History() {}

    // 접근자 메서드
    std::string getTransactionID() const { return transaction_id; }
    std::string getTransactionType() const { return transaction_type; }
    double getAmount() const { return amount; }
    Account* getAccount() const { return account; }
    Session* getSession() const { return session; }
    std::string getAdditionalInformation() const { return additional_information; }

    // 수정자 메서드 (Update 기능 추가)
    void setTransactionType(const std::string& type) {
        transaction_type = type;
    }

    void setAmount(double amt) {
        amount = amt;
    }

    void setAdditionalInformation(const std::string& info) {
        additional_information = info;
    }
};