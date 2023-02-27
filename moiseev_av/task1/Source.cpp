#include <clocale>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;


class Time
{
public:

	Time()
	{
		hours = 12;
		minutes = 30;
		seconds = 15;
	}

	int set_time()
	{
		vector<int> args = time_correct();
		
		if (size(args) == 0)
		{
			return 0;
		}

		hours = args[0];
		minutes = args[1];
		seconds = args[2];
		cout << "\n����� ������� ��������!\n\n" << endl;
	}

	void take_time()
	{
		cout << "\n������� �����: " << hours << "h. " << minutes << "m. " << seconds << "s. \n\n" << endl;
	}

	int difference()
	{
		vector<int> args = time_correct();

		if (size(args) == 0)
		{
			return 0;
		}

		vector<int> new_data = calculations(args[0], args[1], args[2]);

		if (size(args) == 0)
		{
			return 0;
		}

		cout << "\n������� ����������: " << new_data[0] << "h. " << new_data[1] << "m. " << new_data[2] << "s.\n";
	}

	int move_time()
	{
		vector<int> args = time_correct();

		if (size(args) == 0)
		{
			return 0;
		}

		char s;
		cout << "\n���� �� ������ �������� ����� ������, �������: \"+\"" <<
			"\n���� �� ������ �������� ����� �����, �������: \"-\"\n";
		cin >> s;

		if (s == '-')
		{
			if (size(args) == 0)
			{
				return 0;
			}

			if (hours < args[0])
			{
				step_over_time(args[0], args[1], args[2]);
			}

			else if (hours == args[0])
			{
				if (minutes < args[1])
				{
					step_over_time(args[0], args[1], args[2]);
				}

				else if (minutes == args[1])
				{
					if (seconds < args[2])
					{
						step_over_time(args[0], args[1], args[2]);
					}

					else if (seconds = args[2])
					{
						hours = 0;
						minutes = 0;
						seconds = 0;
					}
				}
			}

			else
			{
				vector<int> new_data = calculations(args[0], args[1], args[2]);
				hours = new_data[0];
				minutes = new_data[1];
				seconds = new_data[2];
			}

			cout << "\n����� ������� ��������!\n\n" << endl;
		}

		else if (s == '+')
		{
			int cnt_m = 0, cnt_h = 0;

			if ((seconds + args[2]) > 59)
			{
				seconds += args[2] - 60;
				cnt_m++;
			}

			else
			{
				seconds += args[2];
			}

			if ((minutes + args[1] + cnt_m) > 59)
			{
				minutes += args[1] + cnt_m - 60;
				cnt_h++;
			}

			else
			{
				minutes += args[1] + cnt_m;
			}

			hours += args[0] + cnt_h;
			
			if (hours >= 24)
			{
				hours -= 24;
			}

			cout << "\n����� ������� ��������!\n\n";
		}

		else
		{
			cin.ignore(cin.rdbuf()->in_avail());

			cout << "\n������ �����!\n\n" << endl;
			return 0;
		}
	}

private:

	int hours;
	int minutes;
	int	seconds;

	vector<int> time_correct()
	{	
		int user_hours;
		cout << "\n������� ���������� �����: ";
		cin >> user_hours;

		if (!(user_hours >= 0 && user_hours < 24))
		{
			cout << "\n������ �����!\n\n" << endl;
			return {  };
		}
		
		int user_minutes;
		cout << "\n������� ���������� �����: ";
		cin >> user_minutes;

		if (!(user_minutes >= 0 && user_minutes < 60))
		{
			cout << "\n������ �����!\n\n" << endl;
			return {  };
		}

		int user_seconds;
		cout << "\n������� ���������� ������: ";
		cin >> user_seconds;

		if (!(user_seconds >= 0 && user_seconds < 60))
		{
			cout << "\n������ �����!\n\n" << endl;
			return {  };
		}
		
		int &user_hours_ref = user_hours;
		int& user_minutes_ref = user_minutes;
		int& user_seconds_ref = user_seconds;

		return {user_hours_ref, user_minutes_ref, user_seconds_ref };
	}

