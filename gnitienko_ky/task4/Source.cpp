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
	cout << "Название фильма: ";
	cin >> buf.title; cout << endl;
	cout << "Режиссер фильма: ";
	cin >> buf.director; cout << endl;
	cout << "Сценарист фильма: ";
	cin >> buf.writer; cout << endl;
	cout << "Композитор фильма: ";
	cin >> buf.composer; cout << endl;
	cout << "День выхода фильма: ";
	cin >> buf.day; cout << endl;
	cout << "Месяц выхода фильма: ";
	cin >> buf.month; cout << endl;
	cout << "Год выхода фильма: ";
	cin >> buf.year; cout << endl;
	cout << "Кассовые сборы фильма: ";
	cin >> buf.summ; cout << endl;
	return buf;
}

int main() {
	Filmoteka FILMS;
	setlocale(LC_CTYPE, "Rus");
	char* MainMenu[12] = { (char*)"ФИЛЬМОТЕКА", (char*)"Добавить фильм", (char*)"Изменить данные фильма",
	(char*)"Найти фильм", (char*)"Все фильмы заданного режиссера", (char*)"Все фильмы, вышедшие в прокат в выбранном году",
	(char*)"Фильмы с наибольшими сборами", (char*)"Фильмы с наибольшими сборами в выбранном году",
	(char*)"Текущее число фильмов", (char*)"Удалить фильм", (char*)"Сохранить фильмотеку в файл", (char*)"Считать фильмотеку из файла" };
	int choose = 0;
	while (choose != KEY_EXIT) {
		choose = menu(MainMenu, 12);
		switch (choose) {
		case 1: {
			system("cls");
			cout << "Добавить фильм" << endl;
			cout << "Введите данные" << endl;
			Film buf = EnterFilm();
			FILMS.AddFilm(buf);
			break;
		}
		case 2: {
			system("cls");
			cout << "Изменить данные выбранного фильма" << endl;
			string title; int year;
			cout << "Введите название фильма" << endl;
			cin >> title;
			cout << "Введите год выхода фильма" << endl;
			cin >> year;
			Film buf = EnterFilm();
			FILMS.EditFilm(title, year, buf);
			cout << "Успешно изменено!" << endl;
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			cout << "Найти фильм" << endl;
			string title; int year;
			cout << "Введите название фильма" << endl;
			cin >> title;
			cout << "Введите год выхода фильма" << endl;
			cin >> year;
			Film buf = FILMS.FindFilm(title, year);
			if (buf.title != " ") {
				cout << "Название: " << buf.title << endl;
				cout << "Режиссер: " << buf.director << endl;
				cout << "Сценарист: " << buf.writer << endl;
				cout << "Композитор: " << buf.composer << endl;
				cout << "Дата выхода: " << buf.day << "." << buf.month << "." << buf.year << endl;
				cout << "Кассовые сборы: " << buf.summ << endl;
			}
			else cout << "Фильм не найден" << endl;
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			string direct;
			vector<Film> directfilm;
			cout << "Введите режиссера ";
			cin >> direct;
			cout << "Все фильмы из фильмотеки от " << direct << endl;
			directfilm = FILMS.ByOneDirector(direct);
			for (int i = 0; i < directfilm.size(); i++) {
				cout << "Название: " << directfilm[i].title << " Год выхода: " << directfilm[i].year << endl;
			}
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			cout << "Поиск фильмов по году их выхода в прокат" << endl;
			int year;
			vector<Film> yearfilm;
			cout << "Введите год выхода ";
			cin >> year;
			cout << endl;
			yearfilm = FILMS.ThisYearFilms(year);
			for (int i = 0; i < yearfilm.size(); i++) {
				if (yearfilm[i].title != " ") {
					cout << "Название: " << yearfilm[i].title << endl;
					cout << "Режиссер: " << yearfilm[i].director << endl;
					cout << "Сценарист: " << yearfilm[i].writer << endl;
					cout << "Композитор: " << yearfilm[i].composer << endl;
					cout << "Кассовые сборы: " << yearfilm[i].summ << endl;
					cout << endl;
				}
			}
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			int count = 0;
			cout << "Введите, какое кол-во фильмов с наибольшими сборами вы хотите увидеть ";
			cin >> count;
			cout << "Фильмы с наибольшими сборами: " << endl;
			vector<Film> maxsum = FILMS.MaxSummFilms(count);
			for (int i = 0; i < maxsum.size(); i++) {
				cout << "Название: " << maxsum[i].title << " Кассовые сборы: " << maxsum[i].summ << endl;
			}
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			int count = 0, year = 0;
			cout << "Введите, какое кол-во фильмов с наибольшими сборами вы хотите увидеть ";
			cin >> count;
			cout << "Введите год выхода фильмов в прокат ";
			cin >> year;
			cout << "Фильмы с наибольшими сборами " << year << " года" << endl;
			vector<Film> buf = FILMS.MaxSummThisYear(count, year);
			for (int i = 0; i < buf.size(); i++) {
				cout << i + 1 << "." << "Название: " << buf[i].title << " Кассовые сборы : " << buf[i].summ << endl;
			}
			system("pause");
			break;
		}
		case 8: {
			system("cls");
			cout << "Текущее число фильмов = " << FILMS.GetCount() << endl;
			system("pause");
			break;
		}
		case 9: {
			system("cls");
			string name; int year;
			cout << "Удалить фильм из фильмотеки" << endl;
			cout << "Введите название фильма ";
			cin >> name;
			cout << "Введите год выхода фильма в прокат";
			cin >> year;
			FILMS.Delete(name, year);
			cout << "Успешно удалено!" << endl;
			system("pause");
			break;
		}
		case 10: {
			system("cls");
			string file;
			cout << "Сохранить фильмотеку в файл" << endl;
			cout << "Введите название файла ";
			cin >> file;
			FILMS.SaveFile(file);
			cout << "Сохранение прошло успешно!" << endl;
			system("pause");
			break;
		}
		case 11: {
			system("cls");
			string file;
			cout << "Считать фильмотеку из файла" << endl;
			cout << "Введите название файла ";
			cin >> file;
			FILMS.ReadFile(file);
			cout << "Фильмотека загружена!" << endl;
			system("pause");
			break;
		}
		}
	}
	system("cls");
}