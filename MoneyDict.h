#ifndef MONEYDICT_H
#define MONEYDICT_H

#include <iostream>
#include <map>
#include <vector>

class MoneyDict {
private:
    std::map<int, int> cashes; 
    std::vector<int> checks;
    int check_count;
    int cash_count;
    int total_amount;
    int cash_amount;
    bool isKorean;
    

public:
    MoneyDict();
    void setLanguageState(bool isKorean);
    void resetCash();
    void addCash(int denomination, int count);
    void removeCash(int denomination, int count);
    int getCashCount() const;
    int getCashAmount() const;
    const std::map<int, int>& getCashes() const;
    void addCheck(int amount);
    void removeCheck(int index);
    int getCheckCount() const;
    const std::vector<int>& getChecks() const;
    int getTotalAmount() const;
    void updateTotals();
    void printChecks() const;
    void printCashes() const;
    MoneyDict operator+(const MoneyDict& other) const;
    bool canPay(int amount);
    MoneyDict pay(int amount);
};

#endif // MONEYDICT_H
