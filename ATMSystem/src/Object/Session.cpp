#include <iostream>
#include <string>
#include <vector>


// Session 클래스 정의
class Session {
private:
    std::string session_id;                     // 세션의 고유 ID
    int withdraw_count;                         // 현재 세션에서의 출금 횟수
    std::vector<History*> transaction_history;  // 현재 세션의 거래 내역, REQ2.3: "When a session ends, the summary of all transactions performed in a session must be displayed." 반영한 것!

public:
    // 생성자
    Session(const std::string& id)
        : session_id(id), withdraw_count(0) {}

    // 소멸자
    ~Session() {
        // 동적으로 할당된 History 객체 삭제
        for (auto history : transaction_history) {
            delete history;
        }
    }

    // 출금 횟수 증가
    void incrementWithdrawCount() {
        ++withdraw_count;
    }

    // 출금 횟수 반환
    int getWithdrawCount() const {
        return withdraw_count;
    }

    // 세션 ID 반환
    std::string getSessionID() const {
        return session_id;
    }

    // 세션 ID 수정 (Update 기능 추가), Session id 를 변경해야 할 상황에 대비(필요 없으면 추후에 삭제)
    void setSessionID(const std::string& id) {
        session_id = id;
    }

    // 거래 내역 추가
    void addTransaction(History* history) {
        transaction_history.push_back(history);
    }

    // 거래 내역 반환
    const std::vector<History*>& getTransactionHistory() const {
        return transaction_history;
    }

    // 거래 내역을 출력하는 메서드 추가
    void printTransactionSummary() const {
        if (transaction_history.empty()) {
            std::cout << "이번 세션 동안 수행된 거래가 없습니다.\n";
            return;
        }

        std::cout << "세션 ID: " << session_id << "의 거래 요약\n";
        std::cout << "----------------------------------------\n";
        for (const auto& history : transaction_history) {
            std::cout << "거래 ID: " << history->getTransactionID() << "\n";
            std::cout << "거래 유형: " << history->getTransactionType() << "\n";
            std::cout << "거래 금액: " << history->getAmount() << "\n";
            if (history->getAccount() != nullptr) {
                // Account 클래스에 getAccountNumber() 메서드가 있다고 가정
                std::cout << "계좌 번호: " << history->getAccount()->getAccountNumber() << "\n";
            }
            std::cout << "추가 정보: " << history->getAdditionalInformation() << "\n";
            std::cout << "----------------------------------------\n";
        }
    }

    void removeTransaction(const std::string& transaction_id) {
        // transaction_history 벡터를 처음부터 끝까지 순회합니다.
        for (auto it = transaction_history.begin(); it != transaction_history.end(); ++it) {
            // 현재 iterator가 가리키는 History 객체의 거래 ID를 가져옵니다.
            if ((*it)->getTransactionID() == transaction_id) {
                // 해당 거래 ID가 일치하면, 메모리에서 객체를 해제합니다.
                delete* it;
                // 벡터에서 해당 iterator 위치의 요소를 제거합니다.
                transaction_history.erase(it);
                // 거래를 찾았으므로 반복문을 종료합니다.
                break;
            }
        }
    }
};

// Account 클래스는 실제 구현이 필요하지만, 여기서는 전방 선언만 사용
class Account {
        // Account 클래스의 구현은 다른 부분에서 진행됩니다.
};