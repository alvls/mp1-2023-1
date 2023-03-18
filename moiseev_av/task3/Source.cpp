#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "Console.h"

using namespace std;


class TextEditor {

public:
	TextEditor(string label, int x, int y, int length) : label(label), x(x), y(y), length(length) {

		CorrectValue();
	}

	TextEditor(const TextEditor& sourse) = default;

	TextEditor& operator=(const TextEditor& sourse) = default;

	int get_length() const {

		return length;
	}

	pair<int, int> get_xy() const {

		return pair<int, int>(x, y);
	}

	string get_label() const {

		return label;
	}

	string Text() {
		
		int deleting_len = length;
		int len_label = label.length();
		int origin_x = wherex();
		int origin_y = wherey();

		if (x > len_label)
		{
			deleting_len += len_label;

			gotoxy(x - len_label, y);
			cout << label;
		}

		gotoxy(x, y);
		textbackground(WHITE);
		textcolor(BLACK);

		for (int i = 0; i < length; i++)
		{
			gotoxy(x + i, y);
			cout << ' ';
		}

		gotoxy(x, y);

		string line = "";
		int position = 0;
		char c;

		while ((c = _getch()) != ENTER)
		{	
			if (c == BACKSPACE)
			{
				if (position > 0)
				{
					position--;
					gotoxy(wherex() - 1, y);
					cout << ' ';
					line.erase(position);
					gotoxy(wherex() - 1, y);
				}
				continue;
			}
			
			if (line.length() == length)
			{
				continue;
			}

			position++;
			line += c;
			cout << c;
		}

		textbackground(BLACK);
		textcolor(WHITE);

		int dx = x - len_label;

		for (int i = 0; i < deleting_len; i++)
		{
			gotoxy(dx + i, y);
			cout << ' ';
		}

		gotoxy(origin_x, origin_y);
		return line;
	}

	friend ostream& operator <<(ostream& stream, const TextEditor& sourse) {

		stream << "Text editor parametric [Label = '" << sourse.label << "', X = " << sourse.x << ", Y = " << sourse.y << ", Length = " << sourse.length << "]" << endl;
		return stream;
	}

private:
	string label;
	int x, y, length;

	enum KEYS {

		BACKSPACE = 8,
		ENTER = 13,
	};

	void CorrectValue() {

		HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
		if (!Console)
		{
			throw exception("console is none");
		}
			
		if (x < 0 || y < 0 || length < 0)
		{
			throw invalid_argument("invalid values");
		}

		COORD wnd;
		SMALL_RECT rect;
		getwindow(&rect, &wnd);

		if (wnd.X - x - length - 1 < 0)
		{
			throw invalid_argument("X is oversize");
		}
	}
};


int main() {

	TextEditor line1("Name: ", 47, 5, 15);
	TextEditor line2("Surname: ", 50, 5, 20);
	
	cout << line1 << line2 << endl;

	cout << line1.get_label() << "'" << line1.Text() << "'" << endl;
	cout << line2.get_label() << "'" << line2.Text() << "'" << endl;

	return EXIT_SUCCESS;
}
