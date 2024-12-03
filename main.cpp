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
void displaySnapshot(ATMInterface* atm_interface); // ���� �߰�
void displayAccountSnapshot(ATMInterface* atm_interface); // ���� �߰�


std::vector<std::string> global_card_numbers; // ��� ī�� ��ȣ�� �����ϴ� ���� ����Ʈ �߰�

int main() {
    ATMInterface* atm_interface = new ATMInterface();

    while (true) {
        char choice;
        cout << "���α׷� ����� �Է��ϼ��� (1: �ʱ� ����, /: ������, q: ����): ";
        cin >> choice;

        if (choice == 'q') {
            delete atm_interface;  // �޸� ����
            break;
        } else if (choice == '1') {
            seup_page(atm_interface);
        } 
        else if (choice == '/') {
        // ATM �� ���� ������ ���
        displaySnapshot(atm_interface);
        displayAccountSnapshot(atm_interface);
        }
        else {
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���." << endl;
        }
    }

    return 0;
}

void displaySnapshot(ATMInterface* atm_interface) {
    // �ѱ��� ���
    std::cout << "===== ATM ������ =====" << std::endl;

    const auto& atm_list = atm_interface->getATMList();
    if (atm_list.empty()) {
        std::cout << "���� ��ϵ� ATM�� �����ϴ�." << std::endl;
        return;
    }

    for (const auto& atm : atm_list) {
        std::cout << "ATM [�ø��� ��ȣ: " << atm->serial_number << "] ";
        atm->remained_money->setLanguageState(true); // �׻� �ѱ��� ����
        atm->remained_money->printCashes();
    }
    std::cout << std::endl;
}

void displayAccountSnapshot(ATMInterface* atm_interface) {
    // �ѱ��� ���
    std::cout << "===== ���� ������ =====" << std::endl;

    const auto& accounts = atm_interface->getAccountList();
    if (accounts.empty()) {
        std::cout << "���� ��ϵ� ���°� �����ϴ�." << std::endl;
        return;
    }

    for (const auto& account : accounts) {
        Bank* bank = account->get_bank();
        std::cout << "���� [�����: " << account->get_user_name()
                  << ", ����: " << bank->getBankName() << ", ���¹�ȣ: " << account->get_account_number()
                  << "] �ܾ�: " << account->get_amount() << "��" << std::endl;
    }
    std::cout << std::endl;
}


void mainMenuHandler(ATMInterface* atm_interface) {
    char choice;
    if (atm_interface->p_atm == nullptr) {
        choice = '1';
    } else {
        if (atm_interface->p_atm->language_state) {
            cout << " 1. ī����� || q. ������ || l. ��� �ٲٱ�" << endl;
            cout << "�Է��ϼ���: ";
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
                mainMenuHandler(atm_interface);
            } else {
                cout << "Invalid choice. Please try again.\n";
                mainMenuHandler(atm_interface);
            }
    }
}


void select_atm(ATMInterface* atm_interface) {
    const auto& atm_list = atm_interface->getATMList();  // Getter�� atm_list ����
    if (atm_list.empty()) {
        cout << "������ ATM�� �����ϴ�. ���� ATM�� �߰��ϼ���." << endl;
        return;
    }

    cout << "��� ������ ATM ����Ʈ:" << endl;
    for (size_t i = 0; i < atm_list.size(); ++i) {
        cout << i + 1 << ". Serial Number: " << atm_list[i]->serial_number << endl;
    }

    cout << "������ ATM ��ȣ�� �Է��ϼ���: ";
    size_t choice;
    cin >> choice;

    if (choice >= 1 && choice <= atm_list.size()) {
        atm_interface->p_atm = atm_list[choice - 1];
        cout << "ATM(Serial Number: " << atm_interface->p_atm->serial_number << ")�� ���õǾ����ϴ�." << endl;
    } else {
        cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
    }
}

