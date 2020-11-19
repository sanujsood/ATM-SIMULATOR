#ifndef DIALOG_H
#define DIALOG_H
#include<windows.h>


void WINAPI Account_Blocked(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,bool isUpdated)
{
    if(isUpdated)
    MessageBox(NULL, "Your account has been blocked due to security reasons!", "Account Blocked", MB_OK);
    else
    MessageBox(NULL, "Sorry! There is error in ATM Machine", "ATM Problem", MB_OK);
}
void WINAPI Transaction(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,bool isSuccess,char message[])
{
    if(isSuccess)
    MessageBox(NULL,(const char*)message, "Transaction Detail", MB_OK);
    else
        MessageBox(NULL, "OOPS! Transaction failed. Please try again", "Transaction Detail", MB_OK);
}
void WINAPI Transaction_fund_transfer(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,bool Success1,bool Success2,char message[])
{
    if(Success1 && Success2)
    MessageBox(NULL, (const char*)message, "Transaction Detail", MB_OK);
    else
        MessageBox(NULL, "OOPS! Transaction failed.", "Transaction Detail", MB_OK);
}
void WINAPI Changes(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow,char message[])
{
    MessageBox(NULL,(const char*)message, "Updation Detail", MB_OK);
}
void WINAPI Confirmation(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL,"Both Entered PINs didn't match. Try Again", "PIN Settings", MB_OK);
}
void WINAPI WRONG_OTP(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL,"You entered wrong OTP. Try Again", "OTP Status", MB_OK);
}

#endif
