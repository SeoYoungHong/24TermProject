// Bank.cpp
#include "Bank.h"

// 생성자
Bank::Bank(const std::string& name) : bank_name(name) {}

// 소멸자
Bank::~Bank() {
    // 연결된 계좌까지 지우려면 아래 코드를 사용하세요
    // for (Account* account : accounts) {
    //     delete account;
    // }
    std::cout << bank_name << "가 삭제되었습니다.\n";
}

// 은행 이름 접근자
std::string Bank::getBankName() const {
    return bank_name;
}

void Bank::setBankName(const std::string& name) {
    bank_name = name;
}
