#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Person
{
    string fname, sname;
    int accountId, balance, loan;
};

int accNumChk = 1;
short n ;
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
    accNumChk = chk / 5;
}

void read_file(Person **person, short *n){
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
            fin >> t[i].balance;
            fin >> t[i].loan;
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
        t[i].accountId = accNumChk++;
        t[i].balance = 0;
        t[i].loan = 0;
        cout << endl;
    }
    *person = t;

    fout.open(filename, ios::binary | ios::ate | ios::out | ios::app);
    if (fout.is_open())
    {
        color(10);
        cout << filename << " access granted!" << endl;
        cout << endl;
        color(15);
        for (int i = 0; i < *n; i++)
        {
            fout << t[i].fname << " " << t[i].sname << " " << t[i].accountId << " " << t[i].balance << " " << t[i].loan << endl;
            //fout.write((char*)&t , sizeof(t));
        }
    }
    else
    {
        color(12);
        cout << "File access denied!" << endl;
        cout << endl;
        color(15);
    }
    delete t;
    fout.close();
    cin.ignore();
}

void o_data(Person *person,short *n){
    read_file(&person, n);
    cout << "FirstName \t LastName \t AccID \t\t Balance \t Loan" << endl;
    for (int i = 0; i < *n; i++)
    {
        cout << setw(17) << left << person[i].fname << setw(16) << left << person[i].sname << setw(16) << left << person[i].accountId << setw(16) << left << person[i].balance << person[i].loan << endl;
    }
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
    *n = chk / 5;
}