#ifndef ATM_H
#define ATM_H

#include "../strategy/TransactionStrategy.h"

class ATM {
public:
    void setTransactionStrategy(TransactionStrategy* strategy) {
        this->strategy = strategy;
    }

    void executeTransaction(int amount) {
        if (strategy) {
            strategy->execute(amount);
        } else {
            std::cout << "No transaction strategy set." << std::endl;
        }
    }

private:
    TransactionStrategy* strategy = nullptr;
};

#endif // ATM_H
