#include "Card.h"
#include "Account.h"  // Account Ŭ������ ���Ǹ� ����
using namespace std;
// ������ ����
Card::Card(Account* account, bool is_admin, const std::string& card_number, const std::string& password)
    : p_account(account), p_is_admin(is_admin), p_card_number(card_number), p_password(password) {
    
    account->append_user_card(this);
    }

// �Ҹ��� ����
Card::~Card() {
    // p_account�� ���� �޸� ������ �ؾ� �ϴ� ���, �̰����� ó��
    // ��: delete p_account; (p_account�� Card�� �����ڶ��)
}

Account* Card::getAccount(){
    return p_account;
}
string Card::get_card_num(){
    return p_card_number;
}

bool Card::match_credentials(string card_num, string input_pw){
    return p_card_number == card_num && p_password == input_pw;
}