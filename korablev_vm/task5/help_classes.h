#include <windows.h>
#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include <vector>
#include <iomanip>
#ifndef HELP_CLASS
#define HELP_CLASS
typedef unsigned short time_int;


class MyTime
{
	time_int hours = 0;
	time_int minutes = 0;
	friend class Cinema;
	friend class TicketOffice;
	friend ostream& operator<<(ostream& out, const MyTime& time);
public:
	MyTime(time_int _h = 0, time_int _m = 0) : hours(_h), minutes(_m) {}
	MyTime(const MyTime& time) = default;
	time_int return_hours() { return hours; }

	time_int return_minutes() { return minutes; }

	void set_hours(time_int _h) { hours = _h; }

	void set_minutes(time_int _m) { minutes = _m; }

	MyTime& operator=(const MyTime& time)
	{
		if (this == &time)
			return *this;
		hours = time.hours;
		minutes = time.minutes;
		return *this;
	}
	bool operator!=(const MyTime& time)
	{
		if (hours != time.hours || minutes != time.minutes)
			return true;
		return false;
	}
	bool operator==(const MyTime& time)
	{
		if (hours == time.hours && minutes == time.minutes)
			return true;
		return false;
	}
	bool operator>(const MyTime& time)
	{
		if (hours < time.hours)
			return true;
		if (minutes < time.minutes)
			return true;
		return false;
	}

	bool operator<(const MyTime& time)
	{
		if (hours < time.hours)
			return true;
		if (minutes < time.minutes)
			return true;
		return false;
	}
	MyTime& operator-(const MyTime& time)
	{
		int temp_minutes;
		if (hours < time.hours)
			hours += 24;
		temp_minutes = (hours * 60 + minutes) - (time.hours * 60 + time.minutes);
		hours = 0;
		minutes = 0;
		while (temp_minutes >= 60)
		{
			hours++;
			temp_minutes -= 60;
		}
		minutes = temp_minutes;
		return *this;
	}
	MyTime& operator+(const MyTime& time)
	{
		int temp_minutes;
		temp_minutes = (hours * 60 + minutes) + (time.hours * 60 + time.minutes);
		hours = 0;
		minutes = 0;
		while (temp_minutes >= 60)
		{
			hours++;
			temp_minutes -= 60;
		}
		minutes = temp_minutes;
		return *this;
	}
	int minutes_different(const MyTime& time)
	{
		return (time.hours * 60 + time.minutes) - (hours * 60 + minutes);
	}
};
ostream& operator<<(ostream& out, const MyTime& time)
{
	out << setw(2) << setfill('0') << time.hours << ":"
		<< setw(2) << setfill('0') << time.minutes;
	return out;
}
class MyDate
{
	int day;
	int month;
	int month_long[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	string month_list[13] = {"","января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября",
	"октября", "ноября", "декабря" };
	friend class Cinema;
	friend class TicketOffice;
	friend ostream& operator<<(ostream& out, const MyDate& date);
public:
	int return_day() { return day; }
	int return_month() { return month; }
	void set_day(int d) 
	{ 
		day = d;
		if (day > month_long[month])
		{
			day = day - month_long[month];
			month++;
		}
	}
	void set_month(int m) { month = m; }
	MyDate(int _day = 1, int _month = 1): day(_day), month(_month) {}
	MyDate(const MyDate& date) 
	{
		day = date.day;
		month = date.month;
	}
	MyDate& operator=(const MyDate& date)
	{
		if (this == &date)
			return *this;
		day = date.day;
		month = date.month;
		return *this;
	}
	 MyDate& operator++()
	{
		return *this;
	}
	bool operator<(const MyDate& date)
	{
		if (month < date.month)
			return true;
		if (month == date.month && day < date.day)
			return true;
		return false;
	}
	bool operator>(const MyDate& date)
	{
		if (month > date.month)
			return true;
		if (month == date.month && day > date.day)
			return true;
		return false;
	}
	bool operator==(const MyDate& date)
	{
		if (month == date.month && day == date.day)
			return true;
		return false;
	}
	bool operator!=(const MyDate& date)
	{
		if (month == date.month || day == date.day)
			return true;
		return false;
	}
	MyDate& operator-(const MyDate& date)
	{
		day = day - date.day;
		while (day < 0)
		{
			month--;
			day = month_long[month] + day;
		}
		return *this;
	}
	MyDate& operator+(const MyDate& date)
	{
		day = day + date.day;
		while (day > month_long[month])
		{
			day = day - month_long[month];
			month++;
		}
		return *this;
	}
	int day_differents(const MyDate& date)
	{
		if (month == date.month)
			return day - date.day;
		if (month < date.month)
			return -28;
		return month_long[date.month]-date.day+day;
	}
};
ostream& operator<<(ostream& out, const MyDate& date)
{
	out << date.day << " " << date.month_list[date.month];
	return out;
}
class Hall
{
	int number ;
	int base_rows;
	int base_rows_seats ;
	int vip_rows;
	int vip_rows_seats;
	int price;
	int free_base = 0;
	int free_vip = 0;
	friend class Cinema;
	friend class TicketOffice;
	friend struct Film;
	friend ostream& operator<<(ostream& out, const Hall& hall);
public:
	Hall(int num = 0, int br = 0, int brs = 0, int vr = 0, int vrs = 0, int _price = 0)
	{
		number = num;
		base_rows = br;
		base_rows_seats = brs;
		vip_rows = vr;
		vip_rows_seats = vrs;
		price = _price;
		Construct();
	}
	void Construct()
	{
		free_base = base_rows * base_rows_seats;
		free_vip = vip_rows * vip_rows_seats;
	}
	int return_number() { return number; }
	int return_base_rows() { return base_rows; }
	int return_base_rows_seats() { return base_rows_seats; }
	int return_vip_rows() { return vip_rows; }
	int return_vip_rows_seats() { return vip_rows_seats; }
	int return_price() { return number; }
	void set_number(int num) { number = num; }
	void set_base_rows(int br) { base_rows = br; }
	void set_base_rows_seats(int brs) { base_rows_seats = brs; }
	void set_vip_rows(int vr) { vip_rows = vr; }
	void set_vip_rows_seats(int vrs) { vip_rows_seats = vrs; }
	void set_price(int pr) { price = pr; }
	bool operator==(const Hall& hall)
	{
		if (number == hall.number)
			return true;
		return false;
	}
	Hall& operator=(const Hall& hall)
	{
		if (this == &hall)
			return *this;
		number = hall.number;
		base_rows = hall.base_rows;
		base_rows_seats = hall.base_rows_seats;
		vip_rows = hall.vip_rows;
		vip_rows_seats = hall.vip_rows_seats;
		price = hall.price;
		return *this;
	}
};

ostream& operator<<(ostream& out, const Hall& hall)
{
	out << "Зал: " << hall.number << endl;
	out << "Начальная цена (стандарт): " << hall.price << " рублей" << endl;
	out << "Начальная цена (вип): " << hall.price+150 << " рублей";
	return out;
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
	system("cls");
	cout << "Добро пожаловать в программу-кинотеатр" << endl;
	cout << "Важная информация! Сеансы заполнены с 1 марта по 2 апреля" << endl;
	system("pause");
	system("cls");
}
#endif