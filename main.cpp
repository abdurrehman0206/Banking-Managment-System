#include "functions.h"


int main(){
    // using main for only testing
    //main is hardcoded for now
    read_file(&person, &n);
    id_assign(accNumChk);
    
    //i_data(&person, &n);
    o_data(person, &n);
    login(person, &n , &id);
    change_pin(person, &n);
    withdraw(person, &n);
    send(person, &n);
    modify_acc(person, &n);
    o_data(person, &n);
    
    system("pause");
    return 0;
}