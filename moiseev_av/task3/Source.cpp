#include <iostream>
#include <cstdlib>
#include <clocale>
#include "Console.h"

using namespace std;


class TextEditor {

public:
	TextEditor(int x, int y, int length) {
		
		this->x = x;
		this->y = y;
		this->length = length;

		if (!CorrectValue())
		{
			cout << "Incorrect value." << endl;
			return;
		}

		gotoxy(x, y);
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
	string a = "";
	cin >> a;
	
}