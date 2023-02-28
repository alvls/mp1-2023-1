/* ���������� ����������� ����� "������������ �����". 
����� ������ ������� ���������� ����� (����������� �� ����� 0) � ��������� � ���� 4 ����������� �������������� ��������. 
����� ������ ��������� � ������������ ����. ����� ������ ��������� ��� ����������� ������������, � ����� ������� �������� ���� �� �������.*/

#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include "design.h"
using namespace std;

class RationalFraction
{
	long numerator; //���������, ������������� �� ������
	unsigned long denominator; //����������� �����������
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
	void Optimization()//���������� ����� � ������������� ����
	{
		if (numerator == 0)//���� ��������� 0, ������������� ���: 0/1
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
	long ToCommonDenominator(long a, unsigned long b)//���������� ������ � ������ ����������� (��� �������� � ���������) 
	{
		numerator *= b;
		a *= denominator;
		denominator *= b;
		return a;
	}
	void MultipAndDiv(long a, long b)//������ ��� ��������� � �������
	{
		if (b == 0)
		{
			cout << "������! ������� �� 0 ����������." << endl;
			return;
		}
		numerator *= a;
		denominator *= b;
	}
public: 
	RationalFraction()//�������� "������ �����" ��� ����������� ���������
	{
		numerator = 1;
		denominator = 1;
	}
	RationalFraction(long a,unsigned long b)//"�������" �����
	{
		numerator = a;
		denominator = b;
		Optimization();
	}
	void GetFraction()
	{
		system("cls");
		Optimization();
		cout << "���������: " << numerator << "/" << denominator << endl;
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
RationalFraction SecondFraction()//�������� ��������� ����� ��� ����������
{
	long a;
	unsigned long b;
	RationalFraction EmptySecond;
	cout << "\n������� ��������� �����: ";
	cin >> a;
	do
	{
		cout << "\n������� ����������� �����: ";
		cin >> b;
	} while (b == 0);
	RationalFraction SecondFraction(a, b);
	EmptySecond = SecondFraction;
	return EmptySecond;
}

int menu_mode(char* arr[], int size, RationalFraction r);//������������� ����
void exit_prog();

void main()
{
	setlocale(LC_ALL, "Russian");
	system("title ����������� ������������� ������");
	hidecursor();
	cout << "����� ���������� � ����������� ������������ ������!" << endl;
	cout << "��� ������ ��� ����������� ������ ��������� � ����������� ������ �����," << endl;
	cout << "����� ������� �������� �, �� �������������, ������ ������ ��������� �����. � ��� �������, ������� ����������" << endl;
	cout << "�����! ���� ����� ����������� ������ � ����������." << endl;
	system("pause");
	system("cls");
start:
	long a;
	unsigned long b=1;
	cout << "������� ��������� ����� (�������� ����): ";
	cin >> a;
	do 
	{
		cout << "\n������� ����������� �����: ";
		cin >> b;
		if (b == 0) cout << "����������� �� ����� ���� ����� 0!";
	} while (b == 0);
	RationalFraction fraction(a, b);
	system("cls");
	char* functions[] = {"\t\t�������� ����������� �������:","> ��������","> ���������", "> ���������", "> �������", "> ����� ����������", "> ����� �� ���������", };
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
	cout << "������� �� ������������� ���������!" << endl;
	cout << "�� ��������" << endl;
	system("pause");
	exit(0);
}