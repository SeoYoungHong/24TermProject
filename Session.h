#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <stdexcept> // 예외 처리를 위해 추가

class Session {
private:
    static int session_counter;
    std::string session_id;                     // 세션의 고유 ID
    int withdraw_count;                         // 현재 세션에서의 출금 횟수
    const int withdraw_count_threshold = 3;     // 출금 횟수 한도

public:
    // 생성자
    Session();

    // 소멸자
    ~Session();

    // 출금 횟수 증가
    void incrementWithdrawCount();

    // 출금 횟수 반환
    int getWithdrawCount() const;

    // 세션 ID 반환
    std::string getSessionID() const;
};

#endif // SESSION_H
