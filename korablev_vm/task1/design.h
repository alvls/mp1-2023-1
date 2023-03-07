#include <windows.h>
#include <iostream>
#include <memory>
using namespace std;

enum TColor {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};

//-----------------------------------------------------------------------------
COORD wherexy(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { -1, -1 };
    if (!Console)
        return pos;

    CONSOLE_SCREEN_BUFFER_INFO buf;

    GetConsoleScreenBufferInfo(Console, &buf);
    return buf.dwCursorPosition;
}

//-----------------------------------------------------------------------------
void clrscr(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int col = Attr;
    int width = buf.dwSize.X;
    int height = buf.dwSize.Y;

    COORD zpos;
    zpos.X = 0;
    zpos.Y = 0;
    SetConsoleCursorPosition(Console, zpos);

    FillConsoleOutputAttribute(Console, col, width * height, zpos, &Count);
    FillConsoleOutputCharacter(Console, ' ', width * height, zpos, &Count);
}

//-----------------------------------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(Console, pos);
}

//-----------------------------------------------------------------------------
void textcolor(int color)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_SCREEN_BUFFER_INFO buf;
    GetConsoleScreenBufferInfo(Console, &buf);

    WORD Attr;
    DWORD Count;
    COORD pos = buf.dwCursorPosition;
    ReadConsoleOutputAttribute(Console, &Attr, 1, pos, &Count);

    int bk_col = Attr / 16;
    int col = color % 16;
    col = col + bk_col * 16;

    SetConsoleTextAttribute(Console, col);

    char ch;
    pos = wherexy();
    ReadConsoleOutputCharacter(Console, &ch, 1, pos, &Count);
    cout << ch;
    gotoxy(pos.X, pos.Y);
}

void hidecursor(void)
{
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!Console)
        return;

    CONSOLE_CURSOR_INFO buf;
    GetConsoleCursorInfo(Console, &buf);
    buf.bVisible = 0;
    SetConsoleCursorInfo(Console, &buf);
}

