#include "ATMInterface.h"
#include "Card.h"
#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Session.h"
#include "History.h"
#include <fstream>
#include <algorithm> // std::find를 사용하기 위한 헤더 파일
using namespace std;

extern std::vector<std::string> global_card_numbers;
extern void mainMenuHandler(ATMInterface* atm_interface);

// Constructor implementation
ATMInterface::ATMInterface() {
    // List of bank names

    p_atm=nullptr;
}

ATM* ATMInterface::createATM(){
    Bank* choiced_bank = choiceBank(false, nullptr);
    bool is_single;
    bool is_unilingual;
    cout << "단일 ATM으로 만드시겠습니까? : (1: 단일 은행 ATM, 0: 다중 은행 ATM) "<< endl;
    cin >> is_single;
    cout << "단일 언어로 설정하시겠습니까? : (1: 단일(ENG), 0: 이중(KOR & ENG))"<< endl;
    cin >> is_unilingual;
    ATM* atm = new ATM(choiced_bank, is_single, is_unilingual);
    return atm;
}

void ATMInterface::insertCard() {
    string card_num;
    string card_pw;
    Card* card = nullptr;
    int retry_count = 0;

    // 초기화
    p_is_admin = false;
    is_inserted = false;

    // 관리자 여부 확인
    bool is_admin;
    int temp_admin; // 임시 변수로 입력받음
    while (true) {
        if (p_atm->language_state) {
            cout << "관리자입니까? (1: 네, 0: 아니오): ";
        } else {
            cout << "Is admin? (1: yes, 0: no): ";
        }
        cin >> temp_admin;

        // 입력 값 검증
        if (temp_admin == 0 || temp_admin == 1) {
            is_admin = temp_admin; // 0 또는 1을 bool 값으로 변환
            break; // 유효한 값이므로 반복 종료
        } else {
            if (p_atm->language_state) {
                cout << "잘못된 입력입니다. 0 또는 1을 입력하세요.\n";
            } else {
                cout << "Invalid input. Please enter 0 or 1.\n";
            }
        }
    }

    // 관리자 모드 처리
    if (is_admin) {
        if (p_atm->language_state) {
            cout << "카드 번호: ";
        } else {
            cout << "Card number: ";
        }
        cin >> card_num;

        if (p_atm->language_state) {
            cout << "카드 비밀번호: ";
        } else {
            cout << "Card password: ";
        }
        cin >> card_pw;

        // 관리자 인증
        if (card_num == "0" && card_pw == "0") {
            p_is_admin = true;
            is_inserted = true;

            if (p_atm->language_state) {
                cout << "관리자 모드로 로그인되었습니다.\n";
            } else {
                cout << "Logged in as admin.\n";
            }
        return;

        } else {
        if (p_atm->language_state) {
            cout << "관리자 로그인 실패.\n";
        } else {
            cout << "Failed to login as admin.\n";
        }
        mainMenuHandler(this); // 메인 메뉴로 돌아가기
        return;
}
    }

    // 일반 사용자 처리
    if (p_atm->language_state) {
        cout << "카드 번호: ";
    } else {
        cout << "Card number: ";
    }
    cin >> card_num;

    // 카드 번호로 카드 및 은행 검색
    Bank* associated_bank = nullptr;
for (auto& bank : getBankList()) {
    card = bank->find_card_by_number(card_num);
    if (card != nullptr) {
        associated_bank = bank; // 해당 은행을 저장
        break; // 카드 발견 시 탐색 종료
    }
}

// Single ATM에서 다른 은행 카드가 삽입된 경우 처리
if (p_atm->is_single_bank_atm && associated_bank != nullptr && associated_bank != p_atm->primery_bank) {
    if (p_atm->language_state) {
        cout << "이 ATM은 " << p_atm->primery_bank->getBankName() << " 카드만 지원합니다.\n";
    } else {
        cout << "This ATM only supports cards from " << p_atm->primery_bank->getBankName() << ".\n";
    }
    mainMenuHandler(this); // 메인 메뉴로 돌아가기
    return;
}

// 카드가 없는 경우 처리
if (card == nullptr) {
    if (p_atm->language_state) {
        cout << "카드 번호 " << card_num << "이(가) 존재하지 않습니다.\n";
    } else {
        cout << "Card number " << card_num << " does not exist.\n";
    }
    mainMenuHandler(this); // 메인 메뉴로 돌아가기
    return;
}

// Single ATM이 아니거나 카드가 해당 은행의 카드인 경우 처리
if (associated_bank == nullptr || (!p_atm->is_single_bank_atm || associated_bank == p_atm->primery_bank)) {
    // 카드가 정상적으로 삽입되는 경우 이후 로직 진행
} else {
    // 예상치 못한 경우 기본 메시지 처리
    if (p_atm->language_state) {
        cout << "카드를 처리할 수 없습니다.\n";
    } else {
        cout << "Unable to process the card.\n";
    }
    mainMenuHandler(this); // 메인 메뉴로 돌아가기
    return;
}


    // 비밀번호 확인
    while (retry_count < 3) {
        if (p_atm->language_state) {
            cout << "카드 비밀번호: ";
        } else {
            cout << "Card password: ";
        }
        cin >> card_pw;

        if (card->p_password != card_pw) {
            retry_count++;
            if (p_atm->language_state) {
                cout << "비밀번호 실패. 재시도 " << retry_count << "/3\n";
            } else {
                cout << "Password incorrect. Retry " << retry_count << "/3\n";
            }
        } else {
            // 비밀번호 일치 시 카드 업데이트 및 세션 시작
            update_card(card);
            is_inserted = true;
            p_is_admin = card->p_is_admin;

            if (p_atm->language_state) {
                cout << "카드 삽입 및 세션 시작\n";
            } else {
                cout << "Card inserted and session started\n";
            }
            return;
        }
    }

    // 비밀번호 3회 실패 처리
    if (!is_inserted) {
        if (p_atm->language_state) {
            cout << "비밀번호 3회 실패. 세션 종료.\n";
        } else {
            cout << "Password failed 3 times. Session aborted.\n";
        }
        mainMenuHandler(this); // 메인 메뉴로 돌아가기
        return;
}
}


