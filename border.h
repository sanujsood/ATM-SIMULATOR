#ifndef BORDER_H_INCLUDED
#define BORDER_H_INCLUDED

#include <windows.h>
#include<iostream>

using namespace std;

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void border()
{
    system("cls");
    int i;
	for(i=15;i<97;i++)
	{
	    gotoxy(i,3);
	    cout<<"*";
	}
	for(i=15;i<97;i++)
	{
	    gotoxy(i,23);
	    cout<<"*";
	}
	for(i=4;i<23;i++)
	{
	    gotoxy(15,i);
	    cout<<"*";
	}
	for(i=4;i<23;i++)
	{
	    gotoxy(97,i);
	    cout<<"*";
	}
}


#endif // BORDER_H_INCLUDED
