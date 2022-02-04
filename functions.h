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
short n;
Person *person = new Person[n];
string filename = "accounts.dat";
ifstream fin;
ofstream fout;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int n)
{
    SetConsoleTextAttribute(console, n);
}

void i_data(Person **person,short &n)
{

    short inp;
    cout << "Input ::" << endl;
    cout << "Enter Number of Persons to add :: ";
    cin >> inp;
    if (inp == 0)
    {
        return;
    }
    n = inp;
    Person *t = new Person[inp];
    cout << endl;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "Enter Persons First Name :: ";
        getline(cin, t[i].fname);
        cout << "Enter " << t[i].fname << "'s Last Name :: ";
        getline(cin, t[i].sname);
        t[i].balance = 0;
        t[i].loan = 0;
        cout << endl;
    }
    *person = t;
    
    fout.open(filename , ios::binary | ios::ate | ios::out);
    if (fout.is_open())
    {
        color(10);
        cout << filename << " access granted!" << endl;
        cout << endl;
        color(15);
        for (int i = 0; i < n; i++)
        {
            fout << t[i].fname << "\t" << t[i].sname << "\t" << t[i].accountId << "\t" << t[i].balance << "\t" << t[i].loan << endl;
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