Account* ATMInterface:: createAccount(){
    Bank* choice_bank;
    string user_name;
    choice_bank = choiceBank(false, nullptr); // ATM의 is_single, primary_bank과 관계없이 선택 가능하도록 수정 // 변경된 부분

    // 유저 이름 입력
    cout << "사용자 이름을 입력하세요: ";
        
    cin.ignore(); // 입력 버퍼 초기화
    getline(cin, user_name); // 유저 이름 입력

    Account* p_account = new Account(choice_bank, user_name);
    append_user_account(p_account);
    cout << "계좌가 성공적으로 생성되었습니다: " << endl;

    return p_account;
}


// Card* ATMInterface::createCard(){
//     // Constructor with user input
//     if(atm_list.size()==0){
//         return nullptr;
//     }
//     string account_number;
//     string p_password;
//     string p_card_number;
//     bool card_is_admin = false;
//     bool response=1;
//     Account* p_account = nullptr;
//     Bank* choice_bank = nullptr;
//     if(user_account_list.size()==0){

//         cout << "계좌가 없습니다. 계좌를 만들겠습니까?(1:예, 0:아니오)"<<endl;

//         cin >> response;
//         if(response){
//             p_account = createAccount();
//         }else{
 
//             cout<< "첫 페이지로 이동합니다"<<endl;

//         }
//     }else{
//         cout << "계좌가 있습니다. 계좌를 만들겠습니까?(1:예, 0:아니오)"<<endl;
        
//         cin >> response;
//         if(response){
//             p_account = createAccount();
//         }else{
//             p_account = choiceAccount();
//         }
//     }
//     cout << "카드 번호를 입력하세요: ";
    
//     cin >> p_card_number;
//     choice_bank = p_account->get_bank();
//     if(choice_bank->find_card_by_number(p_card_number)==nullptr){
//         cout << "카드 비밀번호를 입력하세요: ";
        
//         cin >> p_password;
//         Card* new_card = new Card(p_account, card_is_admin, p_card_number, p_password);
//         cout << "카드 추가/세팅에 성공하였습니다." << endl;

//         return new_card;

//     }else{
//         cout <<"이미 존재하는 카드 번호입니다."<<endl;
//         nullptr;
//     }
    
// }

// ATMInterface.cpp
Card* ATMInterface::createCard() {
    if (bank_list.empty()) {
        cout << "생성된 은행이 없습니다. 은행을 먼저 추가하세요." << endl;
        return nullptr; // 변경된 부분
    }
    
    string account_number;
    string p_password;
    string p_card_number;
    bool card_is_admin = false;
    bool response = 1;
    Account* p_account = nullptr;
    Bank* choice_bank = nullptr;
    
    // 계좌 선택 또는 생성
    if (user_account_list.empty()) {
        cout << "생성된 계좌가 없습니다. 계좌를 생성합니다." << endl; // 변경된 부분
        p_account = createAccount();
    } else {
        cout << "계좌를 선택하거나 새로 생성하세요 (1: 선택, 2: 새로 생성): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            p_account = choiceAccount();
        } else {
            p_account = createAccount();
        }
    }

