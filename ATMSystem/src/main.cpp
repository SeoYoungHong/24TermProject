#include <iostream>
#include "object/ATM.h"
#include "strategy/WithdrawalStrategy.h"
#include "strategy/DepositStrategy.h"
#include "strategy/TransferStrategy.h"

int main() {
    ATM atm;

    // 사용자 인증 및 거래 수행 예시
    atm.setTransactionStrategy(new WithdrawalStrategy());
    atm.executeTransaction(100); // 100 단위 인출

    atm.setTransactionStrategy(new DepositStrategy());
    atm.executeTransaction(200); // 200 단위 입금

    atm.setTransactionStrategy(new TransferStrategy());
    atm.executeTransaction(150); // 150 단위 이체

    return 0;
}
