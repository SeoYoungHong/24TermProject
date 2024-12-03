#include <iostream>
#include <string>
#include "ATMInterface.h"
using namespace std;

// Function declarations
int admin_page(ATMInterface* atm_interface);
int tranjection_select_page(ATMInterface* atm_interface);
int tranjection_deposit_money_page(ATMInterface* atm_interface);
int tranjection_withdraw_page(ATMInterface* atm_interface);
int tranjection_transfer_page(ATMInterface* atm_interface);
int go_and_stop_page(ATMInterface* atm_interface);
int print_page(ATMInterface* atm_interface);
int card_account_setup_page(ATMInterface* atm_interface);
int bank_setting(ATMInterface* atm_interface);
int atm_setting(ATMInterface* atm_interface);
int seup_page(ATMInterface* atm_interface);
void displaySnapshot(ATMInterface* atm_interface); // 선언 추가
void displayAccountSnapshot(ATMInterface* atm_interface); // 선언 추가


std::vector<std::string> global_card_numbers; // 모든 카드 번호를 저장하는 전역 리스트 추가

int main() {
    ATMInterface* atm_interface = new ATMInterface();

    while (true) {
        char choice;
        cout << "프로그램 명령을 입력하세요 (1: 초기 설정, /: 스냅샷, q: 종료): ";
        cin >> choice;

        if (choice == 'q') {
            delete atm_interface;  // 메모리 해제
            break;
        } else if (choice == '1') {
            seup_page(atm_interface);
        } 
        else if (choice == '/') {
        // ATM 및 계좌 스냅샷 출력
        displaySnapshot(atm_interface);
        displayAccountSnapshot(atm_interface);
        }
        else {
            cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
        }
    }

    return 0;
}

void displaySnapshot(ATMInterface* atm_interface) {
    // 한국어 출력
    std::cout << "===== ATM 스냅샷 =====" << std::endl;

    const auto& atm_list = atm_interface->getATMList();
    if (atm_list.empty()) {
        std::cout << "현재 등록된 ATM이 없습니다." << std::endl;
        return;
    }

    for (const auto& atm : atm_list) {
        std::cout << "ATM [시리얼 번호: " << atm->serial_number << "] ";
        atm->remained_money->setLanguageState(true); // 항상 한국어 설정
        atm->remained_money->printCashes();
    }
    std::cout << std::endl;
}

void displayAccountSnapshot(ATMInterface* atm_interface) {
    // 한국어 출력
    std::cout << "===== 계좌 스냅샷 =====" << std::endl;

    const auto& accounts = atm_interface->getAccountList();
    if (accounts.empty()) {
        std::cout << "현재 등록된 계좌가 없습니다." << std::endl;
        return;
    }

    for (const auto& account : accounts) {
        Bank* bank = account->get_bank();
        std::cout << "계좌 [사용자: " << account->get_user_name()
                  << ", 은행: " << bank->getBankName() << ", 계좌번호: " << account->get_account_number()
                  << "] 잔액: " << account->get_amount() << "원" << std::endl;
    }
    std::cout << std::endl;
}


