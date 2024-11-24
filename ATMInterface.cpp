#include "ATMInterface.h"
#include "Card.h"
#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Session.h"
#include "History.h"
#include <fstream>
using namespace std;

// Constructor implementation
ATMInterface::ATMInterface() {
    // List of bank names
    cout << "choice bank name"<<endl;
    vector<string> bank_name_list = {"농협", "수협", "국민은행", "우리은행", "하나은행"};

    // Dynamically create Bank objects and store them in bank_list
    for (const auto& bank_name : bank_name_list) {
        bank_list.push_back(new Bank(bank_name));
    }
    p_atm = createATM();

    cout << "[Construct] ATM interface\n";
}

ATM* ATMInterface::createATM(){
    Bank* choiced_bank = choiceBank(false, nullptr);
    bool is_single;
    bool is_unilingual;
    cout << "Single ATM: (1: single, 0: multi)" << endl;
    cin >> is_single;
    cout << "Unilingual: (1: uni, 0: bi)" << endl;
    cin >> is_unilingual;
    p_atm = new ATM(choiced_bank, is_single, is_unilingual);
    return p_atm;
}

void ATMInterface::insertCard() {
    string card_num;
    string card_pw;
    Card* card = nullptr;
    bool is_admin=false;
    p_is_admin=false;
    is_inserted=false;
    cout << "is admin? (1: yes, 0: no)";
    cin >>is_admin;
    if(is_admin){
        cout << "card num: ";
        cin >>card_num;
        cout << "card pw: ";
        cin >>card_pw;
        if(card_num=="0" && card_pw=="0"){
            p_is_admin=true;
            is_inserted=true;
        }else{
            cout<<"fail to admin login"<<endl;
        }
        
    }else{
        Bank* choiced_bank =nullptr;
        if(p_atm->is_single_bank_atm){
            choiced_bank = p_atm->primery_bank;
        }else{

        }
        choiced_bank = choiceBank(p_atm->is_single_bank_atm, p_atm->primery_bank);
        int retry_count =0;
        cout << "card num: ";
        cin >>card_num;
        card = choiced_bank->find_card_by_number(card_num);
        if(card==nullptr){
            cout << "card num: "<<card_num<<"not exist"<<endl;
        }else{
            while(retry_count<3){
            
                cout << "card pw: ";
                cin >>card_pw;
                if(card->p_password!=card_pw){
                    retry_count++;
                    cout <<"pw fail retry"<<retry_count<<"/3"<<endl;
                    continue;
                }else{
                    update_card(card);
                    
                    is_inserted = true;
                    p_is_admin =  card->p_is_admin;
                    cout <<"card insert and session start"<<endl;
                    break;
                }
            }
        }
    }
}

Account* ATMInterface:: createAccount(){
    Bank* choice_bank;
    choice_bank = choiceBank(p_atm->is_single_bank_atm, p_atm->primery_bank);
    Account* p_account = new Account(choice_bank);
    append_user_account(p_account);
    return p_account;
}

Card* ATMInterface::createCard(){
    // Constructor with user input
    
    string account_number;
    string p_password;
    string p_card_number;
    int choice;
    bool card_is_admin = false;
    bool response;
    Account* p_account = nullptr;
    Bank* choice_bank = nullptr;
    if(user_account_list.size()==0){
        cout << "you don'y have any account. Have you make the account?(1:yes, 0:no)"<<endl;
        cin >> response;
        if(response){
            p_account = createAccount();
        }else{
            cout<< "go to the first page";
        }
    }else{
        cout << "you have account. Have you make the account?(1:yes, 0:no)"<<endl;
        cin >> response;
        if(response){
            p_account = createAccount();
        }else{
            p_account = choiceAccount();
        }
    }
    cout << "Enter card number: ";
    cin >> p_card_number;
    cout << "Enter card password: ";
    cin >> p_password;
    Card* new_card = new Card(p_account, card_is_admin, p_card_number, p_password);

    return new_card;
}

void ATMInterface::reset() {
    cout << "ATM Reset Successful.\n";
}

void ATMInterface::printBySession() {
    cout << "Printing session history...\n";
}

void ATMInterface::printByATM() {
    cout << "Printing ATM transaction history...\n";
}

void ATMInterface::insertMoney() {
    cout << "Insert cash into the ATM...\n";
    depositCash();
}

