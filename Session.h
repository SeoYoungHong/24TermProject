#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <stdexcept> // ���� ó���� ���� �߰�

class Session {
private:
    static int session_counter;
    std::string session_id;                     // ������ ���� ID
    int tranjection_count;                         // ���� ���ǿ����� ��� Ƚ��
    const int tranjection_count_threshold = 3;     // ��� Ƚ�� �ѵ�

public:
    // ������
    
    Session();

    // �Ҹ���
    ~Session();

    std::string getSessionID() const;

    // ��� Ƚ�� ����
    bool incrementWithdrawCount();

    // ��� Ƚ�� ��ȯ
    int getWithdrawCount() const;
    

    // ���� ID ��ȯ
    
};

#endif // SESSION_H
