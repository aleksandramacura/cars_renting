#include <iostream>
#include "sqlite3.h"

#define clrscr() system("cls")

using namespace std;

int callback(void *NotUsed, int argc, char **argv, char **azColName);

class Client{

    string name;
    string surname;
    string pesel;
    string email;
    string pnumber;

public:
    Client(string name_, string surname_, string pesel_, string email_, string pnumber_);

    void print_client();

    void add_client_to_SQL();

};
