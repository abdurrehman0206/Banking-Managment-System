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
    int accountId, pin;
    unsigned long long int balance, loan;
};

int accNumChk = 0;
int id = -1;
short n;
Person *person = new Person[n];
const string filename = "accounts.dat";
ifstream fin;
ofstream fout;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

//PROTOTYPE
void color(int n);
void g_xy(int x, int y);
void read_file(Person **person, short *n, int &accNumChk);
void update_file(Person *person, short *n);
void i_data(Person **person, short *n);
void o_data(Person *person, short *n);
void siz(short *n);
bool login(Person *person, short *n, int *id);
void add_money(Person *person, short *n);
void withdraw(Person *person, short *n);
void send(Person *person, short *n);
void get_loan(Person *person, short *n);
void pay_loan(Person *person, short *n);
int accTypeChk(Person *person);
void change_pin(Person *person, short *n);
void alot_loan(Person *person, short *n);
int selection(int);
int main_menu(Person *person, short *n);
int customer_menu(Person *person, short *n);
int management_menu(Person *person, short *n);
bool admin_login();
int id_chk(Person *person, short *n, int t_id);
void print_statement(Person *person, short *n);
//PROTOTYPE