while (true) {
    cout << "카드 번호를 입력하세요: ";
    cin >> p_card_number;

    // 중복 카드 번호 확인
    if (std::find(global_card_numbers.begin(), global_card_numbers.end(), p_card_number) != global_card_numbers.end()) {
        cout << "이미 존재하는 카드 번호입니다. 다시 입력하세요." << endl;
    } else {
        break; // 유효한 카드 번호가 입력되면 반복문 종료
    }
}

    choice_bank = p_account->get_bank();
    if (choice_bank->find_card_by_number(p_card_number) == nullptr) {
        cout << "카드 비밀번호를 입력하세요: ";
        cin >> p_password;

        // 새 카드 생성 및 글로벌 카드 리스트에 추가
        Card* new_card = new Card(p_account, card_is_admin, p_card_number, p_password);
        global_card_numbers.push_back(p_card_number); // 새 카드 번호 추가
        cout << "카드 추가/세팅에 성공하였습니다." << endl;

        return new_card;
    } else {
        cout << "이미 존재하는 카드 번호입니다." << endl; // 중복 메시지 출력
        return nullptr;
    }
}


void ATMInterface::reset() {
    if(p_atm->language_state){
        cout << "ATM이 성공적으로 리셋되었습니다.\n";
    }else{
        cout << "ATM Reset Successful.\n";
    }
}

void ATMInterface::printBySession() {
    if(p_atm->language_state){
        cout << "세션 기록을 출력합니다...\n";
    }else{
        cout << "Printing session history...\n";
    }

}

void ATMInterface::printByATM() {
    if(p_atm->language_state){
        cout << "ATM 거래 내역을 출력합니다...\n";
    }else{
        cout << "Printing ATM transaction history...\n";
    }
}

void ATMInterface::insertMoney() {
    if(p_atm->language_state){
        cout << "ATM에 현금을 넣으세요...\n";
    }else{
        cout << "Insert cash into the ATM...\n";
    }
    depositCash();
}

void ATMInterface::checkFee() {
    if(p_atm->language_state){
        cout << "수수료 세부 정보를 확인합니다...\n";
    }else{
        cout << "Checking fee details...\n";
    }
    checkFeeDetails();
}

void ATMInterface::transfer(Account* target_account, int amount) {
    target_account->update_amount(target_account->get_amount()+amount);
}

void ATMInterface::changeLanguage() {
    if(p_atm->is_unilingual_atm){
        cout << "can not change lanuage"<<endl;
    }else{
        if(p_atm->language_state ==1){
            p_atm->language_state=0;
            cout << "Language changed successfully.\n";
        }else{
            p_atm->language_state=1;
            cout << "언어가 한글로 변경되었습니다.\n";
        }
    }
}

// void ATMInterface::performTransaction(int option) {
//     switch (option) {
//         case 1:
//             insertMoney();
//             break;
//         case 2:
//             withdrawCash();
//             break;
//         case 3:
//             checkFee();
//             break;
//         case 4:
//             transfer();
//             break;
//         case 5:
//             changeLanguage();
//             break;
//         default:
//             cout << "Invalid transaction option. Please try again.\n";
//     }
// }

void ATMInterface::depositCash() {
    double amount;
    if(p_atm->language_state){
        cout << "입금할 금액을 입력하세요: ";
    }else{
        cout << "Enter amount to deposit: ";
    }
    cin >> amount;
    if(p_atm->language_state){
        cout << "금액 " << amount << "원이 성공적으로 입금되었습니다.\n";
    }else{
        cout << "Amount $" << amount << " deposited successfully.\n";
    }
}

void ATMInterface::withdrawCash() {
    double amount;
    if(p_atm->language_state){
        cout << "출금할 금액을 입력하세요: ";
    }else{
        cout << "Enter amount to withdraw: ";
    }
    cin >> amount;
    if(p_atm->language_state){
        cout << "금액 " << amount << "원이 성공적으로 출금되었습니다.\n";
    }else{
        cout << "Amount $" << amount << " withdrawn successfully.\n";
    }
}

