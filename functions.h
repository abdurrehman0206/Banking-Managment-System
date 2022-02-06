#include "data.h"

//FUNCTIONS
void color(int n)
{
    SetConsoleTextAttribute(console, n);
}

//For Cursor Location
void g_xy(int x, int y)
{
    COORD cp;
    cp.X = x;
    cp.Y = y;
    SetConsoleCursorPosition(console, cp);
}

//For printing line
void line(int num)
{
    for (int i = 0; i <= num; i++)
    {
        cout << "=";
    }
    cout << endl;
}

//Reads the file that holds all the data
void read_file(Person **person, short *n, int &accNumChk)
{
    siz(n);
    Person *t = new Person[*n];
    fin.open(filename, ios::in);
    if (fin.is_open())
    {
        for (int i = 0; i < *n; i++)
        {

            fin >> t[i].fname;
            fin >> t[i].sname;
            fin >> t[i].accountId;
            fin >> t[i].accountType;
            fin >> t[i].balance;
            fin >> t[i].loan;
            fin >> t[i].pin;
        }
    }
    else
    {
        color(12);
        cout << "Remote Database Access Failed!" << endl;
        cout << endl;
        color(15);
    }
    fin.close();
    accNumChk = (t[*n - 1].accountId) + 1;
    *person = t;
    delete t;
}

//updates the file if local changes are made
void update_file(Person *person, short *n)
{

    fout.open(filename, ios::out);
    if (fout.is_open())
    {
        for (int i = 0; i < *n; i++)
        {
            fout << person[i].fname << " " << person[i].sname << " " << person[i].accountId << " " << person[i].accountType << " " << person[i].balance << " " << person[i].loan << " " << person[i].pin << endl;
        }
    }
    else
    {
        color(12);
        cout << "Failed to Update Remote Database!" << endl;
        cout << endl;
        color(15);
    }
    fout.close();
    read_file(&person, n, accNumChk);
}

//adding account
void i_data(Person **person, short *n)
{
    short inp;
    cout << "Input ::" << endl;
    cout << "Enter Number of Persons to add :: ";
    cin >> inp;
    if (inp == 0)
    {
        return;
    }
    *n = inp;
    Person *t = new Person[inp];
    cout << endl;
    cin.ignore();
    for (int i = 0; i < *n; i++)
    {
        cout << "Enter Persons First Name :: ";
        getline(cin, t[i].fname);
        cout << "Enter " << t[i].fname << "'s Last Name :: ";
        getline(cin, t[i].sname);
        cout << "Enter " << t[i].fname << " " << t[i].sname << "'s AccType :: ";
        getline(cin, t[i].accountType);
        t[i].accountId = accNumChk++;
        t[i].balance = 0;
        t[i].loan = 0;
        cout << "Enter " << t[i].fname << " " << t[i].sname << "'s Pin :: ";
        cin >> t[i].pin;
        cout << endl;
    }

    fout.open(filename, ios::ate | ios::out | ios::app);
    if (fout.is_open())
    {
        for (int i = 0; i < *n; i++)
        {
            fout << t[i].fname << " " << t[i].sname << " " << t[i].accountId << " " << t[i].accountType << " " << t[i].balance << " " << t[i].loan << " " << t[i].pin << endl;
        }
    }
    else
    {
        color(12);
        cout << "Remote Database Access Failed!" << endl;
        cout << endl;
        color(15);
    }
    read_file(person, n, accNumChk);
    delete t;
    fout.close();
    cin.ignore();
}

//output all the data stored
void o_data(Person *person, short *n)
{
    read_file(&person, n, accNumChk);
    cout << "FirstName \t LastName \t AccID \t\t AccType \t Balance \t Loan" << endl;
    for (int i = 0; i < *n; i++)
    {
        cout << setw(17) << left << person[i].fname << setw(16) << left << person[i].sname << setw(16) << left << person[i].accountId << setw(16) << left << person[i].accountType << setw(16) << left << person[i].balance << person[i].loan << endl;
    }
    cout << endl;
}

//check the number of customers in the database
void siz(short *n)
{
    int chk = 0;
    string garbage;
    fin.open(filename, ios::in);

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, garbage);
            chk++;
        }
    }
    fin.close();
    *n = --chk;
}

//for customer login (pin based)
bool login(Person *person, short *n, int *id)
{
    short pass;
    int t_id;
    cout << "Enter your accountId :: ";
    cin >> t_id;
    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return false;
    }
    *id = t_id;

    cout << "Enter your account Pin :: ";
    cin >> pass;
    if (pass == person[*id].pin)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//adding money to customer account
