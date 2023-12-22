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
        cout << "请将txt文件移动到与exe文件同一目录下" << endl;
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
    // 开辟空间
    this->m_empArray = new User *[num];
    // 将文件中的数据，存到数组中
    this->init_emp();
}
Manage::~Manage()
{
    // cout << "WorkerManager的析构函数" << endl;
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
    cout << "1-查询余额" << endl;
    cout << "2-取款" << endl;
    cout << "3-存款" << endl;
    cout << "4-转账" << endl;
    cout << "5-修改密码" << endl;
    cout << "0-退出" << endl;
}
void Manage::exitsystem()
{
    cout << "欢迎下次使用！" << endl;
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
        // 普通员工
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
    ofs.open(FILENAME, ios::out); // 用输出的方式打开文件 写文件
    // 写入每个人的数据
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
        ofs << "今日可以取款(元): ";
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
//     // 验证account是否为19位数字，password是否为6位
//     if (account.size() != 19)
//     {
//         cout << "账号格式出错" << endl;
//         system("pause");
//         system("cls");
//         return "long";
//     }
//     else if (is_exist(account) == -1)
//     {
//         cout << "新用户" << endl;
//         temp = account;
//         return "new";
//     }
//     cout << "请输入密码(6位):";
//     cin >> password;
//     if (this->m_empArray[is_exist(account)]->password == password)
//     {
//         cout << "pass" << endl;
//         this->m_empArray[is_exist(account)]->checkans == true;
//         temp_account_dex = is_exist(account); // Manage存放数组位置
//         cout << this->m_empArray[temp_account_dex]->account << "的余额为："
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

    cout << this->m_empArray[index]->account << "的余额为："
         << this->m_empArray[index]->balance << endl;
    system("pause");
    system("cls");
}
void Manage::add_emp(string account)
{
    // addnew
    cout << account << "为系统新用户,现在开始创建你的银行账户" << endl;
    int a = 0;
    cout << "1-继续" << endl;
    cout << "0-退出" << endl;
    cin >> a;
    if (a != 1)
    {
        cout << "退出中" << endl;
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
        cout << account << "创建中" << endl;
        string name;
        string password;
        int balance;
        string id_num;
        cout << "请输入姓名:";
        cin >> name;
        cout << "请输入身份证号(18位) :";
        cin >> id_num;
        // 在这里添加对身份证号长度的验证，确保输入为18位
        while (id_num.size() != 18)
        {
            cout << "身份证号必须为18位,请重新输入: ";
            cin >> id_num;
        }
        cout << "请输入密码(6位): ";
        cin >> password;
        while (password.size() != 6)
        {
            cout << "银行卡密码必须为6位,请重新输入: ";
            cin >> password;
        }
        cout << "新用户的余额初始为10000元" << endl;
        User *user = NULL;
        user = new User(account, name, id_num, password, 10000, 20000);
        // save to arr[]
        // m_empnum是原来的人数
        newspace[newsize - 1] = user;
        delete[] this->m_empArray;
        this->m_empArray = newspace;
        this->m_empnum = newsize;
        cout << "成功创建:" << account << endl;
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
    cout << "请输入旧密码:";
    string old_password;
    cin >> old_password;
    if (old_password == this->m_empArray[index]->password)
    {
        cout << "请输入新密码:";
        string new_password;
        cin >> new_password;
        cout << "请再次输入新密码:";
        string new_password2;
        cin >> new_password2;
        if (new_password == new_password2)
        {
            this->m_empArray[index]->password = new_password;
            cout << "密码修改成功" << endl;
            this->save();
            system("pause");
            system("cls");
        }
        else
        {
            cout << "两次输入的密码不一致" << endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        cout << "密码错误" << endl;
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
    cout << "您当前余额为:";
    cout << m_empArray[index]->balance << endl;
    cout << "您今日还可以支取:";
    cout << m_empArray[index]->today_out_balance << endl;
    int want = 0;
    cout << "请输入你想支取的金额(整百数)"
         << endl;
    cout << "输入  0  退卡" << endl;
    cout << ":";

    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "支出不可为负数" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "支取金额不可为0或非整百数" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "退卡中";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    if (want > m_empArray[index]->balance)
    {
        cout << "余额不足,无法为您支取" << endl;
        system("pause");
        system("cls");
    }
    else if (want > 10000)
    {
        cout << "单次取出金额超限10000元" << endl;
        cout << "请退出后再试" << endl;
        system("pause");
        system("cls");
    }
    else if (m_empArray[index]->today_out_balance <= 0)
    {
        cout << "您今日的累计支取金额超出20000元" << endl;
        cout << "请明天再尝试" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "正在为您支取" << want << "元" << endl;
        m_empArray[index]->balance = m_empArray[index]->balance - want;
        m_empArray[index]->today_out_balance -= want;
        cout << "您当前余额为:";
        cout << m_empArray[index]->balance << endl;
        cout << "您今日还可以支取:";
        cout << m_empArray[index]->today_out_balance << endl;
        system("pause");
        system("cls");
    }
    this->save();
}
void Manage::depositfunds(int index)
{
    this->init_emp();
    cout << "您当前余额为:";
    cout << m_empArray[index]->balance << endl;
    cout << "请输入你想存入的金额(整百数)"
         << endl;
    cout << "输入  0  退卡" << endl;
    cout << ":";
    int want = 0;
    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "存入不可为负数" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "存入金额不可为0或非整百数" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "退卡中";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    cout << "正在为您存入" << want << "元" << endl;
    m_empArray[index]->balance = m_empArray[index]->balance + want;
    cout << "您当前余额为:";
    cout << m_empArray[index]->balance << endl;
    system("pause");
    system("cls");
    this->save();
}
void Manage::transfer(int index)
{
    this->init_emp();
    cout << "您当前余额为:";
    cout << m_empArray[index]->balance << endl;
    cout << "请输入对方账号:";
    string account;
    cin >> account;
    int index2 = is_exist(account);
    if (index2 == -1)
    {
        cout << "对方账号不存在" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "请输入转账金额(整百数):";
    int want = 0;
    bool w = false;
    while (!w)
    {
        cin >> want;
        if (want < 0)
        {
            cout << "转账金额不可为负数" << endl;
            w = false;
            continue;
        }
        if (want != 0 && want % 100 != 0)
        {
            cout << "转账金额不可为0或非整百数" << endl;
            w = false;
        }
        else if (want == 0)
        {
            cout << "退卡中";
            exit(0);
        }
        else
        {
            w = true;
        }
    }
    if (want > m_empArray[index]->balance)
    {
        cout << "余额不足,无法为您转账" << endl;
        system("pause");
        system("cls");
    }
    else if (want > 10000)
    {
        cout << "单次转账金额超限10000元" << endl;
        cout << "请退出后再试" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "正在为您转账" << want << "元" << endl;
        m_empArray[index]->balance = m_empArray[index]->balance - want;
        m_empArray[index2]->balance = m_empArray[index2]->balance + want;
        cout << "您当前余额为:";
        cout << m_empArray[index]->balance << endl;
        system("pause");
        system("cls");
    }
    this->save();
}