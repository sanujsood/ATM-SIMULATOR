#ifndef TRANSACTION_H_INCLUDED
#define TRANSACTION_H_INCLUDED

#include "DB.h"

class Transactions
{
    public:
    bool add_transaction(double amount , double balance,string account_no,string particular,int f);
    void display_transactions(string account_no);
};



void sideLine(int k)
{
    for(int i=9;i<=20;i++)
    {
        gotoxy(k,i);
        cout<<"|";
    }
}

void layoutForTransactions()
{
    border();
    for(int i=8;i<=20;i+=2)
    {
        gotoxy(17,i);
        for(int j=0;j<78;j++)
            cout<<"_";
    }
    sideLine(16);
    sideLine(19);
    sideLine(39);
    sideLine(62);
    sideLine(73);
    sideLine(84);
    sideLine(95);
    gotoxy(43,5);
    cout<<"||| LAST 5 TRANSACTIONS |||";

    gotoxy(25,9);
    cout<<"Date,Time";
    gotoxy(46,9);
    cout<<"Particulars";
    gotoxy(66,9);
    cout<<"Debit";
    gotoxy(76,9);
    cout<<"Credit";
    gotoxy(87,9);
    cout<<"Balance";

    int sno = 1;
    for(int i=11;i<=19;i+=2)
    {
        gotoxy(17,i);
        cout<<sno++<<".";
    }

}

bool Transactions::add_transaction(double amount , double balance,string account_no,string particular,int f)
{
    MYSQL *conn1;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn1 = mysql_init(0);
    conn1 =mysql_real_connect(conn1,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    bool isSuccess = false;
    if (conn1)
    {
        int qstate;
        if(f==0)
        {
            if(particular=="Self cash withdrawal")
            {
                stringstream sw;
                sw<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',"<<amount<<",0,"<<balance<<");";
                string query1 = sw.str();
                const char *q = query1.c_str();
                qstate = mysql_query(conn1, q);
                if (qstate == 0)
                    isSuccess = true;
            }
            if(particular=="Self cash deposit")
            {
                stringstream sd;
                sd<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',0,"<<amount<<","<<balance<<");";
                string query2 = sd.str();
                const char *q = query2.c_str();
                qstate = mysql_query(conn1, q);
                if (qstate == 0)
                    isSuccess = true;
            }
        }

        else if(f==1)
        {
            stringstream sft;
            sft<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',"<<amount<<",0,"<<balance<<");";
            string query1 = sft.str();
            const char *q = query1.c_str();
            qstate = mysql_query(conn1, q);
            if (qstate == 0)
                isSuccess = true;
        }

        else if(f==2)
        {
            stringstream sft1;
            sft1<<"INSERT into transactions values('"<<account_no<<"',ADDTIME(sysdate(), '5:30'),'"<<particular<<"',0,"<<amount<<","<<balance<<");";
            string query1 = sft1.str();
            const char *q = query1.c_str();
            qstate = mysql_query(conn1, q);
            if (qstate == 0)
                isSuccess = true;
        }
    }

    mysql_close(conn1);

    return isSuccess;
}


void Transactions::display_transactions(string account_no)
{
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    if (conn)
    {
        stringstream ss;
        ss << "SELECT * from transactions where account_no =  '" << account_no << "' order by date_time desc limit 5";
        string query = ss.str();
        const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            layoutForTransactions();
            res = mysql_store_result(conn);
            gotoxy(47,7);
            cout<<"Account Number : "<< account_no;
            int index = 11;
            while (row = mysql_fetch_row(res))
            {
                gotoxy(20,index);
                cout<<row[1];
                gotoxy(40,index);
                cout<<row[2];
                gotoxy(64,index);
                cout<<row[3];
                gotoxy(75,index);
                cout<<row[4];
                gotoxy(86,index);
                cout<<row[5];
                index+=2;
            }
            gotoxy(40,24);
            cout<<"Press any key to go back...";
            cin.get();
        }
    }
    mysql_close(conn);
}


#endif // TRANSACTION_H_INCLUDED
