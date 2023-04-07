#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Header.h"
#include <clocale>

using namespace std;

struct Film {
	string title;
	string director;
	string writer;
	string composer;
	int day;
	int month;
	int year;
	long int summ;
};

class Filmoteka {
private:
	vector<Film> films;
	void Sort() {
		sort(films.begin(), films.end(), [](Film& a, Film& b) {
			if (a.title != b.title) return a.title < b.title;
			else return a.year < b.year;
			});
	}
	/*void SortMaxSumm() {
		sort(films.begin(), films.end(), [](Film& a, Film& b) {
			if (a.summ > b.summ) return a.summ > b.summ;
			else return a.summ < b.summ;
			});
	}*/
public:
	Filmoteka() { }

	void AddFilm(Film& film) {
		films.push_back(film);
		Sort();
	}

	void EditFilm(string title, int year, Film& film) {
		for (int i = 0; i < films.size(); i++) {
			if (films[i].title == title && films[i].year == year) {
				films[i] = film;
				break;
			}
		}
		Sort();
	}

	Film FindFilm(string title, int year) {
		for (int i = 0; i < films.size(); i++) {
			if (films[i].title == title && films[i].year == year)
				return films[i];
		}
		return Film();
	}

	vector<Film> ByOneDirector(string director) {
		vector<Film> res;
		for (int i = 0; i < films.size(); i++) {
			if (films[i].director == director)
				res.push_back(films[i]);
		}
		return res;
	}

	vector<Film> ThisYearFilms(int year) {
		vector<Film> res;
		for (int i = 0; i < films.size(); i++) {
			if (films[i].year == year)
				res.push_back(films[i]);
		}
		return res;
	}

	vector<Film> MaxSummFilms(int count) {
		vector<Film> max;
		sort(films.begin(), films.end(), [](Film& a, Film& b) {
			return a.summ > b.summ;
			});
		for (int i = 0; i < min(count, (int)films.size()); i++) {
			max.push_back(films[i]);
		}
		Sort();
		return max;
	}
	vector<Film> MaxSummThisYear(int count, int year) {
		vector<Film> res = ThisYearFilms(year);
		sort(res.begin(), res.end(), [](Film& a, Film& b) {
			return a.summ > b.summ;
			});
		vector<Film> Top;
		for (int i = 0; i < min(count, (int)res.size()); i++)
			Top.push_back(res[i]);
		return Top;
	}

	int GetCount() {
		return films.size();
	}

	void Delete(string title, int year) {
		for (int i = 0; i < films.size(); i++)
			if (films[i].title == title && films[i].year == year) {
				films.erase(films.begin() + i);
				break;
			}
	}

	void SaveFile(string name) {
		ofstream file(name);
		for (int i = 0; i < films.size(); i++) {
			file << films[i].title << endl;
			file << films[i].director << endl;
			file << films[i].writer << endl;
			file << films[i].composer << endl;
			file << films[i].day << "." << films[i].month << "." << films[i].year << endl;
			file << films[i].summ << endl;
		}
		file.close();
	}

	void ReadFile(string name) {
		ifstream file(name);
		Film film;
		while (getline(file, film.title)) {
			getline(file, film.director);
			getline(file, film.writer);
			getline(file, film.composer);
			char tmp;
			file >> film.day >> tmp >> film.month >> tmp >> film.year;
			file >> film.summ;
			films.push_back(film);
		}
		file.close();
		Sort();
	}
};

Film EnterFilm() {
	Film buf;
	cout << "�������� ������: ";
	cin >> buf.title; cout << endl;
	cout << "�������� ������: ";
	cin >> buf.director; cout << endl;
	cout << "��������� ������: ";
	cin >> buf.writer; cout << endl;
	cout << "���������� ������: ";
	cin >> buf.composer; cout << endl;
	cout << "���� ������ ������: ";
	cin >> buf.day; cout << endl;
	cout << "����� ������ ������: ";
	cin >> buf.month; cout << endl;
	cout << "��� ������ ������: ";
	cin >> buf.year; cout << endl;
	cout << "�������� ����� ������: ";
	cin >> buf.summ; cout << endl;
	return buf;
}

