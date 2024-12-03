#include "ATMInterface.h"
#include "Card.h"
#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Session.h"
#include "History.h"
#include <fstream>
#include <algorithm> // std::find�� ����ϱ� ���� ��� ����
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
    cout << "���� ATM���� ����ðڽ��ϱ�? : (1: ���� ���� ATM, 0: ���� ���� ATM) "<< endl;
    cin >> is_single;
    cout << "���� ���� �����Ͻðڽ��ϱ�? : (1: ����(ENG), 0: ����(KOR & ENG))"<< endl;
    cin >> is_unilingual;
    ATM* atm = new ATM(choiced_bank, is_single, is_unilingual);
    return atm;
}

void ATMInterface::insertCard() {
    string card_num;
    string card_pw;
    Card* card = nullptr;
    int retry_count = 0;

    // �ʱ�ȭ
    p_is_admin = false;
    is_inserted = false;

    // ������ ���� Ȯ��
    bool is_admin;
    int temp_admin; // �ӽ� ������ �Է¹���
    while (true) {
        if (p_atm->language_state) {
            cout << "�������Դϱ�? (1: ��, 0: �ƴϿ�): ";
        } else {
            cout << "Is admin? (1: yes, 0: no): ";
        }
        cin >> temp_admin;

        // �Է� �� ����
        if (temp_admin == 0 || temp_admin == 1) {
            is_admin = temp_admin; // 0 �Ǵ� 1�� bool ������ ��ȯ
            break; // ��ȿ�� ���̹Ƿ� �ݺ� ����
        } else {
            if (p_atm->language_state) {
                cout << "�߸��� �Է��Դϴ�. 0 �Ǵ� 1�� �Է��ϼ���.\n";
            } else {
                cout << "Invalid input. Please enter 0 or 1.\n";
            }
        }
    }

    // ������ ��� ó��
    if (is_admin) {
        if (p_atm->language_state) {
            cout << "ī�� ��ȣ: ";
        } else {
            cout << "Card number: ";
        }
        cin >> card_num;

        if (p_atm->language_state) {
            cout << "ī�� ��й�ȣ: ";
        } else {
            cout << "Card password: ";
        }
        cin >> card_pw;

        // ������ ����
        if (card_num == "0" && card_pw == "0") {
            p_is_admin = true;
            is_inserted = true;

            if (p_atm->language_state) {
                cout << "������ ���� �α��εǾ����ϴ�.\n";
            } else {
                cout << "Logged in as admin.\n";
            }
        return;

        } else {
        if (p_atm->language_state) {
            cout << "������ �α��� ����.\n";
        } else {
            cout << "Failed to login as admin.\n";
        }
        mainMenuHandler(this); // ���� �޴��� ���ư���
        return;
}
    }

    // �Ϲ� ����� ó��
    if (p_atm->language_state) {
        cout << "ī�� ��ȣ: ";
    } else {
        cout << "Card number: ";
    }
    cin >> card_num;

    // ī�� ��ȣ�� ī�� �� ���� �˻�
    Bank* associated_bank = nullptr;
for (auto& bank : getBankList()) {
    card = bank->find_card_by_number(card_num);
    if (card != nullptr) {
        associated_bank = bank; // �ش� ������ ����
        break; // ī�� �߰� �� Ž�� ����
    }
}

// Single ATM���� �ٸ� ���� ī�尡 ���Ե� ��� ó��
if (p_atm->is_single_bank_atm && associated_bank != nullptr && associated_bank != p_atm->primery_bank) {
    if (p_atm->language_state) {
        cout << "�� ATM�� " << p_atm->primery_bank->getBankName() << " ī�常 �����մϴ�.\n";
    } else {
        cout << "This ATM only supports cards from " << p_atm->primery_bank->getBankName() << ".\n";
    }
    mainMenuHandler(this); // ���� �޴��� ���ư���
    return;
}

// ī�尡 ���� ��� ó��
if (card == nullptr) {
    if (p_atm->language_state) {
        cout << "ī�� ��ȣ " << card_num << "��(��) �������� �ʽ��ϴ�.\n";
    } else {
        cout << "Card number " << card_num << " does not exist.\n";
    }
    mainMenuHandler(this); // ���� �޴��� ���ư���
    return;
}

// Single ATM�� �ƴϰų� ī�尡 �ش� ������ ī���� ��� ó��
if (associated_bank == nullptr || (!p_atm->is_single_bank_atm || associated_bank == p_atm->primery_bank)) {
    // ī�尡 ���������� ���ԵǴ� ��� ���� ���� ����
} else {
    // ����ġ ���� ��� �⺻ �޽��� ó��
    if (p_atm->language_state) {
        cout << "ī�带 ó���� �� �����ϴ�.\n";
    } else {
        cout << "Unable to process the card.\n";
    }
    mainMenuHandler(this); // ���� �޴��� ���ư���
    return;
}


    // ��й�ȣ Ȯ��
    while (retry_count < 3) {
        if (p_atm->language_state) {
            cout << "ī�� ��й�ȣ: ";
        } else {
            cout << "Card password: ";
        }
        cin >> card_pw;

        if (card->p_password != card_pw) {
            retry_count++;
            if (p_atm->language_state) {
                cout << "��й�ȣ ����. ��õ� " << retry_count << "/3\n";
            } else {
                cout << "Password incorrect. Retry " << retry_count << "/3\n";
            }
        } else {
            // ��й�ȣ ��ġ �� ī�� ������Ʈ �� ���� ����
            update_card(card);
            is_inserted = true;
            p_is_admin = card->p_is_admin;

            if (p_atm->language_state) {
                cout << "ī�� ���� �� ���� ����\n";
            } else {
                cout << "Card inserted and session started\n";
            }
            return;
        }
    }

    // ��й�ȣ 3ȸ ���� ó��
    if (!is_inserted) {
        if (p_atm->language_state) {
            cout << "��й�ȣ 3ȸ ����. ���� ����.\n";
        } else {
            cout << "Password failed 3 times. Session aborted.\n";
        }
        mainMenuHandler(this); // ���� �޴��� ���ư���
        return;
}
}


