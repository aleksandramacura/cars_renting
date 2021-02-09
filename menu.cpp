#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include <limits>
#include "cars.h"
#include "clients.h"
#include "rentings.h"
#include "menu.h"
#include <string>

#define clrscr() system("cls")

using namespace std;

extern int user; // 1 -> user; 2 -> operator; 3 -> admin
extern char loged_as[11];
extern int max_id_car;
extern int max_id_client;
extern int max_id_rent;
extern int min_id_car;
extern int min_id_client;
extern int min_id_rent;
extern int returned_car_id;
extern char log_pass_in[10];
extern char log_pass_db[10];
extern char plate_tmp[20];
extern char pesel_tmp[20];
extern int row_counter;

int callback(void *NotUsed, int argc, char **argv, char **azColName);
int callback_1(void* data, int argc, char** argv, char** azColName);
int callback_3(void* data, int argc, char** argv, char** azColName);
int callback_4(void* data, int argc, char** argv, char** azColName);
int callback_4a(void* data, int argc, char** argv, char** azColName);
int callback_car_update(void* data, int argc, char** argv, char** azColName);
int callback_rent_finish(void* data, int argc, char** argv, char** azColName);
int callback_login(void* data, int argc, char** argv, char** azColName);
int callback_plate(void* data, int argc, char** argv, char** azColName);
int callback_car_update(void* data, int argc, char** argv, char** azColName);
int callback_client(void* data, int argc, char** argv, char** azColName);
int callback_test_row(void* data, int argc, char** argv, char** azColName);

void gotoxy(int x,int y);
int read_string(char *str_input, unsigned int maxim_length, int posx, int posy, string info_text);
int read_input(int *number, int maxim, int minim, int posx, int posy, string info_text);
void get_pass(char *password);
int read_pesel(char * pesel);
int insert_date(char *date, int *d, int *m, int *y);
int callback_get_car_id(void* data, int argc, char** argv, char** azColName);
void menu_login_do_1();
void menu_login_do_2();

void Menu::Run(){

        choice = -1;
        int test = 0;

        while(choice != 0)
        {
        system("cls");
        cout << endl << endl;
        cout << "CAR RENTING SYSTEM  -->> Logged as user: " << loged_as << " -->> Level: " << user << endl;
        cout << "1 -> Display Data" << endl;
        cout << "2 -> Add Data" << endl;
        cout << "3 -> Login / Logout" << endl;
        cout << "4 -> Reconstruction" << endl;
        cout << "0 -> EXIT" << endl;

        read_input(&choice, 4, 0, 0, 9, "Make a choice: ");

        switch(choice)
        {
          case 0:
              test = yes_no("Are you sure you want to exit? [Y/N]? ");
              if (test == 0)
                {
                 choice = -1;
                }
              break;
          case 1:
              main_menu_do_1();
              choice = -1;
              break;
          case 2:
              main_menu_do_2();
              choice = -1;
              break;
          case 3:
              Menu_Login();
              choice = -1;
              break;
          case 4:
              menu_recreate_do();
              break;
          default:
              cout << " INNE" << endl;
              break;
        }
      }
 return;
}

void Menu::Menu_1(){

        choice = -1;

        while(choice != 0)
        {
        system("cls");
        cout << endl << endl;
        cout << "CAR RENTING SYSTEM  -->> Logged as user: " << loged_as << " -->> Level: " << user << endl;
        cout << "1 -> Display all cars" << endl;
        cout << "2 -> Display available cars" << endl;
        cout << "3 -> Display all clients" << endl;
        cout << "4 -> Display all rentings" << endl;
        cout << "5 -> Display all active rentings" << endl;
        cout << "6 -> Display finished rentings" << endl;
        cout << "0 -> EXIT" << endl;

        read_input(&choice, 6, 0, 0, 11, "Make a choice: ");

        switch(choice)
        {
          case 0:
              break;
          case 1:
              disp_cars_Menu();
              break;
          case 2:
              disp_av_cars(1);
              break;
          case 3:
              disp_all_clients(1);
              break;
          case 4:
               disp_all_rentings();
               break;
          case 5:
               disp_active_rentings(1);
               break;
          case 6:
               disp_finished_rentings();
               break;
          default:
              cout << " INNE" << endl;
              break;
        }
      }
 return;
}

