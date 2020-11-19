#ifndef DATABASE_H
#define DATABASE_H

#include <winsock.h>  //mandatory to include else will show error in bacnkend libraries also must include above mysql.h
#include <mysql.h>
#include <string>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "border.h"


map<string, string> find_details(string account_no)
{
    string dummy;
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    map<string, string> details;
    if (conn)
    {
        stringstream ss;
        stringstream ss1;

        ss << "select * from accounts where account_no =  '" << account_no << "'";
        string query = ss.str();
        const char *q = query.c_str();
        int qstate = mysql_query(conn, q);
        if (!qstate)
        {
            res = mysql_store_result(conn);
            while (row = mysql_fetch_row(res))
            {    ss1<<row[4];
                  string abc=ss1.str();
                details["account_no"] = row[0];
				details["first_name"] = row[1];
				details["last_name"] = row[2];
                details["pin"] = row[3];
                details["balance"] = abc;
                details["mobile"] = row[5];
                details["email"] = row[6];
                mysql_close(conn);
                return details;
            }
        }
        else
        {
            mysql_close(conn);
            return details;
        }
    }

    mysql_close(conn);
}

bool update(map<string, string> user)
{
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    conn = mysql_init(0);
    conn =mysql_real_connect(conn,"remotemysql.com","7ylda3PEbQ","9jxeBjXw5c","7ylda3PEbQ",3306,NULL,0);
    if (conn)
    {
        int qstate;
        stringstream ss;
        stringstream bal;
        ss << "UPDATE accounts SET pin = '" << user["pin"] << "', balance= '" << user["balance"] << "'  ,  mobile= '" << user["mobile"] << "' WHERE account_no= '" << user["account_no"] << "'";
        string query = ss.str();
        const char *q = query.c_str();
        qstate = mysql_query(conn, q);
        mysql_close(conn);
        if (qstate == 0)
            return true;
        else
            return false;
    }
    mysql_close(conn);
}

#endif

