#include <iostream>

#include "processing_center.h"
#include "atm.h"

using namespace std;

int main() {

	setlocale(LC_ALL, "ru");

    processing_center data;
    atm ATM(data, "logs.txt");

    cout << ATM.get_client(6000) << endl;

    ATM.take_card(6000);
    ATM.check_pin(6666);

    cout << "На счету: " << ATM.get_amount() << "руб." << endl;

    ATM.get_money(18200);
    ATM.take_money(18200, 0, 1, 0, 1, 1, 3);

    ATM.get_card();

	return EXIT_SUCCESS;
}
