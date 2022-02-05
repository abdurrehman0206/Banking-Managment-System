#include "functions.h"

int main()
{
    read_file(&person, &n);
    id_assign(accNumChk);
    int opt, main_opt;
    char yn;
    bool chk;
    bool loop_control = true;
    main_opt = main_menu(person, &n);
    system("CLS");
    switch (main_opt)
    {
    default:
        system("CLS");
        break;
    case 1:
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
                case 6:
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
                    system("pause");
                    system("CLS");
                    break;
                case 5:
                    loop_control = false;
                    system("pause");
                    system("CLS");
                    break;
                }

            } while (loop_control == true);
        }
        system("pause");
        system("CLS");
        break;

    case 2:
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

    system("pause");
    return 0;
}