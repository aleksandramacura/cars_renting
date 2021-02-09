
#include <iostream>
#include "sqlite3.h"

#define clrscr() system("cls")

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName);


class Car{

    string manufacturer;
    string model;
    int year;
    string color;
    string plate;
    int type; // 1 - premium, 2 - gold, 3 - normal;
    int is_active; // 1- is active, 0 - is scraped;
    int is_available; // 1 - is available, 0 - is rented;

public:
    Car(string manufacturer_, string model_, int year_, string color_, string plate_, int type_, int is_active_, int is_available_);

    void print_car();

    void add_car_to_SQL();

};

