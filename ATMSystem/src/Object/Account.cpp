class Account{
public:
    string p_account_number;
    Bank* p_bank;
    int amount;
private:
    Account(string account_number, Bank* bank){
        p_bank = bank;
        p_account_number = account_number;
        amount =0;
        count << "[Construct] create aacount, account_number: " <<account_number<<endl;
    }
    ~Account(){
        cout << "[Destruct] destruct account"
    }
    void unpdate_amount(int changed_amount){
        amount = changed_amount;
    }
};