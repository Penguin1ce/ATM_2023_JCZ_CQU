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
        cout << "�������˺�(19λ): ";
        string account;
        cin >> account;

        // ��֤account�Ƿ�Ϊ19λ����
        if (account.size() != 19)
        {
            cout << "�˺Ÿ�ʽ����" << endl;
            system("pause");
            system("cls");
            continue;
        }
        int index = m.is_exist(account);
        if (index == -1)
        {
            cout << "���û����ȴ���Ȼ���½" << endl;
            m.add_emp(account);
            system("pause");
            system("cls");
        }
        else
        {
            // ��������
            int try_time = 0;
            bool returnToMenu = false;
            while (try_time < 3 && !returnToMenu)
            {
                string password;
                cout << "����������(6λ): ";
                cin >> password;

                if (m.check_password(index, password))
                {
                    cout << "������ȷ" << endl;
                    returnToMenu = true;
                    system("pause");
                    system("cls");
                    // ������ȷ����ʾ�˵�
                    m.showmenu();
                    char choice;
                    cout << "���ѡ��: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case '1':
                        m.show_balance(index);
                        break;
                    case '2': // ȡ��
                        m.withdraw(index);
                        break;
                    case '3': // ���
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
                        cout << "�������" << endl;
                        system("pause");
                        system("cls");
                        exit(0);
                        break;
                    }
                }
                else
                {
                    cout << "�������" << endl;
                    try_time++;
                    if (3 - try_time > 0)
                    {
                        cout << "�㻹��" << 3 - try_time << "�λ���" << endl;
                    }
                }
            }
            if (try_time == 3)
            {
                cout << "�������볢�Գ��ޣ��˳�ϵͳ" << endl;
                system("pause");
                exit(0);
            }
            while (returnToMenu)
            {
                // ��ʾ�˵�
                // system("pause");
                // system("cls");
                int index = m.is_exist(account);
                m.showmenu();
                char choice;
                cout << "���ѡ��: ";
                cin >> choice;
                switch (choice)
                {
                case '1':
                    m.show_balance(index);
                    break;
                case '2': // ȡ��
                    m.withdraw(index);
                    break;
                case '3': // ���
                    m.depositfunds(index);
                    break;
                case '4':
                    m.transfer(index); // ת��
                    break;
                case '5':
                    m.change_password(account);
                    break;
                case '0':
                    system("pause");
                    system("cls");
                    exit(0);
                default:
                    cout << "�������" << endl;
                    system("pause");
                    break;
                }
            }
        }
    }

    system("pause");
    return 0;
}