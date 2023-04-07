#include <clocale>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

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

	bool set_time(int h, int min, int sec)
	{
		vector<int> args = time_correct(h, min, sec);
		
		if (size(args) == 0)
		{
			return false;
		}

		hours = args[0];
		minutes = args[1];
		seconds = args[2];
		print("Время успешно изменено!");
		return true;
	}

	string take_time()
	{
		print("Текущее время: " + to_string(hours) + "h. " + to_string(minutes) + "m. " + to_string(seconds) + "s.");
		return to_string(hours) + "h. " + to_string(minutes) + "m. " + to_string(seconds) + "s.";
	}

	string difference(int h, int min, int sec)
	{
		vector<int> args = time_correct(h, min, sec);

		if (size(args) == 0)
		{
			return "";
		}

		vector<int> new_data = calculations(args[0], args[1], args[2]);

		if (size(args) == 0)
		{
			return "";
		}

		print("Разница составляет: " + to_string(new_data[0]) + "h. " + to_string(new_data[1]) + "m. " + to_string(new_data[2]) + "s.");
		return to_string(new_data[0]) + "h. " + to_string(new_data[1]) + "m. " + to_string(new_data[2]) + "s.";
	}

	bool move_time(int h, int min, int sec, char sign)
	{
		vector<int> args = time_correct(h, min, sec);

		if (size(args) == 0)
		{
			return false;
		}

		if (sign == '-')
		{
			if (size(args) == 0)
			{
				return false;
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

			print("Сдвиг прошёл успешно!");
			return true;
		}
		else if (sign == '+')
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

			print("Сдвиг прошёл успешно!");
			return true;
		}
		else
		{
			cin.ignore(cin.rdbuf()->in_avail());

			print("Ошибка ввода!");
			return false;
		}
	}

private:

	int hours;
	int minutes;
	int	seconds;

	vector<int> time_correct(int user_hours, int user_minutes, int user_seconds)
	{	
		if (!(user_hours >= 0 && user_hours < 24))
		{
			print("Ошибка ввода!");
			return {  };
		}
		
		if (!(user_minutes >= 0 && user_minutes < 60))
		{
			print("Ошибка ввода!");
			return {  };
		}

		if (!(user_seconds >= 0 && user_seconds < 60))
		{
			print("Ошибка ввода!");
			return {  };
		}
		
		int &user_hours_ref = user_hours;
		int &user_minutes_ref = user_minutes;
		int &user_seconds_ref = user_seconds;

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

	void print(string line)
	{
		cout << line << endl;
	}
};


void main() 
{
	setlocale(LC_ALL, "Russian_Russia.1251");

	Time t;

	t.take_time();

	t.set_time(10, 30, 0);

	t.take_time();

	t.move_time(0, 30, 0, '-');

	t.take_time();

	t.difference(5, 45, 0);
}
