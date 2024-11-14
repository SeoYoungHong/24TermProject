
class ATM {
public:
    Bank* primery_bank;
    string serial_number;
    bool is_single_bank_atm;
    bool is_unilingual_atm;
    int langauge_state;
    MoneyDict* remained_money = nullptr;
    MoneyDict* slot_money = nullptr;
    const int cash_maximum = 50;
    const int check_maximum = 30;
    const int input_fee = 0;
    const int withdraw_amount_max = 50000;
    const int withdraw_count_threshold = 3;
    Session* present_session = nullptr;
private:
    ATM(Bank* bank, string serial_num, bool is_single, bool is_unilingual){
        primery_bank = bank;
        serial_number = serial_num;
        is_single_bank_atm = is_single;
        is_unilingual_atm = is_unilingual;
    }
    ~ATM(){
        if(remained_money != nullptr){
            delete remained_money;
            remained_money = nullptr;
        }
        if(slot_money != nullptr){
            delete slot_money;
            slot_money = nullptr
        }
    }
    void update_slot_momey(MoneyDict* input_mony){}
    void update_remained_money(MoneyDict* input_mon)
    void update_session(Session* new_session){
        
    }
};