	vector<int> calculations(int user_hours, int user_minutes, int user_seconds)
	{
		int new_hours, new_minutes, new_seconds;
		bool flag = false;

		if (hours < user_hours)
		{
			vector<int> switched = switching(user_hours, user_minutes, user_seconds);
			user_hours = switched[0];
			user_minutes = switched[1];
			user_seconds = switched[2];
			flag = true;
		}

		else if (hours == user_hours)
		{
			if (minutes < user_minutes)
			{
				vector<int> switched = switching(user_hours, user_minutes, user_seconds);
				user_hours = switched[0];
				user_minutes = switched[1];
				user_seconds = switched[2];
				flag = true;
			}

			else if (minutes == user_minutes)
			{
				if (seconds < user_seconds)
				{
					vector<int> switched = switching(user_hours, user_minutes, user_seconds);
					user_hours = switched[0];
					user_minutes = switched[1];
					user_seconds = switched[2];
					flag = true;
				}
			}
		}

		int cnt_m = 0;
		new_hours = abs(hours - user_hours);

		if (seconds < user_seconds)
		{
			if (new_hours != 0)
			{
				new_seconds = 60 + seconds - user_seconds;
				cnt_m++;
			}

			else
			{
				new_minutes = abs(minutes - user_minutes);

				if (new_minutes != 0)
				{
					new_seconds = 60 + seconds - user_seconds;
					cnt_m++;
				}

				else
				{
					new_seconds = abs(seconds - user_seconds);
				}
			}
		}

		else
		{
			new_seconds = seconds - user_seconds;
		}

		if (minutes < user_minutes)
		{
			if (new_hours != 0)
			{
				new_minutes = 60 + minutes - user_minutes - cnt_m;
				new_hours--;
			}

			else
			{
				new_minutes = abs(minutes - cnt_m - user_minutes);
			}
		}

		else
		{
			if ((minutes - user_minutes) == 0)
			{
				if (new_hours == 0)
				{
					new_seconds = abs(seconds - user_seconds);
					new_minutes = 0;
				}

				else if (cnt_m == 0)
				{
					new_minutes = 0;
				}

				else
				{
					new_minutes = 59;
					new_hours--;
				}
			}

			else
			{
				new_minutes = abs(minutes - cnt_m - user_minutes);
			}
		}

		if (flag)
		{
			switching(user_hours, user_minutes, user_seconds);
		}
		
		int& new_hours_ref = new_hours;
		int& new_minutes_ref = new_minutes;
		int& new_seconds_ref = new_seconds;

		return { new_hours_ref, new_minutes_ref, new_seconds_ref };
	}

	vector<int> switching(int user_hours, int user_minutes, int user_seconds)
	{
		hours = hours + user_hours;
		user_hours = hours - user_hours;
		hours = hours - user_hours;

		minutes = minutes + user_minutes;
		user_minutes = minutes - user_minutes;
		minutes = minutes - user_minutes;

		seconds = seconds + user_seconds;
		user_seconds = seconds - user_seconds;
		seconds = seconds - user_seconds;

		return { user_hours, user_minutes, user_seconds };
	}

	int step_over_time(int user_hours, int user_minutes, int user_seconds)
	{
		vector<int> new_data = calculations(user_hours, user_minutes, user_seconds);
		hours = new_data[0];
		minutes = new_data[1];
		seconds = new_data[2];
		vector<int> new_data1 = calculations(24, 0, 0);
		hours = new_data1[0];
		minutes = new_data1[1];
		seconds = new_data1[2];

		return 0;
	}
};


Time t;

void choose_func()
{
	int function_number;

	cout << "\n��� �� ������ �������?\n\n" << "  (1) ���������� �����\n" << "  (2) ������ �����\n" 
		<< "  (3) ��������� ������� ����� �������� �������� � �������������\n"  
		<< "  (4) �������� ����� �� �������� ��������\n\n" << "������� ����� �� 1 �� 4: ";
	cin >> function_number;

	if (!cin.good()) //���� ��������� ������ ����� �� good
	{
		cin.clear(); //������� ���� ������.
		cin.ignore(cin.rdbuf()->in_avail()); //���������� � ������ ������ ����� � �������� �� ���� ���������� ��������� ��������, ����� - ���������� ��.
	}

	if (function_number > 0 && function_number < 5)
	{
		switch (function_number)
		{
		case 1: t.set_time();
			choose_func();

		case 2: t.take_time();
			choose_func();

		case 3: t.difference();
			choose_func();

		case 4: t.move_time();
			choose_func();

		default:
			choose_func();
		}
	}

	else
	{
		cout << "\n������ �����!\n\n" << endl;
		choose_func();
	}
}

void main() 
{
	setlocale(LC_ALL, "");
	
	choose_func();
}
