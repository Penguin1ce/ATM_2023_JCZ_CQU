#include <iostream>
#include "../inc/Manage.h"
#include "../inc/User.h"
#define FILENAME "empfile.txt"
using namespace std;
int main()
{
    Manage m;
    cout << "Welcome to the ATM system" << endl;
    while (true)
    {
        cout << "请输入账号(19位): ";
        string account;
        cin >> account;

        // 验证account是否为19位数字
        if (account.size() != 19)
        {
            cout << "账号格式出错" << endl;
            system("pause");
            system("cls");
            continue;
        }
        int index = m.is_exist(account);
        if (index == -1)
        {
            cout << "新用户请先创建然后登陆" << endl;
            m.add_emp(account);
            system("pause");
            system("cls");
        }
        else
        {
            // 输入密码
            int try_time = 0;
            bool returnToMenu = false;
            while (try_time < 3 && !returnToMenu)
            {
                string password;
                cout << "请输入密码(6位): ";
                cin >> password;

                if (m.check_password(index, password))
                {
                    cout << "密码正确" << endl;
                    returnToMenu = true;
                    system("pause");
                    system("cls");
                    // 密码正确后，显示菜单
                    m.showmenu();
                    char choice;
                    cout << "你的选择: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case '1':
                        m.show_balance(index);
                        break;
                    case '2': // 取款
                        m.withdraw(index);
                        break;
                    case '3': // 存款
                        m.depositfunds(index);
                        break;
                    case '4':
                        m.transfer(index);
                        break;
                    case '5':
                        m.change_password(account);
                        break;
                    case '0':
                        system("pause");
                        system("cls");
                        exit(0);
                    default:
                        cout << "输入错误" << endl;
                        system("pause");
                        system("cls");
                        exit(0);
                        break;
                    }
                }
                else
                {
                    cout << "密码错误" << endl;
                    try_time++;
                    if (3 - try_time > 0)
                    {
                        cout << "你还有" << 3 - try_time << "次机会" << endl;
                    }
                }
            }
            if (try_time == 3)
            {
                cout << "密码输入尝试超限，退出系统" << endl;
                system("pause");
                exit(0);
            }
            while (returnToMenu)
            {
                // 显示菜单
                // system("pause");
                // system("cls");
                int index = m.is_exist(account);
                m.showmenu();
                char choice;
                cout << "你的选择: ";
                cin >> choice;
                switch (choice)
                {
                case '1':
                    m.show_balance(index);
                    break;
                case '2': // 取款
                    m.withdraw(index);
                    break;
                case '3': // 存款
                    m.depositfunds(index);
                    break;
                case '4':
                    m.transfer(index); // 转账
                    break;
                case '5':
                    m.change_password(account);
                    break;
                case '0':
                    system("pause");
                    system("cls");
                    exit(0);
                default:
                    cout << "输入错误" << endl;
                    system("pause");
                    break;
                }
            }
        }
    }

    system("pause");
    return 0;
}