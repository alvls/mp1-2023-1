#include <iostream>
#include <fstream>
#include <vector> 
#include <ctime>
#include <sstream>
#include <string>
using namespace std;
class pedometre
{
private:
	struct count
	{
		int day, month, year;
		int start_hour, start_min, end_hour, end_min;
		int step;
	};
	vector <count> history;
	tm time;
public:
	pedometre() {}
	pedometre(int day, int month, int year, int hour, int min) {
		Setstarttime(day, month, year, hour, min);
	}
	tm Setstarttime(int day, int month, int year, int hour, int min)
	{
		time.tm_sec = 0;
		time.tm_min = min;
		time.tm_hour = hour;
		time.tm_mday = day;
		time.tm_mon = month + 1;
		time.tm_year = year - 1900;
		mktime(&time);
		return time;
	}
	tm gettime()
	{
		return time;
	}
	void setcount(int day, int month, int year, int start_h, int start_m, int finish_h, int finish_m, int steps)
	{
		count count = { day, month, year, start_h, start_m, finish_h, finish_m, steps };
		history.push_back(count);
	}
	void getcount(int number)
	{
		cout << "Date: " << history[number].day << "." << history[number].month << "." << history[number].year << endl;
		cout << "Start time: " << history[number].start_hour << ":" << history[number].start_min << endl;
		cout << "End time: " << history[number].end_hour << ":" << history[number].end_min << endl;
		cout << "Steps: " << history[number].step << endl;
	}
	int AverageSteps(int month = 0)
	{
		int total_steps = 0;
		int count = 0;
		for (const auto& step : history)
		{
			if (month == 0 || month == step.month)
			{
				total_steps += step.step;
				count++;
			}
		}
		return (count > 0) ? total_steps / count : 0;
	}
	int AverageweekdaySteps(int numberday)
	{
		int total_steps = 0;
		int count = 0;
		for (const auto& step : history)
		{
			tm time = Setstarttime(step.day, step.month, step.year, step.start_hour, step.start_min);
			if (time.tm_wday == numberday)
			{
				total_steps += step.step;
				count++;
			}
		}
		return (count > 0) ? total_steps / count : 0;
	}
	struct Maxstepinfo
	{
		int day;
		int month;
		int year;
		int step;
	};
	Maxstepinfo Maxcountstep(int month = 0)
	{
		int maxstep = 0, maxday = 0, maxmonth = 0, maxyear = 0;
		for (const auto& step : history)
		{
			if (month == 0 || step.month == month)
			{
				int steps = step.step;
				if (steps > maxstep)
				{
					maxstep = steps;
					maxday = step.day;
					maxmonth = step.month;
					maxyear = step.year;
				}
			}
		}
		Maxstepinfo info = { maxday,maxmonth,maxyear,maxstep };
		return info;
	}
	void save_res(string filename) const
	{
		ofstream file(filename);
		if (file.is_open())
		{
			for (const auto& step : history)
			{
				file  << step.day << "." << step.month << "." << step.year << " " << step.start_hour << ":" << step.start_min << " " << step.end_hour << ":" << step.end_min << " " << step.step << "\n";
			}
			file.close();
		}
	}
	bool loadfile(const string& filename)
	{
		ifstream file(filename);
		if (!file.is_open())
		{
			return false;
		}

		int day, month, year, start_h, start_m, end_h, end_m, steps;
		char pass1, pass2;
		string line;

		while (getline(file, line))
		{
			istringstream iss(line);

			if (!(iss >> day >> pass1 >> month >> pass1 >> year >> start_h >> pass2 >> start_m >> end_h >> pass2 >> end_m >> steps))
			{
				continue;
			}

			setcount(day, month, year, start_h, start_m, end_h, end_m, steps);
		}

		file.close();
		return true;
	}
};
int main()
{
	pedometre test(28, 3, 2023, 19, 21);
	pedometre ter1;
	ter1.loadfile("results.txt");
	test.setcount(29, 3, 2023, 13, 30, 15, 50, 2354);
	test.setcount(29, 3, 2023, 16, 30, 19, 50, 12000);
	test.setcount(30, 3, 2023, 13, 30, 15, 50, 2354);
	test.setcount(29, 4, 2023, 16, 30, 19, 50, 12000);
	test.getcount(0);
	cout << test.AverageSteps(3) << endl;
	cout << test.AverageSteps() << endl;
	cout << test.AverageweekdaySteps(0) << endl;
	pedometre::Maxstepinfo maxstep = test.Maxcountstep();
	cout << maxstep.step << endl;
	cout << "Date: " << maxstep.day << "." << maxstep.month << "." << maxstep.year << endl;
	test.save_res("results.txt");
	cout << ter1.AverageSteps() << endl;
	system("pause");
	/*cout << test.AverageSteps() << endl;
	system("pause");*/
}

