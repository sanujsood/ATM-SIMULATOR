#ifndef ACOUNTHOLDER_H
#define ACCOUNTHOLDER_H

#include <limits>
#include "Transaction.h"
#include "email.h"
#include "dialog.h"

class ATM;
class Accountholder
{
       Transactions txn;
       string first_name,last_name,email;
       double balance;
       string mobile;
	   string  pin;
       string account_no;
	   map<string,string> customer;
       friend class ATM;
       public:
       bool PIN_SET=true;
       int count=1;
       void withdraw();
       void deposit();
       void change_mobile_no() ;
       void change_pin() ;
       void display_balance() const;
       void display_details() const;
       void fund_transfer();
       void display_statement();
       void printReceipt(float amount,int x);
       ~Accountholder();
};

void Accountholder::deposit()
{
    border();
    float amt_deposit;
    gotoxy(38,12);
    cout << "Enter amount to be deposited : ";
    cin >> amt_deposit;
    while (amt_deposit < 100 || amt_deposit > 20000)
    {
        border();
        gotoxy(30,12);
        cout << "You can only deposit amount between Rs. 100 and Rs. 20000";
        gotoxy(44,14);
        cout << "Enter correct Amount : ";
        cin >> amt_deposit;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    balance=balance+amt_deposit;
    Sleep(1000);
    string pr="Self cash deposit";
    bool isSuccess = txn.add_transaction(amt_deposit,balance,account_no,pr,0);
    HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           stringstream st;
           st<<amt_deposit;
           string am=st.str();
           string message="Congratulations! Amount Rs."+am+" has been deposited to account_no "+account_no;
           int n=message.length();
           char array1[n+1];
           strcpy(array1,message.c_str());
     Transaction(hInstance,hPrevInstance,lpCmdLine,nCmdShow,isSuccess,array1);
     if(!isSuccess)
     {
         return;
     }
    gotoxy(34,19);
    cout<<"(PRESS Y or y for YES and any other key for NO)";
    gotoxy(38,18);
    cout<<"Do you want the RECEIPT of TRANSACTION ";
    char ch;
    cin>>ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(ch=='Y' || ch == 'y')
    {
        border();
        printReceipt(amt_deposit,1);
    }

}

void Accountholder::withdraw()
{
    border();
    float amt_withdraw;
    gotoxy(38,12);
    cout << "Enter amount to be withdrawn : ";
    cin >> amt_withdraw;
    while (balance < amt_withdraw)
    {
        border();
        gotoxy(38,12);
        cout << "....You don't have sufficient funds....";
        gotoxy(44,14);
        cout << "Enter correct amount : ";
        cin >> amt_withdraw;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    balance=balance-amt_withdraw;
    Sleep(1000);
    string pr="Self cash withdrawal";
    bool isSuccess = txn.add_transaction(amt_withdraw,balance,account_no,pr,0);
     HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
          stringstream st;
          st<<amt_withdraw;
           string am=st.str();
           string message="Congratulations! Amount Rs."+am+" has been withdrawn from account_no "+ account_no;
           int n=message.length();
           char array1[n+1];
           strcpy(array1,message.c_str());
     Transaction(hInstance,hPrevInstance,lpCmdLine,nCmdShow,isSuccess,array1);
     if(!isSuccess)
     {
         return;
     }
    gotoxy(34,19);
    cout<<"(PRESS Y or y for YES and any other key for NO)";
    gotoxy(38,18);
    cout<<"Do you want the RECEIPT of TRANSACTION ";
    char ch;
    cin>>ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(ch=='Y' || ch == 'y')
    {
        border();
        printReceipt(amt_withdraw,0);
    }

}



void Accountholder::fund_transfer()
{
    border();
    double to_be_transferred;
    string entered_account_no, entered_pin;
    gotoxy(37,10);
    cout << "Enter Amount to be transferred : ";
    cin >> to_be_transferred;
    while (balance < to_be_transferred)
    {
        border();
        gotoxy(38,10);
        cout << "....You don't have sufficient funds....";
        gotoxy(44,12);
        cout << "Enter correct Amount : ";
        cin >> to_be_transferred;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    balance=balance-to_be_transferred;
    gotoxy(30,14);
    cout << "Enter correct Account no. of account receiving funds : ";
    cin >> entered_account_no;
    map<string,string> receiver=find_details(entered_account_no);
    double newbalance=stof(receiver["balance"])+to_be_transferred;
    stringstream ss2;
    ss2<<newbalance;
    string bala=ss2.str();
    receiver["balance"]=bala;
    update(receiver);
    string pr="Fund Transfer to "+entered_account_no;
    string pr1="Fund Transfer from "+account_no;
    bool isSuccess1 = txn.add_transaction(to_be_transferred,balance,account_no,pr,1);
    bool isSuccess2 = txn.add_transaction(to_be_transferred,newbalance,entered_account_no,pr1,2);
    HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           stringstream s1;
           s1<<to_be_transferred;
           string amount=s1.str();
           string s="Congratulations! Amount Rs"+amount+" has been transferred from Account no."+account_no+" to Account no."+entered_account_no;
           char array[s.length()+1];
           strcpy(array,s.c_str());
     Transaction_fund_transfer(hInstance,hPrevInstance,lpCmdLine,nCmdShow,isSuccess1,isSuccess2,array);
    if(!isSuccess1 || !isSuccess2)
    {
        return;
    }
    gotoxy(33,19);
    cout<<"(PRESS Y or y for YES and any other key for NO)";
    gotoxy(36,18);
    cout<<"Do you want the RECEIPT of TRANSACTION ";
    char ch;
    cin>>ch;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(ch=='Y' || ch == 'y')
    {
        border();
        gotoxy(65,17);
        cout<<entered_account_no;
        printReceipt(to_be_transferred,2);
    }

}


void Accountholder::display_details() const
{
    border();
    gotoxy(45,5);
    cout<<"****ACCOUNT DETAILS****";
    gotoxy(37,9);
	cout << "Account Number";
	gotoxy(56,9);
	cout <<":";
	gotoxy(62,9);
	cout <<account_no;
    gotoxy(37,11);
    cout << "Name";
    gotoxy(56,11);
    cout <<":";
    gotoxy(62,11);
    cout << first_name<<" "<<last_name;
    gotoxy(37,13);
    cout << "Mobile_Number";
    gotoxy(56,13);
    cout << ":";
    gotoxy(62,13);
    cout << mobile;
    gotoxy(37,15);
    cout << "Email";
    gotoxy(56,15);
    cout << ":";
    gotoxy(62,15);
    cout << email;
    gotoxy(42,18);
    cout<<"Press any key to go back...";
    cin.get();

}

void Accountholder::display_balance() const
{
    border();
    gotoxy(45,7);
    cout<<"****ACCOUNT BALANCE****";
    gotoxy(37,12);
    cout << "Your Balance is";
    gotoxy(56,12);
    cout<<":";
    gotoxy(62,12);
    cout<<balance;
    gotoxy(42,18);
	cout<<"Press any key to go back...";
    cin.get();

}

void Accountholder::change_mobile_no()
{
    border();
    gotoxy(38,6);
    cout<<"You chose changing mobile number.";
    string entered_otp;
    string otp=send_otp(email);
    gotoxy(30,11);
    cout<<"Please verify that it's you by entering the OTP";
    gotoxy(37,12);
    cout<<"sent on your registered email id.";
    gotoxy(44,14);
    cout<<"ENTER OTP : ";
    cin>>entered_otp;
    Sleep(1000);
    if(otp==entered_otp)
    {
        string entered_mn;
        gotoxy(35,16);
        cout << "Enter new mobile number : ";
        cin >> entered_mn;
        while (entered_mn.length() != 10)
        {
            border();
            gotoxy(36,9);
            cout << "Incorrect Number (must be of 10 digits) ";
            gotoxy(34,13);
            cout << "Enter correct mobile number : ";
            cin >> entered_mn;
        }
        string prev_mobile=mobile;
        mobile=entered_mn;
        HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           string message="Congratulations! Mobile number of Account number "+account_no+" changed from "+prev_mobile+" to "+entered_mn;
           char array[message.length()+1];
           strcpy(array,message.c_str());
        Changes(hInstance,hPrevInstance,lpCmdLine,nCmdShow,array);
        cin.get();
    }
    else
    {
        gotoxy(37,18);
        cout<<"Wrong OTP. Please try again later.";
        cin.get();
    }
    gotoxy(42,21);
    cout<<"Press any key to go back...";
    cin.get();
}

void Accountholder::change_pin()
{
    border();
    gotoxy(43,6);
    cout<<"You chose changing PIN";
    string entered_otp;
    string otp=send_otp(email);
    gotoxy(30,11);
    cout<<"Please verify that it's you by entering the OTP";
    gotoxy(37,12);
    cout<<"sent on your registered email id.";
    gotoxy(44,14);
    cout<<"ENTER OTP : ";
    cin>>entered_otp;
    Sleep(1000);
    if(otp==entered_otp)
    {
        string entered_newpin;
        gotoxy(40,16);
        cout << "Enter new PIN : ";
        cin >> entered_newpin;
        while (entered_newpin.length() != 4)
        {
            border();
            gotoxy(36,9);
            cout << "Incorrect PIN (must be of 4 digits) ";
            gotoxy(40,13);
            cout << "Enter a valid PIN : ";
            cin >> entered_newpin;
        }
        string prev_pin=pin;
        pin=entered_newpin;
        HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           string message="Congratulations! PIN of Account number "+account_no+" changed from "+prev_pin+" to "+entered_newpin;
           char array[message.length()+1];
           strcpy(array,message.c_str());
        Changes(hInstance,hPrevInstance,lpCmdLine,nCmdShow,array);
        cin.get();
    }
    else
    {
        gotoxy(37,18);
        cout<<"Wrong OTP. Please try again later.";
        cin.get();
    }
    gotoxy(40,21);
    cout<<"Press any key to go back...";
    cin.get();
}

void printing()
{
    border();
    gotoxy(43,12);
    cout<<".....PLEASE WAIT.....";
    gotoxy(40,14);
    cout<<"PRINTING......";
    gotoxy(40,16);
    cout<<"0                    100";
    gotoxy(41,16);
    for(int i=0;i<20;i++)
    {
        cout<<"#";
        Sleep(200);
    }

    gotoxy(40,18);
    cout<<"....PRINT SUCCESSFUL....";
    gotoxy(37,20);
    cout<<"PRESS ANY KEY TO RETURN TO MAIN MENU...";
    cin.get();
}

void Accountholder::printReceipt(float amount,int x)
{
    gotoxy(45,4);
    cout<<"STATE BANK OF INDIA";
    gotoxy(20,5);
    time_t ttime = time(0);
    char *dt = ctime(&ttime);
    cout<<"Date and Time : ";
    gotoxy(65,5);
    cout<<"ATM ID";
    gotoxy(20,6);
    cout<<dt;
    gotoxy(65,6);
    cout<<"E006773";
    gotoxy(20,8);
    cout<<"CARD NUMBER ";
    gotoxy(65,8);
    srand(time(nullptr));
    cout<<"XXXX XXXX XXXX "<<(rand()%8999 + 1000);
    gotoxy(20,10);
    cout<<"TXN NO.";
    gotoxy(65,10);
    cout<<(rand()%8999 + 1000);
    gotoxy(20,12);
    cout<<"RESPONSE CODE";
    gotoxy(65,12);
    cout<<"000";
    gotoxy(20,14);
    if(x==0) cout<<"WITHDRAWL";
    else if(x==1) cout<<"DEPOSIT";
    else cout<<"TRANSFERRED";
    gotoxy(60,14);
    cout<<"RS.";
    gotoxy(65,14);
    cout<<amount;
    gotoxy(20,16);
    cout<<"FROM A/C";
    gotoxy(65,16);
    cout<<account_no;
    if(x==2)
    {
        gotoxy(20,17);
        cout<<"TO A/C";
    }
    gotoxy(20,18);
    cout<<"MOD BAL";
    gotoxy(60,18);
    cout<<"RS.";
    gotoxy(65,18);
    cout<<"0.00";
    gotoxy(20,20);
    cout<<"AVAIL BAL";
    gotoxy(60,20);
    cout<<"RS.";
    gotoxy(65,20);
    cout<<balance;
    gotoxy(40,22);
    cout<<"Visit us at www.sbi.co.in";

    gotoxy(40,25);
    cout<<"PRESS ANY KEY TO START PRINTING...";
    cin.get();
    printing();
}


void Accountholder::display_statement()
{
    border();
    gotoxy(45,13);
    cout<<"....PLEASE WAIT....";
    txn.display_transactions(account_no);
}

Accountholder::~Accountholder()
{
    if(count<=5 && PIN_SET)
    {
         border();
        stringstream ss2;
    ss2<<balance;
    string bala=ss2.str();
    customer["pin"]=pin;
    customer["balance"]=bala;
    customer["mobile"]=mobile;
    bool isUpdated = update(customer);
    if(isUpdated)
    {
        gotoxy(46,12);
        cout<<"****THANK YOU*****";
        gotoxy(32,15);
        cout<<"Your Changes have been Updated in our DATABASE";
    }
    else
    {
        gotoxy(47,12);
        cout<<"Record UPDATION FAILED";
    }
    }
    else if(count>5)
    {
         gotoxy(30,12);
        customer["pin"]="-1";
        bool isUpdated = update(customer);
           HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
           Account_Blocked(hInstance,hPrevInstance,lpCmdLine,nCmdShow,isUpdated);
    }
    else
    {
            HINSTANCE hInstance;
           HINSTANCE hPrevInstance;
           LPSTR lpCmdLine;
           int nCmdShow;
            WRONG_OTP(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
    }
    gotoxy(47,24);
}

#endif
