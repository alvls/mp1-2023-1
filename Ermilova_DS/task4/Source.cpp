#include <iostream>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

struct Observation
{
	int day, month, year, hour;
	double temperature;
};

class Thermometer {

	int StartDay = 0;
	int StartMonth = 0;
	int StartYear = 0;
	int StartHour = 0;

	vector<Observation> Value;

public:

	Thermometer() = default;

	void SetStart(int day, int month, int year, int hour)
	{
		this->StartDay = day;
		this->StartMonth = month;
		this->StartYear = year;
		this->StartHour = hour;
	}

	void GetStart()
	{
		cout << StartDay << "." << StartMonth << "." << StartYear << "  " << StartHour << "\n " << endl;
	}

	void SetValue(int day, int month, int year, int hour, double value)
	{
		bool found = false;
		for (Observation Observation : Value)
		{
			if (Observation.day == day && Observation.month == month && Observation.year == year && Observation.hour == hour)
			{
				found = true;
				Observation.temperature = value;
			}
		}
		if (found == false) {
			Observation a;
			a.day = day;
			a.month = month;
			a.year = year;
			a.hour = hour;
			a.temperature = value;
			Value.push_back(a);
		}
	}

	double GetValue(int day, int month, int year, int hour)
	{
		for (Observation Observation : Value)
		{
			if (Observation.day == day && Observation.month == month && Observation.year == year && Observation.hour == hour)
			{
				return Observation.temperature;
			}
		}
		return -999;
	}

	double AverageTemperatureDate(int day, int month, int year)
	{
		int cnt = 0;
		double sum = 0;
		for (int i = 1; i < 25; i++)
		{
			if (GetValue(day, month, year, i) != -999)
			{
				cnt++;
				sum += GetValue(day, month, year, i);
			}
		}
		if (sum > 0) {
			return sum / cnt;
		}
		else
		{
			return -999;
		}
	}

	double AverageTemperatureMonth(int month)
	{
		int cnt = 0;
		double sum = 0;
		for (int i = 1; i < 32; i++)
		{
			if (AverageTemperatureDate(i, month, StartYear) != -999)
			{
				cnt++;
				sum += AverageTemperatureDate(i, month, StartYear);
			}
		}
		if (sum > 0) {
			return sum / cnt;
		}
		else
		{
			return -999;
		}
	}

	double AverageTemperatureHistory()
	{
		int cnt = 0;
		double sum = 0;
		for (int i = 1; i < 13; i++)
		{
			if (AverageTemperatureMonth(i) != -999)
			{
				cnt++;
				sum += AverageTemperatureMonth(i);
			}
		}
		if (sum > 0) {
			return sum / cnt;
		}
		else
		{
			return -999;
		}
	}

	double AverageNightTemperature(int month)
	{
		int cnt = 0;
		double sum = 0;
		for (int i = 0; i < 4; i++)
		{
			if (AverageTemperatureDate(i, month, StartYear) != -999)
			{
				cnt++;
				sum += AverageTemperatureDate(i, month, StartYear);
			}
		}
		if (sum > 0) {
			return sum / cnt;
		}
		else
		{
			return -999;
		}
	}

	double AverageDayTemperature(int month)
	{
		int cnt = 0;
		double sum = 0;
		for (int i = 12; i < 17; i++)
		{
			if (AverageTemperatureDate(i, month, StartYear) != -999)
			{
				cnt++;
				sum += AverageTemperatureDate(i, month, StartYear);
			}
		}
		if (sum > 0) {
			return sum / cnt;
		}
		else
		{
			return -999;
		}
	}

	void SaveObservation(string path) {

		ofstream fout;
		fout.open(path);

		if (!fout.is_open())
		{
			cout << "File opening error!\n" << endl;
		}
		else
		{
			for (int i = 0; i < Value.size(); ++i)
				fout << Value[i].day << " " << Value[i].month << " " << Value[i].year << " " << Value[i].hour << " " << Value[i].temperature << "\n";
		}
		fout.close();
	}

