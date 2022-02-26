#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <cstring>
#include <cstdio>

using namespace std;

struct Person
{
    string fname, sname, accountType;
    unsigned int accountId, pin;
    unsigned long long int balance, loan;
};

int accNumChk = 0;
int id = -1;
int n;
Person *person = new Person[n];
const string filename = "accounts.dat";
ifstream fin;
ofstream fout;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
