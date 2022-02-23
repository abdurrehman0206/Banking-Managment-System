#include "functions.h"

int main()
{

    read_file(&person, &n, accNumChk);

    int opt, main_opt;
    char yn;
    bool chk;
    bool loop_control = true;
    do
    {
        system("CLS");
        main_opt = main_menu(person, &n);
        system("CLS");
        switch (main_opt)
        {
        default:
            system("CLS");
            break;
        case 1:
            loop_control = true;
            chk = login(person, &n, &id);
            cin.ignore();
            if (chk == true)
            {
                do
                {
                    opt = customer_menu(person, &n);
                    cout << endl
                         << endl;

                    switch (opt)
                    {
                    default:
                        system("CLS");
                        break;
                    case 8:
                        cout << "Are you sure you want to QUIT![y|Y] :: ";
                        cin >> yn;
                        if (yn == 'y' || yn == 'Y')
                        {
                            exit(0);
                        }
                        break;
                    case 1:
                        withdraw(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 2:
                        send(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 3:
                        change_pin(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 4:
                        get_loan(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 5:
                        pay_loan(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 6:
                        print_statement(person, &n);
                        system("pause");
                        system("CLS");                        
                        break;
                    case 7:
                        loop_control = false;
                        system("pause");
                        system("CLS");
                        break;
                    }

                } while (loop_control == true);
            }
            loop_control = true;
            cin.ignore();
            break;

        case 2:
            loop_control = true;
            chk = admin_login();
            // cin.ignore();
            if (chk == true)
            {
                do
                {
                    opt = management_menu(person, &n);
                    cout << endl
                         << endl;

                    switch (opt)
                    {
                    default:
                        system("CLS");
                        break;
                    case 8:
                        cout << "Are you sure you want to QUIT![y|Y] :: ";
                        cin >> yn;
                        if (yn == 'y' || yn == 'Y')
                        {
                            exit(0);
                        }
                        break;
                    case 1:
                        i_data(&person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 2:
                        modify_acc(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 3:
                        delete_acc(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 4:
                        add_money(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 5:
                        alot_loan(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 6:
                        o_data(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 7:
                        loop_control = false;
                        system("pause");
                        system("CLS");
                        break;
                    }

                } while (loop_control == true);
            }
            loop_control = true;
            break;
        case 3:
            cout << "Are you sure you want to QUIT![y|Y] :: ";
            cin >> yn;
            if (yn == 'y' || yn == 'Y')
            {
                exit(0);
            }
            break;
        }

    } while (true);

    system("pause");
    return 0;
}