void ATMInterface::checkFee() {
    cout << "Checking fee details...\n";
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
    cout << "Enter amount to deposit: ";
    cin >> amount;
    cout << "Amount $" << amount << " deposited successfully.\n";
}

void ATMInterface::withdrawCash() {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    cout << "Amount $" << amount << " withdrawn successfully.\n";
}

void ATMInterface::checkFeeDetails() {
    cout << "Service fee: $2.50.\n";
}

Bank* ATMInterface::choiceBank(bool is_single, Bank* bank){

    if(is_single && bank != nullptr){
        cout << "this atm is single atm you can choice only "<<bank->getBankName()<<endl;
        return bank;
    }else{
        int choice;
        cout << "choice in the bank list banks:\n";
        for (size_t i = 0; i < bank_list.size(); ++i) {
            cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
        }
        
        cin >> choice;
        
        return bank_list[choice-1];
    }
    
}

Card* ATMInterface::choiceCard(){
    int choice;
    cout << "choice in the card list :\n";
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
    cout << "choice in the account list :\n";
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
    cout << "user account appended, card num: "<<endl;
    return user_card_list.push_back(card);
}


void ATMInterface::append_user_account(Account* account){
    cout << "user account appended, acount num: "<<endl;
    return user_account_list.push_back(account);
}

void ATMInterface::update_card(Card* card){
    p_card = card;
    is_inserted = true;
    p_atm->update_session(new Session());

}

Card* ATMInterface::matchcard(Bank* bank, string card_numm, string pw){
    return bank->find_card(card_numm, pw);
}

void ATMInterface::insert_cach(MoneyDict* moneydict) {
    int count_1000 = 0, count_5000 = 0, count_10000 = 0, count_50000 = 0;
    cout << "Insert 1000 won bills: ";
    cin >> count_1000;
    cout << "Insert 5000 won bills: ";
    cin >> count_5000;
    cout << "Insert 10000 won bills: ";
    cin >> count_10000;
    cout << "Insert 50000 won bills: ";
    cin >> count_50000;
    if (count_1000 < 0 || count_5000 < 0 || count_10000 < 0 || count_50000 < 0) {
        cout << "Error: Bill counts cannot be negative." << endl;
        return;
    }
    moneydict->addCash(1000, count_1000);
    moneydict->addCash(5000, count_5000);
    moneydict->addCash(10000, count_10000);
    moneydict->addCash(50000, count_50000);
}



void ATMInterface::insert_check(){
    while (true){
        int amount;
        cout<<"how much do you insert money> (9 is break)"<<endl;
        cout<<"writ your check amount: ";
        cin>>amount;
        if(amount ==9){
            break;
        }
        p_atm->slot_money->addCheck(amount);
    }
    
}

void ATMInterface::atm_to_account(){
    int fee=(p_atm->primery_bank == p_card->getAccount()->get_bank()?1000:2000);
    cout<<"insert fee: "<<fee<<endl;
    insert_cach(p_atm->input_fee);
    if(p_atm->input_fee->getTotalAmount()==fee){
        int solot_amount =  p_atm ->slot_money->getTotalAmount();
        int account_amount = p_card->getAccount()->get_amount();
        cout<<"solot amount: "<<solot_amount<< "account amount: " <<account_amount<<endl;
        p_card->getAccount()->update_amount(solot_amount+account_amount);
        *p_atm->remained_money = *(p_atm->slot_money)+*(p_atm->remained_money)+(*p_atm->input_fee);
        p_atm->reset_slot_money(); 
        History* new_history = new History("deposit",solot_amount, p_card->getAccount(), p_atm->present_session,
        "입금후 잔액",  p_atm);
        new_history->printHistory();
        append_history(new_history);
    }else{
        cout << "fee err"<<endl;
    }
    
}

