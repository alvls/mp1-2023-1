#pragma once

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class eventsCalendar {
private:
	int place = 0;
	string days[30] = {"0", "0", "0" ,"0" , "0","0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0"};
	string months[30] = { "0", "0", "0" ,"0" , "0","0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0" };
	string years[30] = { "0", "0", "0" ,"0" , "0","0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0" };
	string names[30] = { "0", "0", "0" ,"0" , "0","0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0", "0", "0", "0" ,"0" , "0" };
public:
	eventsCalendar() {};

	void setEvent(string name, int day, int month, int year) {
		if (day > 31 || day < 1 || month > 12 || month < 1 || year < 1 || year > 2100) {
			return;
		}
		else {
			for (int i = 0; i < 30; i++) {
				if (names[i] == string("0")) {
					place = i;
					break;
				}
				else if (days[i] == std::to_string(day) && months[i] == std::to_string(month) && years[i] == std::to_string(year)) {
					return;
				}
			}

			days[place] = std::to_string(day);
			months[place] = std::to_string(month);
			years[place] = std::to_string(year);
			names[place] = name;
		}
	}

	int *getDate(string name) {
		for (int i = 0; i < 30; i++) {
			if (names[i] == name) {
				static int date[3] = { std::stoi(days[i]), std::stoi(months[i]), std::stoi(years[i]) };
				return date;
			}
		}
	}

	int *calcDiff(string name, int day, int month, int year) {
		for (int i = 0; i < 30; i++) {
			if (names[i] == name) {
				int inputDays = day + ((month - 1) * 30) + year * 360; // use 30 days in month -> 360 days in year
				//return "difference " + std::to_string(abs(day - std::stoi(days[i]))) + "days " + std::to_string(abs(month - std::stoi(months[i]))) + "months " + std::to_string(abs(year - std::stoi(years[i]))) + "years"; - bad way to calculate
				int eventDays = std::stoi(days[i]) + ((std::stoi(months[i]) - 1) * 30) + (std::stoi(years[i])) * 360;
				int allDaysDiff = abs(inputDays - eventDays);
				int diffYears = allDaysDiff / 360;
				int diffMonths = (allDaysDiff - diffYears * 360) / 30;
				int diffDays = allDaysDiff - diffYears * 360 - diffMonths * 30;
				static int difference[3] = {diffDays, diffMonths, diffYears};
				return difference;
			}
		}
	}
	void moveEvent(string name, int day, int month, int year, string moveTo) {

		if (moveTo == "up") {
			for (int i = 0; i < 30; i++) {
				if (names[i] == name) {
					int allEventDays = std::stoi(days[i]) + ((std::stoi(months[i]) - 1) * 30) + (std::stoi(years[i])) * 360 + day + (month) * 30 + year * 360 - 1;
					int eventYears = allEventDays / 360;
					int eventMonths = (allEventDays - eventYears * 360) / 30;
					int eventDays = allEventDays - eventYears * 360 - eventMonths * 30;
					years[i] = std::to_string(eventYears);
					months[i] = std::to_string(eventMonths + 1);
					days[i] = std::to_string(eventDays + 1);
					return;
				}
			}
		}
		else if (moveTo == "down") {
			for (int i = 0; i < 30; i++) {
				if (names[i] == name) {
					int allEventDays = std::stoi(days[i]) + ((std::stoi(months[i]) - 1) * 30) + (std::stoi(years[i])) * 360 - day - (month) * 30 - year * 360 - 1;
					int eventYears = allEventDays / 360;
					int eventMonths = (allEventDays - eventYears * 360) / 30;
					int eventDays = allEventDays - eventYears * 360 - eventMonths * 30;
					years[i] = std::to_string(eventYears);
					months[i] = std::to_string(eventMonths + 1);
					days[i] = std::to_string(eventDays + 1);
					return;
				}
			}
		}
	}
	~eventsCalendar() {
		 // we don't need to free static arrays
	}

	void print() { // I don't know how class can show itself in this programm, so I did this:
		cout << "existing class functions:" << endl;
		cout << "void setEvent(string name, int day, int month, int year)" << endl;
		cout << "string getDate(string name)" << endl;
		cout << "string calcDiff(string name, int day, int month, int year)" << endl;
		cout << "void moveEvent(string name, int day, int month, int year, string moveTo)" << endl;
		cout << "list of events:" << endl;

		for (int i = 0; i < 30; i++) {
			if (names[i] == "0") {
				break;
			}
			else {
				cout << names[i] << endl;
			}
		}


	}
			
};
int main() {
	eventsCalendar calendar;

	calendar.setEvent("women's day", 8, 3, 2023);
	calendar.setEvent("fake men's day", 8, 3, 2023);
	calendar.setEvent("women's day", 81, 3, 2023);
	calendar.setEvent("birthday", 24, 8, 2004);
	calendar.moveEvent("tusa-jusa", 20, 1, 2,"up");
	calendar.moveEvent("women's day", 200, 1, 2, "wow");
	calendar.moveEvent("women's day", 20, 2, 2, "up");
	calendar.moveEvent("women's day", 28, 5, 0, "down");
	calendar.print();
	int* date = calendar.calcDiff("birthday", 30, 10, 2020);
	cout << date[1] << endl;
	return 0;
}