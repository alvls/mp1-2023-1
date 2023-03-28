#include <iostream>
#include <locale>
#include <Windows.h>
#include <conio.h>
using namespace std;
class TextRedactor
{
private:
	char* str;
	int length;
	int x, y;
public:
	TextRedactor()
	{
		str = new char[2];
		length = 1;
		str[length] = '\0';
		x = 0;
		y = 0;
	}
	void NewLength(int l)
	{
		delete[] str;
		length = l;
		str = new char[length + 1];
		str[length] = '\0';
	}
	int AskLength()
	{
		return length;
	}
	void Position(int X, int Y)
	{
		x = X;
		y = Y;
	}
	int AskX()
	{
		return x;
	}
	int AskY()
	{
		return y;
	}
	void StrInput()
	{
		int c = 0;
		char ss;
		while (c != length)
		{
			ss = _getch();
			str[c] = ss;
			cout << str[c];
			c++;
		}
	}
	char* ReturnStr()
	{
		return str;
	}
	~TextRedactor()
	{
		delete[] str;
	}
};
void SetRedactor(int x, int y)
{
	COORD position = { x,y };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}
void Options()
{
	TextRedactor s;
	int operation, x, y, l, t;
	while (1)
	{
		system("cls");
		cout << "1) задать длину поля ввода" << endl << "2) узнать длину поля ввода" << endl << "3) задать позицию поля ввода в окне консоли" << endl << "4) узнать позицию поля ввода в окне консоли" << endl
			<< "5) ввести строку" << endl << "6) выдать строку" << endl;
		cin >> operation;
		system("cls");
		switch (operation)
		{
		case 1:
			cout << "Введите новую длину поля: " << endl;
			cin >> l;
			system("cls");
			s.NewLength(l);
			cout << "Длина поля изменена" << endl;
			break;
		case 2:
			cout << "Текущая длина поля: " << s.AskLength() << endl;
			break;
		case 3:
			cout << "Введите координату X: ";
			cin >> x;
			cout << "Введите координату Y: ";
			cin >> y;
			s.Position(x, y);
			break;
		case 4:
			cout << "Позиция поля ввода:" << endl;
			cout << "x = " << s.AskX() << endl;
			cout << "y = " << s.AskY() << endl;
			break;
		case 5:
			SetRedactor(s.AskX(), s.AskY());
			s.StrInput();
			break;
		case 6:
			SetRedactor(s.AskX(), s.AskY());
			cout << "Текущая строка: " << s.ReturnStr() << endl;
			break;
		}
		cout << endl << "0 - завершить" << endl << "1 - вернуться к выбору операции" << endl;
		cin >> t;
		if (t != 1)
			break;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	Options();
	system("cls");
	system("pause");
	return 0;
}