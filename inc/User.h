#pragma once // ��ֹͷ�ļ��ظ�����
#include <iostream>
using namespace std;
class User
{
private:
public:
    User();
    ~User();
    User(string account, string name, string id_num, string password, int balance, int today_out_balance);
    User get_inform();
    string account;      // �˺� 19λ����
    string name;         // ����
    string id_num;       // ���֤�� 18λ����
    string password;     // ���� 6λ����
    int balance = 10000; // ��� ��ʼΪ10000Ԫ

    int today_out_balance = 20000;
    bool checkans = false;
};