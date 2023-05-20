#include <iostream>

#include "field.h"

field::field() { system("mode con cols=113 lines=30"); system("title Sea Battle"); }

void field::draw() {

    COORD point;
    for (i = 0; i < draw_size + 4; i += 4)
    {
        for (j = 0; j < draw_size / 2 - 1; j++)
        {
            gotoxy(2 + i, 1 + j);
            dx = wherex();
            dy = wherey();
            cout << '|' << endl;

            if (j % 2 == 0 && i < 40)
            {
                point.X = dx + 2;
                point.Y = dy;
                cells.push_back(point);

                point.X = dx + 70;
                point.Y = dy;
                enemy_cells.push_back(point);
            }

            Sleep(7);
            gotoxy(70 + i, 1 + j);
            cout << '|' << endl;
        }
    }

    for (i = 0; i < draw_size; i += 2)
    {
        gotoxy(3 + i, 0);
        cout << '_';
        Sleep(6);
        gotoxy(2 + i, draw_size / 2);
        cout << "|||";
        Sleep(6);
        gotoxy(71 + i, 0);
        cout << '_';
        Sleep(6);
        gotoxy(70 + i, draw_size / 2);
        cout << "|||";
        Sleep(6);
    }

    for (i = 2; i < draw_size / 2; i += 2)
    {
        for (j = 3; j < draw_size; j += 4)
        {
            gotoxy(0 + j, i);
            cout << "---";
            Sleep(10);
            gotoxy(68 + j, i);
            cout << "---";
            Sleep(10);
        }
    }
}

void field::label(string line, int x, int y, int time) {

    COORD dxy = wherexy();
    gotoxy(x, y);

    for (int i = 0; i < line.length(); i++) { cout << line[i]; Sleep(time); }
}
