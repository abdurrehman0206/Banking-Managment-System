#include "data.h"

// PROTOTYPE

//=====Customer Fucntions=====//
void withdraw(Person *person, short *n);
void send(Person *person, short *n);
void get_loan(Person *person, short *n);
void pay_loan(Person *person, short *n);
void change_pin(Person *person, short *n);
void print_statement(Person *person, short *n);
bool login(Person *person, short *n, int *id);
//=====Customer Fucntions=====//

//======Admin Fucntions======//
void i_data(Person **person, short *n);
void o_data(Person *person, short *n);
void add_money(Person *person, short *n);
void alot_loan(Person *person, short *n);
bool admin_login();
//======Admin Fucntions======//

//======Menu Functions=======//
int main_menu(Person *person, short *n);
int customer_menu(Person *person, short *n);
int management_menu(Person *person, short *n);
//======Menu Functions=======//

//======Real Time Updating=====//
void siz(short *n);
void read_file(Person **person, short *n, int &accNumChk);
void update_file(Person *person, short *n);
//======Real Time Updating=====//

//======Misc Functions=======//
void line(int);
void color(int n);
void g_xy(int x, int y);
void siz(short *n);
int accTypeChk(Person *person);
int selection(int);
int id_chk(Person *person, short *n, int t_id);
//======Misc Functions=======//

// PROTOTYPE