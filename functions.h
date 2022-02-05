#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstring>

using namespace std;

struct Person
{
    string fname, sname, accountType;
    int accountId, balance, loan;
    short pin;
};

int accNumChk = 1;
int id = -1;
short n;
Person *person = new Person[n];
string filename = "accounts.dat";
ifstream fin;
ofstream fout;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

//PROTOTYPE
void color(int n);
void id_assign(int &accNumChk);
void read_file(Person **person, short *n);
void i_data(Person **person, short *n);
void o_data(Person *person, short *n);
void siz(short *n);
void login(Person *person, short *n , int *id);
void withdraw(Person *person, short *n);
int accTypeChk(Person *person);
void update_file(Person *person, short *n);
//PROTOTYPE

//FUNCTIONS
void color(int n)
{
    SetConsoleTextAttribute(console, n);
}

void id_assign(int &accNumChk)
{
    string garbage;
    int chk = 0;

    fin.open(filename);

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            fin >> garbage;
            chk++;
        }
    }
    fin.close();
    accNumChk = chk / 7;
}

void read_file(Person **person, short *n)
{
    siz(n);
    Person *t = new Person[*n];
    fin.open(filename, ios::in);
    if (fin.is_open())
    {
        color(10);
        cout << filename << " access granted!" << endl;
        cout << endl;
        color(15);
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
        cout << "File access denied!" << endl;
        cout << endl;
        color(15);
    }
    fin.close();
    *person = t;
    delete t;
    cin.ignore();
}

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
    cin.ignore();
}

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
        t[i].pin = 1111; //default pin set to 1111 can be changed later
        cout << endl;
    }

    fout.open(filename, ios::ate | ios::out | ios::app);
    if (fout.is_open())
    {
        color(10);
        cout << filename << " access granted!" << endl;
        cout << endl;
        color(15);
        for (int i = 0; i < *n; i++)
        {
            fout << t[i].fname << " " << t[i].sname << " " << t[i].accountId << " " << t[i].accountType << " " << t[i].balance << " " << t[i].loan << " " << t[i].pin << endl;
        }
    }
    else
    {
        color(12);
        cout << "File access denied!" << endl;
        cout << endl;
        color(15);
    }
    *person = t;
    delete t;
    fout.close();
    cin.ignore();
}

void o_data(Person *person, short *n)
{
    read_file(&person, n);
    cout << "FirstName \t LastName \t AccID \t\t AccType \t Balance \t Loan" << endl;
    for (int i = 0; i < *n; i++)
    {
        cout << setw(17) << left << person[i].fname << setw(16) << left << person[i].sname << setw(16) << left << person[i].accountId << setw(16) << left << person[i].accountType << setw(16) << left << person[i].balance << person[i].loan << endl;
    }
    cout << endl;
}

void siz(short *n)
{
    int chk = 0;
    string garbage;
    fin.open(filename);

    if (fin.is_open())
    {
        while (!fin.eof())
        {
            fin >> garbage;
            chk++;
        }
    }
    fin.close();
    *n = chk / 7;
}

void login(Person *person, short *n , int *id)
{
    short pass;
    cout << "Enter your accountId :: ";
    cin >> *id;
    cout << "Enter your account Pin :: ";
    cin >> pass;
    if (pass == person[*id].pin)
    {
        cout << "FirstName \t LastName \t AccID \t\t Balance \t Loan" << endl;
        cout << setw(17) << left << person[*id].fname << setw(16) << left << person[*id].sname << setw(16) << left << person[*id].accountId << setw(16) << left << person[*id].balance << person[*id].loan << endl;
    }
    else
    {
        cout << "Please Enter Correct Pin!" << endl;
    }
}

void withdraw(Person *person, short *n)
{
    cin.ignore();
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
    cout << "Remaining Balance :: " << person[id].balance << endl;
    update_file(person, n);
}

int accTypeChk(Person *person)
{
    string type;
    type = (person[id].accountType);
    int max_amm;
    if ((strcmpi(type.c_str(), "platinum")) == 0)
    {
        max_amm = 100000;
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