int ATMInterface::withdraw(){
    int fee=(p_atm->primery_bank == p_card->getAccount()->get_bank()?1000:2000);
    Account* p_account = p_card->getAccount();
    int get_amount;
    cout <<"your account amount: "<<p_account->get_amount() << "fee is: "<<fee<<endl;
    cout << "how much do you get the amount?";
    cin>>get_amount;
    if(get_amount+fee>p_account->get_amount()){
        cout<<get_amount<<"don't have that much money."<<endl;
        cout<<"you have only"<<p_account->get_amount()<<endl;
    }else if(p_atm->remained_money->canPay(get_amount)){
        p_account->update_amount(p_account->get_amount()-get_amount-fee);
        MoneyDict paid_money = p_atm->remained_money->pay(get_amount);
        cout<<"money paid: "<<get_amount<<endl;
        paid_money.printCashes();
        History* new_history = new History("deposit",get_amount, p_card->getAccount(), p_atm->present_session,
        "입금후 잔액",  p_atm);
        new_history->printHistory();
        append_history(new_history);
    }else{
        cout << "we don't have money"<<endl;
    }

}

Account* ATMInterface::check_account_num(){
    string account_num;
    Account* account = nullptr;
    Bank* bank = choiceBank(p_atm->is_single_bank_atm, p_atm->primery_bank);
    int retry_count =0;
    cout << "account num: ";
    cin >>account_num;
    account = bank->find_account_by_number(account_num);
    if(account==nullptr){
        cout << "account num: "<<account_num<<"not exist"<<endl;
    }
    return account;
}

bool ATMInterface::account_to_account(){
    
    Account* target_account = check_account_num();
    int amount;
    if(target_account==nullptr){
        return false;
    }
    cout << "how much to transfer?"<<endl;
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
        return false;
    }else{
        p_account -> update_amount(p_account->get_amount()-amount-fee);
        transfer(target_account, amount);
        return true;
    }
    
}

bool ATMInterface::slot_to_account(){
    insert_cach(p_atm->slot_money);
    insert_check();
    int fee = 1000;
    cout<<"insert fee: "<<fee<<endl;
    insert_cach(p_atm->input_fee);
    if(p_atm->input_fee->getTotalAmount()==fee){
        Account* target_account = check_account_num();
        int amount = p_atm->slot_money->getTotalAmount();
        if(target_account==nullptr){
            return false;
        }
        *p_atm->remained_money = *(p_atm->slot_money)+*(p_atm->remained_money)+*(p_atm->input_fee);
        transfer(target_account, amount);
        p_atm->reset_slot_money();
        return true;
    }else{
        cout <<"fee err"<<endl;
    }
}

void ATMInterface::append_history(History* new_history){
    history_list.push_back(new_history);
}

void ATMInterface::print_by_session(Session* session) {
    string session_id = session->getSessionID();
    bool found = false;
    cout << "print by session"<<endl;
    // Iterate over the history list
    for (const auto& history : history_list) {
        // Assuming History has a `getHistory` method that gives us a HistoryData object
        HistoryData data = history->getHistory();

        // Compare session_id
        if (data.session_id == session_id) {
            found = true;
            history->printHistory();
            std::cout << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        std::cout << "No transactions found for session ID: " << session_id << std::endl;
    }
}

void ATMInterface::print_by_atm() {
    string serial_num = p_atm->serial_number;
    bool found = false;
    cout << "print by atm"<<endl;
    // Iterate over the history list
    for (const auto& history : history_list) {
        // Assuming History has a `getHistory` method that gives us a HistoryData object
        HistoryData data = history->getHistory();

        // Compare session_id
        if (data.atm_serial_num == serial_num) {
            found = true;
            history->printHistory();
            std::cout << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        std::cout << "No transactions found for atm serial number: " << serial_num << std::endl;
    }
}

void ATMInterface::export_by_atm() {
    string serial_num = p_atm->serial_number;
    bool found = false;
    
    // 파일 출력 스트림 객체 생성
    std::ofstream outFile("transaction_by_atm.txt");

    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    outFile << "Transactions for ATM serial number: " << serial_num << std::endl;
    outFile << "======================================" << std::endl;

    // Iterate over the history list
    for (const auto& history : history_list) {
        // Assuming History has a `getHistory` method that gives us a HistoryData object
        HistoryData data = history->getHistory();

        // Compare session_id (atm_serial_num) with the given ATM serial number
        if (data.atm_serial_num == serial_num) {
            found = true;
            // Write the history to file (assuming `printHistory` writes to console, we'll call the logic)
            history->printHistoryToFile(outFile);  // Adjust the method to print to file
            outFile << "------------------------------------" << std::endl;
        }
    }

    if (!found) {
        outFile << "No transactions found for ATM serial number: " << serial_num << std::endl;
    }

    // Close the file after writing
    outFile.close();
}