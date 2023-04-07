//собственно, сам класс для контактов
#include "header.h"

Contacts::Contacts() 
{
	name = "Имя";
	surname = "Фамилия";
	patronymic = "Отчество";
	phone = "+00000000000";
	day = 1;
	month = 1;
	year = 2000;
	favourite = false;
}
Contacts::Contacts(string _name, string _surname, string _patronymic, string _phone, int _day, int _month, int _year, bool _favourite):
	name(_name), surname (_surname), patronymic(_patronymic), phone (_phone), day(_day), month(_month), year(_year), favourite(_favourite) {}

string Contacts::get_name() { return name; }

string Contacts::get_surname() { return surname; }

string Contacts::get_patronymic() { return patronymic; }

string Contacts::get_phone() { return phone; }

int Contacts::get_day() { return day; }

int Contacts::get_month() { return month; }

int Contacts::get_year() { return year; }

bool Contacts::favourite_contact() { return favourite; }

void Contacts::set_name(string _name) { name = _name; }

void Contacts::set_surname(string _surname) { surname = _surname; }

void Contacts::set_patronymic(string _patronymic) { patronymic = _patronymic; }

void Contacts::set_phone(string _phone) { phone = _phone; }

void Contacts::set_day(int _day) { day = _day; }

void Contacts::set_month(int _month) { month = _month; }

void Contacts::set_year(int _year) { year = _year; }

void Contacts::set_favourite_true() { favourite = true; }

void Contacts::set_favourite_false() { favourite = false; }

void Contacts::set_favourite(bool status)
{
	if (status == true)
		favourite = true;
	else
		favourite = false;
}

void Contacts::print_contact_lite()
{
	setlocale(LC_ALL, "Rus");
	cout << surname << " " << name << " " << patronymic << " " << phone << endl;
}

void Contacts::print_contact()
{
	setlocale(LC_ALL, "Rus");
	cout << "/////////////////////////////////////////////////////////////////////" << endl;
	cout << "\t\t\tФИО: " << surname << " " << name << " " << patronymic << endl;
	cout << "\t\t\tКонтактный телефон: " << phone << endl;
	cout << "\t\t\tДата рождения: " << day << "/" << month << "/" << year << endl;
	cout << "\t\t\tНаходится в избранном: ";
	if (favourite == true)
		cout << "Да" << endl;
	else
		cout << "Нет" << endl;
	cout << "//////////////////////////////////////////////////////////////////////" << endl;
}
Contacts& Contacts::operator=(const Contacts& c)
{
	if (this == &c)
		return *this;
	name = c.name;
	surname = c.surname;
	patronymic = c.patronymic;
	day = c.day;
	month = c.month;
	year = c.year;
	phone = c.phone;
	favourite = c.favourite;
	return *this;
}
bool Contacts::operator!=(const Contacts& c)
{
	if (name != c.name || surname != c.surname || patronymic != c.patronymic)
		return true;
	else
		return false;
}
bool Contacts::operator==(const Contacts& c)
{
	if (name == c.name && surname == c.surname && patronymic == c.patronymic)
		return true;
	else
		return false;
}
bool Contacts::operator<(const Contacts& c)
{
	if (surname < c.surname)
		return true;
	else
		if (surname > c.surname)
			return false;
		else
			if (name < c.name)
				return true;
			else
				if (name > c.name)
					return false;
				else
					if (patronymic < c.patronymic)
						return true;
					else
						return false;
}