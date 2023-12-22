#include "../inc/Manage.h"
#include "../inc/User.h"
using namespace std;
string temp = "";
Manage::Manage()
{
    time_now = get_time();
    // cout<<"Manage()"<<endl;
    ifstream ifs;
    ifs.open(FILENAME, ios::in); // read
    if (!ifs.is_open())
    {
        cout << "File is not exit" << endl;
        this->m_empnum = 0;
        this->m_empArray = NULL;
        this->m_fileisempty = true;
        ifs.close();
        cout << "�뽫txt�ļ��ƶ�����exe�ļ�ͬһĿ¼��" << endl;
        system("pause");
        exit(0);
        return;
    }
    if (ifs.eof())
    {
        cout << "File is empty" << endl;
        this->m_empnum = 0;
        this->m_empArray = NULL;
        this->m_fileisempty = true;
        ifs.close();
        return;
    }
    //
    int num = this->get_number();
    if (num == 0)
    {
        this->m_fileisempty = true;
    }
    else
    {
        this->m_fileisempty = false;
    }
    this->m_empnum = num;
    // ���ٿռ�
    this->m_empArray = new User *[num];
    // ���ļ��е����ݣ��浽������
    this->init_emp();
}
Manage::~Manage()
{
    // cout << "WorkerManager����������" << endl;
    if (this->m_empArray != NULL)
    {

        delete[] this->m_empArray;
        this->m_empArray = NULL;
    }
}
void Manage::showmenu()
{
    long long int now = time(0);
    char *dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    cout << "TIME:" << gmtm->tm_year + 1900 << "-" << gmtm->tm_mon + 1 << "-" << gmtm->tm_mday << endl;
    cout << "Main Menu:" << endl;
    cout << "1-��ѯ���" << endl;
    cout << "2-ȡ��" << endl;
    cout << "3-���" << endl;
    cout << "4-ת��" << endl;
    cout << "5-�޸�����" << endl;
    cout << "0-�˳�" << endl;
}
void Manage::exitsystem()
{
    cout << "��ӭ�´�ʹ�ã�" << endl;
    system("pause");
    exit(0);
}
int Manage::get_number()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    string account;
    string name;
    string id_num;
    string password;
    int single;
    int balance;
    int num = 0;
    string x;
    while (ifs >> x && ifs >> account && ifs >> x && ifs >> name && ifs >> x && ifs >> id_num && ifs >> x && ifs >> password && ifs >> x && ifs >> balance && ifs >> x && ifs >> single)
    {
        num++;
    }

    this->time_old = x;
    // cout << this->time_old;
    return num;
}
void Manage::init_emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    string account;
    string name;
    string id_num;
    string password;
    int balance;
    int index = 0;
    string x;
    int single;
    while (ifs >> x && ifs >> account && ifs >> x && ifs >> name && ifs >> x && ifs >> id_num && ifs >> x && ifs >> password && ifs >> x && ifs >> balance && ifs >> x && ifs >> single)
    {
        User *temp = NULL;
        if (time_now != time_old)
        {
            single = 20000;
        }
        // ��ͨԱ��
        temp = new User(account, name, id_num, password, balance, single);
        this->m_empArray[index] = temp;
        index++;
    }
    // string time_old;
    // ifs >> time_old;
    // this->time_old = time_old;
    ifs.close();
    this->save();
}
int Manage::is_exist(string account)
{
    int index = -1;
    for (int i = 0; i < this->m_empnum; i++)
    {
        if (this->m_empArray[i]->account == account)
        {
            index = i;
            break;
        }
    }
    return index;
}
User **Manage::getEmpArray()
{
    return m_empArray;
}
void Manage::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); // ������ķ�ʽ���ļ� д�ļ�
    // д��ÿ���˵�����
    for (int i = 0; i < this->m_empnum; i++)
    {
        ofs << "account: ";
        ofs << this->m_empArray[i]->account << "\n";
        ofs << "name: ";
        ofs << this->m_empArray[i]->name << "\n";
        ofs << "id_num: ";
        ofs << this->m_empArray[i]->id_num << "\n";
        ofs << "password: ";
        ofs << this->m_empArray[i]->password << "\n";
        ofs << "balance: ";
        ofs << this->m_empArray[i]->balance << "\n";
        ofs << "���տ���ȡ��(Ԫ): ";
        ofs << this->m_empArray[i]->today_out_balance << "\n";

        ofs << endl;
    }
    ofs << get_time() << endl;
    // close
    ofs.close();
}
// string Manage::safe(string account_1)
// {
//     string account = account_1;
//     string password;
//     // ��֤account�Ƿ�Ϊ19λ���֣�password�Ƿ�Ϊ6λ
//     if (account.size() != 19)
//     {
//         cout << "�˺Ÿ�ʽ����" << endl;
//         system("pause");
//         system("cls");
//         return "long";
//     }
//     else if (is_exist(account) == -1)
//     {
//         cout << "���û�" << endl;
//         temp = account;
//         return "new";
//     }
//     cout << "����������(6λ):";
//     cin >> password;
//     if (this->m_empArray[is_exist(account)]->password == password)
//     {
//         cout << "pass" << endl;
//         this->m_empArray[is_exist(account)]->checkans == true;
//         temp_account_dex = is_exist(account); // Manage�������λ��
//         cout << this->m_empArray[temp_account_dex]->account << "�����Ϊ��"
//              << this->m_empArray[temp_account_dex]->balance << endl;
//         system("pause");
//         system("cls");
//         return "pass";
//     }
//     else if (this->m_empArray[is_exist(account)]->password != password)
//     {
//         this->m_empArray[is_exist(account)]->checkans == false;
//         return "wrongpass";
//     }
// }
void Manage::show_balance(int index)
{

    cout << this->m_empArray[index]->account << "�����Ϊ��"
         << this->m_empArray[index]->balance << endl;
    system("pause");
    system("cls");
}
void Manage::add_emp(string account)
{
    // addnew
    cout << account << "Ϊϵͳ���û�,���ڿ�ʼ������������˻�" << endl;
    int a = 0;
    cout << "1-����" << endl;
    cout << "0-�˳�" << endl;
    cin >> a;
    if (a != 1)
    {
        cout << "�˳���" << endl;
        exit(0);
    }
    else
    {
        int newsize = this->m_empnum + 1;
        User **newspace = new User *[newsize];
        // copy to new space
        if (this->m_empArray != NULL)
        {
            for (int i = 0; i < this->m_empnum; i++)
            {
                newspace[i] = this->m_empArray[i];
            }
        }
        cout << account << "������" << endl;
        string name;
        string password;
        int balance;
        string id_num;
        cout << "����������:";
        cin >> name;
        cout << "���������֤��(18λ) :";
        cin >> id_num;
        // ��������Ӷ����֤�ų��ȵ���֤��ȷ������Ϊ18λ
        while (id_num.size() != 18)
        {
            cout << "���֤�ű���Ϊ18λ,����������: ";
            cin >> id_num;
        }
        cout << "����������(6λ): ";
        cin >> password;
        while (password.size() != 6)
        {
            cout << "���п��������Ϊ6λ,����������: ";
            cin >> password;
        }
        cout << "���û�������ʼΪ10000Ԫ" << endl;
        User *user = NULL;
        user = new User(account, name, id_num, password, 10000, 20000);
        // save to arr[]
        // m_empnum��ԭ��������
        newspace[newsize - 1] = user;
        delete[] this->m_empArray;
        this->m_empArray = newspace;
        this->m_empnum = newsize;
        cout << "�ɹ�����:" << account << endl;
        this->m_fileisempty = false;
        this->save();
        system("pause");
        system("cls");
    }
}
string Manage::get_time()
{
    long long int now = time(0);
    char *dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    string time_now = to_string(gmtm->tm_year + 1900) + "-" + to_string(gmtm->tm_mon + 1) + "-" + to_string(gmtm->tm_mday);
    return time_now;
}
void Manage::change_password(string account)
{
    int index = is_exist(account);
    cout << "�����������:";
    string old_password;
    cin >> old_password;
    if (old_password == this->m_empArray[index]->password)
    {
        cout << "������������:";
        string new_password;
        cin >> new_password;
        cout << "���ٴ�����������:";
        string new_password2;
        cin >> new_password2;
        if (new_password == new_password2)
        {
            this->m_empArray[index]->password = new_password;
            cout << "�����޸ĳɹ�" << endl;
            this->save();
            system("pause");
            system("cls");
        }
        else
        {
            cout << "������������벻һ��" << endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        cout << "�������" << endl;
        system("pause");
        system("cls");
    }
}
bool Manage::check_password(int index, string password)
{
    if (this->m_empArray[index]->password == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Manage::withdraw(int index)
{
    this->init_emp();
    system("cls");
    cout << "����ǰ���Ϊ:";
    cout << m_empArray[index]->balance << endl;
    cout << "�����ջ�����֧ȡ:";
    cout << m_empArray[index]->today_out_balance << endl;
    int want = 0;
    cout << "����������֧ȡ�Ľ��(������)"
         << endl;
    cout << "����  0  �˿�" << endl;
    cout << ":";

    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "֧������Ϊ����" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "֧ȡ����Ϊ0���������" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "�˿���";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    if (want > m_empArray[index]->balance)
    {
        cout << "����,�޷�Ϊ��֧ȡ" << endl;
        system("pause");
        system("cls");
    }
    else if (want > 10000)
    {
        cout << "����ȡ������10000Ԫ" << endl;
        cout << "���˳�������" << endl;
        system("pause");
        system("cls");
    }
    else if (m_empArray[index]->today_out_balance <= 0)
    {
        cout << "�����յ��ۼ�֧ȡ����20000Ԫ" << endl;
        cout << "�������ٳ���" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "����Ϊ��֧ȡ" << want << "Ԫ" << endl;
        m_empArray[index]->balance = m_empArray[index]->balance - want;
        m_empArray[index]->today_out_balance -= want;
        cout << "����ǰ���Ϊ:";
        cout << m_empArray[index]->balance << endl;
        cout << "�����ջ�����֧ȡ:";
        cout << m_empArray[index]->today_out_balance << endl;
        system("pause");
        system("cls");
    }
    this->save();
}
void Manage::depositfunds(int index)
{
    this->init_emp();
    cout << "����ǰ���Ϊ:";
    cout << m_empArray[index]->balance << endl;
    cout << "�������������Ľ��(������)"
         << endl;
    cout << "����  0  �˿�" << endl;
    cout << ":";
    int want = 0;
    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "���벻��Ϊ����" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "�������Ϊ0���������" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "�˿���";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    cout << "����Ϊ������" << want << "Ԫ" << endl;
    m_empArray[index]->balance = m_empArray[index]->balance + want;
    cout << "����ǰ���Ϊ:";
    cout << m_empArray[index]->balance << endl;
    system("pause");
    system("cls");
    this->save();
}
void Manage::transfer(int index)
{
    this->init_emp();
    cout << "����ǰ���Ϊ:";
    cout << m_empArray[index]->balance << endl;
    cout << "������Է��˺�:";
    string account;
    cin >> account;
    int index2 = is_exist(account);
    if (index2 == -1)
    {
        cout << "�Է��˺Ų�����" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "������ת�˽��(������):";
    int want = 0;
    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "ת�˽���Ϊ����" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "ת�˽���Ϊ0���������" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "�˿���";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    if (want > m_empArray[index]->balance)
    {
        cout << "����,�޷�Ϊ��ת��" << endl;
        system("pause");
        system("cls");
    }
    else if (want > 10000)
    {
        cout << "����ת�˽���10000Ԫ" << endl;
        cout << "���˳�������" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "����Ϊ��ת��" << want << "Ԫ" << endl;
        m_empArray[index]->balance = m_empArray[index]->balance - want;
        m_empArray[index2]->balance = m_empArray[index2]->balance + want;
        cout << "����ǰ���Ϊ:";
        cout << m_empArray[index]->balance << endl;
        system("pause");
        system("cls");
    }
    this->save();
}