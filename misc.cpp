#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"
#include "cars.h"
#include "clients.h"
#include "rentings.h"
#include "menu.h"
#include <conio.h>
#include <string.h>
#include <limits>
#include <windows.h>

#define clrscr() system("cls")

COORD coord = {0,0};

void get_pass(char *password)
{
 string pass = "";
 char ch;
 cout << "Password: ";
 ch = _getch();                                                                                                              // getting character from the keyboard
 while(ch != 13){                                                                                                            // 13 - ASCII code for enter
  pass.push_back(ch);
  cout << '*';
  ch = _getch();
 }
 strcpy(password, pass.c_str());
 return;
}

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int is_valid_pesel(const char * pesel)
{
  const static unsigned weights[] = {9, 7, 3, 1, 9, 7, 3, 1, 9, 7};
  unsigned sum = 0;
  for(size_t i = 0; i < 10; ++i)
    {
     sum += (pesel[i] - '0') * weights[i];
    }
    if ((sum % 10) == (unsigned int)(pesel[10] - '0'))
     return 1;
    else
     return 0;
}

int read_pesel(char *pesel) {

    char pesel_tmp[20];
    cout << "PESEL number: ";
    cin.clear();
    cin.ignore(numeric_limits < streamsize >::max(), '\n' );

    cin >> pesel_tmp;

    if(strlen(pesel_tmp) != 11)
    {
     return 1;
    }

    for(size_t i = 0; i < 11; ++i)
    {
     if(! isdigit(pesel_tmp[i]))
      {
       return 1;
      }
    }

 if (is_valid_pesel(pesel_tmp) == 1)
 {
    strcpy(pesel, pesel_tmp);
    return 0;
 }
 else
 {
    return 1;
 }
}

int yes_no(string descr)
{
 char ch;

 cout << endl << descr << endl;

 ch = _getch();
 while((ch != 'Y') && (ch != 'y') && (ch != 'N') && (ch != 'n'))
 {
  ch = _getch();
 }

 if ((ch == 'Y') || (ch == 'y'))
 {
  return 1;
 }
 else
 {
  return 0;
 }
}

int read_string(char *str_input, unsigned int maxim_length, int posx, int posy, string info_text)
{
       string input;
       unsigned int str_len = 0;

       gotoxy(posx,posy);
       cout << "                                                                             " ;
       gotoxy(posx,posy);
       cout << info_text;
       cin >> input;

       str_len = (maxim_length > input.length() ? input.length() : maxim_length);

       for(unsigned int i = 0; i < str_len; i++)
       {
        str_input[i] = input.at(i);
       }
       str_input[str_len] = 0;

       return 0;
}

bool is_leapyear(int yy)
{
 return ((!(yy%4) && (yy%100)) || !(yy%400));
}

int insert_date(char *date, int *d, int *m, int *y)
{
 char test[20];
 int month_len[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

 cout << "Data DD-MM-YYYY: ";
 cin >> test;

 if (strlen(test) != 10)
  return 0;

 if ((test[2] != '-') || (test[5] != '-'))
  return 0;

 if ((isdigit(test[0])) && (isdigit(test[1])) && (isdigit(test[3])) && (isdigit(test[4])) && (isdigit(test[6])) && (isdigit(test[7])) && (isdigit(test[8])) && (isdigit(test[9])))
     {
      *d = 10 * (test[0]-48) + (test[1]-48);
      *m = 10 * (test[3]-48) + (test[4]-48);
      *y = 1000 * (test[6]-48) + 100 * (test[7]-48) + 10 * (test[8]-48) + (test[9]-48);

      if ((*y > 2050) || (*y < 1990))
        return 0;

      if ((*m > 12) || (*m <= 0))
        return 0;

      if (is_leapyear(*y) && *m == 2)
        month_len[1]++;

      if ((*d < 1) || (*d > month_len[(*m) - 1]))
        return 0;
       else
       {
        strcpy(date, test);
        return 1;
       }
     }
     else
     {
      return 0;
     }
}

int countLeapYears(int y, int m)
{
    int years = y;

    // Check if the current year needs to be
    // considered for the count of leap years
    // or not
    if (m <= 2)
        years--;

    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
     // multiple of 100.
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(int dt1y, int dt1m, int dt1d, int dt2y, int dt2m, int dt2d)
{
    const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1y dt1m dt1d'

    // initialize count using years and day
    long int n1 = dt1y * 365 + dt1d;

    // Add days for months in given date
    for (int i = 0; i < dt1m - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1y, dt1m);

    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2y dt2m dt2d'

    long int n2 = dt2y * 365 + dt2d;
    for (int i = 0; i < dt2m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2y, dt2m);

    // return difference between two counts
    return (n2 - n1);
}
