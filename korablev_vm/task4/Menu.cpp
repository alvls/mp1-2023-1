//меню и функции для main
#include "header.h"

int menu_mode_clear(string* arr, int size)
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
		case 37:
			return -1;
		}
		if (choice >= size)
			choice = 1;
		if (choice < 1)
			choice = size - 1;
	}
	return choice;
}
int menu_mode_contact(string* arr, int size, Contacts& contact)
{
	char ch = 0;
	int choice = 1, i;
	while (ch != 13)
	{
		system("cls");
		contact.print_contact();
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
		case 37:
			return -1;
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
int menu_mode_list(Storage& list)
{
	int size = list.get_contacts_count();
	char ch = 0;
	int choice = 0, i;
	bool next = true;
	while (ch != 13 && next == true)
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
			cout << i << ")";
			list[i].print_contact_lite();
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
		case 37:
			next == false;
			return -1;
			break;
		case 27:
			exit_prog();
		}
		if (choice >= size)
			choice = 0;
		if (choice < 0)
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
void hello()
{
	cout << "Добро пожаловать в вашу телефонную книгу" << endl;
	cout << "Эта инструкция появится один раз и в дальнейшем не будет вам мешать" << endl;
	cout << "Приятной работы" << endl;
	system("pause");
	system("cls");
}
string get_way()
{
	string way;
	cout << "Введите путь к файлу(для использования файла по умолчанию введите default): ";
	cin >> way;
	if (way == "default")
		way = "MyPhoneBook.txt";
	return way;
}