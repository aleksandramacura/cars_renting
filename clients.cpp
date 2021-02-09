#include "clients.h"

Client::Client(string name_ = " ", string surname_ = " ", string pesel_ = " ", string email_ = " ", string pnumber_ = " "){

        name = name_;
        surname = surname_;
        email = email_;
        pesel = pesel_;
        pnumber = pnumber_;

}

void Client::print_client(){
        cout << "Client info:" << endl;
        cout << "Name: " << name << endl;
        cout << "Surname: " << surname << endl;
        cout << "PESEL: " << pesel << endl;
        cout << "Email: " << email << endl;
        cout << "Phone number: " << pnumber << endl;
        return;
}

void Client::add_client_to_SQL(){
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        string sql_str;

        sql_str =  "INSERT INTO CLIENTS (NAME, SURNAME, EMAIL, PESEL, PHONE_NUMBER)  VALUES ('" + name + "' , '" + surname + "' , '" + email + "' , '" + pesel + "' , '" + pnumber + "'); " ;

          rc = sqlite3_open("cars_renting.db", &db);

          if( rc ) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            return;
           }

          rc = sqlite3_exec(db, sql_str.c_str(), callback, 0, &zErrMsg);

          if( rc != SQLITE_OK ){
            cerr << "SQL Error: " << zErrMsg << endl;
            sqlite3_free(zErrMsg);
          } else {
            cout << "Records created successfully" << endl;
          }
        sqlite3_close(db);
        return;
    }