void Menu::Menu_2(){

        choice = -1;

        while(choice != 0)
        {
        system("cls");
        cout << endl << endl;
        cout << "CAR RENTING SYSTEM  -->> Logged as user: " << loged_as << " -->> Level: " << user << endl;
        cout << "1 -> Add new car" << endl;
        cout << "2 -> Add new client" << endl;
        cout << "3 -> Add new renting" << endl;
        cout << "4 -> Returning the car" << endl;
        cout << "0 -> EXIT" << endl;

        read_input(&choice, 4, 0, 0, 9, "Make a choice: ");

        switch(choice)
        {
          case 0:
              break;
          case 1:
              add_car();
              break;
          case 2:
              add_client();
              break;
          case 3:
              add_renting();
              break;
          case 4:
              car_returning();
              break;
          default:
              cout << " INNE" << endl;
              break;
        }
      }
 return;
}

void Menu::Menu_Login(){

        choice = -1;

        while(choice != 0)
        {
        system("cls");
        cout << endl << endl;
        cout << "CAR RENTING SYSTEM  -->> Logged as user: " << loged_as << " -->> Level: " << user << endl;
        cout << "1 -> LOGIN" << endl;
        cout << "2 -> LOGOUT" << endl;
        cout << "0 -> EXIT" << endl;

        read_input(&choice, 2, 0, 0, 7, "Make a choice: ");

        switch(choice)
        {
          case 0:
              break;
          case 1:
              menu_login_do_1();
              break;
          case 2:
              menu_login_do_2();
              break;
          default:
              cout << " INNE" << endl;
              break;
        }
      }
 return;
}


int Menu::disp_cars_Menu(){
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);
    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << "ALL CARS " << endl << endl;
        cout << "| ID  | Manufacturer        |  Model     |  Color   | Plate    | Type  | Year   | Is Active? |   Is Avb ? | " << endl;
        cout << "+=====+=====================|============|==========|==========|=======|========|============|============|" << endl;
    }

   sql_str = "SELECT * FROM CARS;";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_1, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "-----------------------------------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   system("pause >> null");

   return (0);
}

int Menu::disp_av_cars(int wait){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << endl << "AVALIABLE CARS " << endl << endl;
        cout << "| ID  | Manufacturer        |  Model     |  Color   | Plate    | Type  | Year   | Is Active? | Is Availa? | " << endl;
        cout << "+=====+=====================|============|==========|==========|=======|========|============|============|" << endl;
    }

   sql_str = "SELECT * FROM CARS WHERE IS_AVAILABLE=1;";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_1, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "-----------------------------------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   if (wait == 1)
    system("pause >> null");

   return (0);
return 0;
}

int Menu::read_input(int *number, int maxim, int minim, int posx, int posy, string info_text)
{
       string input;
       int inp_int;
       bool valid = false;
       while(!valid){
           gotoxy(posx,posy);
           cout << "                                                                             " ;
           gotoxy(posx,posy);
           cout << info_text;
           cin >> input;
           if(cin.fail())
           {
            cin.clear();
            cin.ignore(numeric_limits < streamsize >::max(), '\n' );
           }

           inp_int = atoi(input.c_str());

           if((inp_int >= minim) && (inp_int <= maxim))
           {
               valid = true;
               *number = inp_int;
           }

           if ((inp_int == 0) && ((input.at(0) != '0') || (input.length() != 1)))
           {
               valid = false;
           }

       }
       return valid;
}

