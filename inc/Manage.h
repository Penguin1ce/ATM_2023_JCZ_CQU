#pragma once // 防止头文件重复包含
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
    void showmenu();   // 展示菜单
    void exitsystem(); // 退出
    int is_exist(string account);
    // remain worker's number

    int get_number();
    void init_emp();
    int m_empnum;
    User **m_empArray;
    bool m_fileisempty = true;
    User **getEmpArray(); // 获取储存在内存中的数据
    // string safe(string account);
    void add_emp(string account); // 添加新的用户
    void save();
    int temp_account_dex = -1;
    int try_times = 0;
    void show_balance(int index);
    string get_time();

    void change_password(string account);
    bool check_password(int index, string password);
    void withdraw(int index);     // 取钱
    void depositfunds(int index); // 存钱
    void transfer(int index);     // 转账
    string time_now;
    string time_old;
};
