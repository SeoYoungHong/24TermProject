#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(std::string name, std::string accountNumber) 
        : name(name), accountNumber(accountNumber) {}

private:
    std::string name;
    std::string accountNumber;
};

#endif // USER_H
