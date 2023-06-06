#include <iostream>

#include "sea_battle.h"

using namespace std;

int main() {

    setlocale(LC_ALL, "ru");
    
    sea_battle game;
    
    game.start();
    
    system("pause");
    return EXIT_SUCCESS;
}