Account* ATMInterface:: createAccount(){
    Bank* choice_bank;
    string user_name;
    choice_bank = choiceBank(false, nullptr); // ATM�� is_single, primary_bank�� ������� ���� �����ϵ��� ���� // ����� �κ�

    // ���� �̸� �Է�
    cout << "����� �̸��� �Է��ϼ���: ";
        
    cin.ignore(); // �Է� ���� �ʱ�ȭ
    getline(cin, user_name); // ���� �̸� �Է�

    Account* p_account = new Account(choice_bank, user_name);
    append_user_account(p_account);
    cout << "���°� ���������� �����Ǿ����ϴ�: " << endl;

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

//         cout << "���°� �����ϴ�. ���¸� ����ڽ��ϱ�?(1:��, 0:�ƴϿ�)"<<endl;

//         cin >> response;
//         if(response){
//             p_account = createAccount();
//         }else{
 
//             cout<< "ù �������� �̵��մϴ�"<<endl;

//         }
//     }else{
//         cout << "���°� �ֽ��ϴ�. ���¸� ����ڽ��ϱ�?(1:��, 0:�ƴϿ�)"<<endl;
        
//         cin >> response;
//         if(response){
//             p_account = createAccount();
//         }else{
//             p_account = choiceAccount();
//         }
//     }
//     cout << "ī�� ��ȣ�� �Է��ϼ���: ";
    
//     cin >> p_card_number;
//     choice_bank = p_account->get_bank();
//     if(choice_bank->find_card_by_number(p_card_number)==nullptr){
//         cout << "ī�� ��й�ȣ�� �Է��ϼ���: ";
        
//         cin >> p_password;
//         Card* new_card = new Card(p_account, card_is_admin, p_card_number, p_password);
//         cout << "ī�� �߰�/���ÿ� �����Ͽ����ϴ�." << endl;

//         return new_card;

//     }else{
//         cout <<"�̹� �����ϴ� ī�� ��ȣ�Դϴ�."<<endl;
//         nullptr;
//     }
    
// }

// ATMInterface.cpp
Card* ATMInterface::createCard() {
    if (bank_list.empty()) {
        cout << "������ ������ �����ϴ�. ������ ���� �߰��ϼ���." << endl;
        return nullptr; // ����� �κ�
    }
    
    string account_number;
    string p_password;
    string p_card_number;
    bool card_is_admin = false;
    bool response = 1;
    Account* p_account = nullptr;
    Bank* choice_bank = nullptr;
    
    // ���� ���� �Ǵ� ����
    if (user_account_list.empty()) {
        cout << "������ ���°� �����ϴ�. ���¸� �����մϴ�." << endl; // ����� �κ�
        p_account = createAccount();
    } else {
        cout << "���¸� �����ϰų� ���� �����ϼ��� (1: ����, 2: ���� ����): ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            p_account = choiceAccount();
        } else {
            p_account = createAccount();
        }
    }

while (true) {
    cout << "ī�� ��ȣ�� �Է��ϼ���: ";
    cin >> p_card_number;

    // �ߺ� ī�� ��ȣ Ȯ��
    if (std::find(global_card_numbers.begin(), global_card_numbers.end(), p_card_number) != global_card_numbers.end()) {
        cout << "�̹� �����ϴ� ī�� ��ȣ�Դϴ�. �ٽ� �Է��ϼ���." << endl;
    } else {
        break; // ��ȿ�� ī�� ��ȣ�� �ԷµǸ� �ݺ��� ����
    }
}

    choice_bank = p_account->get_bank();
    if (choice_bank->find_card_by_number(p_card_number) == nullptr) {
        cout << "ī�� ��й�ȣ�� �Է��ϼ���: ";
        cin >> p_password;

        // �� ī�� ���� �� �۷ι� ī�� ����Ʈ�� �߰�
        Card* new_card = new Card(p_account, card_is_admin, p_card_number, p_password);
        global_card_numbers.push_back(p_card_number); // �� ī�� ��ȣ �߰�
        cout << "ī�� �߰�/���ÿ� �����Ͽ����ϴ�." << endl;

        return new_card;
    } else {
        cout << "�̹� �����ϴ� ī�� ��ȣ�Դϴ�." << endl; // �ߺ� �޽��� ���
        return nullptr;
    }
}


