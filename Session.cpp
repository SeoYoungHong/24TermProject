#include "Session.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

// 12자리 계좌 번호를 생성하는 함수 정의
string generatesessionNumber() {
    random_device rd;           // 시드 값 생성
    mt19937 gen(rd());          // Mersenne Twister 난수 엔진
    uniform_int_distribution<> dist(0, 9); // 0부터 9까지 균등 분포

    string account_number;
    for (int i = 0; i < 6; ++i) {
        account_number += to_string(dist(gen));
    }
    return account_number;
}

Session::Session()
    : session_id(generatesessionNumber()), withdraw_count(0) {
        cout << "new session created sessionnum: "<<session_id<<endl;
    }

Session::~Session() {}

void Session::incrementWithdrawCount() {
    ++withdraw_count;
    if (withdraw_count > withdraw_count_threshold) {
        throw std::runtime_error("출금 횟수가 한도를 초과했습니다.");
    }
}

int Session::getWithdrawCount() const {
    return withdraw_count;
}

std::string Session::getSessionID() const {
    return session_id;
}