void ATMInterface::checkFeeDetails() {
    if(p_atm->language_state){
        cout << "서비스 수수료: 2,500원.\n";
    }else{
        cout << "Service fee: $2500.\n";
    }
}

Bank* ATMInterface::choiceBank(bool is_single, Bank* bank){

    if(is_single && bank != nullptr){
        int choice;
        cout << "은행을 고르시오. : \n";
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }else{
        int choice;
        cout << "은행을 고르시오. : \n";
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }
    
}

Bank* ATMInterface::choiceBanking(bool is_single, Bank* bank){

    if(is_single && bank != nullptr){
        int choice;
        if(p_atm->language_state){
        cout << "은행을 고르세요:\n";
    }else{
        cout << "choose the bank :\n";
    }
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }else{
        int choice;
        if(p_atm->language_state){
        cout << "은행을 고르세요:\n";
    }else{
        cout << "choose the bank :\n";
    }
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }
    
}

Card* ATMInterface::choiceCard(){
    int choice;
    if(p_atm->language_state){
        cout << "카드 목록에서 선택하세요:\n";
    }else{
        cout << "choice in the card list :\n";
    }
    if(user_card_list.size() ==0){
        return nullptr;
    }
    for (size_t i = 0; i < user_card_list.size(); ++i) {
        cout << i + 1 << ". " << user_card_list[i]->get_card_num() << "\n";
    }
    
    cin >> choice;
    
    return user_card_list[choice-1];
}



Account* ATMInterface::choiceAccount(){
    int choice;
    cout << "계좌 목록에서 선택하세요:\n";
    
    if(user_account_list.size() ==0){
        return nullptr;
    }
    for (size_t i = 0; i < user_account_list.size(); ++i) {
        cout << i + 1 << ". " << user_account_list[i]->get_account_number() << "\n";
    }
    
    cin >> choice;
    
    return user_account_list[choice-1];
}


void ATMInterface::append_user_card(Card* card){

    cout << "사용자 카드 추가됨, 카드 번호: "<<endl;
    
    return user_card_list.push_back(card);
}


void ATMInterface::append_user_account(Account* account){
    // if(p_atm->language_state){
    //     cout << "사용자 계좌 추가됨, 계좌 번호: "<<endl;
    // }else{
    //     cout << "user account appended, account num: "<<endl;
    // }
    return user_account_list.push_back(account);
}

void ATMInterface::update_card(Card* card){
    p_card = card;
    is_inserted = true;
    p_atm->update_session(new Session());
    if (p_atm->language_state) {
         cout << "새로운 세션 시작됨. 세션 번호: "<<p_atm->present_session->getSessionID()<<endl;
    } else {
        cout << "new session created. session num: "<<p_atm->present_session->getSessionID()<<endl;
    }
    

}

Card* ATMInterface::matchcard(Bank* bank, string card_numm, string pw){
    return bank->find_card(card_numm, pw);
}

int ATMInterface::insert_cach(MoneyDict* moneydict ,bool is_initial=false) {
    int count_1000 = 0, count_5000 = 0, count_10000 = 0, count_50000 = 0;
    if (p_atm->language_state) {
        cout << "1000원 지폐 개수 입력: ";
    } else {
        cout << "Enter the number of 1000 KRW bills: ";
    }
    cin >> count_1000;
    if (p_atm->language_state) {
        cout << "5000원 지폐 개수 입력: ";
    } else {
        cout << "Enter the number of 5000 KRW bills: ";
    }
    cin >> count_5000;

    if (p_atm->language_state) {
        cout << "10000원 지폐 개수 입력: ";
    } else {
        cout << "Enter the number of 10000 KRW bills: ";
    }
    cin >> count_10000;

    if (p_atm->language_state) {
        cout << "50000원 지폐 개수 입력: ";
    } else {
        cout << "Enter the number of 50000 KRW bills: ";
    }
    cin >> count_50000;

    
    if (count_1000 < 0 || count_5000 < 0 || count_10000 < 0 || count_50000 < 0) {
        if(p_atm->language_state){
            cout << "오류: 지폐 수는 음수일 수 없습니다." << endl;
        }else{
            cout << "Error: Bill counts cannot be negative." << endl;
        }
        return 0;
    }
    moneydict->setLanguageState(p_atm->language_state == 1);
    moneydict->addCash(1000, count_1000);
    moneydict->addCash(5000, count_5000);
    moneydict->addCash(10000, count_10000);
    moneydict->addCash(50000, count_50000);

    if(moneydict->getCashCount()>p_atm->cash_maximum){
        moneydict->resetCash();
        if (p_atm->language_state) {
        cout << "입력 가능한 최대 지폐 수를 초과하였습니다.(모든 금액을 반환합니다.)" << endl;
        } else {
            cout << "The total cash count exceeds the maximum limit.(Returning all the money.)" << endl;
        }
        return 0;
    }else{
        if (p_atm->language_state) {
            cout << "정상적으로 입력되었습니다." << endl;
        } else {
            cout << "Cash inserted successfully." << endl;
        }
        return 1;
    }
    
}

