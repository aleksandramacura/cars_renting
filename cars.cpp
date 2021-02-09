#include "cars.h"

Car::Car(string manufacturer_ = " ", string model_ = " ", int year_ = 0, string color_ = " ", string plate_ = " ", int type_ = 0, int is_active_ = 1, int is_available_ = 1){

        manufacturer = manufacturer_;
        model = model_;
        color =color_;
        plate = plate_;
        year =  year_;
        type = type_ ;
        is_active = is_active_ ;
        is_available = is_available_;
}

void Car::print_car(){
        cout << "Car info:" << endl;
        cout << "Manufacturer: " << manufacturer << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Color: " << color << endl;
        cout << "Number plate: " << plate << endl;
        cout << "Type of the car - how expensive:" << type << endl;
        return;
}

void Car::add_car_to_SQL(){
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        string sql_str;

        rc = sqlite3_open("cars_renting.db", &db);

        if( rc ) {
            cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
            return;
        }

      sql_str = "INSERT INTO CARS (MANUFACTURER,MODEL,COLOR,PLATE,TYPE,YEAR,IS_ACTIVE,IS_AVAILABLE) VALUES ('" + manufacturer + "' , '" + model + "' , '" + color + "' , '" + plate \
                + "' , " + to_string(type) + " , " + to_string(year) + " , " + to_string(is_active) + " , " + to_string(is_available) + " ); ";

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
