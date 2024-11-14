class Card{
public:
    Account* p_account;
    bool p_is_admin;
    string p_card_number;
    string p_password;
private:
    Card(Account* account, bool is_admin, string card_number, string password){
        p_account = account;
        p_is_admin = is_admin;
        p_card_number = card_number;
        p_password = password;
    }
    ~Card(){
        delete p_card_number;
        delete p_password;
    }
};