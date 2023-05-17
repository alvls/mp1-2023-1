#pragma once
using namespace std;
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <locale>
#include <string>
#include <conio.h>
#include <vector>
#define INITIALSIZE 5

enum { LOSE=0, WIN, PLAY };
enum { ST_LOSE, ST_WIN };
enum TColor 
{
    BLACK=0, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
    LIGHTMAGENTA, YELLOW, WHITE
};
enum direct { UP, DOWN, LEFT, RIGHT };
enum exit_menu { NEWGAME = 1, EXIT};
enum dir_key
{
	UPKEY= 72,
	LEFTKEY = 75,
	RIGHTKEY = 77,
	DOWNKEY = 80
};


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
void gotoxy(const COORD pos)
{
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, pos);
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
	gotoxy(pos);
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

void exit_prog()
{
	system("cls");
	cout << "Спасибо за использование программы!" << endl;
	cout << "До свидания" << endl;
	system("pause");
	exit(0);
}

int menu_mode(string* arr, int size)
{
	char ch = 0;
	int choice = 1, i;
	while (ch != 13)
	{
		system("cls");
		for (i = 0; i < size; i++)
		{
			if (i == choice)
			{
				textcolor(LIGHTMAGENTA);
			}
			else
			{
				textcolor(WHITE);
			}
			std::cout << arr[i] << endl;
		}
		hidecursor();
		textcolor(WHITE);
		ch = _getch();
		if (ch == -32)
			ch = _getch();
		switch (ch)
		{
		case 72:
			choice--;
			break;
		case 80:
			choice++;
			break;
		case 27:
			exit_prog();
		case 37:
			return -1;
		}
		if (choice >= size)
			choice = 1;
		if (choice < 1)
			choice = size - 1;
	}
	return choice;
}

void hello()
{
	cout << "Добро пожаловать в игру змейка." << endl;
	cout << "Перед началом игры нужно установить несколько параметров." << endl;
}

#include "Field.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"