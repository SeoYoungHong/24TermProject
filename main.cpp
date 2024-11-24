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

int main() {
    char choice;
    cout << "process start"<<endl;
    ATMInterface* atm_interface = new ATMInterface();
    cout << "ATM System Initializing...\n";

    while (true) {
        cout << "1. Card/Account Setup || 2. Insert Card || q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1':
                card_account_setup_page(atm_interface);
                break;
            case '2':
                atm_interface->insertCard();
                if(atm_interface->is_inserted){
                    if(atm_interface->p_is_admin){
                    admin_page(atm_interface);
                    }else{
                        tranjection_select_page(atm_interface);
                    }
                }
                
                break;
            case '4':
                delete atm_interface;  // 메모리 해제
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }    
    }
    return 0;
}
int card_account_setup_page(ATMInterface* atm_interface){
    atm_interface->createCard();
    return 0;
}

int tranjection_select_page(ATMInterface* atm_interface){
    char choice;
    cout << "1. insert money ||2. withdraw money||3. fransfer money || q. Exit || l. change language "<<endl;
    cout << "Enter your choice: ";
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
        case '4':
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
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
        cout << "1. insert cach ||2. insert check ||3. deposit || q. Exit || l. change language "<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case '1':
                atm_interface->insert_cach();
                break;
            case '2':
                atm_interface->insert_check();
                break;
            case '3':
                atm_interface->atm_to_account();
                return 0;
            case 'q':
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}



//account -> slot
int tranjection_withdraw_page(ATMInterface* atm_interface){
    atm_interface->withdraw();
    return 0;
}

//1. slot -> account
//2. account -> account
int tranjection_transfer_page(ATMInterface* atm_interface){
    char choice;
    cout << "1. slot to account ||2. account to account || q. Exit || l. change language "<<endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
        case '1':
            atm_interface->slot_to_account();
            break;
        case '2':
            atm_interface->account_to_account();

            break;
        case '3':
            return 0;
        case 'q':
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    return 0;
}

int go_and_stop_page(ATMInterface* atm_interface){
    char choice;
    cout << "1. more transaction || 2. print session history|| q. Exit || l. change language "<<endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case '1':
            tranjection_select_page(atm_interface);
            break;
        case '2':
            print_page(atm_interface);
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            go_and_stop_page(atm_interface);
            break;
    }
    return 0;
}

int print_page(ATMInterface* atm_interface){
    char choice;
    Session* presentsession = atm_interface->p_atm->present_session;
    atm_interface->print_by_session(presentsession);
    cout << "1. retry || q. Exit || l. change language "<<endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case '1':
            break;
        case '2':

            break;
        case '3':
            break;
        case '4':
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    return 0;
}

int admin_page(ATMInterface* atm_interface){
    char choice;
    cout << "1. show all of the tranjections || q. Exit || l. change language "<<endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
    return 0;
}