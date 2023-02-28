/* Необходимо разработать класс "Рациональная дробь". 
Класс должен хранить корректные дроби (знаменатель не равен 0) и выполнять с ними 4 стандартные арифметические операции. 
Дробь должна храниться в несократимом виде. Класс должен содержать все необходимые конструкторы, а также «уметь» выводить себя на консоль.*/

#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include "design.h"
using namespace std;

class RationalFraction
{
	long numerator; //числитель, запрашивается со знаком
	unsigned long denominator; //беззнаковый знаменатель
	unsigned long NOD(unsigned long a, unsigned long b)
	{
		if (a % b == 0)
			return b;
		if (b % a == 0)
			return a;
		if (a > b)
			return NOD(a % b, b);
		return NOD(a, b % a);
	}
	void Optimization()//Приведение дроби к несократимому виду
	{
		if (numerator == 0)//если числитель 0, нескократимый вид: 0/1
		{
			denominator = 1;
			return;
		}
		unsigned long nm_tmp, nod;
		if (numerator < 0)
			nm_tmp = (-1) * numerator;
		else
			nm_tmp = numerator;
		nod = NOD(nm_tmp, denominator);
		numerator /= long (nod);
		denominator /= nod;
	}
	long ToCommonDenominator(long a, unsigned long b)//Приведение дробей к общему знаменателю (для сложения и вычитания) 
	{
		numerator *= b;
		a *= denominator;
		denominator *= b;
		return a;
	}
	void MultipAndDiv(long a, long b)//шаблон для умножения и деления
	{
		if (b == 0)
		{
			cout << "Ошибка! Деление на 0 невозможно." << endl;
			return;
		}
		numerator *= a;
		denominator *= b;
	}
public: 
	RationalFraction()//создание "пустой дроби" для дальнейшего изменения
	{
		numerator = 1;
		denominator = 1;
	}
	RationalFraction(long a,unsigned long b)//"рабочая" дробь
	{
		numerator = a;
		denominator = b;
		Optimization();
	}
	void GetFraction()
	{
		system("cls");
		Optimization();
		cout << "Результат: " << numerator << "/" << denominator << endl;
	}
	void Summation(RationalFraction fraction)
	{
		long num = fraction.numerator;
		unsigned long den = fraction.denominator;
		num = ToCommonDenominator(num, den);
		numerator += num;
	}
	void Subtraction(RationalFraction fraction)
	{
		long num = fraction.numerator;
		unsigned long den = fraction.denominator;
		num = ToCommonDenominator(num, den);
		numerator -= num;
	}
	void Multiplication(RationalFraction fraction)
	{
		long num = fraction.numerator;
		unsigned long den = fraction.denominator;
		MultipAndDiv(num,den);
	}
	void Division(RationalFraction fr)
	{
		long num = fr.numerator;
		long den = long (fr.denominator);
		if (num < 0)
		{
			den *= -1;
			num *= -1;
		}
		num = unsigned long(num);
		MultipAndDiv(den,num);
	}
};
RationalFraction SecondFraction()//загрузка следующей дроби для вычислений
{
	long a;
	unsigned long b;
	RationalFraction EmptySecond;
	cout << "\nВведите числитель дроби: ";
	cin >> a;
	do
	{
		cout << "\nВведите знаменатель дроби: ";
		cin >> b;
	} while (b == 0);
	RationalFraction SecondFraction(a, b);
	EmptySecond = SecondFraction;
	return EmptySecond;
}

int menu_mode(char* arr[], int size, RationalFraction r);//интерактивное меню
void exit_prog();

void main()
{
	setlocale(LC_ALL, "Russian");
	system("title Калькулятор рациоенальных дробей");
	system("chcp 1251");
	system("cls");
	hidecursor();
	cout << "Добро пожаловать в калькулятор рациональных дробей!" << endl;
	cout << "Для начала вам понадобится ввести числитель и знаменатель первой дроби," << endl;
	cout << "затем выбрать операцию и, по необходимости, ввести данные следующей дроби. И так столько, сколько необходимо" << endl;
	cout << "Важно! Знак дроби указывается вместе с числителем." << endl;
	system("pause");
	system("cls");
start:
	long a;
	unsigned long b=1;
	cout << "Введите числитель дроби (учитывая знак): ";
	cin >> a;
	do 
	{
		cout << "\nВведите знаменатель дроби: ";
		cin >> b;
		if (b == 0) cout << "Знаменатель не может быть равен 0!";
	} while (b == 0);
	RationalFraction fraction(a, b);
	system("cls");
	char* functions[] = {"\t\tВыберите необходимую функцию:","> Сложение","> Вычитание", "> Умножение", "> Деление", "> Новое вычисление", "> Выйти из программы", };
	RationalFraction NextFraction;
	int repeat = 1;
	while (repeat == 1)
	{
		int funct = menu_mode(functions,7,fraction);
		system("cls");
		switch (funct)
		{
		case 1:
			NextFraction = SecondFraction();
			fraction.Summation(NextFraction);
			break;
		case 2:
			NextFraction = SecondFraction();
			fraction.Subtraction(NextFraction);
			break;
		case 3:
			NextFraction = SecondFraction();
			fraction.Multiplication(NextFraction);
			break;
		case 4:
			NextFraction = SecondFraction();
			fraction.Division(NextFraction);
			break;
		case 5:
			goto start;
			break;
		case 6:
			exit_prog();
			break;
		}
	}
}


int menu_mode(char* arr[], int size, RationalFraction r)
{
	char ch = 0;
	int choice = 1, i;
	while (ch != 13)
	{
		r.GetFraction();
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
			printf("%s \n", arr[i]);
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