int ATMInterface::insert_cache(MoneyDict* moneydict ,bool is_initial=false) {
    int count_1000 = 0, count_5000 = 0, count_10000 = 0, count_50000 = 0;
    
    cout << "1000원 지폐 개수 입력: ";
    cin >> count_1000;
    cout << "5000원 지폐 개수 입력: ";
    cin >> count_5000;
    cout << "10000원 지폐 개수 입력: ";
    cin >> count_10000;
    cout << "50000원 지폐 개수 입력: ";
    cin >> count_50000;
    
    if (count_1000 < 0 || count_5000 < 0 || count_10000 < 0 || count_50000 < 0) {
        if(p_atm->language_state){
            cout << "오류: 지폐 수는 음수일 수 없습니다." << endl;
        }else{
            cout << "Error: Bill counts cannot be negative." << endl;
        }
        return 0;
    }
    moneydict->setLanguageState(p_atm->language_state == 1);
    moneydict->addCash(1000, count_1000);
    moneydict->addCash(5000, count_5000);
    moneydict->addCash(10000, count_10000);
    moneydict->addCash(50000, count_50000);

    if(p_atm->language_state){
            cout<<"정상적으로 입력되었습니다"<<endl;
        }else{
            cout << "Successfully inserted" << endl;
        }
    
    return 1;
    
}


void ATMInterface::insert_check(){
    while (true){
        int amount;
        if(p_atm->language_state){
            cout<<"얼마를 입금하시겠습니까? (0는 종료)"<<endl;
            cout<<"수표 금액을 입력하세요: ";
        }else{
            cout<<"how much do you insert money? (0 is break)"<<endl;
            cout<<"write your check amount: ";
        }
        cin>>amount;

        if(amount ==0){
            break;
        }
        if(amount<100000){
            
            if(p_atm->language_state){
            cout<<"수표입금은 10만원 부터 가능합니다."<<endl;
        }else{
            cout<<"Check deposits are only allowed for amounts starting from 100,000 KRW."<<endl;
        }
        }
        p_atm->slot_money->setLanguageState(p_atm->language_state == 1);
        p_atm->slot_money->addCheck(amount);
        if(p_atm->slot_money->getCheckCount()==p_atm->check_maximum){

            if(p_atm->language_state){
            cout<<"입금 가능한 최대 수표를 입금하였습니다. 입금을 종료합니다."<<endl;
        }else{
            cout<<"The maximum number of depositable checks has been reached. Deposits will now stop."<<endl;
        }
            break;
        }
    }
    
}

void ATMInterface::atm_to_account() {
    int fee = (p_atm->primery_bank == p_card->getAccount()->get_bank() ? 1000 : 2000);
     while (true) {
        if (p_atm->language_state) {
            cout << "수수료: " << fee << "원" << endl;
        } else {
            cout << "Fee: " << fee << endl;
        }
        insert_cach(p_atm->input_fee);

        if (p_atm->input_fee->getTotalAmount() == fee) {
            int slot_amount = p_atm->slot_money->getTotalAmount();
            Account* account = p_card->getAccount();
            int account_amount = account->get_amount();

            account->update_amount(slot_amount + account_amount);
            *p_atm->remained_money = *(p_atm->slot_money) + *(p_atm->remained_money) + (*p_atm->input_fee);
            p_atm->reset_slot_money();
            

            // 입금 후 잔액을 가져와서 언어에 따라 메시지 생성
            int new_balance = account->get_amount();
            std::string balance_message = p_atm->language_state ? 
                                        "잔액: " + std::to_string(new_balance) + "원" :
                                        "Balance: " + std::to_string(new_balance) + "KRW";

            if (p_atm->language_state) {
                History* new_history = new History(TransactionType::Deposit, slot_amount, account,
                                            p_atm->present_session, "balance_after_transaction",std::to_string(new_balance), p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank()); // 수정된 printHistory 호출
                append_history(new_history);;
            } else {
            // History 객체 생성 시 메시지 포함
                History* new_history = new History(TransactionType::Deposit, slot_amount, account,
                                            p_atm->present_session, "balance_after_transaction",std::to_string(new_balance), p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank()); // 수정된 printHistory 호출
                append_history(new_history);
            
            }
            break;
        } else {
            p_atm->input_fee->resetCash();
            if (p_atm->language_state) {
                cout << "수수료 오류" << endl;
            } else {
                cout << "Fee error" << endl;
            }
        }
    }
}

