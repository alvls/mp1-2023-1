#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <tuple>
using namespace std;

class calendar
{
private:
	int day[30] = {}, month[30] = {}, year[30] = {};
	string EventName[30] = {};
	int temp;
	int i = 0;
public:
	calendar()
	{};
	void installdate(string eventname, int Day, int Month, int Year)
	{
		if (Day > 0 && Month > 0 && Month <= 12 && Year > 0 && Year <= 2100)
		{
			bool check = false;
			for (int h = 0; h < i; h++)
			{
				if ((day[h] == day[i]) && (month[h] == month[i]) && (year[h] == year[i]))
				{
					check = true;
					break;
				}
			}
			if (check)
			{
				return;
			}
			else
			{
				int max_days = 31;
				if (Month == 2) 
				{
					if (Year % 4 == 0 && (Year % 100 != 0 || Year % 400 == 0))
					{
						max_days = 29;
					}
					else {
						max_days = 28;
					}
				}
				else if (Month == 4 || Month == 6 || Month == 9 || Month == 11)
				{
					max_days = 30;
				}
				if (Day <= max_days)
				{
					day[i] = Day;
					month[i] = Month;
					year[i] = Year;
					EventName[i] = eventname;
					i++;
				}
				else
					return;
			}
		}
		else
			return;
	}
	std::tuple<int, int, int> get_date(string eventname)
	{
		int h = 0;
		do
		{
			if (EventName[h] != eventname)
				h++;
			else
			{
				if (day[h] == 0 && month[h] == 0 && year[h] == 0)
				{
					return std::make_tuple(0, 0, 0);
				}
				else
				{
					return std::make_tuple(day[h], month[h], year[h]);
				}
			}
		} while (h < 30);

		return std::make_tuple(0, 0, 0);
	}
	int  difference(int day1, int month1, int year1, string eventname, string dmy)
	{
		int day2, month2, year2;
		int h = 0;
		do
		{
			if (EventName[h] != eventname)
				h++;
			else
			{
				day2 = day[h];
				month2 = month[h];
				year2 = year[h];
				if (dmy == "month")
				{
					if (year1 > year2)
					{
						int t = ((12 - month2) + ((year1 - year2 - 1) * 12) + month1);
						return t;
					}
					else if (year2 > year1)
					{
						int t = ((12 - month1) + ((year2 - year1 - 1) * 12 + month2));
						return t;
					}
					else if (year2 == year1)
					{
						int t = fabs(month1 - month2);
						return t;
					}
				}
				else if (dmy == "day")
				{
					int t = (fabs(JuliansDate(year1, month1, day1) - JuliansDate(year2, month2, day2)));
					return t;
				}
				else if (dmy == "year")
				{
					int t = fabs(year1 - year2);
					return t;
				}
			}
		} while (h < 30);
		if (h == 30)
			return 0;
	}
	void bias(string up_down, string moveable_obj, int dayy, int monthh, int yearr)
	{
		int h = 0;
		int temp, a;
		while (EventName[h] != moveable_obj)
			h++;
		if (up_down == "up")
		{
			temp = JuliansDate(year[h], month[h], day[h]);
			a = temp + dayy + monthh * 30 + yearr * 365;
			year[h] = ReverseJuliansDate(a, 1);
			month[h] = ReverseJuliansDate(a, 2);
			day[h] = ReverseJuliansDate(a, 3);
		}
		else if (up_down == "down")
		{
			temp = JuliansDate(year[h], month[h], day[h]);
			a = temp - (dayy + monthh * 30 + yearr * 365);
			year[h] = ReverseJuliansDate(a, 1);
			month[h] = ReverseJuliansDate(a, 2);
			day[h] = ReverseJuliansDate(a, 3);
		}
	}
	int JuliansDate(int year, int month, int day)
	{
		int a, y, m, jdn;
		a = (14 - month) / 12;
		y = year + 4800 - a;
		m = month + 12 * a - 3;
		jdn = day + ((153 * m + 2) / 5) + (365 * y) + (y / 4) - (y / 100) + (y / 400) - 32045;
		return(jdn);
	}
	int ReverseJuliansDate(int JLNSD, int numb)
	{
		int c, a, d, b, e, m, day11, month11, year11;
		a = JLNSD + 32044;
		b = (4 * a + 3) / 146097;
		c = a - ((146097 * b) / 4);
		d = (4 * c + 3) / 1461;
		e = c - ((1461 * d) / 4);
		m = ((5 * e + 2) / 153);
		day11 = e - ((153 * m + 2) / 5) + 1;
		month11 = m + 3 - 12 * (m / 10);
		year11 = 100 * b + d - 4800 + (m / 10);
		switch (numb)
		{
		case 1:
			return (year11);
			break;
		case 2:
			return (month11);
			break;
		case 3:
			return(day11);
			break;
		}
	}
};
	
void main()
{
	setlocale(LC_ALL, "Russian");
	calendar c;
	c.installdate("hbd", 20, 10, 2004);
	c.installdate("hbdm1", 21, 11, 2004);
	c.get_date("hbd");
	c.get_date("hbdm1");
	c.difference(5, 8, 2004, "hbd", "month");
	system("pause");
}