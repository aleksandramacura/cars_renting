#include <iostream>
#include "sqlite3.h"

#define clrscr() system("cls")

using namespace std;
int yes_no(string descr);
int callback(void *NotUsed, int argc, char **argv, char **azColName);

int callback(void *NotUsed, int argc, char **argv, char **azColName);

class Renting{

    string plate;
    string pesel;
    string renting_date;
    string return_date;

    int number_of_days;
    bool is_returned;
    double value;
    int car_id;
    int client_id;

public:
    Renting(string plate_, string pesel_, string renting_date_, int number_of_days_, bool is_returned_, int car_id_, int client_id_, string return_date_);

    void print_renting();

    void add_renting_to_SQL();
};

