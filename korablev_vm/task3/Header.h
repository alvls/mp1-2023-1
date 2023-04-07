#pragma once
#include <windows.h>
#include <iostream>
#include <memory>
#include <cmath>
#include <locale>
#include <string>
#include <conio.h>

typedef double(*Fx)(double);
using namespace std;


int menu_mode(string* arr, int size);
void exit_prog();
double* get_lim();
double* get_right_lim();
int get_segment();
double line(double x);
void hello();

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};
enum en_side
{
    _right = 1,
    _left = 2,
    _mid = 3,
};
enum en_fnc
{
    _line = 1,
    _exp = 2,
    _sin = 3,
    _cos = 4,
    _tan = 5,
    _atan = 6,
    _sqrt = 7
};
enum en_exit
{
    _new = 1,
    _ex_file = 2,
};

COORD wherexy(void);
void clrscr(void);
void gotoxy(int x, int y);
void textcolor(int color);
void hidecursor(void);