#ifndef WITHDRAWALSTRATEGY_H
#define WITHDRAWALSTRATEGY_H

#include "TransactionStrategy.h"
#include <iostream>

class WithdrawalStrategy : public TransactionStrategy {
public:
    void execute(int amount) override {
        std::cout << "Withdrawing " << amount << " units." << std::endl;
    }
};

#endif // WITHDRAWALSTRATEGY_H