int seup_page(ATMInterface* atm_interface) {
    char choice;
    while (true) {
        cout << "1. ���� ���� || 2. ATM ���� || 3. ����, ī�� ���� || 4. ATM ���� || q. ������" << endl;
        cout << "�Է��ϼ��� : ";

        int result = 0;
        cin >> choice;

        switch (choice) {
            case '1':
                result = bank_setting(atm_interface);
                if (result == 0) {
                    cout << "���� �߰�/���ÿ� �����߽��ϴ�" << endl;
                }
                break;
            case '2':
                result = atm_setting(atm_interface);
                if (result == 0) {
                    cout << "ATM �߰�/���ÿ� �����߽��ϴ�" << endl;
                }
                break;
            case '3':
                result = card_account_setup_page(atm_interface);
                if (result == 0) {
                    cout << "ī�� �߰�/���ÿ� �����߽��ϴ�." << endl;
                }
                
                break;
            case '4':
                select_atm(atm_interface);
                if (atm_interface->p_atm != nullptr) {
                    mainMenuHandler(atm_interface); // ���õ� ATM���� �۾� ����
                }
                break;
            case '/':
                displaySnapshot(atm_interface);
                displayAccountSnapshot(atm_interface);
            break;
            case 'q':
                return 0; // �ʱ�ȭ ������ ����
            
            default:
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���." << endl;
        }
    }
}

int bank_setting(ATMInterface* atm_interface) {
    cout << "�߰��� ������� �Է����ּ���: ";
    string bank_name;

    // std::getline()���� ���� ���� �Է� �ޱ�
    cin.ignore(); // ���� �Է� ������ �ܿ� �����͸� ����
    std::getline(cin, bank_name);

    int result = atm_interface->append_bank(bank_name);
    if (result == 0) {
    } else {
        cout << "���� '" << bank_name << "' �߰�/���ÿ� �����߽��ϴ�" << endl;
    }
    return result;
}

int atm_setting(ATMInterface* atm_interface) {
    ATM* atm = atm_interface->append_ATM();
    if (atm != nullptr) {
        // ���� ATM�� ������ �ڵ����� ����
        if (atm_interface->p_atm == nullptr) {
            atm_interface->p_atm = atm;
        } else {
            // ���� ATM�� ���� ���, �׻� �� ATM���� ��ü
            atm_interface->p_atm = atm;
        }

        // ATM�� �ʱ� ĳ�� ����
        atm_interface->insert_cache(atm->remained_money, true);
        return 1;
    } else {
        return 0; // ATM ���� ���� ��
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
        cout << "1. �Ա� || 2. ��� || 3. �۱� || q. ������ || l. ��� �ٲٱ� "<<endl;
        cout << "�Է��ϼ���: ";
        
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
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
            cout << "1. ���� �ֱ� || 2. ��ǥ �ֱ� || 3. �Ա� || q. ������ || l. ��� �ٲٱ� "<<endl;
            cout << "�Է��ϼ���: ";
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
                    cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
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


    // ��� ���� ����
     int result = atm_interface->withdraw();
        if (result == 3) {
        // ���� ���� �� ���� �޴��� ����
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
        cout << "1. ���Կ��� ���·� ||2. ���¿��� ���·� || q. ������ || l. ��� �ٲٱ� "<<endl;
        cout << "�Է��ϼ���: ";
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
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
        cout << "1. �� �ŷ��ϱ� || 2. ���� ��� ���(������) || l. ��� �ٲٱ� "<<endl;
        cout << "�Է��ϼ���: ";
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
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
        cout << "1. ��õ� || q. ������ || l. ��� �ٲٱ� "<<endl;
        cout << "�Է��ϼ���: ";
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
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
        cout << "1. ��� �ŷ� ���� �� �ŷ� �������� || q. ������ "<<endl;
        cout << "�Է��ϼ���: ";
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
                cout << "�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n";
                admin_page(atm_interface);
            }else{
                cout << "Invalid choice. Please try again.\n";
                admin_page(atm_interface);
            }
    }
    return 0;
}