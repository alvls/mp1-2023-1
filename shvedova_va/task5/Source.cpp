//���� ��������
//1) ������ ���� ��������
//����� �����: 1234
//PIN - ���: 0102
//������: 100500
//2) �������� ����� ����������
//����� ����� : 9876
//PIN - ��� : 5443
//������ : 2001456
//3) ������� ������ ����������
//����� ����� : 3456
//PIN - ��� : 1234
//������ : 100000000
//4) ����� ��� �������
//����� ����� : 0009
//PIN - ��� : 1212
//������ : 1789345
//5) ������� ����� �������������
//����� ����� : 5566
//PIN - ��� : 9988
//������ : 4694366
//6) ��������� ������ ����������
//����� ����� : 2730
//PIN - ��� : 1111
//������ : 3525
#include <iostream>
#include <locale>
#include <conio.h>
#include "CashMachine.h"
bool InvalidPIN(string p)
{
	if (p.length() != 4)
		return false;
	if ((p < "0000") || (p > "9999"))
		return false;
	return true;
}
void Options()
{
	Client tmp;
	Client num1("1234", "������ ���� ��������", 100500, "0102", 1);
	Client num2("9876", "�������� ����� ����������", 2001456, "5443", 1);
	Client num3("3456", "������� ������ ����������", 100000000, "1234", 1);
	Client num4("0009", "����� ��� �������", 1789345, "1212", 1);
	Client num5("5566", "������� ����� �������������", 4694366, "9988", 1);
	Client num6("2730", "��������� ������ ����������", 3525, "1111", 1);
	ProcessingCenter ProcCen;
	CashMachine ATM;
	string card, pin;
	int option, num, c, money, count = 0;
	bool t = true;
	ProcCen.AddClient(num1);
	ProcCen.AddClient(num2);
	ProcCen.AddClient(num3);
	ProcCen.AddClient(num4);
	ProcCen.AddClient(num5);
	ProcCen.AddClient(num6);
	ATM.CreateClientBase(ProcCen);
	try
	{
		cout << "������� ����� �����: ";
		cin >> card;
		system("cls");
		num = ATM.FindByCard(card);
		if (!ATM.InfAboutClient(num).GetStatus())
			throw (6);
		while (count != 3)
		{
			cout << "������� PIN - ���: ";
			cin >> pin;
			system("cls");
			if (InvalidPIN(pin))
			{
				if (!ATM.CheckPIN(pin, num))
				{
					count++;
					if (count != 3)
						cout << "�������� PIN - ���, ���������� �����" << endl;
					else
					{
						ATM.InfAboutClient(num).ChangeStatus(0);
						throw (5);
					}
				}
				else
					break;
			}
			else
			{
				count++;
				if (count != 3)
					cout << "������������ PIN - ���" << endl;
				else
				{
					ATM.InfAboutClient(num).ChangeStatus(0);
					throw (5);
				}
			}
		}
		while (t)
		{
			system("cls");
			cout << ATM.InfAboutClient(num).GetFIO() << ", ����������, �������� ��������:" << endl << "1) ������ ��������� �����"
				<< endl << "2) ����� ��������" << endl << "3) ������ ��������" << endl << "4) ������� �����" << endl;
			cin >> option;
			system("cls");
			switch (option)
			{
			case 1:
				cout << "������: " << ATM.InfAboutClient(num).GetBalance() << " ���." << endl;
				break;
			case 2:
				cout << "//������ ��������//" << endl << "�������� ������������ ������ � �������� ��������� �� ����� 100 ���."
					<< endl << "������� ���� ����� ������ ���� ������ 100" << endl
					<< "������������ ����� ��� ������ - 200000 ���." << endl << "������� �����: ";
				cin >> money;
				system("cls");
				if ((money % 100 != 0) || (money <= 0) || (money > MaxGetSum))
				{
					cout << "������������ �����" << endl;
					break;
				}
				else
				{
					if (money > ATM.InfAboutClient(num).GetBalance())
					{
						cout << "������������ �������" << endl;
						break;
					}
					if (ATM.CashOut(num, money))
						cout << "�������� �������� - " << money << " ���." << endl;
					else
						cout << "� ��������� ������������ �������" << endl;
				}
				break;
			case 3:
				cout << "//�������� ��������//" << endl << "�������� ������������ ������ � �������� ��������� �� ����� 100 ���."
					<< endl << "������� ���� ����� ������ ���� ������ 100" << endl
					<< "������������ ����� ��� �������� �� ���� - 200000 ���." << endl << "������� �����: ";
				cin >> money;
				system("cls");
				if ((money % 100 != 0) || (money <= 0) || (money > MaxGetSum))
				{
					cout << "������������ �����" << endl;
					break;
				}
				else
				{
					if (ATM.CashIn(num, money))
						cout << "�� ��� ���� ��������� - " << money << " ���." << endl;
					else
						cout << "�������� ����������" << endl;
				}
				break;
			case 4:
				t = false;
				break;
			default:
				break;
			}
			if (t)
			{
				cout << endl << "0 - ������� �����" << endl << "1 - ����������" << endl;
				cin >> c;
				if (c != 1)
					t = false;
			}
		}
		system("cls");
		cout << "__�� ��������, " << ATM.InfAboutClient(num).GetFIO() << "!__" << endl;
		cout << "//����� ��������//" << endl;
	}
	catch (int i)
	{
		switch (i)
		{
		case 1:
			cout << "������ ������������ ����� �����" << endl;
			break;
		case 2:
			cout << "������������ � ����� ������� ����� �� ������" << endl;
			break;
		
		case 5:
			cout << "������� ����� �������, ����� �������������" << endl;
			break;
		case 6:
			cout << "����� �������������" << endl;
			break;

		}
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("cls");
	Options();
	system("pause");
	return 0;
}