int Menu::disp_all_clients(int wait){

    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT * FROM CLIENTS ORDER BY SURNAME;";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << "ALL CLIENTS " << endl << endl;
        cout << "|  ID |   Name          |   SURNAME       |   E-MAIL                  |   PESEL         |   PHONE NUMBER  |" << endl;
        cout << "+=====+=================+=================+===========================+=================+=================+" << endl;
    }

   rc = sqlite3_exec(db, sql_str.c_str(), callback_3, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "-----------------------------------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   if (wait == 1)
    system("pause >> null");

   return (0);

}

int Menu::disp_all_rentings(){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << "ALL RENTINGS " << endl << endl;
        cout << "|  ID |   PESEL     |  RENT DATE  | DAYS    | RETURNED | PLATE           | RETRUN DATE |" << endl;
        cout << "+=====+=============+=============+=========+==========+=================+=============+" << endl;
    }

   sql_str = "SELECT * FROM RENTING;";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_4a, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "----------------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   system("pause >> null");

   return (0);
}


int Menu::disp_active_rentings(int wait){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << "ACTIVE RENTINGS " << endl << endl;
        cout << "|  ID |   PESEL     |   RENT DATE     |   DAYS    |  RETURNED | PLATE           |" << endl;
        cout << "+=====+=============+=================+===========+===========+=================+" << endl;
    }

   sql_str ="SELECT * FROM RENTING WHERE IS_RETURNED=0;";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_4, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "---------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   if (wait == 1)
    system("pause >> null");

   return (0);
}


int Menu::disp_finished_rentings(){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
    else
    {
        cout << "FINISHED RENTINGS " << endl << endl;
        cout << "|  ID |   PESEL     |  RENT DATE  | DAYS    | RETURNED | PLATE           | RETRUN DATE |" << endl;
        cout << "+=====+=============+=============+=========+==========+=================+=============+" << endl;
    }

   sql_str = "SELECT * FROM RENTING WHERE IS_RETURNED=1;";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_4a, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "----------------------------------------------------------------------------------------" << endl;
      cout << "Table read successfully" << endl;
   }
   sqlite3_close(db);

   system("pause >> null");

   return (0);
}


int Menu::add_car(){

    int test = 0;
    char man[20];
    char model[20];
    int year = 0;
    char col[20] = "White";
    char plate[20] = "SCI12366";
    int type = 0;
    int active = 0;
    int av = 0;

    clrscr();

    cout <<"Please insert the car info: " << endl;

    read_string(man, 19, 0, 1, "Car manufacturer: ");

    read_string(model, 19, 0, 3, "Car model: ");

    read_input(&year, 2050, 1999, 0, 5, "Year when the car was produced: ");

    read_string(col, 19, 0, 7, "Color: ");

    read_string(plate, 19, 0, 9, "Plate number: ");

    read_input(&type, 3, 1, 0, 11, "Type( 1 - premium, 2 - gold, 3 - normal): ");

    read_input(&active, 1, 0, 0, 13, "Is it still used? (1- yes, 0 - no): ");

    read_input(&av, 1, 0, 0, 15, "Is it available to rent now? (1- yes, 0 - no): ");

    cout << endl;

    Car c1(man,model,year, col, plate, type, active, av);
    c1.print_car();

    test = yes_no("Save data to database [Y/N]? ");
    if (test == 1)
    {
     c1.add_car_to_SQL();
     system("pause >> null");
    }

    return (0);
}

int Menu::add_client(){

    int test = 1;
    char name[20];
    char surname[20];
    char pesel_char[12] = {'\0'};
    char email[40] = "xxxxx@yy.zz";
    char phone[29];

    clrscr();

    cout <<"Please insert the new client info: " << endl;

    read_string(name, 19, 0, 1, "Name: ");

    read_string(surname, 19, 0, 3, "Surname: ");

    while(test != 0)
    {
     gotoxy(0, 5);
     cout << "                                          ";
     gotoxy(0, 5);
     strcpy(pesel_char,"");
     test = read_pesel(pesel_char);
    }

    read_string(email, 39, 0, 7, "E-mail: ");

    read_string(phone, 19, 0, 9, "Phone number: ");

    Client c1(name, surname, pesel_char, email, phone);
    c1.print_client();

    test = yes_no("Save data to database [Y/N]? ");
    if (test == 1)
    {
     c1.add_client_to_SQL();
     system("pause >> null");
    }

    return (0);
}

