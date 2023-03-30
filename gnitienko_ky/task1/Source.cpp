#include <stdio.h>
#include <math.h>
#include <io.h>
#include <Windows.h>
#include <locale.h>
#include <iostream>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

class Time {
	time_t hours, UserHours;
	time_t minutes, UserMinutes;
	time_t seconds, UserSeconds;
public:
	Time() {
		time_t now = time(0);
		tm* ltm = localtime(&now);
		hours = ltm->tm_hour;
		minutes = ltm->tm_min;
		seconds = ltm->tm_sec;
	}
	void EnterTime(int a, int b, int c) {
		UserHours = a;
		UserMinutes = b;
		UserSeconds = c;
	}
	void Print1() {
		cout << "Текущее время: " << hours << ":" << minutes << ":" << seconds << endl;
	}
	void Print2() {
		cout << "Пользовательское время: " << UserHours << ":" << UserMinutes << ":" << UserSeconds << endl;
	}
	Time Difference(const Time& t) {
		Time t_buf;
		t_buf.hours = abs(hours - t.UserHours);
		t_buf.minutes = abs(minutes - t.UserMinutes);
		t_buf.seconds = abs(seconds - t.UserSeconds);
		return t_buf;
	}
	int DifferenceHour() {
		return abs(hours - UserHours);
	}
	int DifferenceMinnute() {
		return abs(minutes - UserMinutes);
	}
	int DifferenceSeconds() {
		return abs(seconds - UserSeconds);
	}
	int PlusHour(int h, int m, int s) {
		int hour, minute, sec;
		int buffHours1 = h , buffMinutes1 = m, buffSeconds1 = s;
		if (buffSeconds1 / 60 > 0)  buffMinutes1 += (buffSeconds1 / 60);
		if ((buffSeconds1 % 60) + seconds > 60) buffMinutes1++;
		if (buffMinutes1 / 60 > 0)  buffHours1 += (buffMinutes1 / 60);
		if ((buffMinutes1 % 60) + minutes > 60) buffHours1++;
		while (((hours + buffHours1) % 24 <= 24) && ((hours + buffHours1) % 24 >= 0)) { hour = hours + buffHours1; buffHours1 -= 24; }
		while (((minutes + buffMinutes1) % 60 <= 60) && ((minutes + buffMinutes1) % 60 >= 0)) { minute = minutes + buffMinutes1; buffMinutes1 -= 60; }
		while (((seconds + buffSeconds1) % 60 <= 60) && ((seconds + buffSeconds1) % 60 >= 0)) { sec = seconds + buffSeconds1; buffSeconds1 -= 60; }
		return hour;
	}
	int PlusMinute(int h, int m, int s) {
		int hour, minute, sec;
		int buffHours1 = h, buffMinutes1 = m, buffSeconds1 = s;
		if (buffSeconds1 / 60 > 0)  buffMinutes1 += (buffSeconds1 / 60);
		if ((buffSeconds1 % 60) + seconds > 60) buffMinutes1++;
		if (buffMinutes1 / 60 > 0)  buffHours1 += (buffMinutes1 / 60);
		if ((buffMinutes1 % 60) + minutes > 60) buffHours1++;
		while (((hours + buffHours1) % 24 <= 24) && ((hours + buffHours1) % 24 >= 0)) { hour = hours + buffHours1; buffHours1 -= 24; }
		while (((minutes + buffMinutes1) % 60 <= 60) && ((minutes + buffMinutes1) % 60 >= 0)) { minute = minutes + buffMinutes1; buffMinutes1 -= 60; }
		while (((seconds + buffSeconds1) % 60 <= 60) && ((seconds + buffSeconds1) % 60 >= 0)) { sec = seconds + buffSeconds1; buffSeconds1 -= 60; }
		return minute;
	}
	int PlusSec(int h, int m, int s) {
		int hour, minute, sec;
		int buffHours1 = h, buffMinutes1 = m, buffSeconds1 = s;
		if (buffSeconds1 / 60 > 0)  buffMinutes1 += (buffSeconds1 / 60);
		if ((buffSeconds1 % 60) + seconds > 60) buffMinutes1++;
		if (buffMinutes1 / 60 > 0)  buffHours1 += (buffMinutes1 / 60);
		if ((buffMinutes1 % 60) + minutes > 60) buffHours1++;
		while (((hours + buffHours1) % 24 <= 24) && ((hours + buffHours1) % 24 >= 0)) { hour = hours + buffHours1; buffHours1 -= 24; }
		while (((minutes + buffMinutes1) % 60 <= 60) && ((minutes + buffMinutes1) % 60 >= 0)) { minute = minutes + buffMinutes1; buffMinutes1 -= 60; }
		while (((seconds + buffSeconds1) % 60 <= 60) && ((seconds + buffSeconds1) % 60 >= 0)) { sec = seconds + buffSeconds1; buffSeconds1 -= 60; }
		return sec;
	}
	int MinusHour(int h, int m, int s) {
		int hour;
		int buffHours2 = h, buffMinutes2 = m, buffSeconds2 = s;
		if (buffSeconds2 / 60 > 0) { buffMinutes2 += (buffSeconds2 / 60); buffSeconds2 = s % 60; }
		if (buffMinutes2 / 60 > 0) { buffHours2 += (buffMinutes2 / 60); buffMinutes2 = buffMinutes2 % 60; }
		buffHours2 = buffHours2 % 24;
		if (hours - buffHours2 < 0) {
			hour = (hours + 24) - buffHours2;
		}
		else hour = hours - buffHours2;
		return hour;
	}
	int MinusMinute(int h, int m, int s) {
		int minute;
		int buffHours2 = h, buffMinutes2 = m, buffSeconds2 = s;
		if (buffSeconds2 / 60 > 0) { buffMinutes2 += (buffSeconds2 / 60); buffSeconds2 = s % 60; }
		if (buffMinutes2 / 60 > 0) { buffHours2 += (buffMinutes2 / 60); buffMinutes2 = buffMinutes2 % 60; }
		buffHours2 = buffHours2 % 24;
		//******************************************//
		if (minutes - buffMinutes2 < 0) {
			minute = (minutes + 60) - buffMinutes2;
		}
		else minute = minutes - buffMinutes2;
		return minute;
	}
	int MinusSec(int h, int m, int s) {
		int sec;
		int buffHours2 = h, buffMinutes2 = m, buffSeconds2 = s;
		if (buffSeconds2 / 60 > 0) { buffMinutes2 += (buffSeconds2 / 60); buffSeconds2 = s % 60; }
		if (buffMinutes2 / 60 > 0) { buffHours2 += (buffMinutes2 / 60); buffMinutes2 = buffMinutes2 % 60; }
		buffHours2 = buffHours2 % 24;

		if (seconds - buffSeconds2 < 0) {
			sec = (seconds + 60) - buffSeconds2;
		}
		else sec = seconds - buffSeconds2;
		return sec;
	}
};