void ATMInterface::reset() {
    if(p_atm->language_state){
        cout << "ATM�� ���������� ���µǾ����ϴ�.\n";
    }else{
        cout << "ATM Reset Successful.\n";
    }
}

void ATMInterface::printBySession() {
    if(p_atm->language_state){
        cout << "���� ����� ����մϴ�...\n";
    }else{
        cout << "Printing session history...\n";
    }

}

void ATMInterface::printByATM() {
    if(p_atm->language_state){
        cout << "ATM �ŷ� ������ ����մϴ�...\n";
    }else{
        cout << "Printing ATM transaction history...\n";
    }
}

void ATMInterface::insertMoney() {
    if(p_atm->language_state){
        cout << "ATM�� ������ ��������...\n";
    }else{
        cout << "Insert cash into the ATM...\n";
    }
    depositCash();
}

void ATMInterface::checkFee() {
    if(p_atm->language_state){
        cout << "������ ���� ������ Ȯ���մϴ�...\n";
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
            cout << "�� �ѱ۷� ����Ǿ����ϴ�.\n";
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
        cout << "�Ա��� �ݾ��� �Է��ϼ���: ";
    }else{
        cout << "Enter amount to deposit: ";
    }
    cin >> amount;
    if(p_atm->language_state){
        cout << "�ݾ� " << amount << "���� ���������� �ԱݵǾ����ϴ�.\n";
    }else{
        cout << "Amount $" << amount << " deposited successfully.\n";
    }
}

void ATMInterface::withdrawCash() {
    double amount;
    if(p_atm->language_state){
        cout << "����� �ݾ��� �Է��ϼ���: ";
    }else{
        cout << "Enter amount to withdraw: ";
    }
    cin >> amount;
    if(p_atm->language_state){
        cout << "�ݾ� " << amount << "���� ���������� ��ݵǾ����ϴ�.\n";
    }else{
        cout << "Amount $" << amount << " withdrawn successfully.\n";
    }
}

void ATMInterface::checkFeeDetails() {
    if(p_atm->language_state){
        cout << "���� ������: 2,500��.\n";
    }else{
        cout << "Service fee: $2500.\n";
    }
}

