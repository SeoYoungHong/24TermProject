#include "Session.h"

#include <iostream>
#include <random> // 난수 생성을 위한 헤더
#include <string>

using namespace std;

int Session::session_counter = 1;

Session::Session()
    :tranjection_count(0) {
        string serial_num = to_string(session_counter);
        serial_num = string(6 - serial_num.length(), '0') + serial_num;
        session_id = serial_num;
        session_counter++;
        
    }

Session::~Session() {}



bool Session::incrementWithdrawCount() {
    ++tranjection_count;
    if (tranjection_count > tranjection_count_threshold) {
        return false;
    }
    return true;
}

int Session::getWithdrawCount() const {
    return tranjection_count;
}

std::string Session::getSessionID() const {
    return session_id;
}
