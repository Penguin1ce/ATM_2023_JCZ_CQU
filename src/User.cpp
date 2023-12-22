#include "../inc/User.h"
User::User(string account, string name, string id_num, string password, int balance, int today_out_balance)
{
    this->account = account;
    this->name = name;
    this->id_num = id_num;
    this->password = password;
    this->balance = balance;
    this->today_out_balance = today_out_balance;
}