int Menu::add_renting(){

    int test = 0;
    int id_car = 0;
    int id_client = 0;
    char plates[20];
    char pesel[20];
    char renting_date[20];
    char return_date[20];
    int number_of_days;
    int is_returned;;
    int test_date = 0;
    int dd, mm, yy;

    clrscr();

    max_id_car = 0;
    min_id_car = 9999;

    test_date = 0;
    while (test_date == 0)
    {
     cout << "                              ";
     cout << "                              ";
     disp_av_cars(0);
     read_input(&id_car, max_id_car, 0, 0, 0, "Which car (0 -> return): ");
     if (id_car == 0)
        return 1;
     test_date = test_car_id(id_car);
    }

    get_plate_cars(id_car, plates);

    max_id_client = 0;
    min_id_client = 9999;

    test_date = 0;
    while (test_date == 0)
    {
     cout << "                              ";
     cout << "                              ";
     disp_all_clients(0);
     read_input(&id_client, max_id_client, 0, 0, 0, "Which client (0 -> return): ");
     if (id_client == 0)
        return 1;
     test_date = test_client_id(id_client);
    }

    get_client_pesel(id_client, pesel);

    test_date = 0;
    cout << "Renting date: ";
    while (test_date == 0)
    {
     gotoxy(0, 2);
     cout << "                                         ";
     gotoxy(0, 2);
     test_date = insert_date(renting_date, &dd, &mm, &yy);
    }

    read_input(&number_of_days, 30, 1, 0, 4, "Number of days: ");

    read_input(&is_returned, 1, 0, 0, 6, "Is returned? (1- yes, 0- no): ");

    strcpy(return_date, "00-00-0000");

    Renting r1(plates, pesel, renting_date, number_of_days, is_returned, id_car, id_client, return_date);

    test = yes_no("Save data to database [Y/N]? ");
    if (test == 1)
    {
     r1.add_renting_to_SQL();
     make_car_rented(id_car, 0);
     cout << "Data saved." << endl;
     system("pause >> null");
    }

    return 0;
}

int Menu::car_returning(){

    int test = 0;
    int id_rent = 0;
    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    char return_date[20];
    int test_date = 0;
    int dd, mm, yy;

    clrscr();

    max_id_rent = 0;
    min_id_rent = 9999;

    test_date = 0;
    while (test_date == 0)
    {
     cout << "                              ";
     cout << "                              ";
     disp_active_rentings(0);
     read_input(&id_rent, max_id_rent, 0, 0, 0, "Which car is being returned? (0 -> return): ");
     if (id_rent == 0)
        return 1;
     test_date = test_rent_id(id_rent);
    }

   clrscr();

    test_date = 0;
    cout << "Returning date: ";
    while (test_date == 0)
    {
     gotoxy(16, 0);
     cout << "                                         ";
     gotoxy(16, 0);
     test_date = insert_date(return_date, &dd, &mm, &yy);
    }

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT * FROM RENTING WHERE ID=" + to_string(id_rent) + ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   returned_car_id = 0;
   rc = sqlite3_exec(db, sql_str.c_str(), callback_get_car_id, 0, &zErrMsg);


   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);

    test = yes_no("Save data to database [Y/N]? ");
    if (test == 1)
    {
     make_car_rented(returned_car_id, 1);
     make_rent_finished(id_rent, return_date);
     cout << "Data saved." << endl;
     system("pause >> null");
    }

    return 0;
}

