#include "Header.h"

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
int get_segment()
{
	int seg=0;
	do 
	{
		system("cls");
		cout << "Введите количество сегментов (прямоугольников) - ";
		cin >> seg;
	} while (seg < 1);
	return seg;
}
double* get_lim()
{
	double lims[2];
	do
	{
		system("cls");
		cout << "Введите левый предел - ";
		cin >> lims[0];
		cout << "\nВведите правый предел - ";
		cin >> lims[1];
	} while (lims[0] > lims[1]);
	system("cls");
	cout << "Левый предел: " << lims[0] << endl;
	cout << "Правый предел: " << lims[1] << endl;
	system("pause");
	system("cls");
	return lims;
}
double line(double x)
{
	return x;
}
void exit_prog()
{
	system("cls");
	cout << "Спасибо за использование программы!" << endl;
	cout << "До свидания" << endl;
	system("pause");
	exit(0);
}
void hello()
{
	cout << "Добро пожаловать в калькулятор интегралов" << endl;
	cout << "Данная программа выполняет свои расчеты методом прямоугольников" << endl;
	cout << "В процессе подсчета вы сможете выбрать подметод." << endl; 
	system("pause");
	system("cls");
}