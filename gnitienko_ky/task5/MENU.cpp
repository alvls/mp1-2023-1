#include <iostream>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include "Header.h"

using namespace std;

void place_editor(short X, short Y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleCursorPosition(hConsole, pos);
	Y = Y + 10;
	X = 60 - X;
	SetConsoleCursorPosition(hConsole, { X, Y });
}

int menu(char* menu[], int j) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
	int key = 1;
	int code = 0;
	COORD cursor;
	do {
		system("cls");
		if (code == KEY_ARROW_UP) key--;
		if (code == KEY_ARROW_DOWN) key++;
		if (key < 1) key = j - 1;
		if (key > j - 1) key = 1;
		SetConsoleTextAttribute(hStdOut, 9);
		for (int i = 0; i < j; i++) {
			if (i == 0) {
				SetConsoleTextAttribute(hStdOut, 5);
			}
			else SetConsoleTextAttribute(hStdOut, 9);
			place_editor(strlen(menu[i]) / 2, i);
			cout << menu[i] << endl;
		}
		SetConsoleTextAttribute(hStdOut, 11);
		cursor.Y = key;
		cursor.X = 0;
		SetConsoleCursorPosition(hStdOut, cursor);
		place_editor(strlen(menu[key]) / 2 + 2, key);
		cout << "->" << menu[key] << "<-";
		if ((code = _getch()) == KEY_EXIT) {
			key = KEY_EXIT;
			break;
		}
	} while ((code = _getch()) != KEY_ENTER);
	return key;
}