void mainMenuHandler(ATMInterface* atm_interface) {
    char choice;
    if (atm_interface->p_atm == nullptr) {
        choice = '1';
    } else {
        if (atm_interface->p_atm->language_state) {
            cout << " 1. 카드삽입 || q. 나가기 || l. 언어 바꾸기" << endl;
            cout << "입력하세요: ";
        } else {
            cout << " 1. Insert Card || q. quit || l. change language" << endl;
            cout << "Enter your choice: ";
        }
        cin >> choice;
    }

    switch (choice) {
        case 'q':
            cout << "start initail setting" << endl;
            seup_page(atm_interface);
            break;
        case '1':
            atm_interface->insertCard();
            if (atm_interface->is_inserted) {
                if (atm_interface->p_is_admin) {
                    admin_page(atm_interface);
                } else {
                    tranjection_select_page(atm_interface);
                }
            }
            break;
        case 'l':
            atm_interface->changeLanguage();
            mainMenuHandler(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            mainMenuHandler(atm_interface);
            break;
        default:
            if (atm_interface->p_atm->language_state) {
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                mainMenuHandler(atm_interface);
            } else {
                cout << "Invalid choice. Please try again.\n";
                mainMenuHandler(atm_interface);
            }
    }
}


void select_atm(ATMInterface* atm_interface) {
    const auto& atm_list = atm_interface->getATMList();  // Getter로 atm_list 접근
    if (atm_list.empty()) {
        cout << "선택할 ATM이 없습니다. 먼저 ATM을 추가하세요." << endl;
        return;
    }

    cout << "사용 가능한 ATM 리스트:" << endl;
    for (size_t i = 0; i < atm_list.size(); ++i) {
        cout << i + 1 << ". Serial Number: " << atm_list[i]->serial_number << endl;
    }

    cout << "선택할 ATM 번호를 입력하세요: ";
    size_t choice;
    cin >> choice;

    if (choice >= 1 && choice <= atm_list.size()) {
        atm_interface->p_atm = atm_list[choice - 1];
        cout << "ATM(Serial Number: " << atm_interface->p_atm->serial_number << ")이 선택되었습니다." << endl;
    } else {
        cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
    }
}

int seup_page(ATMInterface* atm_interface) {
    char choice;
    while (true) {
        cout << "1. 은행 세팅 || 2. ATM 세팅 || 3. 계좌, 카드 세팅 || 4. ATM 선택 || q. 나가기" << endl;
        cout << "입력하세요 : ";

        int result = 0;
        cin >> choice;

        switch (choice) {
            case '1':
                result = bank_setting(atm_interface);
                if (result == 0) {
                    cout << "은행 추가/세팅에 실패했습니다" << endl;
                }
                break;
            case '2':
                result = atm_setting(atm_interface);
                if (result == 0) {
                    cout << "ATM 추가/세팅에 실패했습니다" << endl;
                }
                break;
            case '3':
                result = card_account_setup_page(atm_interface);
                if (result == 0) {
                    cout << "카드 추가/세팅에 실패했습니다." << endl;
                }
                
                break;
            case '4':
                select_atm(atm_interface);
                if (atm_interface->p_atm != nullptr) {
                    mainMenuHandler(atm_interface); // 선택된 ATM에서 작업 수행
                }
                break;
            case '/':
                displaySnapshot(atm_interface);
                displayAccountSnapshot(atm_interface);
            break;
            case 'q':
                return 0; // 초기화 페이지 종료
            
            default:
                cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
        }
    }
}

int bank_setting(ATMInterface* atm_interface) {
    cout << "추가할 은행명을 입력해주세요: ";
    string bank_name;

    // std::getline()으로 공백 포함 입력 받기
    cin.ignore(); // 이전 입력 버퍼의 잔여 데이터를 제거
    std::getline(cin, bank_name);

    int result = atm_interface->append_bank(bank_name);
    if (result == 0) {
    } else {
        cout << "은행 '" << bank_name << "' 추가/세팅에 성공했습니다" << endl;
    }
    return result;
}

int atm_setting(ATMInterface* atm_interface) {
    ATM* atm = atm_interface->append_ATM();
    if (atm != nullptr) {
        // 현재 ATM이 없으면 자동으로 설정
        if (atm_interface->p_atm == nullptr) {
            atm_interface->p_atm = atm;
        } else {
            // 기존 ATM이 있을 경우, 항상 새 ATM으로 교체
            atm_interface->p_atm = atm;
        }

        // ATM의 초기 캐시 삽입
        atm_interface->insert_cache(atm->remained_money, true);
        return 1;
    } else {
        return 0; // ATM 생성 실패 시
    }
}  
    
int card_account_setup_page(ATMInterface* atm_interface){
    Card* card =atm_interface->createCard();
    if(card==nullptr){
        return 0;
    }else{
        return 1;
    }
    
}


int tranjection_select_page(ATMInterface* atm_interface){
    char choice;
    if(atm_interface->p_atm->language_state){
        cout << "1. 입금 || 2. 출금 || 3. 송금 || q. 나가기 || l. 언어 바꾸기 "<<endl;
        cout << "입력하세요: ";
        
    }else{
        cout << "1. insert money ||2. withdraw money||3. fransfer money || q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
    }
    cin >> choice;

    switch (choice) {
        case '1':
            tranjection_deposit_money_page(atm_interface);
            break;
        case '2':
            tranjection_withdraw_page(atm_interface);
            break;
        case '3':
            tranjection_transfer_page(atm_interface);
            break;
        case 'q':
            print_page(atm_interface);
            break;
        case 'l':
            atm_interface->changeLanguage();
            tranjection_select_page(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            tranjection_select_page(atm_interface);
            break;
        default:
            if(atm_interface->p_atm->language_state){
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                tranjection_select_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                tranjection_select_page(atm_interface);
            }
    }
    if(atm_interface->is_inserted){
        go_and_stop_page(atm_interface);
    }else{
        print_page(atm_interface);
    }
    
    return 0;
}

//money slot-> card account
int tranjection_deposit_money_page(ATMInterface* atm_interface){
    
    while(true){
        char choice;
        if(atm_interface->p_atm->language_state){
            cout << "1. 현금 넣기 || 2. 수표 넣기 || 3. 입금 || q. 나가기 || l. 언어 바꾸기 "<<endl;
            cout << "입력하세요: ";
        }else{
            cout << "1. insert cach || 2. insert check ||3. deposit || q. Exit || l. change language "<<endl;
            cout << "Enter your choice: ";
        }
        cin >> choice;
        switch (choice) {
            case '1':
                atm_interface->insert_cach(atm_interface->p_atm->slot_money,false);
                break;
            case '2':
                atm_interface->insert_check();
                break;
            case '3':
                atm_interface->atm_to_account();
                return 0;
            case 'q':
                tranjection_select_page(atm_interface);
                return 0;
            case 'l':
                atm_interface->changeLanguage();
                tranjection_deposit_money_page(atm_interface);
                break;
            case '/':
                displaySnapshot(atm_interface);
                displayAccountSnapshot(atm_interface);
                tranjection_deposit_money_page(atm_interface);
                break;
            default:
                if(atm_interface->p_atm->language_state){
                    cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                    tranjection_deposit_money_page(atm_interface);
                }else{
                    cout << "Invalid choice. Please try again.\n";
                    tranjection_deposit_money_page(atm_interface);
                }
        }
    }
    return 0;
}



//account -> slot
int tranjection_withdraw_page(ATMInterface* atm_interface) {


    // 출금 로직 실행
     int result = atm_interface->withdraw();
        if (result == 3) {
        // 세션 종료 후 메인 메뉴로 복귀
        print_page(atm_interface);
    }else{
    return 0;
    }
}


//1. slot -> account
//2. account -> account
int tranjection_transfer_page(ATMInterface* atm_interface){
    char choice;
    if(atm_interface->p_atm->language_state){
        cout << "1. 슬롯에서 계좌로 ||2. 계좌에서 계좌로 || q. 나가기 || l. 언어 바꾸기 "<<endl;
        cout << "입력하세요: ";
    }else{
        cout << "1. slot to account ||2. account to account || q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
    }
    cin >> choice;
    switch (choice) {
        case '1':
            atm_interface->slot_to_account();
            break;
        case '2':
            atm_interface->account_to_account();

            break;
        case 'q':
        print_page(atm_interface);
            return 0;
        case 'l':
            atm_interface->changeLanguage();
            tranjection_transfer_page(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            tranjection_transfer_page(atm_interface);
            break;
        default:
            if(atm_interface->p_atm->language_state){
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                tranjection_transfer_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                tranjection_transfer_page(atm_interface);
            }
    }
    return 0;
}

int go_and_stop_page(ATMInterface* atm_interface){
    char choice;
    if(atm_interface->p_atm->language_state){
        cout << "1. 더 거래하기 || 2. 세션 기록 출력(나가기) || l. 언어 바꾸기 "<<endl;
        cout << "입력하세요: ";
    }else{
        cout << "1. more transaction || 2. print session history|| q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
    }
    cin >> choice;



    switch (choice) {
        case '1':
            tranjection_select_page(atm_interface);
            break;
        case '2':
            print_page(atm_interface);
            break;
        case 'l':
            atm_interface->changeLanguage();
            go_and_stop_page(atm_interface);
            break;
        case 'q':
            mainMenuHandler(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            go_and_stop_page(atm_interface);
            break;
        default:
            if(atm_interface->p_atm->language_state){
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                go_and_stop_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                go_and_stop_page(atm_interface);
            }
            break;
    }
    return 0;
}

int print_page(ATMInterface* atm_interface){
    char choice;
    Session* presentsession = atm_interface->p_atm->present_session;
    atm_interface->print_by_session(presentsession);
    if(atm_interface->p_atm->language_state){
        cout << "1. 재시도 || q. 나가기 || l. 언어 바꾸기 "<<endl;
        cout << "입력하세요: ";
    }else{
        cout << "1. retry || q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
    }
    cin >> choice;


    switch (choice) {
        case '1':
            print_page(atm_interface);
            break;
        case 'q':
            mainMenuHandler(atm_interface);
            break;
        case 'l':
            atm_interface->changeLanguage();
            print_page(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            print_page(atm_interface);
            break;
        default:
            if(atm_interface->p_atm->language_state){
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                print_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                print_page(atm_interface);
            }

    }
    return 0;
}

int admin_page(ATMInterface* atm_interface){
    char choice;
    if(atm_interface->p_atm->language_state){
        cout << "1. 모든 거래 보기 및 거래 내보내기 || q. 나가기 "<<endl;
        cout << "입력하세요: ";
    }else{
        cout << "1. show all of the tranjections and export tranjections || q. Exit"<<endl;
        cout << "Enter your choice: ";
    }
    cin >> choice;


    switch (choice) {
        case '1':
            atm_interface->print_by_atm();
            atm_interface->export_by_atm();
            mainMenuHandler(atm_interface);
            break;
        case '2':
            atm_interface->export_by_atm();
            mainMenuHandler(atm_interface);
            break;
        case 'q':
            mainMenuHandler(atm_interface);
            break;
        case 'l':
            atm_interface->changeLanguage();
            admin_page(atm_interface);
            break;
        case '/':
            displaySnapshot(atm_interface);
            displayAccountSnapshot(atm_interface);
            admin_page(atm_interface);
            break;
        default:
            if(atm_interface->p_atm->language_state){
                cout << "잘못된 선택입니다. 다시 시도해주세요.\n";
                admin_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                admin_page(atm_interface);
            }
    }
    return 0;
}