int Menu::make_rent_finished(int id, char *date){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    clrscr();
    string sql_str;

    exit = sqlite3_open("cars_renting.db", &db);

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   sql_str = "UPDATE RENTING SET IS_RETURNED=1, RETURN_DATE='";
   sql_str += date;
   sql_str += "' WHERE ID=" + to_string(id) + ";";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_rent_finish, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   sql_str = "SELECT * FROM RENTING WHERE ID='" + to_string(id) + "';";

   rc = sqlite3_exec(db, sql_str.c_str(), callback_rent_finish, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }


   sqlite3_close(db);

   return (0);
return 0;
}

void Menu::main_menu_do_1()
{
 if (user < 1)
 {
  clrscr();
  cout << endl << endl;
  cout << "CAR RENTING SYSTEM  -->> Operation not allowed for the user: " << loged_as << " -->> Level: " << user << endl;
  system("pause >> null");
  return;
 }
 else
 {
  Menu_1();
 }
}

void Menu::main_menu_do_2()
{
 if (user < 2)
 {
  clrscr();
  cout << endl << endl;
  cout << "CAR RENTING SYSTEM  -->> Operation not allowed for the user: " << loged_as << " -->> Level: " << user << endl;
  system("pause >> null");
  return;
 }
 else
 {
  Menu_2();
 }
}

void Menu::menu_recreate_do()
{
 if (user < 4)
 {
  clrscr();
  cout << endl << endl;
  cout << "CAR RENTING SYSTEM  -->> Operation not allowed for the user: " << loged_as << " -->> Level: " << user << endl;
  system("pause >> null");
  return;
 }
 else
 {
  data_base_reconstruction();
 }
}

void Menu::data_base_reconstruction()
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sql_str;

   rc = sqlite3_open("cars_renting.db", &db);

   if( rc ) {
      cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
      return;
   } else {
      cout << "Database created successfully" << endl;
   }

   system("pause >> null");

   sql_str = "CREATE TABLE CARS(ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "MANUFACTURER           TEXT                NOT NULL," \
      "MODEL                  TEXT                NOT NULL," \
      "COLOR                  TEXT                NOT NULL," \
      "PLATE                  TEXT                NOT NULL," \
      "TYPE                   INT                 NOT NULL," \
      "YEAR                   INT                 NOT NULL," \
      "IS_ACTIVE              INT                 NOT NULL," \
      "IS_AVAILABLE           INT                 NOT NULL)";

   rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "Table CARS SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "Table CARS created successfully" << endl;
   }

   system("pause >> null");

    sql_str = "CREATE TABLE CLIENTS(ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "NAME                   TEXT                NOT NULL," \
      "SURNAME                TEXT                NOT NULL," \
      "EMAIL                  TEXT                NOT NULL," \
      "PESEL                  TEXT                NOT NULL," \
      "PHONE_NUMBER           INT                 NOT NULL);";

   rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "Table CLIENTS SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "Table CLIENTS created successfully" << endl;
   }

   system("pause >> null");

   sql_str = "CREATE TABLE RENTING(ID INTEGER PRIMARY KEY AUTOINCREMENT," \
       "PLATE                 TEXT                NOT NULL,"\
       "PESEL                 INT                 NOT NULL,"\
       "RENTING_DATE          DATE                NOT NULL,"\
       "NUMBER_OF_DAYS        INT                 NOT NULL,"\
       "IS_RETURNED           INT                 NOT NULL,"\
       "VALUE                 INT                 NOT NULL,"\
       "CAR_ID                INT                 NOT NULL,"\
       "CLIENT_ID             INT                 NOT NULL,"\
       "RETURN_DATE           DATE                NOT NULL);";

    rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "Table RENTINGS SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "Table RENTINGS created successfully" << endl;
   }

   system("pause >> null");

   sql_str = "CREATE TABLE USER (NAME CHAR[11]," \
       "PASS                  CHAR[11],"\
       "STATUS                INT);";

   rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "Table USER SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "Table USER created successfully" << endl;
   }
      system("pause >> null");

   sql_str =  "INSERT INTO USER (NAME, PASS, STATUS) VALUES ('Admin', '1234', 3);" \
              "INSERT INTO USER (NAME, PASS, STATUS) VALUES ('Operator', 'EEEE', 2);" \
              "INSERT INTO USER (NAME, PASS, STATUS) VALUES ('User', 'FFFF', 1);";

   rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);


   if( rc != SQLITE_OK ){
      cerr << "Table USER SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   } else {
      cout << "Table USER initiated successfully" << endl;
   }

   system("pause >> null");

   sqlite3_close(db);

}

