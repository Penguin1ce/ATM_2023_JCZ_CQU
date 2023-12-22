#pragma once // ��ֹͷ�ļ��ظ�����
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "User.h"
#define FILENAME "empfile.txt"
using namespace std;
class Manage
{
public:
    Manage();
    ~Manage();
    void showmenu();   // չʾ�˵�
    void exitsystem(); // �˳�
    int is_exist(string account);
    // remain worker's number

    int get_number();
    void init_emp();
    int m_empnum;
    User **m_empArray;
    bool m_fileisempty = true;
    User **getEmpArray(); // ��ȡ�������ڴ��е�����
    // string safe(string account);
    void add_emp(string account); // ����µ��û�
    void save();
    int temp_account_dex = -1;
    int try_times = 0;
    void show_balance(int index);
    string get_time();

    void change_password(string account);
    bool check_password(int index, string password);
    void withdraw(int index);     // ȡǮ
    void depositfunds(int index); // ��Ǯ
    void transfer(int index);     // ת��
    string time_now;
    string time_old;
};