	void GetObservation(string path) {

		Observation a;
		ifstream fin;
		fin.open(path);

		if (!fin.is_open())
		{
			cout << "File opening error!\n" << endl;
		}
		else
		{

			int day, month, year, hour;
			double value;
			while (fin >> day >> month >> year >> hour >> value) {
				a.day = day;
				a.month = month;
				a.year = year;
				a.hour = hour;
				a.temperature = value;
				Value.push_back(a);
			}
		}
		fin.close();
	}
};

int main()
{
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	double value = 0;
	int cnt = 0;
	int choice = 999;
	string path;
	Thermometer a;

	while (choice != 0) {
		cout << "Press 1 to set the start date and time of observations\nPress 2 to find out the initial date and time of observations\nPress 3 to set observation\nPress 4 to get the temperature in the selected observation\nPress 5 to set a series of observations for the selected date\nPress 6 to find the average temperature for the selected date\nPress 7 to find the average temperature for the selected month\nPress 8 to find the average temperature for the entire history of observations\nPress 9 to find the average daily temperature for the selected month\nPress 10 to find the average night temperature for the selected month\nPress 11 to save the observation history to a file\nPress 12 to read the observation history from the file\nPress 13 to close the program\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter a day\n";
			cin >> day;
			cout << "Enter a month\n";
			cin >> month;
			cout << "Enter a year\n";
			cin >> year;
			cout << "Enter a hour\n";
			cin >> hour;
			a.SetStart(day, month, year, hour);
			break;

		case 2:
			a.GetStart();
			break;

		case 3:
			cout << "Enter a day\n";
			cin >> day;
			cout << "Enter a month\n";
			cin >> month;
			cout << "Enter a year\n";
			cin >> year;
			cout << "Enter a hour\n";
			cin >> hour;
			cout << "Enter a value\n";
			cin >> value;
			a.SetValue(day, month, year, hour, value);
			break;

		case 4:
			cout << "Enter a day\n";
			cin >> day;
			cout << "Enter a month\n";
			cin >> month;
			cout << "Enter a year\n";
			cin >> year;
			cout << "Enter a hour\n";
			cin >> hour;
			cout << a.GetValue(day, month, year, hour) << "\n";
			break;

		case 5:
			cout << "Enter a day\n";
			cin >> day;
			cout << "Enter a month\n";
			cin >> month;
			cout << "Enter a year\n";
			cin >> year;
			cout << "Enter the number of observations\n";
			cin >> cnt;
			for (int i = 0; i < cnt; i++)
			{
				cout << "Enter a hour\n";
				cin >> hour;
				cout << "Enter a value\n";
				cin >> value;
				a.SetValue(day, month, year, hour, value);
			}
			break;
		case 6:
			cout << "Enter a day\n";
			cin >> day;
			cout << "Enter a month\n";
			cin >> month;
			cout << "Enter a year\n";
			cin >> year;
			cout << a.AverageTemperatureDate(day, month, year) << "\n";
			break;

		case 7:
			cout << "Enter a month\n";
			cin >> month;
			cout << a.AverageTemperatureMonth(month) << "\n";
			break;

		case 8:
			cout << a.AverageTemperatureHistory() << "\n";
			break;

		case 9:
			cout << "Enter a month\n";
			cin >> month;
			cout << a.AverageDayTemperature(month) << "\n";
			break;

		case 10:
			cout << "Enter a month\n";
			cin >> month;
			cout << a.AverageNightTemperature(month) << "\n";
			break;

		case 11:
			cout << "Enter the path to the file\n" << endl;
			cin >> path;
			a.SaveObservation(path);
			break;

		case 12:
			cout << "Enter the path to the file\n" << endl;
			cin >> path;
			a.GetObservation(path);
			break;
		}
	}
}