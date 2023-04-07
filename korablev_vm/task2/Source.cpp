/* Необходимо разработать класс "Полином".
Класс должен хранить полином (многочлен) от одной переменной (х). Степень полинома n находится в диапазоне от 0 до 12.
Класс должен предоставлять следующие операции: 
	1) задать степень полинома, 
	2) задать коэффициенты мономов полинома, 
	3) узнать степень полинома, 
	4) узнать значение коэффициента по его номеру, 
	5) вычислить значение полинома в заданной точке х, 
	6) найти производную полинома.
Класс должен содержать все необходимые конструкторы, деструктор, а также «уметь» выводить себя на консоль.*/

#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <cmath>
#include "design.h"
using namespace std;

class Polinom
{
	int deg; //степень полинома
	int mon[13] = { 0 };//массив коэффициентов
public:
	Polinom(int dg)
	{
		deg = dg;
	}
	void change_deg(int dg)//изменение степени
	{
		this->deg = dg;
		if (mon[dg] == 0)
			mon[dg] = 1;
	}
	void change_mon(int coef, int index)//задание коэффициента
	{
		this->mon[index] = coef;
	}
	int get_deg()
	{
		return this->deg;
	}
	void correct_deg()
	{
		while (1)
		{
			if (mon[deg] == 0)
				deg--;
			else
				break;
		}
	}
	int get_answ(int num)
	{
		return this->mon[num];
	}
	int get_value(int x)
	{
		int result = 0;
		for (int i = 0; i <= deg; i++)
		{
			result += mon[i] * int(pow(x, i));
		}
		return result;
	}
	void get_result()//красивое отображение полинома на экране
	{
		if (deg > 1)
		{
			if (mon[deg] == 1 && deg > 1)
				cout << noshowpos << "x^" << deg;
			else
				cout << noshowpos << mon[deg] << "x^" << deg;
			for (int i = deg - 1; i > 1; i--)
			{
				if (mon[i] != 0)
					cout << showpos << mon[i] << noshowpos <<"x^" << i;
			}
			if (mon[1] != 0)
				cout << showpos << mon[1] << "x";
			if (mon[0] != 0)
				cout << showpos << mon[0];
		}
		else
		{
			if (deg == 1)
			{
				if (mon[1] == 1)
					cout << "x";
				else if (mon[1] != 0)
					cout << noshowpos << mon[1] << "x";
				if (mon[0] != 0)
					cout << showpos << mon[0];
			}
			else
				cout << noshowpos << mon[0];
		}
		cout << endl;
	}
	Polinom derivative()
	{
		Polinom result(deg - 1);
		for (int i = 1; i <= deg; i++)
		{
			result.change_mon(mon[i] * i,i - 1);
		}
		return result;
	}
};

int menu_mode(string* arr, int size, Polinom r);
void exit_prog();
int set_deg();

void main()
{
	setlocale(LC_ALL, "Russian");
	system("title Редактор полиномов");
	system("chcp 1251");
	system("cls");
	cout << "Добро пожаловать в редактор полиномов!" << endl;
	system("pause");
	system("cls");
	int x, coef, answ, pol_deg;
	Polinom der(0);
	Polinom pol(0);
	string functions[] = { "\t\tВыберите желаемое действие:","> Задать новый полином","> Задать степень полинома","> Задать коэффициенты мономов", "> Узнать степень полинома", "> Узнать значение коэффициента", "> Вычислить значение полинома", "> Вычислить производную полинома", "> Выйти из программы" };
	while (1)
	{
		pol_deg = 0;
		int funct = menu_mode(functions, 9, pol);
		system("cls");
		switch (funct)
		{
		case 1:
			pol_deg = set_deg();
			pol.change_deg(pol_deg);
			cout << "Введите коэфициенты (по возрастанию степени):" << endl;
			for (int i = 0; i <= pol_deg; i++)
			{
				cin >> coef;
				pol.change_mon(coef, i);
			}
			pol.correct_deg();
			break;
		case 2:
			pol_deg = set_deg();
			pol.change_deg(pol_deg);
			cout << "Установлена степень полинома " << pol_deg << endl;
			break;
		case 3:
			do
			{
				system("cls");
				cout << "Введите номер необходимого коэффициента (начиная с 0): ";
				cin >> pol_deg;
			} while (pol_deg < 0 || pol_deg > pol.get_deg());;
			cout << "Введите желаемое значение коэфициента: ";
			cin >> coef;
			pol.change_mon(coef, pol_deg);
			pol.correct_deg();
			break;
		case 4:
			answ = pol.get_deg();
			cout << noshowpos << "Степень полинома = " << answ << endl;
			system("pause");
			break;
		case 5:
			do
			{
				system("cls");
				cout << "Введите номер необходимого коэффициента (начиная с 0): ";
				cin >> coef;
			} while (coef < 0 || coef > pol.get_deg());
			answ = pol.get_answ(coef);
			cout << "Коэффициент под номером " << noshowpos << coef << " = " << answ << endl;
			system("pause");
			break;
		case 6:
			cout << "Введите значение, при котором необходимо вычислить результат: ";
			cin >> x;
			answ = pol.get_value(x);
			cout << "Ответ: " << noshowpos << answ << endl;
			system("pause");
			break;
		case 7:
			der = pol.derivative();;
			cout << "Производная полинома = ";
			der.get_result();
			system("pause");
			break;
		case 8:
			exit_prog();
			break;
		}
	}
}

int set_deg()
{
	int deg; 
	do
	{
		system("cls");
		cout << "Введите степень полинома (от 0 до 12): ";
		cin >> deg;
	} while (deg < 0 || deg > 12);
	return deg;
}

int menu_mode(string* arr, int size, Polinom r)
{
	char ch = 0;
	int choice = 1, i;
	while (ch != 13)
	{
		system("cls");
		cout << "Ваш полином: ";
		r.get_result();
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
			cout << arr[i] << endl;
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
		}
		if (choice >= size)
			choice = 1;
		if (choice < 1)
			choice = size - 1;
	}
	return choice;
}
void exit_prog()
{
	system("cls");
	cout << "Спасибо за использование программы!" << endl;
	cout << "До свидания" << endl;
	system("pause");
	exit(0);
}