int main() {
	Filmoteka FILMS;
	setlocale(LC_CTYPE, "Rus");
	char* MainMenu[12] = { (char*)"����������", (char*)"�������� �����", (char*)"�������� ������ ������",
	(char*)"����� �����", (char*)"��� ������ ��������� ���������", (char*)"��� ������, �������� � ������ � ��������� ����",
	(char*)"������ � ����������� �������", (char*)"������ � ����������� ������� � ��������� ����",
	(char*)"������� ����� �������", (char*)"������� �����", (char*)"��������� ���������� � ����", (char*)"������� ���������� �� �����" };
	int choose = 0;
	while (choose != KEY_EXIT) {
		choose = menu(MainMenu, 12);
		switch (choose) {
		case 1: {
			system("cls");
			cout << "�������� �����" << endl;
			cout << "������� ������" << endl;
			Film buf = EnterFilm();
			FILMS.AddFilm(buf);
			break;
		}
		case 2: {
			system("cls");
			cout << "�������� ������ ���������� ������" << endl;
			string title; int year;
			cout << "������� �������� ������" << endl;
			cin >> title;
			cout << "������� ��� ������ ������" << endl;
			cin >> year;
			Film buf = EnterFilm();
			FILMS.EditFilm(title, year, buf);
			cout << "������� ��������!" << endl;
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			cout << "����� �����" << endl;
			string title; int year;
			cout << "������� �������� ������" << endl;
			cin >> title;
			cout << "������� ��� ������ ������" << endl;
			cin >> year;
			Film buf = FILMS.FindFilm(title, year);
			if (buf.title != " ") {
				cout << "��������: " << buf.title << endl;
				cout << "��������: " << buf.director << endl;
				cout << "���������: " << buf.writer << endl;
				cout << "����������: " << buf.composer << endl;
				cout << "���� ������: " << buf.day << "." << buf.month << "." << buf.year << endl;
				cout << "�������� �����: " << buf.summ << endl;
			}
			else cout << "����� �� ������" << endl;
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			string direct;
			vector<Film> directfilm;
			cout << "������� ��������� ";
			cin >> direct;
			cout << "��� ������ �� ���������� �� " << direct << endl;
			directfilm = FILMS.ByOneDirector(direct);
			for (int i = 0; i < directfilm.size(); i++) {
				cout << "��������: " << directfilm[i].title << " ��� ������: " << directfilm[i].year << endl;
			}
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			cout << "����� ������� �� ���� �� ������ � ������" << endl;
			int year;
			vector<Film> yearfilm;
			cout << "������� ��� ������ ";
			cin >> year;
			cout << endl;
			yearfilm = FILMS.ThisYearFilms(year);
			for (int i = 0; i < yearfilm.size(); i++) {
				if (yearfilm[i].title != " ") {
					cout << "��������: " << yearfilm[i].title << endl;
					cout << "��������: " << yearfilm[i].director << endl;
					cout << "���������: " << yearfilm[i].writer << endl;
					cout << "����������: " << yearfilm[i].composer << endl;
					cout << "�������� �����: " << yearfilm[i].summ << endl;
					cout << endl;
				}
			}
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			int count = 0;
			cout << "�������, ����� ���-�� ������� � ����������� ������� �� ������ ������� ";
			cin >> count;
			cout << "������ � ����������� �������: " << endl;
			vector<Film> maxsum = FILMS.MaxSummFilms(count);
			for (int i = 0; i < maxsum.size(); i++) {
				cout << "��������: " << maxsum[i].title << " �������� �����: " << maxsum[i].summ << endl;
			}
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			int count = 0, year = 0;
			cout << "�������, ����� ���-�� ������� � ����������� ������� �� ������ ������� ";
			cin >> count;
			cout << "������� ��� ������ ������� � ������ ";
			cin >> year;
			cout << "������ � ����������� ������� " << year << " ����" << endl;
			vector<Film> buf = FILMS.MaxSummThisYear(count, year);
			for (int i = 0; i < buf.size(); i++) {
				cout << i + 1 << "." << "��������: " << buf[i].title << " �������� ����� : " << buf[i].summ << endl;
			}
			system("pause");
			break;
		}
		case 8: {
			system("cls");
			cout << "������� ����� ������� = " << FILMS.GetCount() << endl;
			system("pause");
			break;
		}
		case 9: {
			system("cls");
			string name; int year;
			cout << "������� ����� �� ����������" << endl;
			cout << "������� �������� ������ ";
			cin >> name;
			cout << "������� ��� ������ ������ � ������";
			cin >> year;
			FILMS.Delete(name, year);
			cout << "������� �������!" << endl;
			system("pause");
			break;
		}
		case 10: {
			system("cls");
			string file;
			cout << "��������� ���������� � ����" << endl;
			cout << "������� �������� ����� ";
			cin >> file;
			FILMS.SaveFile(file);
			cout << "���������� ������ �������!" << endl;
			system("pause");
			break;
		}
		case 11: {
			system("cls");
			string file;
			cout << "������� ���������� �� �����" << endl;
			cout << "������� �������� ����� ";
			cin >> file;
			FILMS.ReadFile(file);
			cout << "���������� ���������!" << endl;
			system("pause");
			break;
		}
		}
	}
	system("cls");
}