int ATMInterface::withdraw(){
    const int MAX_WITHDRAWAL_AMOUNT = 500000;
    int fee=(p_atm->primery_bank == p_card->getAccount()->get_bank()?1000:2000);
    Account* p_account = p_card->getAccount();
    int get_amount;
    if(p_atm->language_state){
        cout <<"당신의 계좌 잔액: "<<p_account->get_amount() << " 수수료는: "<<fee<<endl;
        cout << "얼마를 출금하시겠습니까?";
    }else{
        cout <<"your account amount: "<<p_account->get_amount() << " fee is: "<<fee<<endl;
        cout << "how much do you get the amount?";
    }
    // if 문 추가하고 get_amount 변수가 50만원 넘을 경우 출금 안됨
    cin>>get_amount;
     if (get_amount > MAX_WITHDRAWAL_AMOUNT) {
        if (p_atm->language_state) {
            cout << "거래당 출금 한도를 초과했습니다. 최대 출금 금액은 50만 원입니다.\n";
        } else {
            cout << "You have exceeded the withdrawal limit per transaction. The maximum withdrawal is 500,000 KRW.\n";
        }
        return 0;
    }
    
    if(get_amount+fee>p_account->get_amount()){
        if(p_atm->language_state){
            cout<<get_amount<<"원 만큼의 금액이 없습니다."<<endl;
            cout<<"당신은 "<<p_account->get_amount()<<"원 만 가지고 있습니다"<<endl;
        }else{
            cout<<get_amount<<" don't have that much money."<<endl;
            cout<<"you have only "<<p_account->get_amount()<<endl;
        }
    }else if(p_atm->remained_money->canPay(get_amount)){
        Session* current_session = p_atm->present_session;

    // 출금 횟수 증가
        if (!current_session->incrementWithdrawCount()) { // 출금 횟수 제한 초과 확인
            if (p_atm->language_state) {
                std::cout << "출금 횟수가 한도를 초과했습니다. 세션을 다시 시작하세요." << std::endl;
            } else {
                std::cout << "Withdrawal limit exceeded. Please start a new session." << std::endl;
            }
            return 3; // 출금 실패 처리
            }else{
            p_account->update_amount(p_account->get_amount()-get_amount-fee);
            p_atm->slot_money->setLanguageState(p_atm->language_state == 1);
            MoneyDict paid_money = p_atm->remained_money->pay(get_amount);
            if(p_atm->language_state){
                cout<<"지불된 금액: "<<get_amount<<endl;
            }else{
                cout<<"money paid: "<<get_amount<<endl;
            }
            paid_money.setLanguageState(p_atm->language_state == 1);
            paid_money.printCashes();

            

            if(p_atm->language_state){
                int remaining_balance = p_account->get_amount(); // 출금 후 잔액 가져오기
                std::string balance_message = "잔액: " + std::to_string(remaining_balance) + "원";
                History* new_history = new History(TransactionType::Withdrawal,get_amount, p_card->getAccount(), p_atm->present_session,
                "balance_after_transaction",std::to_string(remaining_balance),  p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
                append_history(new_history);
            }else{
                int remaining_balance = p_account->get_amount(); // 출금 후 잔액 가져오기
                std::string balance_message = "Balance: " + std::to_string(remaining_balance) + " KRW";
                History* new_history = new History( TransactionType::Withdrawal,get_amount, p_card->getAccount(), p_atm->present_session,
                "balance_after_transaction",std::to_string(remaining_balance),  p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
                append_history(new_history);
            }
        }
    }else{
        if(p_atm->language_state){
            cout << "출금할 수 없습니다."<<endl;
        }else{
            cout << "we can't withdraw money"<<endl;
        }
    return 3;
    }
    return 0;
}

const std::vector<ATM*>& ATMInterface::getATMList() const {
    return atm_list;
}

const std::vector<Account*>& ATMInterface::getAccountList() const {
    return user_account_list;
}


Account* ATMInterface::check_account_num(){
    string account_num;
    Account* account = nullptr;
    Bank* bank = choiceBanking(p_atm->is_single_bank_atm, p_atm->primery_bank);
    if(p_atm->language_state){
        cout << "계좌 번호: ";
    }else{
        cout << "account num: ";
    }
    cin >>account_num;
    account = bank->find_account_by_number(account_num);
    if(account==nullptr){
        if(p_atm->language_state){
            cout << "계좌 번호: "<<account_num<<" 존재하지 않습니다"<<endl;
        }else{
            cout << "account num: "<<account_num<<" not exist"<<endl;
        }
    }
    return account;
}

bool ATMInterface::account_to_account(){
    
    Account* target_account = check_account_num();
    int amount;
    if(target_account==nullptr){
        return false;
    }
    if(p_atm->language_state){
        cout << "얼마를 송금하시겠습니까?"<<endl;
    }else{
        cout << "how much to transfer?"<<endl;
    }
    cin>>amount;
    Account* p_account = p_card->getAccount();
    Bank* primery_bank = p_atm->primery_bank;
    Bank* target_bank = target_account->get_bank();
    Bank* card_bank = p_card->getAccount()->get_bank();
    int fee =0;
    if(primery_bank==target_bank && primery_bank==card_bank){
        fee = 2000;
    }else if(primery_bank!=target_bank && primery_bank!=card_bank){
        fee = 4000;
    }else{
        fee =3000;
    }
    if(amount+fee>p_account->get_amount()){
        cout <<"계좌 잔액보다 많은 금액입니다. 송금불가능합니다."<<endl;
        return false;
    }else{
        p_account -> update_amount(p_account->get_amount()-amount-fee);
        transfer(target_account, amount);


        std::string target_account_info = target_account->get_account_number() + " (" + target_account->get_user_name() + ")";

        if(p_atm->language_state){
            History* new_history = new History(TransactionType::Transfer,amount, p_card->getAccount(), p_atm->present_session,
            "target_account",target_account->get_account_number(),  p_atm,p_card->getAccount()->get_bank());
            new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
            append_history(new_history);
        }else{
            
            History* new_history = new History(TransactionType::Transfer,amount, p_card->getAccount(), p_atm->present_session,
            "target_account",target_account->get_account_number(),  p_atm,p_card->getAccount()->get_bank());
            new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
            append_history(new_history);
        }
        return true;
    }
    
}

bool ATMInterface::slot_to_account() {
    Account* target_account = check_account_num(); // 은행 및 계좌번호 먼저 확인
    if (target_account == nullptr) {
        return false;
    }
    std::string target_account_info = target_account->get_account_number() + " (" + target_account->get_user_name() + ")";


    if (p_atm->language_state) {
        cout << "계좌 확인 완료. 돈과 수표를 삽입하세요." << endl;
    } else {
        cout << "Account verified. Please insert cash and checks." << endl;
    }

    insert_cach(p_atm->slot_money); // 돈 삽입
    insert_check();                 // 수표 삽입

    int fee = 1000; // 수수료 고정
    while (true) {
        if (p_atm->language_state) {
            cout << "수수료: " << fee << "원" << endl;
        } else {
            cout << "Insert fee: " << fee << endl;
        }

        insert_cach(p_atm->input_fee); // 수수료 입력받기

        if (p_atm->input_fee->getTotalAmount() == fee) {
            int amount = p_atm->slot_money->getTotalAmount(); // 삽입된 총 금액 계산
            *p_atm->remained_money = *(p_atm->slot_money) + *(p_atm->remained_money) + *(p_atm->input_fee);

            // 대상 계좌로 송금
            transfer(target_account, amount);
            p_atm->reset_slot_money(); // 슬롯 초기화

            // 거래 기록 생성 및 저장
            if (p_atm->language_state) {
                History* new_history = new History(TransactionType::Transfer, amount, p_card->getAccount(),
                                                   p_atm->present_session, "target_account",target_account->get_account_number(), p_atm, p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm, p_card->getAccount()->get_bank());
                append_history(new_history);
            } else {
                History* new_history = new History(TransactionType::Transfer, amount, p_card->getAccount(),
                                                   p_atm->present_session, "target_account",target_account->get_account_number(), p_atm, p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm, p_card->getAccount()->get_bank());
                append_history(new_history);
            }
            return true; // 작업 성공
        } else {
            p_atm->input_fee->resetCash(); // 잘못된 수수료 입력 시 초기화
            if (p_atm->language_state) {
                cout << "수수료 오류입니다. 다시 입력해주세요." << endl;
            } else {
                cout << "Fee error. Please try again." << endl;
            }
        }
    }
}


void ATMInterface::append_history(History* new_history){
    history_list.push_back(new_history);
}

void ATMInterface::print_by_session(Session* session) {
    string session_id = session->getSessionID();
    bool found = false;

    if (p_atm->language_state) {
        std::cout << "세션별로 출력합니다" << std::endl;
    } else {
        std::cout << "Print by session" << std::endl;
    }

    // 거래 기록 탐색
    for (const auto& history : history_list) {
        HistoryData data = history->getHistory();

        // 세션 ID 비교
        if (data.session_id == session_id) {
            found = true;
            history->printHistory(p_atm,p_card->getAccount()->get_bank()); // 지금 수정한 부분
            std::cout << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        if (p_atm->language_state) {
            std::cout << "세션 ID: " << session_id << "에 대한 거래가 없습니다" << std::endl;
        } else {
            std::cout << "No transactions found for session ID: " << session_id << std::endl;
        }
    }
}


void ATMInterface::print_by_atm() {
    string serial_num = p_atm->serial_number;
    bool found = false;
    if(p_atm->language_state){
        cout << "ATM별로 출력합니다"<<endl;
    }else{
        cout << "print by atm"<<endl;
    }
    // Iterate over the history list
    for (const auto& history : history_list) {
        // Assuming History has a `getHistory` method that gives us a HistoryData object
        HistoryData data = history->getHistory();

        // Compare session_id
        if (data.atm_serial_num == serial_num) {
            found = true;
            history->printHistory(p_atm,p_card->getAccount()->get_bank());
            std::cout << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        if(p_atm->language_state){
            std::cout << "ATM 일련번호: " << serial_num << "에 대한 거래가 없습니다" << std::endl;
        }else{
            std::cout << "No transactions found for atm serial number: " << serial_num << std::endl;
        }
    }
}

void ATMInterface::export_by_atm() {
    std::ofstream outFile("transaction_by_atm.txt");
    if (!outFile) {
        if (p_atm->language_state) {
            std::cerr << "파일을 쓰기 위해 열 때 오류가 발생했습니다." << std::endl;
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
        return;
    }

    bool found = false;
    std::string serial_num = p_atm->serial_number;

    // Header 출력
    if (p_atm->language_state) {
        outFile << "ATM 일련번호: " << serial_num << "의 거래 내역" << std::endl;
        outFile << "======================================" << std::endl;
    } else {
        outFile << "Transactions for ATM serial number: " << serial_num << std::endl;
        outFile << "======================================" << std::endl;
    }

    // 거래 기록 출력
    for (const auto& history : history_list) {
        HistoryData data = history->getHistory();

        // ATM Serial Number 필터링 유지
        if (data.atm_serial_num == serial_num) {
            found = true;
            history->printHistoryToFile(outFile, p_atm,p_card->getAccount()->get_bank()); // ATM* 전달로 언어 반영
            outFile << "------------------------------------" << std::endl;
        }
    }

    // 거래 내역이 없을 경우 메시지 출력
    if (!found) {
        if (p_atm->language_state) {
            outFile << "ATM 일련번호: " << serial_num << "에 대한 거래가 없습니다" << std::endl;
        } else {
            outFile << "No transactions found for ATM serial number: " << serial_num << std::endl;
        }
    }

    outFile.close();

    // 성공 메시지 출력
    if (p_atm->language_state) {
        std::cout << "정상적으로 출력되었습니다." << std::endl;
    } else {
        std::cout << "Successfully executed." << std::endl;
    }
}

ATM* ATMInterface::append_ATM(){
    if(bank_list.size()==0){
        cout <<"create bank fist"<<endl;
        return nullptr;
    }else{
        ATM* atm =createATM();
        if(atm!=nullptr){
            atm_list.push_back(atm);
            return atm;
        }else{
            return nullptr;
        }
        
    }
}

int ATMInterface::append_bank(string bank_name){
    for (const auto& bank : bank_list) {
        if(bank->getBankName()==bank_name){
            return 0;
        } 
    }
    bank_list.push_back(new Bank(bank_name));
    return 1;
}
