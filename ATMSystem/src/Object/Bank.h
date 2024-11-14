// Bank.h
#ifndef BANK_H
#define BANK_H

#include <string>
#include <iostream>

class Bank {
private:
    std::string bank_name;

public:
    // ������
    Bank(const std::string& name);

    // �Ҹ���
    ~Bank();

    // ���� �̸� ������
    std::string getBankName() const;

    void setBankName(const std::string& name);
};

#endif // BANK_H