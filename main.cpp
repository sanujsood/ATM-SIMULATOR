
#include "ATM.h"
#include <Windows.h>

void firstPage()
{
    	border();
	gotoxy(30,6);
	cout<<"DR. B.R AMBEDKAR NATIONAL INSTITUTE OF TECHNOLOGY";
	gotoxy(48,9);
	cout<<"OOPS PROJECT";
	gotoxy(43,12);
	cout<<"WELCOME TO OUR PROJECT";
	gotoxy(39,14);
	cout<<" TOPIC- ATM MANAGEMENT SYSTEM";
	gotoxy(37,18);
	cout<<"MADE BY : ";
	gotoxy(52,17);
	cout<<"KESHAV VARSHNEY";
	gotoxy(52,18);
	cout<<"RAHUL ARORA";
	gotoxy(52,19);
	cout<<"SANUJ SOOD";
	gotoxy(37,25);
	cout<<"PRESS ANY KEY TO CONTINUE..";
	cin.get();

}

void secondPage()
{
    border();
    gotoxy(35,9);
    cout << "=========================================";
    gotoxy(43,13);
    cout << "||   WELCOME TO  ATM   ||" ;
    gotoxy(35,17);
    cout << "=========================================" ;
    gotoxy(37,25);
	cout<<"PRESS ANY KEY TO CONTINUE..";
	cin.get();
}

int main()
{
    system("color B0");
    firstPage();
    secondPage();
    ATM atm;
    if(atm.acc.count<=5 && atm.acc.PIN_SET)
    {
        bool again=true;
    	do
    	{
			border();
			gotoxy(48,5);
			cout<<"....ATM MENU....";
			gotoxy(30,8);
			cout<<"1. Deposit";
			gotoxy(63,8);
			cout<<"2. Cash Withdrawl";
			gotoxy(30,10);
			cout<<"3. Balance Enquiry";
			gotoxy(63,10);
			cout<<"4. Fund Transfer";
			gotoxy(30,12);
			cout<<"5. Last 5 Transactions";
			gotoxy(63,12);
			cout<<"6. Account Details";
			gotoxy(30,14);
			cout<<"7. Change Mobile No.";
			gotoxy(63,14);
			cout<<"8. Change your ATM Pin";
			gotoxy(53,16);
			cout<<"9. Exit";
			int ch;
			gotoxy(40,19);
			cout<<"Enter Your Choice : ";
			cin>>ch;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch(ch)
			{
				case 1: atm.acc.deposit();
					break;
				case 2: atm.acc.withdraw();
					break;
				case 3: atm.acc.display_balance();
					break;
				case 4: atm.acc.fund_transfer();
					break;
				case 5: atm.acc.display_statement();
					break;
				case 6: atm.acc.display_details();
					break;
				case 7: atm.acc.change_mobile_no();
					break;
				case 8: atm.acc.change_pin();
					break;
				case 9: again=false;
					break;
				default : gotoxy(40,20);
					  cout<<"...You Entered Wrong Choice...";
					  gotoxy(37,21);
					  cout<<"Please Enter your Choice Again..";
					  Sleep(1000);
			}

		}while(again);
    }
    return 0;
}

