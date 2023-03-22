#include <iostream>
#include <cstdlib>
#include <conio.h>

#include "Console.h"
#include "TextEditor.h"

using namespace std;

enum Keycodes {

	Enter = 13,
	Backspace = 8,
	Delete = 83,
	Left = 75,
	Right = 77,
	Special = -32, //Такие клавиши как: LEFT, RIGHT, DEL состоят из 2х символов, один из которых: Special
};

TextEditor::TextEditor(string label, int x, int y, int length)
	: label(label)
	, x(x)
	, y(y)
	, length(length) {

	verify_value();
}

int TextEditor::get_length() const {

	return length;
}

pair<int, int> TextEditor::get_xy() const {

	return pair<int, int>(x, y);
}

string TextEditor::get_label() const {

	return label;
}

void reprint_line(string& str, int length, int x) {

	int len = length - str.length();
	int origin_x = wherex();

	gotoxy(x, wherey());
	cout << str;

	for (int i = 0; i < len; i++)
	{
		cout << ' ';
	}
	gotoxy(origin_x, wherey());
}

string TextEditor::read() {

	int label_len = label.length();
	int deleting_len = length + label_len;

	int origin_x = wherex();
	int origin_y = wherey();

	gotoxy(x - label_len, y);
	cout << label;
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
	char c;

	int position = 0, line_len, offset;
	bool special_key = false;

	while ((c = _getch()) != Keycodes::Enter)
	{
		line_len = line.length();

		if (c == Keycodes::Special) { special_key = true; continue; }

		if (special_key)
		{
			if ((c == Keycodes::Right && (position < line_len)) || ((c == Keycodes::Left) && (position > 0)))
			{
				offset = (c == Keycodes::Right) ? 1 : (-1);
				position += offset;
				
				gotoxy(wherex() + offset, y);
			}

			else if ((c == Keycodes::Delete) && (position < line_len - 1) && (line_len > 0))
			{
				line = line.substr(0, position + 1) + line.substr(position + 2, line_len);
				reprint_line(line, length, x);
			}

			special_key = false;
			continue;
		}

		if (c == Keycodes::Backspace && position > 0)
		{
			position--;
			gotoxy(wherex() - 1, y);

			line = line.substr(0, position) + line.substr(position + 1, line_len);
			reprint_line(line, length, x);

			continue;
		}

		if (!isprint(static_cast<unsigned char>(c))) continue;

		if (line_len == length || position > length - 1) continue;

		if (position >= line_len) { line += c; cout << c; }

		else
		{
			line = line.substr(0, position) + c + line.substr(position, line.length());
			int ox = wherex();

			gotoxy(x, y);
			cout << line;
			gotoxy(ox + 1, y);
		}

		position++;
	}

	textbackground(BLACK);
	textcolor(WHITE);

	int dx = x - label_len;

	for (int i = 0; i < deleting_len; i++)
	{
		gotoxy(dx + i, y);
		cout << ' ';
	}

	gotoxy(origin_x, origin_y);
	return line;
}

ostream& operator <<(ostream& stream, const TextEditor& source) {

	stream << "Text editor parameters [Label = '" << source.label << "', X = " << source.x;
	stream << ", Y = " << source.y << ", Length = " << source.length << "]" << endl;
	return stream;
}

void TextEditor::verify_value() {

	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)
	{
		throw exception("Console is not available");
	}

	if (x < 0 || y < 0 || length < 0)
	{
		throw invalid_argument("Invalid values");
	}

	if (x < label.length())
	{
		throw invalid_argument("Label is too long for this coords");
	}

	COORD wnd;
	SMALL_RECT rect;
	getwindow(&rect, &wnd);

	if (wnd.X - x - length - 1 < 0)
	{
		throw invalid_argument("X is oversize");
	}
}
