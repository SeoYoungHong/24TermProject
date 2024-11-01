#ifndef DEPOSITSTRATEGY_H
#define DEPOSITSTRATEGY_H

#include "TransactionStrategy.h"
#include <iostream>

class DepositStrategy : public TransactionStrategy {
public:
    void execute(int amount) override {
        std::cout << "Depositing " << amount << " units." << std::endl;
    }
};

#endif // DEPOSITSTRATEGY_H
