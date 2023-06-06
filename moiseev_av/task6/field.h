#pragma once
#include <vector>

#include "Console.h"

using namespace std;


class field {

public:
    vector<COORD> cells;
    vector<COORD> enemy_cells;

    field();

    void draw();

    void label(string line, int x, int y, int time = 0);

private:
    int draw_size = 40;
    int dx = 0, dy = 0;
    int i = 0, j = 0;
};