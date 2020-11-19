#ifndef ATM_H
#define ATM_H
#include "Accountholder.h"

class ATM{
public:
    Accountholder acc;
    ATM();
};

ATM :: ATM()
{
    border();
    string entered_account_no, entered_pin;
    gotoxy(35,8);
    cout << "Enter your correct Account no : ";
    cin >> entered_account_no;
    gotoxy(0,24);
    acc.customer  = find_details(entered_account_no);
    acc.account_no= acc.customer["account_no"];
    acc.first_name= acc.customer["first_name"];
    acc.last_name= acc.customer["last_name"];
    acc.pin= acc.customer["pin"];
    acc.balance=stof(acc.customer["balance"]);
    acc.mobile= acc.customer["mobile"];
    acc.email= acc.customer["email"];

    if(acc.pin=="-1")
    {
        acc.PIN_SET=false;
        border();
        string otp,entered_otp,entered_pin1;
        gotoxy(40,10);
        cout<<"Your Pin has not been set.";
        otp=send_otp(acc.email);
        gotoxy(30,12);
        cout<<"Please verify that it's you by entering the OTP";
        gotoxy(37,13);
        cout<<"sent on your registered email id.";
        gotoxy(44,15);
        cout<<"ENTER OTP : ";
        cin>>entered_otp;
        if(otp==entered_otp)
        {
            acc.PIN_SET=true;
            string confirm="do";
        while(entered_pin1!=confirm)
        {
            border();
            gotoxy(34,10);
            cout << "Enter your PIN : ";
            cin >> entered_pin1;
            while (entered_pin1.length() != 4)
            {
                border();
                gotoxy(36,9);
                cout << "Incorrect  (choose a pin of 4 digits) ";
                gotoxy(44,13);
                cout << "Enter valid PIN : ";
                cin >> entered_pin1;
            }
            gotoxy(34,13);
            cout<<"Enter your PIN again for confirmation : ";
            cin>>confirm;
            if(entered_pin1!=confirm)
            {
                HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           Confirmation(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
            }
        }
            acc.pin=entered_pin1;
            gotoxy(36,19);
            cout<<"....PIN SET SUCCESSFULLY!!....";
            Sleep(1000);
        }
        else
        {
            gotoxy(47,25);
        }
    }
    else
    {
        gotoxy(40,12);

        cout << "Enter PIN : ";
        cin >> entered_pin;
        Sleep(500);
        while (acc.count<=5 && acc.pin!= entered_pin)
        {
            acc.count++;
            border();
            gotoxy(40,12);
            cout << "Enter correct PIN : ";
            cin >>entered_pin;
        }
    }
}



#endif 
