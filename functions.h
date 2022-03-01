#include "prototype.h"

// FUNCTIONS

//======Real Time Updating=====//

// Reads the file that holds all the data
void read_file(Person **person, int *n, int &accNumChk)
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
    fin.seekg(0, ios::end);
    fin.close();
    accNumChk = (t[*n - 1].accountId) + 1;
    *person = t;
    delete t;
}

// updates the file if local changes are made
void update_file(Person *person, int *n)
{

    fout.open(filename, ios::out | ios::trunc);
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

//======Real Time Updating=====//

//=======Customer Functions=========//

// for customer to withdraw money
void withdraw(Person *person, int *n)
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
        string statfile = "statement-";
        statfile = statfile.append(to_string(person[id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Withdrew Money"
                 << "\t"
                 << "-" << amount << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        fout.close();
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

// for customer to send money to another account
void send(Person *person, int *n)
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
    if (amount > 0 && amount <= max_amm && person[id].balance >= amount && person[id].balance > person[r_id].loan)
    {
        person[id].balance -= amount;
        person[r_id].balance += amount;
        color(10);
        cout << "Successfully sent " << amount << " to " << person[r_id].fname << " " << person[r_id].sname << endl;
        color(15);
        cout << "Remaining Balance :: " << person[id].balance << endl;
        string statfile = "statement-";
        statfile = statfile.append(to_string(person[id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Sent Money"
                 << "\t"
                 << "-" << amount << "\t"
                 << "to"
                 << "\t" << person[r_id].fname << " " << person[r_id].sname << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        fout.close();
        statfile = "statement-";
        statfile = statfile.append(to_string(person[r_id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Recieved Money"
                 << "\t"
                 << "+" << amount << "\t"
                 << "from"
                 << "\t" << person[id].fname << " " << person[id].sname << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        fout.close();
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
    else if (person[id].balance == person[id].loan)
    {
        color(12);
        cout << "You have active loan !" << endl;
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

// for customer to get a loan
void get_loan(Person *person, int *n)
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
        string statfile = "statement-";
        statfile = statfile.append(to_string(person[id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Borrowed Loan "
                 << "\t"
                 << "+" << amount << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        fout.close();
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }
    update_file(person, n);
}

// for customer to pay loan
void pay_loan(Person *person, int *n)
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
        string statfile = "statement-";
        statfile = statfile.append(to_string(person[id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Payed Loan "
                 << "\t"
                 << "-" << amount << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        fout.close();
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

// for customer to change pin
void change_pin(Person *person, int *n)
{
    int t_pin;
    cout << "Enter new Pin :: ";
    cin >> t_pin;
    person[id].pin = t_pin;
    update_file(person, n);
}

// Print customer statement
void print_statement(Person *person, int *n)
{

    cout << "Statement for " << person[id].fname << " " << person[id].sname << endl;
    cout << endl;
    string line;
    string statfile = "statement-";
    statfile = statfile.append(to_string(person[id].accountId));
    statfile += ".txt";
    fin.open(statfile, ios::in);
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            getline(fin, line);
            cout << line << endl;
        }
    }
    else
    {
        color(12);
        cout << "Failed to retreive statement!" << endl;
        color(15);
    }
    fin.close();
}

// for customer login (pin based)
bool login(Person *person, int *n, int *id)
{
    int pass;
    int t_id;
    g_xy(42, 13);
    cout << "ID" << endl;
    g_xy(48, 12);
    line(23);
    g_xy(48, 13);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 14);
    line(23);
    g_xy(42, 16);
    cout << "PIN" << endl;
    g_xy(48, 15);
    line(23);
    g_xy(48, 16);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 17);
    line(23);
    g_xy(58, 13);
    cin >> t_id;
    g_xy(58, 16);
    cin >> pass;

    t_id = id_chk(person, n, t_id);
    if (t_id == -1)
    {
        color(12);
        g_xy(49, 19);
        cout << "Account Does Not Exist" << endl;
        g_xy(55, 21);
        cout << "Going Back" << endl;
        for (int i = 0; i < 5; i++)
        {
            g_xy(58 + i, 23);
            cout << "*";
            Sleep(400);
        }
        color(15);
        return false;
    }
    *id = t_id;

    if (pass == person[*id].pin)
    {
        color(10);
        g_xy(52, 19);
        cout << "Login Successful" << endl;
        g_xy(55, 21);
        cout << "Please Wait" << endl;

        for (int i = 0; i < 5; i++)
        {
            g_xy(58 + i, 23);
            cout << "*";
            Sleep(400);
        }

        color(15);
        return true;
    }
    else
    {
        color(12);
        g_xy(54, 19);
        cout << "Login Failed" << endl;
        g_xy(55, 21);
        cout << "Going Back" << endl;
        for (int i = 0; i < 5; i++)
        {
            g_xy(58 + i, 23);
            cout << "*";
            Sleep(400);
        }
        color(15);
        return false;
    }
}

//=======Customer Functions=========//

//=======Admin Functions=========//

// adding accounts to database
void add_acc(Person **person, int *n)
{
    int inp;
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

    for (int i = 0; i < *n; i++)
    {
        cin.ignore();
        cout << "Enter Persons First Name :: ";
        getline(cin, t[i].fname);
        cout << "Enter " << t[i].fname << "'s Last Name :: ";
        getline(cin, t[i].sname);

        do
        {
            cout << "Enter " << t[i].fname << " " << t[i].sname << "'s AccType :: ";
            getline(cin, t[i].accountType);
        } while ((stricmp("platinum", (t[i].accountType).c_str()) != 0) && (stricmp("gold", (t[i].accountType).c_str()) != 0) && (stricmp("bronze", (t[i].accountType).c_str()) != 0) && (stricmp("silver", (t[i].accountType).c_str()) != 0));

        t[i].accountId = accNumChk++;
        cout << "Account Number Assigned to " << t[i].fname << " " << t[i].sname << " :: " << t[i].accountId << endl;
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
    fout.close();
    read_file(person, n, accNumChk);
    delete t;
    cin.ignore();
}

// Outputs data stored in the file
void o_data(Person *person, int *n)
{
    read_file(&person, n, accNumChk);
    cout << "FirstName \t LastName \t AccID \t\t AccType \t Balance \t Loan" << endl;
    for (int i = 0; i < *n; i++)
    {
        cout << setw(17) << left << person[i].fname << setw(16) << left << person[i].sname << setw(16) << left << person[i].accountId << setw(16) << left << person[i].accountType << setw(16) << left << person[i].balance << person[i].loan << endl;
    }
    cout << endl;
}

// adding money to customer account
void add_money(Person *person, int *n)
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
    else
    {
        cout << "Enter amount to add to " << person[t_id].fname << " " << person[t_id].sname << " :: ";
        cin >> amount;
        person[t_id].balance += amount;
        color(10);
        cout << "Successfully Added :: " << amount << " to " << person[t_id].fname << " " << person[t_id].sname << endl;
        color(15);
        update_file(person, n);
        string statfile = "statement-";
        statfile = statfile.append(to_string(person[t_id].accountId));
        statfile += ".txt";
        fout.open(statfile, ios::out | ios::app);
        if (fout.is_open())
        {
            fout << "Bank Deposit"
                 << "\t"
                 << "+" << amount << endl;
        }
        else
        {
            color(12);
            cout << "Error! Could not update statement!" << endl;
            color(15);
        }
        cin.clear();
        fout.close();
    }
}

// for management to alot loan to an account
void alot_loan(Person *person, int *n)
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
        cout << "Enter ammount to add to " << person[t_id].fname << " " << person[t_id].sname << " :: ";
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

// for management to modify an account
void modify_acc(Person *person, int *n)
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
    else if (t_id <= accNumChk)
    {
        cin.ignore();
        cout << setw(17) << left << person[t_id].fname << setw(16) << left << person[t_id].sname << setw(16) << left << person[t_id].accountId << setw(16) << left << person[t_id].accountType << setw(16) << left << person[t_id].balance << person[t_id].loan << endl;
        cout << "Enter New First Name :: ";
        getline(cin, person[t_id].fname);
        cout << "Enter New Last Name for " << person[t_id].fname << " :: ";
        getline(cin, person[t_id].sname);

        do
        {
            cout << "Enter " << person[t_id].fname << " " << person[t_id].sname << "'s AccType :: ";
            getline(cin, person[t_id].accountType);
        } while ((stricmp("platinum", (person[t_id].accountType).c_str()) != 0) && (stricmp("gold", (person[t_id].accountType).c_str()) != 0) && (stricmp("silver", (person[t_id].accountType).c_str()) != 0) && (stricmp("bronze", (person[t_id].accountType).c_str()) != 0));
        update_file(person, n);
    }
    else
    {
        color(12);
        cout << "Technical Error!" << endl;
        color(15);
    }
    update_file(person, n);
    read_file(&person, n, accNumChk);
}

// for management to delete accounts
void delete_acc(Person *person, int *n)

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
    if (t_id <= accNumChk)
    {
        fout.open(filename, ios::out | ios::trunc);
        if (fout.is_open())
        {
            color(10);
            cout << endl
                 << "Account Deleted :: " << person[t_id].fname << " " << person[t_id].sname << " " << person[t_id].accountId << endl;
            color(15);
            int ind = 0;
            for (int i = 0; i < *n; i++)
            {

                if (i == t_id)
                {
                    continue;
                }
                else
                {
                    person[ind] = person[i];
                    fout << person[ind].fname << " " << person[ind].sname << " " << person[ind].accountId << " " << person[ind].accountType << " " << person[ind].balance << " " << person[ind].loan << " " << person[ind].pin << endl;
                    ind++;
                }
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
    update_file(person, n);
    read_file(&person, n, accNumChk);
}

// for management login
bool admin_login()
{
    string pass;
    g_xy(42, 13);
    cout << "Pass" << endl;
    g_xy(48, 12);
    line(23);
    g_xy(48, 13);
    cout << setw(23) << left << "|"
         << "|" << endl;
    g_xy(48, 14);
    line(23);
    g_xy(57, 13);
    getline(cin, pass);
    if (pass == "admin")
    {
        color(10);
        g_xy(52, 19);
        cout << "Login Successful" << endl;
        g_xy(55, 21);
        cout << "Please Wait" << endl;

        for (int i = 0; i < 5; i++)
        {
            g_xy(58 + i, 23);
            cout << "*";
            Sleep(400);
        }

        color(15);
        return true;
    }
    else
    {
        color(12);
        g_xy(54, 19);
        cout << "Login Failed" << endl;
        g_xy(55, 21);
        cout << "Going Back" << endl;
        for (int i = 0; i < 5; i++)
        {
            g_xy(58 + i, 23);
            cout << "*";
            Sleep(400);
        }
        color(15);
        return false;
    }
}

//=======Admin Functions=========//

//======Menu Functions=======//

// main menu
int main_menu(Person *person, int *n)
{
    cin.clear();
    int opt = -1;
    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << "  Customer Menu "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << " Managments Menu "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << "       QUIT "
         << "|" << endl;
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    opt = selection(4);
    return opt;
}

// customer menu
int customer_menu(Person *person, int *n)
{
    cin.clear();
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

    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    if (opt == 2)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << " Withdraw Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << " Withdraw Money"
             << "|" << endl;
    }

    if (opt == 3)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "   Send Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "   Send Money"
             << "|" << endl;
    }
    if (opt == 4)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "   Change Pin"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "   Change Pin"
             << "|" << endl;
    }

    if (opt == 5)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "    Get Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "    Get Loan"
             << "|" << endl;
    }
    if (opt == 6)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << "    Pay Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << "    Pay Loan"
             << "|" << endl;
    }
    if (opt == 7)
    {
        color(10);
        cout << setw(50) << left << ">"
             << setw(69) << left << " Show Statement"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|"
             << setw(69) << left << " Show Statement"
             << "|" << endl;
    }

    cout << setw(50) << left << "|"
         << setw(69) << left << "    Go Back"
         << "|" << endl;

    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    color(15);
    cout << setw(40) << left << "|" << person[id].fname << "\t" << person[id].sname << "\t" << person[id].accountId << "\t" << person[id].accountType << "\t" << person[id].balance << "\t" << person[id].loan << setw(32) << left << "\t"
         << "|" << endl;

    line(119);
    if (opt == -1 && flip == 0)
    {
        opt = selection(8);
        goto label1;
    }
    return opt;
}

// management menu
int management_menu(Person *person, int *n)
{
    cin.clear();
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

    line(119);
    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    if (opt == 2)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "  Add Accounts"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "  Add Accounts"
             << "|" << endl;
    }

    if (opt == 3)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << " Modify Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << " Modify Account"
             << "|" << endl;
    }
    if (opt == 4)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << " Delete Account"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << " Delete Account"
             << "|" << endl;
    }
    if (opt == 5)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "   Add Money"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "   Add Money"
             << "|" << endl;
    }

    if (opt == 6)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "   Alot Loan"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "   Alot Loan"
             << "|" << endl;
    }
    if (opt == 7)
    {
        color(10);
        cout << setw(50) << left << ">" << setw(69) << left << "Account Database"
             << "<" << endl;
        color(15);
    }
    else
    {
        cout << setw(50) << left << "|" << setw(69) << left << "Account Database"
             << "|" << endl;
    }

    cout << setw(50) << left << "|" << setw(69) << left << "    Go Back"
         << "|" << endl;

    cout << setw(50) << left << "|" << setw(69) << left << ""
         << "|" << endl;
    line(119);
    color(15);
    if (opt == -1 && flip == 0)
    {
        opt = selection(8);
        goto label1;
    }
    return opt;
}

//======Menu Functions=======//

//======Misc Functions=======//

// account id check
int id_chk(Person *person, int *n, int t_id)
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

// for scrolling selection
int selection(int yxis)
{
    unsigned int pos = 1, y = 1;
    g_xy(69, 1);
    char c;
    while (true)
    {
        color(12);
        system("pause>nul");

        if (GetAsyncKeyState(VK_DOWN) && y <= yxis)
        {
            g_xy(70, y);

            cout << "    ";
            g_xy(43, y);

            cout << "    ";
            y++;
            g_xy(70, y);
            cout << "<===";
            g_xy(43, y);
            cout << "===>";
            pos++;
            continue;
        }
        if (GetAsyncKeyState(VK_UP) && y > 1)
        {

            g_xy(70, y);
            cout << "    ";
            g_xy(43, y);
            cout << "    ";
            y--;
            g_xy(70, y);
            cout << "<===";
            g_xy(43, y);
            cout << "===>";
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

void color(int n)
{
    SetConsoleTextAttribute(console, n);
}

// For Cursor Location
void g_xy(int x, int y)
{
    COORD cp;
    cp.X = x;
    cp.Y = y;
    SetConsoleCursorPosition(console, cp);
}

// For printing line
void line(int num)
{
    for (int i = 0; i <= num; i++)
    {
        cout << "=";
    }
    cout << endl;
}

// check the number of customers in the database
void siz(int *n)
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
    chk--;
    *n = chk;
}

// checks the customers Account Type
int accTypeChk(Person *person)
{
    string type;
    type = (person[id].accountType);
    long long int max_amm;
    if ((strcmpi(type.c_str(), "platinum")) == 0)
    {
        max_amm = 10000000;
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

//======Misc Functions=======//
