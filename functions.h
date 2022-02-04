#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Person
{
    string fname, sname;
    int accountId, balance, loan;
};
short n;
Person *person = new Person[n];
string filename;


void i_data(Person **person,short &n)
{

    short inp;
    cout << "Input ::" << endl;
    cout << "Enter Number of Courses :: ";
    cin >> inp;
    if (inp == 0)
    {
        return;
    }
    n = inp;
    filename = "Nil";
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
    delete t;

}
