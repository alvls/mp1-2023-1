#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class TextRedactor {
	int len;
	COORD pos;
public:
	TextRedactor() : len(10), pos({ 0,0 }) {};
	void SetLen(int a) {
		len = a;
	}
	int GetLen() {
		return len;
	}
	void set_position(COORD position) {
		pos = position;
	}
	short get_positionX() {
		return  pos.X;
	}
	short get_positionY() {
		return  pos.Y;
	}
	void place_editor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleCursorPosition(hConsole, pos);
		SetConsoleCursorPosition(hConsole, { pos.X, pos.Y });
	}
	string get_str() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, { pos.X, pos.Y });
		string str;
		getline(cin, str);
		if (str.length() > len) {
			str = str.substr(0, len);
		}
		return str;
	}
	~TextRedactor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, pos);
		cout << string(len, ' ');
	}
};

int main() {
	setlocale(LC_ALL, "Rus");
	TextRedactor t;
	string str, str2;
	int a;
	cout << "Введите длину поля ввода: ";
	cin >> a;
	t.SetLen(a);
	cout << "Длина поля ввода равна " << t.GetLen() << endl;
	cout << "Введите X и Y для смены позиции ввода ";
	short x, y;
	cin >> x;
	cin >> y;
	t.set_position({ x,y });
	cout << "Позиция поля ввода " << t.get_positionX() << " " << t.get_positionY();
	cout << endl;
	system("pause");
	system("cls");
	t.place_editor();
	str = t.get_str();
	getline(cin, str);
	if (str.length() > t.GetLen()) {
		str = str.substr(0, t.GetLen());
	}
	system("cls");
	cout << " Ваша строка: " << str << endl;
	system("pause");
}