void Menu::menu_login_do_1()                                                                                                   // function for logging in
{
 char log_name[10];
 sqlite3 *db;
 char *zErrMsg = 0;
 int rc;
 string sql_str;

 user = 0;
 strcpy(loged_as, "None");

 clrscr();
 cout << endl << endl;
 cout << "CAR RENTING SYSTEM " << endl << endl;

 cout << "Login name: ";
 cin >> log_name;

 strcpy(log_pass_in,"");
 get_pass(log_pass_in);

 if ((strcmp(log_name, "SuperUser")==0) && (strcmp(log_pass_in, "135790")==0))
 {
   strcpy(loged_as,"SuperUser");
   user = 4;
 }
 else
 {
 rc = sqlite3_open("cars_renting.db", &db);

 sql_str = "SELECT * FROM USER WHERE Name='";
 sql_str += log_name;
 sql_str += "';";

    if (rc) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return;
    }

     rc = sqlite3_exec(db, sql_str.c_str(), callback_login, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);
 }
   return;
}

void Menu::menu_login_do_2()                                                                                                       // function for logging out
{
 user = 0;
 strcpy(loged_as, "None");
}

int Menu::get_plate_cars(int id, char *plate){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);


    sql_str = "SELECT * FROM CARS WHERE IS_AVAILABLE=1 AND ID=" + to_string(id) + ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   strcpy(plate_tmp, " ");
   rc = sqlite3_exec(db, sql_str.c_str(), callback_plate, 0, &zErrMsg);
   strcpy(plate, plate_tmp);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
  sqlite3_close(db);
   return (0);
return 0;
}

int Menu::make_car_rented(int id, int status){
    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "UPDATE CARS SET IS_AVAILABLE=" + to_string(status) +  " WHERE ID=" + to_string(id) +  ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }
   rc = sqlite3_exec(db, sql_str.c_str(), callback_car_update, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);

   return (0);
return 0;
}

int Menu::get_client_pesel(int id, char *pesel){

    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;
    string sql_str;

    clrscr();

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT * FROM CLIENTS ORDER BY SURNAME AND ID=" + to_string(id) + ";";


    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   strcpy(pesel_tmp, " ");
   rc = sqlite3_exec(db, sql_str.c_str(), callback_client, 0, &zErrMsg);
   strcpy(pesel, pesel_tmp);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);
   return (0);

}

int Menu::test_client_id(int cl_id)
{
    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT COUNT(*) FROM CLIENTS WHERE ID=" + to_string(cl_id) + ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   row_counter = 0;
   rc = sqlite3_exec(db, sql_str.c_str(), callback_test_row, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }

   sqlite3_close(db);

   return row_counter;
}

int Menu::test_car_id(int car_id)
{
    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT COUNT(*) FROM CARS WHERE IS_AVAILABLE=1 AND ID=" + to_string(car_id) + ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   row_counter = 0;
   rc = sqlite3_exec(db, sql_str.c_str(), callback_test_row, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);

   return row_counter;
}

int Menu::test_rent_id(int rent_id)
{
    string sql_str;
    sqlite3* db;
    int exit = 0;
    char *zErrMsg = 0;
    int rc;

    exit = sqlite3_open("cars_renting.db", &db);

    sql_str = "SELECT COUNT(*) FROM RENTING WHERE IS_RETURNED=0 AND ID=" + to_string(rent_id) + ";";

    if (exit) {
        cerr << "Error open DB " << sqlite3_errmsg(db) << endl;
        return (-1);
    }

   row_counter = 0;
   rc = sqlite3_exec(db, sql_str.c_str(), callback_test_row, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL Error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);

   return row_counter;
}
