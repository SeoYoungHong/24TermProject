#ifndef TRANSACTIONSTRATEGY_H
#define TRANSACTIONSTRATEGY_H

class TransactionStrategy {
public:
    virtual void execute(int amount) = 0; // 순수 가상 함수
    virtual ~TransactionStrategy() = default; // 가상 소멸자
};

#endif // TRANSACTIONSTRATEGY_H
