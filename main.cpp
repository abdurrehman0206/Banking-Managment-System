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
            break;
        case 2:
            loop_control = true;
            chk = login(person, &n, &id);
            cin.clear();
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
                        break;
                    case 2:
                        withdraw(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 3:
                        send(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 4:
                        change_pin(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 5:
                        get_loan(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 6:
                        pay_loan(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 7:
                        print_statement(person, &n);
                        system("pause>nul");
                        system("CLS");
                        break;
                    case 8:
                        loop_control = false;
                        cin.clear();
                        system("CLS");
                        break;
                    }

                } while (loop_control == true);
            }
            loop_control = true;
            break;

        case 3:
            loop_control = true;
            chk = admin_login();
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
                    case 2:
                        add_acc(&person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 3:
                        modify_acc(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 4:
                        delete_acc(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 5:
                        add_money(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 6:
                        alot_loan(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 7:
                        o_data(person, &n);
                        system("pause");
                        system("CLS");
                        break;
                    case 8:
                        loop_control = false;
                        cin.clear();
                        system("CLS");
                        break;
                    }

                } while (loop_control == true);
            }
            loop_control = true;
            break;
        case 4:
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