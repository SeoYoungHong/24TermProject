#ifndef TRANSFERSTRATEGY_H
#define TRANSFERSTRATEGY_H

#include "TransactionStrategy.h"
#include <iostream>

class TransferStrategy : public TransactionStrategy {
public:
    void execute(int amount) override {
        std::cout << "Transferring " << amount << " units." << std::endl;
    }
};

#endif // TRANSFERSTRATEGY_H