Bank* ATMInterface::choiceBank(bool is_single, Bank* bank){

    if(is_single && bank != nullptr){
        int choice;
        cout << "������ ���ÿ�. : \n";
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }else{
        int choice;
        cout << "������ ���ÿ�. : \n";
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
        cout << "������ ������:\n";
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
        cout << "������ ������:\n";
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
        cout << "ī�� ��Ͽ��� �����ϼ���:\n";
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
    cout << "���� ��Ͽ��� �����ϼ���:\n";
    
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

    cout << "����� ī�� �߰���, ī�� ��ȣ: "<<endl;
    
    return user_card_list.push_back(card);
}


void ATMInterface::append_user_account(Account* account){
    // if(p_atm->language_state){
    //     cout << "����� ���� �߰���, ���� ��ȣ: "<<endl;
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
         cout << "���ο� ���� ���۵�. ���� ��ȣ: "<<p_atm->present_session->getSessionID()<<endl;
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
        cout << "1000�� ���� ���� �Է�: ";
    } else {
        cout << "Enter the number of 1000 KRW bills: ";
    }
    cin >> count_1000;
    if (p_atm->language_state) {
        cout << "5000�� ���� ���� �Է�: ";
    } else {
        cout << "Enter the number of 5000 KRW bills: ";
    }
    cin >> count_5000;

    if (p_atm->language_state) {
        cout << "10000�� ���� ���� �Է�: ";
    } else {
        cout << "Enter the number of 10000 KRW bills: ";
    }
    cin >> count_10000;

    if (p_atm->language_state) {
        cout << "50000�� ���� ���� �Է�: ";
    } else {
        cout << "Enter the number of 50000 KRW bills: ";
    }
    cin >> count_50000;

    
    if (count_1000 < 0 || count_5000 < 0 || count_10000 < 0 || count_50000 < 0) {
        if(p_atm->language_state){
            cout << "����: ���� ���� ������ �� �����ϴ�." << endl;
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
        cout << "�Է� ������ �ִ� ���� ���� �ʰ��Ͽ����ϴ�.(��� �ݾ��� ��ȯ�մϴ�.)" << endl;
        } else {
            cout << "The total cash count exceeds the maximum limit.(Returning all the money.)" << endl;
        }
        return 0;
    }else{
        if (p_atm->language_state) {
            cout << "���������� �ԷµǾ����ϴ�." << endl;
        } else {
            cout << "Cash inserted successfully." << endl;
        }
        return 1;
    }
    
}

