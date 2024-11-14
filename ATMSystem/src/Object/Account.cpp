#include "Account.h"
#include "Bank.h"  // Bank 클래스의 정의를 포함

// 생성자 정의
Account::Account(string account_number, Bank* bank)
    : p_account_number(account_number), p_bank(bank), amount(0) {
    cout << "[Construct] create account, account_number: " << account_number << endl;
}

// 소멸자 정의
Account::~Account() {
    cout << "[Destruct] destruct account, account_number: " << p_account_number << endl;
    // p_bank에 대한 메모리 해제를 해야 하는 경우, 이곳에서 처리 (필요시)
    // 예: delete p_bank; (만약 Account가 Bank의 소유자라면)
}

// 잔액 업데이트 함수 정의
void Account::update_amount(int changed_amount) {
    amount = changed_amount;
    cout << "Updated amount: " << amount << endl;
}