void add_money(Person *person, short *n)
{
    int t_id;
    int amount;
    cout << "Enter Account ID to add money to :: ";
    cin >> t_id;
    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return;
    }
    cout << "Enter amount to add to " << person[t_id].fname << " " << person[t_id].sname << " :: ";
    cin >> amount;
    person[t_id].balance += amount;
    color(10);
    cout << "Successfully Added :: " << amount << " to " << person[t_id].fname << " " << person[t_id].sname << endl;
    color(15);
    update_file(person, n);
}

//for customer to withdraw money
void withdraw(Person *person, short *n)
{
    int amount = 0, max_amm;
    cout << "Enter Amount to withdraw :: ";
    cin >> amount;
    max_amm = accTypeChk(person);
    if (amount > 0 && amount <= max_amm && person[id].balance > amount)
    {
        person[id].balance -= amount;
        color(10);
        cout << "Successfully transaction of :: " << amount << endl;
        color(15);
        cout << "Remaining Balance :: " << person[id].balance << endl;
    }
    else if (person[id].balance < amount)
    {
        color(12);
        cout << "Not Enough Money!" << endl;
        color(15);
    }
    else if (amount > max_amm)
    {
        color(12);
        cout << "Account Type does not allow this amount!" << endl;
        color(15);
    }
    else if (max_amm = 0)
    {
        color(12);
        cout << "Please get your account type updated from the bank!" << endl;
        color(15);
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }

    update_file(person, n);
}

//for customer to send money to another account
void send(Person *person, short *n)
{
    int amount = 0, max_amm, r_id;
    cout << "Enter ID of the Account to send to :: ";
    cin >> r_id;
    r_id = id_chk(person, n, r_id);
    if (r_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return;
    }
    cout << "Enter Amount to send to " << person[r_id].fname << " " << person[r_id].sname << " :: ";
    cin >> amount;
    max_amm = accTypeChk(person);
    if (amount > 0 && amount <= max_amm && person[id].balance > amount)
    {
        person[id].balance -= amount;
        person[r_id].balance += amount;
        color(10);
        cout << "Successfully sent " << amount << " to " << person[r_id].fname << " " << person[r_id].sname << endl;
        color(15);
        cout << "Remaining Balance :: " << person[id].balance << endl;
    }
    else if (person[id].balance < amount)
    {
        color(12);
        cout << "Not Enough Money!" << endl;
        color(15);
    }
    else if (amount > max_amm)
    {
        color(12);
        cout << "Account Type does not allow this amount!" << endl;
        color(15);
    }
    else if (max_amm = 0)
    {
        color(12);
        cout << "Please get your account type updated from the bank!" << endl;
        color(15);
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }

    update_file(person, n);
}

//for customer to get a loan
void get_loan(Person *person, short *n)
{
    int amount = 0, max_amm;

    cout << "Enter amount of loan to take :: ";
    cin >> amount;

    max_amm = accTypeChk(person);

    if (amount > 0 && amount <= max_amm)
    {
        person[id].balance += amount;
        person[id].loan += amount;
        color(10);
        cout << "Successfully Took Loan of " << amount << endl;

        color(15);
        cout << "New Balance :: " << person[id].balance << endl;
        cout << "Loan Added :: " << person[id].loan << endl;
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }
    update_file(person, n);
}

//for customer to pay loan
void pay_loan(Person *person, short *n)
{
    int amount = 0, max_amm;

    cout << "Enter amount of loan to pay :: ";
    cin >> amount;
    if (amount < person[id].balance && amount <= person[id].loan)
    {
        person[id].balance -= amount;
        person[id].loan -= amount;
        color(10);
        cout << "Successfully Paid Loan of " << amount << endl;
        color(15);
        cout << "New Balance :: " << person[id].balance << endl;
        cout << "Updated loan :: " << person[id].loan << endl;
    }
    else if (amount > person[id].loan)
    {
        color(12);
        cout << "You are trying to pay more than you owe!" << endl;
        color(15);
    }
    else if (amount > person[id].balance)
    {
        color(12);
        cout << "You do not have enough cash in your account!" << endl;
        color(15);
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }

    update_file(person, n);
}

