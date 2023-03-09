#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
using namespace std;

class calendar
{
private:
	unsigned short day[29] = {}, month[29] = {}, year[29] = {};
	string EventName[29] = {};
	string Day[29] = {};
	string Month[29] = {};
	unsigned short day1, month1, year1;
	string Year1;
	string Day1;
	string Month1;
	string dd, mm, yy;
	int temp;
	int i = 0,d2,m2,y2;
public:
	void menu()
	{
		cout << "1)�������� ����� �������" << endl;
		cout << "2)������ ���� �������" << endl;
		cout << "3)��������� ������� ����� ������" << endl;
		cout << "4)�������� ������� �� ������ ��������" << endl;
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
	 int ReverseJuliansDate(int JLNSD,int numb)
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
	int bias()
	{
		int t, temp, temp1, daybias, sign, a, monthbias,yearbias;
		int r = 1;
		int j = 0;
		if (day[0] == 0)
		{
			cout << "��� �������� ���." << endl;
			return 0;
		}
		else
			for (j; j < i; j++, r++)
			{
				cout << r << ")" << EventName[j] << " - " << Day[j] << "." << Month[j] << "." << year[j] << endl;
			}
		cout << "����� ���� ������ ���� �������. �������� �� ������ ��, ������� ���������� ������������." << endl;
		cin >> t;
		temp = JuliansDate(year[t - 1], month[t - 1], day[t - 1]); 
		cout << "��������, � ����� �������� ����� �������� �����" << endl;
		cout << "1)� �����" << endl;
		cout << "2)� �������" << endl;
		cout << "3)� ����" << endl;
		cin >> temp1;
		switch (temp1)
		{
		case 3:
			{
				cout << "�������  ���������� ����, �� ������� ���������� �������� �������." << endl;
				cin >> daybias;
				cout << "���� ������ �������� ������� '������' ������� 1, '�����' ������� 0" << endl;
				cin >> sign;
				if (sign == 1)
				{
					a = temp + daybias;
				}
				else if (sign == 0)
				{
					a = temp - daybias;
				}
				year[t - 1] = ReverseJuliansDate(a, 1);
				month[t - 1] = ReverseJuliansDate(a, 2);
				day[t - 1] = ReverseJuliansDate(a, 3);
				if (month[t - 1] < 10)
					Month[t - 1] = '0' + to_string(month[t - 1]);
				else
					Month[t - 1] = to_string(month[t - 1]);
				day[t - 1] = ReverseJuliansDate(a, 3);
				if (day[t - 1] < 10)
					Day[t - 1] = '0' + to_string(day[t - 1]);
				else
					Day[t - 1] = to_string(day[t - 1]);
				cout << "��������� �������. ���������� �� ����� � ������� ���� � ������� 2." << endl;
				break;
			}
		case 2:
		{
			cout << "������� ���������� �������, �� ������� ���������� �������� �������, � ������ ����, ��� � ������� � ������ 30 ����." << endl;
			cin >> monthbias;
			cout << "���� ������ �������� ������� '������' ������� 1, '�����' ������� 0" << endl;
			cin >> sign;
			if (sign == 1)
			{
				a = temp + monthbias * 30;
			}
			else if (sign == 0)
			{
				a = temp - monthbias * 30;
			}
			year[t - 1] = ReverseJuliansDate(a, 1);
			month[t - 1] = ReverseJuliansDate(a, 2);
			day[t - 1] = ReverseJuliansDate(a, 3);
			if (month[t - 1] < 10)
				Month[t - 1] = '0' + to_string(month[t - 1]);
			else
				Month[t - 1] = to_string(month[t - 1]);
			day[t-1] = ReverseJuliansDate(a, 3);
			if (day[t - 1] < 10)
				Day[t - 1] = '0' + to_string(day[t - 1]);
			else
				Day[t - 1] = to_string(day[t - 1]);
			cout << "��������� �������. ���������� �� ����� � ������� ���� � ������� 2." << endl;
			break;
		}
		case 1:
		{cout << "������� ���������� ���, �� ������� ���������� �������� �������" << endl;
		cin >> yearbias;
		cout << "���� ������ �������� ������� '������' ������� 1, '�����' ������� 0" << endl;
		cin >> sign;
		if (sign == 1)
		{
			a = temp + yearbias * 365.25;
		}
		else if (sign == 0)
		{
			a = temp - yearbias * 365.25;
		}
		year[t - 1] = ReverseJuliansDate(a, 1);
		month[t - 1] = ReverseJuliansDate(a, 2);
		day[t - 1] = ReverseJuliansDate(a, 3);
		if (month[t - 1] < 10)
			Month[t - 1] = '0' + to_string(month[t - 1]);
		else
			Month[t - 1] = to_string(month[t - 1]);
		day[t - 1] = ReverseJuliansDate(a, 3);
		if (day[t - 1] < 10)
			Day[t - 1] = '0' + to_string(day[t - 1]);
		else
			Day[t - 1] = to_string(day[t - 1]);
		cout << "��������� �������. ���������� �� ����� � ������� ���� � ������� 2." << endl;
		break;
		}
		}

	}
	void check()
	{
		for (int h = 0; h < i; h++)
		{
			if ((day[h] == day[i]) && (month[h] == month[i]) && (year[h] == year[i]))
			{
				cout << "---------------------------------------------" << endl;
				cout << "��������� ���� ��� ������������!" << endl;
				break;
			}
			else
			{
				i++;
				break;
			}
				
		}
	}
	int differense()
	{
		if (day[0] == 0)
		{
			cout << "��� �������� ���." << endl;
			return 0;
		}
		int t, r = 1, temp2;
		cout << "������� ����, ��� ������� ����� ��������� �������." << endl;
		cout << "��� - ";
		cin >> year1;
		cout << "����� ������ - ";
		cin >> Month1;
		cout << "����� - ";
		cin >> Day1;
		day1 = atoi(Day1.c_str());
		month1 = atoi(Month1.c_str());
		cout << "---------------------------------------------" << endl;
		cout << "�������� �������, ������� � ������� ���������� ���������." << endl;
		cout << "---------------------------------------------" << endl;
		for (int j = 0; j < i; j++, r++)
		{
			cout << r << ")" << EventName[j] << " - " << Day[j] << "." << Month[j] << "." << year[j] << endl;
		}
		cout << "---------------------------------------------" << endl;
		cout << "������� �����:";
		cin >> t;
		cout << "�������  ����� ��������� �����:" << endl;
		cout << Day[t - 1] << "." << Month[t - 1] << "." << year[t - 1] << endl;
		cout << "       and" << endl;
		cout << Day1 << "." << Month1 << "." << year1 << endl;
		cout << "---------------------------------------------" << endl;
		do
		{
			cout << "�������� � ����� �������� ������� �������" << endl;
			cout << "1)� �����" << endl;
			cout << "2)� �������" << endl;
			cout << "3)� ����" << endl;
			cin >> temp2;
			switch (temp2)
			{
			case 1:
				cout << "������� ����� ���������� ������ � ����� = " << fabs(year[t - 1] - year1)<< endl;
				cout << "---------------------------------------------" << endl;
				cout << "������� 1 ���� ������ ��������� ������� � ������ ��������� ��� 0 ����� ������� � ������� ����." << endl;
				cin >> temp2;
				break;
			case 2:
				if (year[t - 1] > year1)
					cout << "������� ����� ���������� ������ � ������� = " << ((12 - month1) + ((year[t - 1] - year1 - 1) * 12) + month[t - 1]) << endl;
				else if (year1 > year[t - 1])
					cout << "������� ����� ���������� ������ � ������� = " << ((12 - month[t - 1]) + ((year1 - year[t - 1] - 1) * 12) + month1) << endl;
				else if (year1 == year[t - 1])
					cout << "������� ����� ���������� ������ � ������� = " << fabs(month1 - month[t-1]) << endl;
				cout << "---------------------------------------------" << endl;
				cout << "������� 1 ���� ������ ��������� ������� � ������ ��������� ��� 0 ����� ������� � ������� ����." << endl;
				cin >> temp2;
				break;
			case 3:
				cout << "������� � ���� ����� ������ = " << (fabs(JuliansDate(year[t - 1], month[t - 1], day[t - 1] - JuliansDate(year1, month1, day1))))<< endl;
				cout << "---------------------------------------------" << endl;
				cout << "������� 1 ���� ������ ��������� ������� � ������ ��������� ��� 0 ����� ������� � ������� ����." << endl;
				cin >> temp2;
				break;
			}

		} while (temp2 != 0);
	}
	void NewEvent()
	{
		cout << "������� �������� �������, ������� ������ ��������.\n";
			cin >> EventName[i];
			cout << "������� ���� ����� �������. \n";
			cout << "��� - ";
			cin >> year[i];
			while (year[i] < 1 || year[i] > 2100)
			{
				cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 2100 ����." << endl;
				year[i] = 0;
				cin >> year[i];
			}
			cout << "����� ������ - ";
			cin >> Month[i];
			month[i] = atoi(Month[i].c_str());
			while (month[i] < 1 || month[i] > 12)
			{
				cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 12 ������." << endl;
				cin >> Month[i];
				month[i] = atoi(Month[i].c_str());
			}
			cout << "����� - ";
			cin >> Day[i];
			day[i] = atoi(Day[i].c_str());
			if ((month[i] == 2) && ((year[i] % 100) % 4) == 0)
			{
				while (day[i] < 1 || day[i] > 29)
				{
					cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 29 ����." << endl;
					cin >> Day[i];
					day[i] = atoi(Day[i].c_str());
				}
			}
			else if (((month[i] == 2) && ((year[i] % 100) % 4) != 0))
			{
				while (day[i] < 1 || day[i] > 28)
				{
					cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 28 ����." << endl;
					cin >> Day[i];
					day[i] = atoi(Day[i].c_str());
				}
			}
			else if ((month[i] == 1 || (month[i] == 3 || (month[i] == 5 || (month[i] == 7 || (month[i] == 8 || (month[i] == 10 || (month[i] == 12))))))))
			{
				while (day[i] < 1 || day[i] > 31)
				{
					cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 31 ����." << endl;
					cin >> Day[i];
					day[i] = atoi(Day[i].c_str());
				}
			}
			else if ((month[i] == 4) || (month[i] == 6) || (month[i]== 9) || (month[i] == 11))
			{
				while (day[i] < 1 || day[i] > 30)
				{
					cout << "������� ������������ ����. ���������� ����� � ��������� �� 1 �� 30 ����." << endl;
					cin >> Day[i];
					day[i] = atoi(Day[i].c_str());
				}
			}
			if (i == 0)
			{
				i++;
			}
			else
				check();
	}
	int checkEvents()
	{
		int t;
		int r = 1;
		if (day[0] == 0)
		{
			cout << "��� �������� ���." << endl;
			return 0;
		}
		else
			for (int j = 0; j < i; j++,r++)
			{
				cout << r<<")" << EventName[j] /*<< " - " << Day[j] << "." << Month[j] << "." << year[j] */<< endl;
			}
		cout << "����� ������ ����, ������� ����� �������" << endl;
		cin >> t;
		cout << EventName[t-1] << " - " << Day[t-1] << "." << Month[t-1] << "." << year[t-1] << endl;
	}
	void swap()
	{
		do
		{
			cout << "---------------------------------------" << endl;
			cout << "������� ����� ��������" << endl;
			cin >> temp;
			switch (temp)
			{
			case 1:
				NewEvent();
				break;
			case 2:
				checkEvents();
				break;
			case 3:
				differense();
				break;
			case 4:
				bias();
				break;
			}
		} while (temp != 0);
		
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	calendar c;
	c.menu();
	c.swap();
	system("pause");
}