void main() {
	int a, b, c;
	int h, m, s;
	setlocale(LC_CTYPE, "Rus");
	Time t;
	Time a;
	t.Print1();
	//*********************************************//
	cout << "Введите любое время: " << endl;
	cout << "Часы: ";
	cin >> a;
	while (a < 0 || a > 23) {
		cout << "Введите корректное кол-во часов: ";
		cin >> a;
	}
	cout << "Минуты: ";
	cin >> b;
	while (b < 0 || b > 59) {
		cout << "Введите корректное кол-во минут: ";
		cin >> b;
	}
	cout << "Секунды: ";
	cin >> c;
	while (c < 0 || c > 59) {
		cout << "Введите корректное кол-во секунд: ";
		cin >> c;
	}
	t.EnterTime(a, b, c);
	t.Print2();
	cout << "Разница между текущим и пользовательским временем: ";// << t.DifferenceHour() << ":" << t.DifferenceMinnute() << ":" << t.DifferenceSeconds() << endl;
	t.Difference(t); cout << endl;
	system("pause");
	system("cls");
	//*********************************************//
	t.Print1();
	cout << "Введите время, на которое будет сдвинуто текущее" << endl;
	cout << "Часы: ";
	cin >> h;
	cout << "Минуты: ";
	cin >> m;
	cout << "Секунды: ";
	cin >> s;
	cout << "Время со сдвигом в большую сторону: " << t.PlusHour(h, m, s) << ":" << t.PlusMinute(h, m, s) << ":" << t.PlusSec(h, m, s) << endl;
	cout << "Время со сдвигом в меньшую сторону: " << t.MinusHour(h, m, s) << ":" << t.MinusMinute(h, m, s) << ":" << t.MinusSec(h, m, s) << endl;
	system("pause");
}