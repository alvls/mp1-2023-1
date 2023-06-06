#pragma once
#include <vector>

#include "Console.h"

using namespace std;


class ship {

public:
    static int kills;
    static int enemy_kills;

    int deck = 0;
    bool dead;
    bool flug;
    COORD coord;
    vector<COORD> tails;

    ship(int deck);

    void set_coords();

    void take_damage();

    void draw(char symbol, TColor color, bool flag = true);

private:
    int wounded = 0;
    COORD point;
};