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
	cout << "Для удобства работы создан путь к файлу по умолчанию. Находится в папке с Source" << endl;
	cout << "При создании повторяющегося контакта сохраняются его старые значения." << endl;
	cout << "Приятной работы" << endl;
	system("pause");
	system("cls");
}
void create_new_contact(Contacts& contact, Storage& list)
{
	string name, surname, patronymic, phone;
	string YesNo[] = { "\t\t Добавить в избранное?", "> Да", "> Нет" };
	int day, month, year, func_prev;
	bool favourite;
	system("cls");
	cout << "Введите ФИО контакта:" << endl;
	cin >> surname;
	cin >> name;
	cin >> patronymic;
	contact.set_name(name);
	contact.set_surname(surname);
	contact.set_patronymic(patronymic);
	if (list.is_exist(contact))
	{
		system("cls");
		cout << "Ошибка. Этот контакт уже есть в вашей телефонной книге" << endl;
		system("pause");
		return;
	}
	cout << "\nВведите номер телефона в формате +00000000000" << endl;
	cin >> phone;
	cout << "Введите дату рождения в цифровом формате (разделение через Enter):" << endl;
	cin >> day;
	cin >> month;
	cin >> year;
	cout << "Вы хотите добавить этот контакт в избаранные?" << endl;
	func_prev = menu_mode_clear(YesNo, 3);
	switch (func_prev)
	{
	case 1:
		favourite = true;
		break;
	case 2:
		favourite = false;
		break;
	}
	contact.set_phone(phone);
	contact.set_day(day);
	contact.set_month(month);
	contact.set_year(year);
	contact.set_favourite(favourite);
	list.create_contact(contact);
	if (list.is_exist(contact))
	{
		cout << "Ошибка. Этот контакт уже есть в вашей телефонной книге" << endl;
		system("pause");
	}
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