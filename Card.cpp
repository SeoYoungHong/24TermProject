#include "Card.h"
#include "Account.h"  // Account 클래스의 정의를 포함
using namespace std;
// 생성자 정의
Card::Card(Account* account, bool is_admin, const std::string& card_number, const std::string& password)
    : p_account(account), p_is_admin(is_admin), p_card_number(card_number), p_password(password) {
    
    account->append_user_card(this);
    }

// 소멸자 정의
Card::~Card() {
    // p_account에 대한 메모리 해제를 해야 하는 경우, 이곳에서 처리
    // 예: delete p_account; (p_account가 Card의 소유자라면)
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