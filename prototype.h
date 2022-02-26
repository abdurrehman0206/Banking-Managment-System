#include "data.h"

// PROTOTYPE

//=====Customer Fucntions=====//
void withdraw(Person *person, int *n);
void send(Person *person, int *n);
void get_loan(Person *person, int *n);
void pay_loan(Person *person, int *n);
void change_pin(Person *person, int *n);
void print_statement(Person *person, int *n);
bool login(Person *person, int *n, int *id);
//=====Customer Fucntions=====//

//======Admin Fucntions======//
void add_acc(Person **person, int *n);
void o_data(Person *person, int *n);
void add_money(Person *person, int *n);
void alot_loan(Person *person, int *n);
bool admin_login();
//======Admin Fucntions======//

//======Menu Functions=======//
int main_menu(Person *person, int *n);
int customer_menu(Person *person, int *n);
int management_menu(Person *person, int *n);
//======Menu Functions=======//

//======Real Time Updating=====//
void siz(int *n);
void read_file(Person **person, int *n, int &accNumChk);
void update_file(Person *person, int *n);
//======Real Time Updating=====//

//======Misc Functions=======//
void line(int);
void color(int n);
void g_xy(int x, int y);
void siz(int *n);
int accTypeChk(Person *person);
int selection(int);
int id_chk(Person *person, int *n, int t_id);
//======Misc Functions=======//

// PROTOTYPE