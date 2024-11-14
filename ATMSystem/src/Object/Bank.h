// Bank.h
#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>

class Bank {
private:
    std::string bank_name;

public:
    // 생성자
    Bank(const std::string& name);

    // 소멸자
    ~Bank();

    // 은행 이름 접근자
    std::string getBankName() const;

    void setBankName(const std::string& name);
};

#endif // BANK_H
