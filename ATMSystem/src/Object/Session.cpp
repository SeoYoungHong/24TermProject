#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>  // 예외 처리를 위해 추가

// Session 클래스 정의
class Session {
private:
    std::string session_id;                     // 세션의 고유 ID
    int withdraw_count;                         // 현재 세션에서의 출금 횟수
    const int withdraw_count_threshold = 3;     // 출금 횟수 한도

public:
    // 생성자
    Session(const std::string& id)
        : session_id(id), withdraw_count(0) {}

    // 소멸자
    ~Session() {}

    // 출금 횟수 증가
    void incrementWithdrawCount() {
        ++withdraw_count;
        // threshold 추가에 따른 예외처리
        if (withdraw_count > withdraw_count_threshold) {
            throw std::runtime_error("출금 횟수가 한도를 초과했습니다.");
        }
    }

    // 출금 횟수 반환
    int getWithdrawCount() const {
        return withdraw_count;
    }

    // 세션 ID 반환
    std::string getSessionID() const {
        return session_id;
    }
};
