ATMSystem/
│
├── src/
│   ├── main.cpp                      // 진입점
│   ├── ATM/                          // ATM 관련 클래스
│   │   ├── ATM.h                     // ATM 클래스 정의
│   │   ├── ATMMachine.h              // ATM 기계 클래스 정의
│   │   ├── ATMFactory.h              // ATM 팩토리 인터페이스
│   │   └── ConcreteATMs.h            // 구체적인 ATM 클래스들
│   │
│   ├── transactions/                  // 트랜잭션 관련 클래스
│   │   ├── Transaction.h              // 트랜잭션 기본 클래스
│   │   ├── Withdraw.h                 // 인출 트랜잭션
│   │   ├── Deposit.h                  // 예금 트랜잭션
│   │   ├── Transfer.h                 // 송금 트랜잭션
│   │   └── Command.h                  // 커맨드 패턴 구현
│   │
│   ├── user/                          // 사용자 관련 클래스
│   │   ├── User.h                     // 사용자 클래스
│   │   └── Account.h                  // 계좌 클래스
│   │
│   ├── observers/                     // 옵저버 패턴 관련 클래스
│   │   ├── Observer.h                 // 옵저버 인터페이스
│   │   ├── BalanceObserver.h          // 잔액 관찰자
│   │   └── CashObserver.h             // 현금 관찰자
│   │
│   └── strategies/                    // 전략 패턴 관련 클래스
│       ├── Strategy.h                 // 전략 인터페이스
│       ├── CashWithdrawalStrategy.h   // 현금 인출 전략
│       └── TransferStrategy.h          // 송금 전략
│
├── include/                           // 헤더 파일
│   ├── ATM.h                          // ATM 관련 헤더
│   ├── Transaction.h                  // 트랜잭션 관련 헤더
│   ├── User.h                         // 사용자 관련 헤더
│   └── Observer.h                     // 옵저버 관련 헤더
│
└── tests/                             // 테스트 관련 파일
    ├── ATMMachineTest.cpp             // ATM 기계 테스트
    ├── TransactionTest.cpp            // 트랜잭션 테스트
    └── UserTest.cpp                   // 사용자 테스트