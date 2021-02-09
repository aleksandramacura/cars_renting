#include "menu.h"

// Global variables
char log_pass_in[10];
char log_pass_db[10];
int control_var = 0;
int control_var1 = 0;
int finish = 0;
int user = 0; // 1 -> user; 2 -> operator; 3 -> admin
char loged_as[11] = "None";
int row_counter = 0;
int max_id_car = 0;
int max_id_client = 0;
int max_id_rent = 0;
int min_id_car = 9999;
int min_id_client = 9999;
int min_id_rent = 9999;
char plate_tmp[20];
char pesel_tmp[20];
int returned_car_id = 0;

int main() {
  Menu MainMenu;
  MainMenu.Run();
}

