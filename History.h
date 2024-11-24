#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <fstream>
#include <iostream>
#include "Account.h"
#include "ATM.h" 

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


class History {
private:
    static int history_counter;
    std::string transaction_id;           
    std::string transaction_type;         
    int amount;                          
    std::string account_num;                     
    std::string session_id; 
    std::string atm_serial_num;                    
    std::string additional_information; 

public:

    History(std::string trans_type, int amt,
    Account* acc, Session* sess, const std::string info, ATM* atm);

    ~History();

    HistoryData getHistory() const;

    void setTransactionType(const std::string& type);
    void setAmount(int amt);
    void setAdditionalInformation(const std::string& info);
    void printHistory();
    void printHistoryToFile(std::ofstream& outFile) ;
};

#endif 
