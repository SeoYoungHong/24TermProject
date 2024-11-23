#include "ATMInterface.h"
#include "Card.h"
#include "Account.h"
#include "Bank.h"
#include "ATM.h"
#include "Session.h"

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
    Bank* choiced_bank = choiceBank();
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
    bool response;
    if(is_inserted){
        cout  << "already card inserted. do you wnat to chage the card?(1: yes, 0: no)"<<endl;
        cin >> response;
        if(response){
            is_inserted=false;
            cout << "card return"<<endl;
        }else{
            cout << "card inserted"<<endl;
        }
    }
    if(!is_inserted){
        if(user_card_list.size()==0){
            cout << "you don'y have any card. Have you make the card?(1:yes, 0:no)"<<endl;
            cin >> response;

            if(response){
                Card* creaed_card = createCard();
                append_user_card(creaed_card);
                update_card(creaed_card);
            }else{
                cout<< "go to the first page";
            }
        }
        else{
            update_card(choiceCard());
            cout << "Card Inserted." << endl;
            is_inserted = true;
            if(p_card->p_is_admin){
                this->p_is_admin = true;
                cout << "inserted card is admin" << endl;
            }
            else{
                this -> p_is_admin = false; 
                cout << "inserted card is not admin" << endl;
            }  
        }
    }
    
}

void ATMInterface:: createAccount(){
    Bank* choice_bank;
    if(p_atm->is_single_bank_atm){
        choice_bank = p_atm->primery_bank;
    }else{
        choice_bank = choiceBank();
    }
    Account* p_account = new Account(choice_bank);
    append_user_account(p_account);
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
            createAccount();
        }else{
            cout<< "go to the first page";
        }
    }else{
        this->p_card = choiceCard();
        cout << "Card Inserted." << endl;
        if(p_card->p_is_admin){
            this->p_is_admin = true;
            cout << "inserted card is admin" << endl;
        }
        else{
            this -> p_is_admin = false; 
            cout << "inserted card is not admin" << endl;
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

void ATMInterface::transfer() {
    cout << "Initiating funds transfer...\n";
    cout << "Transfer completed successfully.\n";
}

void ATMInterface::changeLanguage() {
    cout << "Language changed successfully.\n";
}

void ATMInterface::performTransaction(int option) {
    switch (option) {
        case 1:
            insertMoney();
            break;
        case 2:
            withdrawCash();
            break;
        case 3:
            checkFee();
            break;
        case 4:
            transfer();
            break;
        case 5:
            changeLanguage();
            break;
        default:
            cout << "Invalid transaction option. Please try again.\n";
    }
}

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

Bank* ATMInterface::choiceBank(){
    int choice;
    cout << "choice in the bank list banks:\n";
    for (size_t i = 0; i < bank_list.size(); ++i) {
        cout << i + 1 << ". " << bank_list[i]->getBankName() << "\n";
    }
    
    cin >> choice;
    
    return bank_list[choice-1];
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