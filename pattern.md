ATMSystem/
│
├── src/                     // 소스 코드
│   ├── main.cpp             // 프로그램 진입점
│   ├── object/              // 객체 관련 파일
│   │   ├── ATM.cpp          // ATM 클래스 구현
│   │   ├── ATM.h            // ATM 클래스 헤더
│   │   ├── User.cpp         // User 클래스 구현
│   │   └── User.h           // User 클래스 헤더
│   └── strategy/            // 전략 관련 파일
│       ├── TransactionStrategy.h // 전략 인터페이스
│       ├── WithdrawalStrategy.cpp // 인출 전략 구현
│       ├── WithdrawalStrategy.h
│       ├── DepositStrategy.cpp    // 입금 전략 구현
│       ├── DepositStrategy.h
│       ├── TransferStrategy.cpp    // 이체 전략 구현
│       └── TransferStrategy.h
│
├── tests/                   // 테스트 코드
│   ├── ATMTest.cpp          // ATM 클래스 테스트
│   ├── WithdrawalTest.cpp   // 인출 전략 테스트
│   ├── DepositTest.cpp      // 입금 전략 테스트
│   └── TransferTest.cpp     // 이체 전략 테스트
│
├── docs/                    // 문서화
│   ├── design.md            // 설계 문서
│   ├── user_manual.md       // 사용자 매뉴얼
│   └── api_reference.md      // API 레퍼런스
│
└── CMakeLists.txt           // CMake 설정 파일
