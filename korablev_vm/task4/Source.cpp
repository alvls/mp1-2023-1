#include "header.h"

//Разработать класс Контакты.
//Класс должен хранить информацию о контактах владельца.
// Каждый контакт содержит следующие данные : фамилия; имя; отчество; 
//	телефон; 
//	день рождения(день, месяц, год);
//	признак, относится ли контакт к избранным.
//Контакты хранятся упорядоченно по фамилии, имени, отчеству.
//Фамилия, имя, отчество(ФИО) являются обязательными полями.Данные вводятся на русском языке.
//Класс должен содержать необходимые служебные методы.
//Класс должен предоставлять следующие операции : 
// 1) создать новый контакт, 2) изменить выбранный контакт
// 3) найти контакт по ФИО, 4) найти контакт по телефону, 
// 5) выдать все контакты на заданную букву, 6) узнать текущее число контактов, 
// 7) внести контакт в список избранных, 8) удалить контакт из списка избранных,
// 9) выдать все избранные контакты, 10) удалить контакт, 
// 11) сохранить контакты в файл, 12) считать контакты из файла.

int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	system("title Телефонная книга");
	system("cls");
	hello();
	Storage storage;
	string main_func[] = { "\t\t Выберите желаемую функцию:", "> Создать новый контакт", "> Вывести список контактов", "> Найти контакт по ФИО", "> Найти контакт по телефону ", "> Контакты на заданную букву", "> Избранные контакты", "> Текущее число контактов", "> Сохранить в файл", "> Экспорт из файла" };
	string contact_func[] = { "\t\t Выберите желаемую функцию:", "> Изменить контакт", "> Изменить статус избранного", "> Удалить контакт", "> Вернуться назад"};
	string name, surname, patronymic, phone, way;
	Contacts temp;
	size_t size;
	int day, month, year;
	char letter;
	int func_menu;
	int func_list = 1;
	int func_contact = 1;
	bool active = true;
	bool active_contact = true;
	while (active)
	{
		func_menu = menu_mode_clear(main_func, 10);
		switch (func_menu)
		{
		case 1:
			create_new_contact(temp, storage);
			break;
		case 2:
			size = storage.get_contacts_count();
			if (size > 0)
			{
				func_list = menu_mode_list(storage);
				active_contact = true;
				while (active_contact && func_list >= 0)
				{
					func_contact = menu_mode_contact(contact_func, 5, storage[func_list]);
					switch (func_contact)
					{
					case 1:
						cout << "Введите ФИО контакта:" << endl;
						cin >> surname;
						cin >> name;
						cin >> patronymic;
						cout << "\nВведите номер телефона в формате +00000000000" << endl;
						cin >> phone;
						cout << "\nВведите дату рождения в цифровом формате (разделение через пробел или Enter):" << endl;
						cin >> day;
						cin >> month;
						cin >> year;
						storage.change_contact(name, surname, patronymic, phone, day, month, year, storage[func_list].favourite_contact(), func_list);
						break;
					case 2:
						if (storage[func_list].favourite_contact())
							storage[func_list].set_favourite_false();
						else
							storage[func_list].set_favourite_true();
						break;
					case 3:
						if (storage.get_contacts_count() > 1)
						{
							storage.delete_contact(func_list);
							active_contact = false;
						}
						else
						{
							system("cls");
							cout << "Ошибка! В вашей телефонной книге должен быть хотя бы 1 контакт." << endl;
							system("pause");
						}
						break;
					case 4:
						active_contact = false;
						break;
					}
				}
			}
			break;
		case 3:
			system("cls");
			cout << "Введите ФИО контакта:" << endl;
			cin >> surname;
			cin >> name;
			cin >> patronymic;
			storage.contacts_by_name(name, surname, patronymic);
			system("pause");
			break;
		case 4:
			cout << "\nВведите номер телефона в формате +00000000000" << endl;
			cin >> phone;
			storage.contacts_by_phone(phone);
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "Введите желаемую букву для поиска - ";
			cin >> letter;
			system("cls");
			storage.contacts_by_letter(letter);
			system("pause");
			break;
		case 6:
			system("cls");
			storage.print_favourite_contacts();
			system("pause");
			break;
		case 7:
			system("cls");
			cout << "Текущее число контактов: " << storage.get_contacts_count() << endl;
			system("pause");
			break;
		case 8:
			system("cls");
			way = get_way();
			system("cls");
			storage.save_file(way);
			cout << "Сохранено" << endl;
			system("pause");
			break;
		case 9:
			system("cls");
			way = get_way();
			storage.load_file(way);
			system("cls");
			cout << "Данные прочитаны" << endl;
			system("pause");
			break;
		}
	}
	return 0;
}