int ATMInterface::insert_cache(MoneyDict* moneydict ,bool is_initial=false) {
    int count_1000 = 0, count_5000 = 0, count_10000 = 0, count_50000 = 0;
    
    cout << "1000�� ���� ���� �Է�: ";
    cin >> count_1000;
    cout << "5000�� ���� ���� �Է�: ";
    cin >> count_5000;
    cout << "10000�� ���� ���� �Է�: ";
    cin >> count_10000;
    cout << "50000�� ���� ���� �Է�: ";
    cin >> count_50000;
    
    if (count_1000 < 0 || count_5000 < 0 || count_10000 < 0 || count_50000 < 0) {
        if(p_atm->language_state){
            cout << "����: ���� ���� ������ �� �����ϴ�." << endl;
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
            cout<<"���������� �ԷµǾ����ϴ�"<<endl;
        }else{
            cout << "Successfully inserted" << endl;
        }
    
    return 1;
    
}


void ATMInterface::insert_check(){
    while (true){
        int amount;
        if(p_atm->language_state){
            cout<<"�󸶸� �Ա��Ͻðڽ��ϱ�? (0�� ����)"<<endl;
            cout<<"��ǥ �ݾ��� �Է��ϼ���: ";
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
            cout<<"��ǥ�Ա��� 10���� ���� �����մϴ�."<<endl;
        }else{
            cout<<"Check deposits are only allowed for amounts starting from 100,000 KRW."<<endl;
        }
        }
        p_atm->slot_money->setLanguageState(p_atm->language_state == 1);
        p_atm->slot_money->addCheck(amount);
        if(p_atm->slot_money->getCheckCount()==p_atm->check_maximum){

            if(p_atm->language_state){
            cout<<"�Ա� ������ �ִ� ��ǥ�� �Ա��Ͽ����ϴ�. �Ա��� �����մϴ�."<<endl;
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
            cout << "������: " << fee << "��" << endl;
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
            

            // �Ա� �� �ܾ��� �����ͼ� �� ���� �޽��� ����
            int new_balance = account->get_amount();
            std::string balance_message = p_atm->language_state ? 
                                        "�ܾ�: " + std::to_string(new_balance) + "��" :
                                        "Balance: " + std::to_string(new_balance) + "KRW";

            if (p_atm->language_state) {
                History* new_history = new History(TransactionType::Deposit, slot_amount, account,
                                            p_atm->present_session, "balance_after_transaction",std::to_string(new_balance), p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank()); // ������ printHistory ȣ��
                append_history(new_history);;
            } else {
            // History ��ü ���� �� �޽��� ����
                History* new_history = new History(TransactionType::Deposit, slot_amount, account,
                                            p_atm->present_session, "balance_after_transaction",std::to_string(new_balance), p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank()); // ������ printHistory ȣ��
                append_history(new_history);
            
            }
            break;
        } else {
            p_atm->input_fee->resetCash();
            if (p_atm->language_state) {
                cout << "������ ����" << endl;
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
        cout <<"����� ���� �ܾ�: "<<p_account->get_amount() << " �������: "<<fee<<endl;
        cout << "�󸶸� ����Ͻðڽ��ϱ�?";
    }else{
        cout <<"your account amount: "<<p_account->get_amount() << " fee is: "<<fee<<endl;
        cout << "how much do you get the amount?";
    }
    // if �� �߰��ϰ� get_amount ������ 50���� ���� ��� ��� �ȵ�
    cin>>get_amount;
     if (get_amount > MAX_WITHDRAWAL_AMOUNT) {
        if (p_atm->language_state) {
            cout << "�ŷ��� ��� �ѵ��� �ʰ��߽��ϴ�. �ִ� ��� �ݾ��� 50�� ���Դϴ�.\n";
        } else {
            cout << "You have exceeded the withdrawal limit per transaction. The maximum withdrawal is 500,000 KRW.\n";
        }
        return 0;
    }
    
    if(get_amount+fee>p_account->get_amount()){
        if(p_atm->language_state){
            cout<<get_amount<<"�� ��ŭ�� �ݾ��� �����ϴ�."<<endl;
            cout<<"����� "<<p_account->get_amount()<<"�� �� ������ �ֽ��ϴ�"<<endl;
        }else{
            cout<<get_amount<<" don't have that much money."<<endl;
            cout<<"you have only "<<p_account->get_amount()<<endl;
        }
    }else if(p_atm->remained_money->canPay(get_amount)){
        Session* current_session = p_atm->present_session;

    // ��� Ƚ�� ����
        if (!current_session->incrementWithdrawCount()) { // ��� Ƚ�� ���� �ʰ� Ȯ��
            if (p_atm->language_state) {
                std::cout << "��� Ƚ���� �ѵ��� �ʰ��߽��ϴ�. ������ �ٽ� �����ϼ���." << std::endl;
            } else {
                std::cout << "Withdrawal limit exceeded. Please start a new session." << std::endl;
            }
            return 3; // ��� ���� ó��
            }else{
            p_account->update_amount(p_account->get_amount()-get_amount-fee);
            p_atm->slot_money->setLanguageState(p_atm->language_state == 1);
            MoneyDict paid_money = p_atm->remained_money->pay(get_amount);
            if(p_atm->language_state){
                cout<<"���ҵ� �ݾ�: "<<get_amount<<endl;
            }else{
                cout<<"money paid: "<<get_amount<<endl;
            }
            paid_money.setLanguageState(p_atm->language_state == 1);
            paid_money.printCashes();

            

            if(p_atm->language_state){
                int remaining_balance = p_account->get_amount(); // ��� �� �ܾ� ��������
                std::string balance_message = "�ܾ�: " + std::to_string(remaining_balance) + "��";
                History* new_history = new History(TransactionType::Withdrawal,get_amount, p_card->getAccount(), p_atm->present_session,
                "balance_after_transaction",std::to_string(remaining_balance),  p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
                append_history(new_history);
            }else{
                int remaining_balance = p_account->get_amount(); // ��� �� �ܾ� ��������
                std::string balance_message = "Balance: " + std::to_string(remaining_balance) + " KRW";
                History* new_history = new History( TransactionType::Withdrawal,get_amount, p_card->getAccount(), p_atm->present_session,
                "balance_after_transaction",std::to_string(remaining_balance),  p_atm,p_card->getAccount()->get_bank());
                new_history->printHistory(p_atm,p_card->getAccount()->get_bank());
                append_history(new_history);
            }
        }
    }else{
        if(p_atm->language_state){
            cout << "����� �� �����ϴ�."<<endl;
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
        cout << "���� ��ȣ: ";
    }else{
        cout << "account num: ";
    }
    cin >>account_num;
    account = bank->find_account_by_number(account_num);
    if(account==nullptr){
        if(p_atm->language_state){
            cout << "���� ��ȣ: "<<account_num<<" �������� �ʽ��ϴ�"<<endl;
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
        cout << "�󸶸� �۱��Ͻðڽ��ϱ�?"<<endl;
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
        cout <<"���� �ܾ׺��� ���� �ݾ��Դϴ�. �۱ݺҰ����մϴ�."<<endl;
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
    Account* target_account = check_account_num(); // ���� �� ���¹�ȣ ���� Ȯ��
    if (target_account == nullptr) {
        return false;
    }
    std::string target_account_info = target_account->get_account_number() + " (" + target_account->get_user_name() + ")";


    if (p_atm->language_state) {
        cout << "���� Ȯ�� �Ϸ�. ���� ��ǥ�� �����ϼ���." << endl;
    } else {
        cout << "Account verified. Please insert cash and checks." << endl;
    }

    insert_cach(p_atm->slot_money); // �� ����
    insert_check();                 // ��ǥ ����

    int fee = 1000; // ������ ����
    while (true) {
        if (p_atm->language_state) {
            cout << "������: " << fee << "��" << endl;
        } else {
            cout << "Insert fee: " << fee << endl;
        }

        insert_cach(p_atm->input_fee); // ������ �Է¹ޱ�

        if (p_atm->input_fee->getTotalAmount() == fee) {
            int amount = p_atm->slot_money->getTotalAmount(); // ���Ե� �� �ݾ� ���
            *p_atm->remained_money = *(p_atm->slot_money) + *(p_atm->remained_money) + *(p_atm->input_fee);

            // ��� ���·� �۱�
            transfer(target_account, amount);
            p_atm->reset_slot_money(); // ���� �ʱ�ȭ

            // �ŷ� ��� ���� �� ����
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
            return true; // �۾� ����
        } else {
            p_atm->input_fee->resetCash(); // �߸��� ������ �Է� �� �ʱ�ȭ
            if (p_atm->language_state) {
                cout << "������ �����Դϴ�. �ٽ� �Է����ּ���." << endl;
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
        std::cout << "���Ǻ��� ����մϴ�" << std::endl;
    } else {
        std::cout << "Print by session" << std::endl;
    }

    // �ŷ� ��� Ž��
    for (const auto& history : history_list) {
        HistoryData data = history->getHistory();

        // ���� ID ��
        if (data.session_id == session_id) {
            found = true;
            history->printHistory(p_atm,p_card->getAccount()->get_bank()); // ���� ������ �κ�
            std::cout << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        if (p_atm->language_state) {
            std::cout << "���� ID: " << session_id << "�� ���� �ŷ��� �����ϴ�" << std::endl;
        } else {
            std::cout << "No transactions found for session ID: " << session_id << std::endl;
        }
    }
}


void ATMInterface::print_by_atm() {
    string serial_num = p_atm->serial_number;
    bool found = false;
    if(p_atm->language_state){
        cout << "ATM���� ����մϴ�"<<endl;
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
            std::cout << "ATM �Ϸù�ȣ: " << serial_num << "�� ���� �ŷ��� �����ϴ�" << std::endl;
        }else{
            std::cout << "No transactions found for atm serial number: " << serial_num << std::endl;
        }
    }
}

void ATMInterface::export_by_atm() {
    std::ofstream outFile("transaction_by_atm.txt");
    if (!outFile) {
        if (p_atm->language_state) {
            std::cerr << "������ ���� ���� �� �� ������ �߻��߽��ϴ�." << std::endl;
        } else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
        return;
    }

    bool found = false;
    std::string serial_num = p_atm->serial_number;

    // Header ���
    if (p_atm->language_state) {
        outFile << "ATM �Ϸù�ȣ: " << serial_num << "�� �ŷ� ����" << std::endl;
        outFile << "======================================" << std::endl;
    } else {
        outFile << "Transactions for ATM serial number: " << serial_num << std::endl;
        outFile << "======================================" << std::endl;
    }

    // �ŷ� ��� ���
    for (const auto& history : history_list) {
        HistoryData data = history->getHistory();

        // ATM Serial Number ���͸� ����
        if (data.atm_serial_num == serial_num) {
            found = true;
            history->printHistoryToFile(outFile, p_atm,p_card->getAccount()->get_bank()); // ATM* ���޷� ��� �ݿ�
            outFile << "------------------------------------" << std::endl;
        }
    }

    // �ŷ� ������ ���� ��� �޽��� ���
    if (!found) {
        if (p_atm->language_state) {
            outFile << "ATM �Ϸù�ȣ: " << serial_num << "�� ���� �ŷ��� �����ϴ�" << std::endl;
        } else {
            outFile << "No transactions found for ATM serial number: " << serial_num << std::endl;
        }
    }

    outFile.close();

    // ���� �޽��� ���
    if (p_atm->language_state) {
        std::cout << "���������� ��µǾ����ϴ�." << std::endl;
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
