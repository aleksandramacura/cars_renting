#include <iostream>
#include "sqlite3.h"

#define clrscr() system("cls")

using namespace std;

class Menu{
private:
   int choice;

public:
   int disp_cars_Menu();
   int disp_av_cars(int wait);
   int read_input(int *number, int maxim, int minim, int posx, int posy, string info_text);
   int disp_all_clients(int wait);
   int disp_all_rentings();
   int disp_active_rentings(int wait);
   int disp_finished_rentings();
   int add_client();
   int add_renting();
   int car_returning();
   int make_rent_finished(int id, char *date);
   void Run();
   void Menu_1();
   void Menu_2();
   void Menu_Login();
   void menu_login_do_1();
   void menu_login_do_2();
   void main_menu_do_1();
   void main_menu_do_2();
   void menu_recreate_do();
   void data_base_reconstruction();
   int add_car();
   int get_plate_cars(int id, char *plate);
   int make_car_rented(int id, int status);
   int get_client_pesel(int id, char *pesel);
   int test_client_id(int cl_id);
   int test_car_id(int car_id);
   int test_rent_id(int rent_id);

   Menu(int choice_ = -1){
        choice = choice_;}
};