//checks the customers Account Type
int accTypeChk(Person *person)
{
    string type;
    type = (person[id].accountType);
    int max_amm;
    if ((strcmpi(type.c_str(), "platinum")) == 0)
    {
        max_amm = 1000000;
        return max_amm;
    }
    else if ((strcmpi(type.c_str(), "gold")) == 0)
    {
        max_amm = 75000;
        return max_amm;
    }
    else if ((strcmpi(type.c_str(), "silver")) == 0)
    {
        max_amm = 50000;
        return max_amm;
    }
    else if ((strcmpi(type.c_str(), "bronze")) == 0)
    {
        max_amm = 25000;
        return max_amm;
    }
    else
    {
        max_amm = 0;
        return max_amm;
    }
}

//for customer to change pin
void change_pin(Person *person, short *n)
{
    int t_pin;
    cout << "Enter new Pin :: ";
    cin >> t_pin;
    person[id].pin = t_pin;
    update_file(person, n);
}

//for management to alot loan to an account
void alot_loan(Person *person, short *n)
{
    int amount, t_id;
    cout << "Enter account ID to alot loan to :: ";
    cin >> t_id;
    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return;
    }
    if (t_id <= accNumChk)
    {
        cout << "Enter ammount to add to " << person[t_id].fname << " " << person[t_id].sname << " ::";
        cin >> amount;
        person[t_id].loan += amount;
        person[t_id].balance += amount;
        color(10);
        cout << "Successfully added " << amount << " to " << person[t_id].fname << " " << person[t_id].sname << endl;
        color(15);
        cout << "New Balance :: " << person[t_id].balance << endl;
        cout << "Loan Added :: " << person[t_id].loan << endl;
    }

    update_file(person, n);
}

//for management to modify an account
void modify_acc(Person *person, short *n)
{
    int t_id;
    cout << "Enter ID of account you want to modify :: ";
    cin >> t_id;
    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return;
    }
    cin.ignore();
    if (t_id <= accNumChk)
    {
        cout << setw(17) << left << person[t_id].fname << setw(16) << left << person[t_id].sname << setw(16) << left << person[t_id].accountId << setw(16) << left << person[t_id].accountType << setw(16) << left << person[t_id].balance << person[t_id].loan << endl;
        cout << "Enter New First Name :: ";
        getline(cin, person[t_id].fname);
        cout << "Enter New Last Name for " << person[t_id].fname << " ::";
        getline(cin, person[t_id].sname);
        cout << "Enter " << person[t_id].fname << " " << person[t_id].sname << "'s AccType :: ";
        getline(cin, person[t_id].accountType);
        update_file(person, n);
    }
    else
    {
        color(12);
        cout << "Account does not exist!" << endl;
        color(15);
    }
    read_file(&person, n, accNumChk);
}

//for management to delete accounts
void delete_acc(Person *person, short *n)

{
    int t_id;
    int t = 0;
    cout << "Enter ID of account you want to delete :: ";
    cin >> t_id;
    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        cout << "Account Does Not Exist !" << endl;
        color(15);
        return;
    }
    //cin.ignore();
    if (t_id <= accNumChk)
    {

        fout.open(filename, ios::out | ios::trunc);
        if (fout.is_open())
        {
            for (int i = 0; i < *n; i++)
            {
                if (i == t_id)
                {
                    person[i].fname = "";
                    person[i].sname = "";
                    person[i].accountId = -1;
                    person[i].accountType = "";
                    person[i].balance = 0;
                    person[i].loan = 0;
                    person[i].pin = 0;
                    continue;
                }
                fout << person[i].fname << " " << person[i].sname << " " << person[i].accountId << " " << person[i].accountType << " " << person[i].balance << " " << person[i].loan << " " << person[i].pin << endl;
            }
        }
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }
    fin.close();
    read_file(&person, n, accNumChk);
}

//main menu 
int main_menu(Person *person, short *n)
{

    bool flip = 0;
    int opt = -1;
    line(43);

    cout << setw(43) << left << "| Customer Menu"
         << "|" << endl;

    cout << setw(43) << left << "| Managment Menu"
         << "|" << endl;
    cout << setw(43) << left << "| QUIT!"
         << "|" << endl;

    cout << setw(43) << left << "|"
         << "|" << endl;
    line(43);
    opt = selection(3);
    return opt;
}

