#include "rentings.h"

Renting::Renting(string plate_ = "0", string pesel_ = "0", string renting_date_ = "00-00-0000", int number_of_days_ = 0, bool is_returned_ = 0,  int car_id_ = 0,   int client_id_ = 0, string return_date_ = "00-00-0000"){

        plate = plate_;
        pesel = pesel_;
        renting_date = renting_date_;
        return_date = return_date_;
        value = 0;

        number_of_days = number_of_days_;
        is_returned = is_returned_;
        car_id = car_id_;
        client_id = client_id_;
    }

void Renting::print_renting(){
        cout << "Renting info:" << endl;
        cout << "PESEL of the renting person: " << pesel << endl;
        cout << "Plate of the rented car: " << plate << endl;
        cout << "Date of renting: " << renting_date << endl;
        cout << "Number of days: " << number_of_days << endl;
        cout << "Date of return: " << return_date << endl;
        cout << "Is returned? (0- no, 1 - yes): " << is_returned << endl;
        cout << "Car ID: " << car_id;
        cout << "Client ID: " << car_id << endl;
        return;
    }

void Renting::add_renting_to_SQL(){
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        string sql_str;
        rc = sqlite3_open("cars_renting.db", &db);

        if( rc ) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            return;
        } else {
            cout << "Opened database successfully" << endl;
        }

        sql_str = "INSERT INTO RENTING (PLATE, PESEL, RENTING_DATE, NUMBER_OF_DAYS, IS_RETURNED, VALUE, CAR_ID, CLIENT_ID, RETURN_DATE)  VALUES ('" \
                 + plate + "' , '" + pesel + "' , '" + renting_date + "' , '" + to_string(number_of_days) + "' , '" + to_string(is_returned) + "' , '" + to_string(value)  \
                 + "' , '" + to_string(car_id) + "' , '" + to_string(client_id) + "' , '" + return_date + "' ); ";

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
