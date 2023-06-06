#include <iostream>

#include "ship.h"

int ship::kills = 0;
int ship::enemy_kills = 0;

ship::ship(int deck) : deck(deck), dead(false), flug(true) {

        point.X = 4; point.Y = 0;
        coord.X = -1;
        coord.Y = -1;

        if (deck == 2) { tails.push_back(point); }

        else if (deck == 3)
        {
            tails.push_back(point);
            point.X = 8; point.Y = 0;
            tails.push_back(point);
        }
        else if (deck == 4)
        {
            tails.push_back(point);
            point.X = 8; point.Y = 0;
            tails.push_back(point);
            point.X = 12; point.Y = 0;
            tails.push_back(point);
        }
    }

void ship::set_coords() {

    coord = wherexy();
    for (int i = 0; i < tails.size(); i++)
    {
        tails[i].X += coord.X;
        tails[i].Y += coord.Y;
    }
}

void ship::take_damage() { wounded++; if (wounded == deck) dead = true; }

void ship::draw(char symbol, TColor color, bool flag) {

    textcolor(color);
    COORD xy = wherexy();
    COORD dxy = wherexy();

    if (flag) { dxy.X = 0; dxy.Y = 0; }

    gotoxy(coord.X, coord.Y);
    cout << symbol;
    for (int i = 0; i < tails.size(); i++)
    {
        gotoxy(dxy.X + tails[i].X, dxy.Y + tails[i].Y);
        cout << symbol;
    }

    gotoxy(xy.X, xy.Y);
}
