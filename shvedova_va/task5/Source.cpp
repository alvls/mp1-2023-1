//БАЗА КЛИЕНТОВ
//1) Иванов Иван Иванович
//номер карты: 1234
//PIN - код: 0102
//баланс: 100500
//2) Кольцова Ольга Николаевна
//номер карты : 9876
//PIN - код : 5443
//баланс : 2001456
//3) Голубев Леонид Алексеевич
//номер карты : 3456
//PIN - код : 1234
//баланс : 100000000
//4) Львов Лев Львович
//номер карты : 0009
//PIN - код : 1212
//баланс : 1789345
//5) Кошкина Мария Александровна
//номер карты : 5566
//PIN - код : 9988
//баланс : 4694366
//6) Медведева Камила Михайловна
//номер карты : 2730
//PIN - код : 1111
//баланс : 3525
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
	Client num1("1234", "Иванов Иван Иванович", 100500, "0102", 1);
	Client num2("9876", "Кольцова Ольга Никоваевна", 2001456, "5443", 1);
	Client num3("3456", "Голубев Леонид Алексеевич", 100000000, "1234", 1);
	Client num4("0009", "Львов Лев Львович", 1789345, "1212", 1);
	Client num5("5566", "Кошкина Мария Александровна", 4694366, "9988", 1);
	Client num6("2730", "Медведева Камила Михайловна", 3525, "1111", 1);
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
		cout << "Введите номер карты: ";
		cin >> card;
		system("cls");
		num = ATM.FindByCard(card);
		if (!ATM.InfAboutClient(num).GetStatus())
			throw (6);
		while (count != 3)
		{
			cout << "Введите PIN - код: ";
			cin >> pin;
			system("cls");
			if (InvalidPIN(pin))
			{
				if (!ATM.CheckPIN(pin, num))
				{
					count++;
					if (count != 3)
						cout << "Неверный PIN - код, попробуйте снова" << endl;
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
					cout << "Недопустимый PIN - код" << endl;
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
			cout << ATM.InfAboutClient(num).GetFIO() << ", пожалуйста, выберите операцию:" << endl << "1) узнать состояние счета"
				<< endl << "2) снять наличные" << endl << "3) внести наличные" << endl << "4) забрать карту" << endl;
			cin >> option;
			system("cls");
			switch (option)
			{
			case 1:
				cout << "Баланс: " << ATM.InfAboutClient(num).GetBalance() << " руб." << endl;
				break;
			case 2:
				cout << "//Снятие наличных//" << endl << "Банкомат поддерживает работу с купюрами ценностью не менее 100 руб."
					<< endl << "Поэтому ваша сумма должна быть кратна 100" << endl
					<< "Максимальная сумма для снятия - 200000 руб." << endl << "Введите сумму: ";
				cin >> money;
				system("cls");
				if ((money % 100 != 0) || (money <= 0) || (money > MaxGetSum))
				{
					cout << "Недопустимая сумма" << endl;
					break;
				}
				else
				{
					if (money > ATM.InfAboutClient(num).GetBalance())
					{
						cout << "Недостаточно средств" << endl;
						break;
					}
					if (ATM.CashOut(num, money))
						cout << "Заберите наличные - " << money << " руб." << endl;
					else
						cout << "В банкомате недостаточно средств" << endl;
				}
				break;
			case 3:
				cout << "//Внесение наличных//" << endl << "Банкомат поддерживает работу с купюрами ценностью не менее 100 руб."
					<< endl << "Поэтому ваша сумма должна быть кратна 100" << endl
					<< "Максимальная сумма для внесения на счет - 200000 руб." << endl << "Введите сумму: ";
				cin >> money;
				system("cls");
				if ((money % 100 != 0) || (money <= 0) || (money > MaxGetSum))
				{
					cout << "Недопустимая сумма" << endl;
					break;
				}
				else
				{
					if (ATM.CashIn(num, money))
						cout << "На ваш счет зачислено - " << money << " руб." << endl;
					else
						cout << "Банкомат переполнен" << endl;
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
				cout << endl << "0 - забрать карту" << endl << "1 - продолжить" << endl;
				cin >> c;
				if (c != 1)
					t = false;
			}
		}
		system("cls");
		cout << "__До свидания, " << ATM.InfAboutClient(num).GetFIO() << "!__" << endl;
		cout << "//Сеанс завершен//" << endl;
	}
	catch (int i)
	{
		switch (i)
		{
		case 1:
			cout << "Введен недопустимый номер карты" << endl;
			break;
		case 2:
			cout << "Пользователь с таким номером карты не найден" << endl;
			break;
		
		case 5:
			cout << "Слишком много попыток, карта заблокирована" << endl;
			break;
		case 6:
			cout << "Карта заблокирована" << endl;
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