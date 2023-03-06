/* ���������� ����������� ����� "�������".
����� ������ ������� ������� (���������) �� ����� ���������� (�). ������� �������� n ��������� � ��������� �� 0 �� 12.
����� ������ ������������� ��������� ��������: 
	1) ������ ������� ��������, 
	2) ������ ������������ ������� ��������, 
	3) ������ ������� ��������, 
	4) ������ �������� ������������ �� ��� ������, 
	5) ��������� �������� �������� � �������� ����� �, 
	6) ����� ����������� ��������.
����� ������ ��������� ��� ����������� ������������, ����������, � ����� ������� �������� ���� �� �������.*/

#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <cmath>
#include "design.h"
using namespace std;

class Polinom
{
	int deg; //������� ��������
	int mon[13] = { 0 };//������ �������������
public:
	Polinom(int dg)
	{
		deg = dg;
	}
	void change_deg(int dg)//��������� �������
	{
		this->deg = dg;
		if (mon[dg] == 0)
			mon[dg] = 1;
	}
	void change_mon(int coef, int index)//������� ������������
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
	void get_result()//�������� ����������� �������� �� ������
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
	system("title �������� ���������");
	system("chcp 1251");
	system("cls");
	cout << "����� ���������� � �������� ���������!" << endl;
	system("pause");
	system("cls");
	int x, coef, answ, pol_deg;
	Polinom pol(0);
	Polinom der(0);
	string functions[] = { "\t\t�������� �������� ��������:","> ������ ����� �������","> ������ ������� ��������","> ������ ������������ �������", "> ������ ������� ��������", "> ������ �������� ������������", "> ��������� �������� ��������", "> ��������� ����������� ��������", "> ����� �� ���������" };
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
			cout << "������� ����������� (�� ����������� �������):" << endl;
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
			cout << "����������� ������� �������� " << pol_deg << endl;
			break;
		case 3:
			do
			{
				system("cls");
				cout << "������� ����� ������������ ������������ (������� � 0): ";
				cin >> pol_deg;
			} while (pol_deg < 0 || pol_deg > pol.get_deg());;
			cout << "������� �������� �������� �����������: ";
			cin >> coef;
			pol.change_mon(coef, pol_deg);
			pol.correct_deg();
			break;
		case 4:
			answ = pol.get_deg();
			cout << noshowpos << "������� �������� = " << answ << endl;
			system("pause");
			break;
		case 5:
			do
			{
				system("cls");
				cout << "������� ����� ������������ ������������ (������� � 0): ";
				cin >> coef;
			} while (coef < 0 || coef > pol.get_deg());
			answ = pol.get_answ(coef);
			cout << "����������� ��� ������� " << noshowpos << coef << " = " << answ << endl;
			system("pause");
			break;
		case 6:
			cout << "������� ��������, ��� ������� ���������� ��������� ���������: ";
			cin >> x;
			answ = pol.get_value(x);
			cout << "�����: " << noshowpos << answ << endl;
			system("pause");
			break;
		case 7:
			der = pol.derivative();;
			cout << "����������� �������� = ";
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
		cout << "������� ������� �������� (�� 0 �� 12): ";
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
		cout << "��� �������: ";
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
	cout << "������� �� ������������� ���������!" << endl;
	cout << "�� ��������" << endl;
	system("pause");
	exit(0);
}