#include <iostream>
#include <cstdlib>
#include <clocale>
#include <conio.h>
#include "Console.h"

using namespace std;


class TextEditor {

public:

	enum KEYS {
		BACKSPACE = 8,
		ENTER = 13,
		SPACE = 32,
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77
	};

	TextEditor(int x, int y, int length) {
		
		this->x = x;
		this->y = y;
		this->length = length;

		if (!CorrectValue())
		{
			cout << "Incorrect value." << endl;
			return;
		}

		cout << "TextEditorParametric(X = " << x << ", Y = " << y << ", Length = " << length << ")";
	}

	void Text() {

		gotoxy(x, y);

		char c;
		while (c = _getch() != ENTER)
		{

		}

	}

private:
	int x, y, length;

	bool CorrectValue() {
		
		if (x < 0 || y < 0 || length < 0)
		{
			return false;
		}

		COORD wnd;
		SMALL_RECT rect;

		getwindow(&rect, &wnd);

		if (wnd.X - x - length - 1 < 0)
		{
			return false;
		}

		return true;
	}
};

void main() {

	setlocale(LC_ALL, "");

	TextEditor edit(5, 5, 10);
	edit.Text();
}