#pragma once // 防止头文件重复包含
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
    string account;      // 账号 19位数字
    string name;         // 姓名
    string id_num;       // 身份证号 18位数字
    string password;     // 密码 6位数字
    int balance = 10000; // 余额 初始为10000元

    int today_out_balance = 20000;
    bool checkans = false;
};