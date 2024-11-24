#include "Session.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

int Session::session_counter = 1;

Session::Session()
    :withdraw_count(0) {
        string serial_num = to_string(session_counter);
        serial_num = string(6 - serial_num.length(), '0') + serial_num;
        session_id = serial_num;
        session_counter++;
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
