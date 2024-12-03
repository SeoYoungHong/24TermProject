#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <fstream>
#include <iostream>
#include "Account.h"
#include "ATM.h" 
#include "Bank.h" // Bank Ŭ���� ���� �ʿ�
#include "History.h"
#include "Session.h"  // Session Ŭ������ ������ �ʿ��մϴ�

class Session;

struct HistoryData {
    std::string transaction_id;           
    std::string transaction_type;         
    int amount;                           
    std::string account_num;                     
    std::string session_id;  
    std::string atm_serial_num;                   
    std::string additional_information;   
};
enum class TransactionType {
    Deposit,
    Withdrawal,
    Transfer
};
class History {
private:
    static int history_counter;
    std::string transaction_id;           
    TransactionType transaction_type;          
    int amount;                           
    std::string account_num;                     
    std::string session_id; 
    std::string atm_serial_num;                    
    std::string additional_information;
    std::string additional_information_key; 
    std::string additional_information_value;
    Bank* bank; // Bank ������ �߰�

public:
    // ������ ����: Bank* bank_ptr�� �߰��Ͽ� �ʱ�ȭ
    History(TransactionType trans_type, int amt,
            Account* acc, Session* sess, const std::string info_key,const std::string info_value, ATM* atm, Bank* bank);
    

    ~History();

    HistoryData getHistory() const;

    void setTransactionType(TransactionType type);
    void setAmount(int amt);
    void setAdditionalInformation(const std::string& info);

    std::string getTransactionType(bool isKorean) const;
    std::string getAdditionalInformation(bool isKorean) const;
    void printHistory(const ATM* atm, Bank* bank) const; // ������ �޼���
    void printHistoryToFile(std::ofstream& outFile, const ATM* atm, Bank* bank) const; // ������ �޼���

    std::string getBankName() const; // Bank �̸� ��ȯ �޼���
};

#endif