//customer menu
int customer_menu(Person *person, short *n)
{

    bool flip = 0;
    int opt = -1;
label1:
    if (opt == -1)
    {
        flip = 0;
    }
    else
    {
        flip = 1;
    }
    system("CLS");

    line(43);
    if (opt == 1)
    {
        color(10);
        cout << setw(43) << left << "> Withdraw Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Withdraw Money"
             << "|" << endl;
    }

    if (opt == 2)
    {
        color(10);
        cout << setw(43) << left << "> Send Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Send Money"
             << "|" << endl;
    }
    if (opt == 3)
    {
        color(10);
        cout << setw(43) << left << "> Change Pin"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Change Pin"
             << "|" << endl;
    }

    if (opt == 4)
    {
        color(10);
        cout << setw(43) << left << "> Get Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Get Loan"
             << "|" << endl;
    }
    if (opt == 5)
    {
        color(10);
        cout << setw(43) << left << "> Pay Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Pay Loan"
             << "|" << endl;
    }

    cout << setw(43) << left << "| Go To Main Menu!"
         << "|" << endl;

    cout << setw(43) << left << "| QUIT!"
         << "|" << endl;

    cout << setw(43) << left << "|"
         << "|" << endl;
    line(43);
    color(15);
    cout << "| First Name  : " << setw(27) << left << person[id].fname << "|" << endl;
    cout << "| Last Name   : " << setw(27) << left << person[id].sname << "|" << endl;
    cout << "| AccountID   : " << setw(27) << left << person[id].accountId << "|" << endl;
    cout << "| AccountType : " << setw(27) << left << person[id].accountType << "|" << endl;
    cout << "| Balance     : " << setw(27) << left << person[id].balance << "|" << endl;
    cout << "| Loan        : " << setw(27) << left << person[id].loan << "|" << endl;

    line(43);
    if (opt == -1 && flip == 0)
    {
        opt = selection(7);
        goto label1;
    }
    return opt;
}

//management menu
int management_menu(Person *person, short *n)
{

    bool flip = 0;
    int opt = -1;
label1:
    if (opt == -1)
    {
        flip = 0;
    }
    else
    {
        flip = 1;
    }
    system("CLS");

    line(43);
    if (opt == 1)
    {
        color(10);
        cout << setw(43) << left << "> Add Account "
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Add Account"
             << "|" << endl;
    }

    if (opt == 2)
    {
        color(10);
        cout << setw(43) << left << "> Modify Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Modify Account"
             << "|" << endl;
    }
    if (opt == 3)
    {
        color(10);
        cout << setw(43) << left << "> Delete Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Delete Account"
             << "|" << endl;
    }
    if (opt == 4)
    {
        color(10);
        cout << setw(43) << left << "> Add Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Add Money"
             << "|" << endl;
    }

    if (opt == 5)
    {
        color(10);
        cout << setw(43) << left << "> Alot Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Alot Loan"
             << "|" << endl;
    }
    if (opt == 6)
    {
        color(10);
        cout << setw(43) << left << "> Show All Account Database"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(43) << left << "| Show All Account Database"
             << "|" << endl;
    }

    cout << setw(43) << left << "| Go To Main Menu!"
         << "|" << endl;

    cout << setw(43) << left << "| QUIT!"
         << "|" << endl;

    cout << setw(43) << left << "|"
         << "|" << endl;
    line(43);
    color(15);
    if (opt == -1 && flip == 0)
    {
        opt = selection(8);
        goto label1;
    }
    return opt;
}

//for scrolling selection
int selection(int yxis)
{
    unsigned int pos = 0, y = 0;
    g_xy(36, 0);
    char c;
    while (true)
    {
        color(12);
        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && y <= yxis)
        {
            g_xy(36, y);
            if (y == 0)
            {
                color(15);
                cout << "====";
                color(12);
            }
            else
            {
                cout << "    ";
            }
            y++;
            g_xy(36, y);
            cout << "<===";
            pos++;
            continue;
        }
        if (GetAsyncKeyState(VK_UP) && y > 0)
        {

            g_xy(36, y);
            cout << "    ";
            y--;
            g_xy(36, y);
            cout << "<===";
            pos--;
            continue;
        }

        if (GetAsyncKeyState(VK_RETURN))
        {
            color(15);
            return pos;
        }
    }
}

//for management login
bool admin_login()
{
    string pass;
    cout << "Enter Admin Password :: ";
    getline(cin, pass);
    if (pass == "admin")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//account id check 
int id_chk(Person *person, short *n, int t_id)
{
    for (int i = 0; i < *n; i++)
    {
        if (person[i].accountId == t_id)
        {
            return i;
        }
    }
    return -1;
}
