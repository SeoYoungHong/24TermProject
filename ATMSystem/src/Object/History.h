// History.h
#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include "Account.h"  // Account 클래스의 구현이 필요합니다.

// 전방 선언
class Session;

// HistoryData 구조체 정의
struct HistoryData {
    std::string transaction_id;           // 거래의 고유 ID
    std::string transaction_type;         // 거래 유형
    int amount;                           // 거래 금액
    Account* account;                     // 거래와 관련된 계좌
    Session* session;                     // 거래가 속한 세션
    std::string additional_information;   // 추가 정보
};

// History 클래스 정의
class History {
private:
    std::string transaction_id;           // 거래의 고유 ID
    std::string transaction_type;         // 거래 유형 (예: 입금, 출금, 이체)
    int amount;                           // 거래 금액
    Account* account;                     // 거래와 관련된 계좌
    Session* session;                     // 거래가 속한 세션
    std::string additional_information;   // 추가 정보

public:
    // 생성자
    History(const std::string& trans_id, const std::string& trans_type, int amt,
        Account* acc, Session* sess, const std::string& info);

    // 소멸자
    ~History();

    // getHistory 메서드: 모든 멤버 변수를 포함하는 구조체를 반환
    HistoryData getHistory() const;

    // 수정자 메서드 (Update 기능 추가)
    void setTransactionType(const std::string& type);
    void setAmount(int amt);
    void setAdditionalInformation(const std::string& info);
};

#endif // HISTORY_H
