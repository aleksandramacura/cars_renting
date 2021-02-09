#include <iostream>
#include "sqlite3.h"
#include <string.h>
#include <iomanip>
#include "cars.h"
#include "clients.h"
#include "rentings.h"
#include "menu.h"

#define clrscr() system("cls")

extern char log_pass_in[10];
extern char log_pass_db[10];
extern int user; // 1 -> user; 2 -> operator; 3 -> admin
extern char loged_as[11];
extern int max_id_car;
extern int max_id_client;
extern int max_id_rent;
extern int min_id_car;
extern int min_id_client;
extern int min_id_rent;
extern int returned_car_id;
extern char plate_tmp[20];
extern char pesel_tmp[20];
extern int row_counter;

int getDifference(int dt1y, int dt1m, int dt1d, int dt2y, int dt2m, int dt2d);
void gotoxy(int x,int y);

int callback(void *NotUsed, int argc, char **argv, char **azColName) {

 return 0;
}

int callback_login(void* data, int argc, char** argv, char** azColName)                                           // callback to function for logging in, checking the passsword
{
 int test = 1;

 strcpy(log_pass_db, argv[1]);

 for (unsigned int i = 0; i < strlen(log_pass_db); i++)
    log_pass_db[i] += 2;

 for (unsigned int i = 0; i < strlen(log_pass_db); i++)
 {
  if (log_pass_db[i] != log_pass_in[i])
    test = 0;
 }

 if (strlen(log_pass_db) != strlen(log_pass_in))
    test = 0;

 if (test == 1)
 {
  user = atoi(argv[2]);                                                                                                  // atoi - ASCII to integer
  strcpy(loged_as, argv[0]);
 }

 return 0;
}

int callback_1(void* data, int argc, char** argv, char** azColName)                                                                 //callback displaying all cars
{
    cout << "| " << setw(3) << argv[0];
    cout << " | " << setw(19) << argv[1];
    cout << " | " << setw(10) << argv[2];
    cout << " | " << setw(8) << argv[3];
    cout << " | " << setw(8) << argv[4];
    cout << " | " << setw(5) << argv[5];
    cout << " | " << setw(6) << argv[6];
    cout << " | " << setw(10) << argv[7];
    cout << " | " << setw(10) << argv[8] << " |" << endl;

    if (atoi(argv[0]) > max_id_car)
         max_id_car = atoi(argv[0]);

    if (atoi(argv[0]) < min_id_car)
         min_id_car = atoi(argv[0]);

    return 0;
}

int callback_plate(void* data, int argc, char** argv, char** azColName)
{
    strcpy(plate_tmp, argv[4]);

    return 0;
}

int callback_car_update(void* data, int argc, char** argv, char** azColName)
{
    return 0;
}

int callback_rent_finish(void* data, int argc, char** argv, char** azColName)
{
    int year1, month1, day1;
    int year2, month2, day2;
    int number_of_days;
    int diff;

    day1 = 10 * (argv[3][0]-48) + (argv[3][1]-48);
    month1 = 10 * (argv[3][3]-48) + (argv[3][4]-48);
    year1 = 1000 * (argv[3][6]-48) + 100 * (argv[3][7]-48) + 10 * (argv[3][8]-48) + (argv[3][9]-48);

    day2 = 10 * (argv[9][0]-48) + (argv[9][1]-48);
    month2 = 10 * (argv[9][3]-48) + (argv[9][4]-48);
    year2 = 1000 * (argv[9][6]-48) + 100 * (argv[9][7]-48) + 10 * (argv[9][8]-48) + (argv[9][9]-48);

    number_of_days = getDifference(year1, month1, day1, year2, month2, day2);

    diff = number_of_days - atoi(argv[4]);

    gotoxy(0,3);
    cout << "Currently finished renting:" << endl;
    cout << "Renting date: " << argv[3] << endl;
    cout << "Return date : " << argv[9] << endl;
    cout << "Number of prepaid days: " << argv[4] << endl;
    cout << "Real number of days   : " << number_of_days << endl << endl;
    if (diff > 0)
    {
      cout << "Must be paid extra for: " << diff << " days." << endl;
    }
    else
    {
      cout << "paid for " << (diff * (-1)) << " days too much." << endl;
    }

    system("pause >> null");

    return 0;
}

int callback_3(void* data, int argc, char** argv, char** azColName)                                      // callback for displaying all of the clients
{
    cout << "| " << setw(3) << argv[0];
    cout << " | " << setw(15) << argv[1];
    cout << " | " << setw(15) << argv[2];
    cout << " | " << setw(25) << argv[3];
    cout << " | " << setw(15) << argv[4];
    cout << " | " << setw(15) << argv[5] << " |" << endl;

    if (atoi(argv[0]) > max_id_client)
     max_id_client = atoi(argv[0]);

    if (atoi(argv[0]) < min_id_client)
     min_id_client = atoi(argv[0]);

    return 0;
}

int callback_client(void* data, int argc, char** argv, char** azColName)
{
    strcpy(pesel_tmp, argv[4]);

    return 0;
}

int callback_4(void* data, int argc, char** argv, char** azColName)
{
    cout << "| " << setw(3) << argv[0];
    cout << " | " << setw(11) << argv[2];
    cout << " | " << setw(15) << argv[3];
    cout << " | " << setw(9) << argv[4];
    cout << " | " << setw(9) << argv[5];
    cout << " | " << setw(15) << argv[1] << " |" << endl;

    if (atoi(argv[0]) > max_id_rent)
     max_id_rent = atoi(argv[0]);

    if (atoi(argv[0]) < min_id_rent)
     min_id_rent = atoi(argv[0]);

    return 0;
}

int callback_4a(void* data, int argc, char** argv, char** azColName)
{
    cout << "| " << setw(3) << argv[0];
    cout << " | " << setw(11) << argv[2];
    cout << " | " << setw(11) << argv[3];
    cout << " | " << setw(7) << argv[4];
    cout << " | " << setw(8) << argv[5];
    cout << " | " << setw(15) << argv[1];
    cout << " | " << setw(11) << argv[9] << " |" << endl;

    if (atoi(argv[0]) > max_id_rent)
     max_id_rent = atoi(argv[0]);

    if (atoi(argv[0]) < min_id_rent)
     min_id_rent = atoi(argv[0]);

    return 0;
}

int callback_test_row(void* data, int argc, char** argv, char** azColName)
{
    row_counter = atoi(argv[0]);

    return 0;
}

int callback_get_car_id(void* data, int argc, char** argv, char** azColName)
{
    returned_car_id = atoi(argv[7]);

    return 0;
}

