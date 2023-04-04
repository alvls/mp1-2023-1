#include <iostream>
#include <locale>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;
class Film
{
	string FilmName;
	string DirName, DirSurname;
	string ScrName, ScrSurname;
	string ComName, ComSurname;
	int day, month, year;
	long long int money;
public:
	Film()
	{
		FilmName = "FilmName";
		DirName = "DirName";
		DirSurname = "DirSurname";
		ScrName = "ScrName";
		ScrSurname = "ScrSurname";
		ComName = "ComName";
		ComSurname = "ComSurname";
		day = 1;
		month = 1;
		year = 1000;
		money = 1000000;
	}
	bool operator==(const Film& fi)
	{
		if ((FilmName == fi.FilmName) && (DirName == fi.DirName) && (DirSurname == fi.DirSurname) && (ScrName == fi.ScrName) && (ScrSurname == fi.ScrSurname) &&
			(ComName == fi.ComName) && (ComSurname == fi.ComSurname) && (day == fi.day) && (month == fi.month) && (year == fi.year) && (money == fi.money))
			return true;
		return false;
	}
	bool operator>(const Film& f)
	{
		if (FilmName > f.FilmName)
			return true;
		else if (FilmName < f.FilmName)
			return false;
		else if (year > f.year)
			return true;
		return false;
	}
	bool operator<(const Film& f)
	{
		if (FilmName < f.FilmName)
			return true;
		else if (FilmName > f.FilmName)
			return false;
		else
			if (year < f.year)
				return true;
		return false;
	}
	Film& operator=(const Film& fi)
	{
		if (this == &fi)
			return *this;
		FilmName = fi.FilmName;
		DirName = fi.DirName;
		DirSurname = fi.DirSurname;
		ScrName = fi.ScrName;
		ScrSurname = fi.ScrSurname;
		ComName = fi.ComName;
		ComSurname = fi.ComSurname;
		day = fi.day;
		month = fi.month;
		year = fi.year;
		money = fi.money;
		return *this;
	}
	string GetFilmName() { return FilmName; }
	string GetDirName() { return DirName; }
	string GetDirSurname() { return DirSurname; }
	string GetScrName() { return ScrName; }
	string GetScrSurname() { return ScrSurname; }
	string GetComName() { return ComName; }
	string GetComSurname() { return ComSurname; }
	int GetDay() { return day; }
	int GetMonth() { return month; }
	int GetYear() { return year; }
	int GetMoney() { return money; }
	void SetFilmName(string _FilmName) { FilmName = _FilmName; }
	void SetDirName(string _DirName) { DirName = _DirName; }
	void SetDirSurname(string _DirSurname) { DirSurname = _DirSurname; }
	void SetScrName(string _ScrName) { ScrName = _ScrName; }
	void SetScrSurname(string _ScrSurname) { ScrSurname = _ScrSurname; }
	void SetComName(string _ComName) { ComName = _ComName; }
	void SetComSurname(string _ComSurname) { ComSurname = _ComSurname; }
	void Setday(int _day) { day = _day; }
	void Setmonth(int _month) { month = _month; }
	void Setyear(int _year) { year = _year; }
	void Setmoney(long long int _money) { money = _money; }
	void PrintFilm()
	{
		cout << "Название фильма: " << FilmName << endl;
		cout << "Режисcер: " << DirName << " " << DirSurname << endl;
		cout << "Сценарист: " << ScrName << " " << ScrSurname << endl;
		cout << "Композитор: " << ComName << " " << ComSurname << endl;
		cout << "Дата выхода: " << day << "." << month << "." << year << endl;
		cout << "Сборы: " << money << " руб." << endl;
	}
};
class FilmLibrary
{
	vector <Film> library;
public:
	FilmLibrary() {}
	int SizeLibrary() { return library.size(); }//узнать число фильмов
	void DeleteFilm(int index) { library.erase(library.begin() + index); }//удаление фильма
	void SortByNameAndYear()//сортировка по имени или году
	{
		int i, j, c;
		Film tmp;
		for (i = 0;i < library.size() - 1;i++)
		{
			c = 0;
			for (j = library.size() - 1;j > i;j--)
				if (library[j - 1] > library[j])
				{
					c++;
					tmp = library[j - 1];
					library[j - 1] = library[j];
					library[j] = tmp;
				}
			if (c == 0)
				break;
		}
	}
	void SortByMoney()//сортировка по сборам
	{
		int i, j, c;
		Film tmp;
		for (i = 0;i < library.size() - 1;i++)
		{
			c = 0;
			for (j = library.size() - 1;j > i;j--)
				if (library[j - 1].GetMoney() < library[j].GetMoney())
				{
					c++;
					tmp = library[j - 1];
					library[j - 1] = library[j];
					library[j] = tmp;
				}
			if (c == 0)
				break;
		}
	}
	bool AddFilm(const Film& f)//добавление фильма
	{
		bool add;
		for (int i = 0;i < library.size();i++)
			if (library[i] == f)
				return false;
		library.push_back(f);
		SortByNameAndYear();
		return true;
	}
	void EditFilm(int ind, string _FilmName, string _DirName, string _DirSurname, string _SctName, string _ScrSurname, string _ComName, string _ComSurname,
		int _day, int _month, int _year, int _money)//изменение данных фильма
	{
		library[ind].SetFilmName(_FilmName);
		library[ind].SetDirName(_DirName);
		library[ind].SetDirSurname(_DirSurname);
		library[ind].SetScrName(_SctName);
		library[ind].SetScrSurname(_ScrSurname);
		library[ind].SetComName(_ComName);
		library[ind].SetComSurname(_ComSurname);
		library[ind].Setday(_day);
		library[ind].Setmonth(_month);
		library[ind].Setyear(_year);
		library[ind].Setmoney(_money);
		SortByNameAndYear();
	}
	int FindByYearAndName(int y, string n)//поиск фильма по названию и году
	{
		Film tmp;
		for (int i = 0;i < library.size();i++)
		{
			if ((library[i].GetYear() == y) && (library[i].GetFilmName() == n))
				return i;
		}
		return -1;
	}
	vector <Film> ChooseByDirector(string DirectorSur)//отбор фильмов по режиссеру
	{
		vector <Film> DirFilms;
		for (int i = 0;i < library.size();i++)
			if (library[i].GetDirSurname() == DirectorSur)
				DirFilms.push_back(library[i]);
		return DirFilms;
	}
	vector <Film> ChooseByYear(int year)//отбор фильмов по году
	{
		vector <Film> YearFilms;
		for (int i = 0;i < library.size();i++)
			if (library[i].GetYear() == year)
				YearFilms.push_back(library[i]);
		return YearFilms;
	}
	vector <Film> ChooseByMoney(int count, int year)//заданное число фильмов с наибольшими сборами (и с выбором года)
	{
		vector <Film> MoneyFilms;
		if (year == 0)
			for (int i = 0;i < count;i++)
				MoneyFilms.push_back(library[i]);
		else
			for (int i = 0;i < count;i++)
				if (library[i].GetYear() == year)
					MoneyFilms.push_back(library[i]);
		return MoneyFilms;
	}
	bool FindSame(Film f)
	{
		for (int i = 0;i < library.size();i++)
			if (f == library[i])
				return true;
		return false;
	}
	bool ReadFile()//на примере файла "Films.txt"
	{
		ifstream rfile("Films.txt");
		string FName, DName, DSurname, SName, SSurname, CName, CSurname;
		int d, m, y;
		long long int money;
		Film tmp;
		if (!rfile.is_open())
			return false;
		while (!rfile.eof())
		{
			getline(rfile, FName, '/');
			rfile >> DName >> DSurname >> SName >> SSurname >> CName >> CSurname >> d >> m >> y >> money;
			tmp.SetFilmName(FName);
			tmp.SetDirName(DName);
			tmp.SetDirSurname(DSurname);
			tmp.SetScrName(SName);
			tmp.SetScrSurname(SSurname);
			tmp.SetComName(CName);
			tmp.SetComSurname(CSurname);
			tmp.Setday(d);
			tmp.Setmonth(m);
			tmp.Setyear(y);
			tmp.Setmoney(money);
			if (!FindSame(tmp))
				library.push_back(tmp);
		}
		SortByNameAndYear();
		rfile.close();
		return true;
	}
	void SaveFile()//на примере файла "Films.txt"
	{
		ofstream sfile("Films1.txt");
		for (int i = 0;i < library.size();i++)
		{
			sfile << library[i].GetFilmName() << '/';
			sfile << library[i].GetDirName() << " ";
			sfile << library[i].GetDirSurname() << " ";
			sfile << library[i].GetScrName() << " ";
			sfile << library[i].GetScrSurname() << " ";
			sfile << library[i].GetComName() << " ";
			sfile << library[i].GetComSurname() << " ";
			sfile << library[i].GetDay() << " ";
			sfile << library[i].GetMonth() << " ";
			sfile << library[i].GetYear() << " ";
			sfile << library[i].GetMoney();
		}
		sfile.close();
	}
	Film& operator[](int ind) { return library[ind]; }
	~FilmLibrary() {}
};
void Options()
{
	FilmLibrary films;
	vector <Film> tmp_films;
	Film new_film, tmp;
	int operation;
	string FName, DName, DSurname, SName, SSurname, CName, CSurname;
	int d, m, y, ind, t, count;
	long long int money;
	while (1)
	{
		system("cls");
		cout << "1) добавить фильм" << endl << "2) изменить данные выбранного фильма" << endl << "3) найти фильм по названию и году" << endl << "4) выдать все фильмы заданного режиссера" << endl
			<< "5) выдать все фильмы, вышедшие в прокат в выбранном году" << endl << "6) выдать заданное число фильмов с наибольшими сборами" << endl << "7) выдать заданное число фильмов с наибольшими сборами в выбранном году" << endl
			<< "8) узнать текущее число фильмов" << endl << "9) удалить фильм" << endl << "10) сохранить фильмотеку в файл" << endl << "11) считать фильмотеку из файла" << endl;
		cin >> operation;
		system("cls");
		switch (operation)
		{
		case 1:
			cout << "Введите название фильма (добавьте / в конце названия): ";
			getline(cin, FName, '/');
			cout << "Введите имя и фамилию режиссера (через пробел): " << endl;
			cin >> DName;
			cin >> DSurname;
			cout << "Введите имя и фамилию сценариста (через пробел): " << endl;
			cin >> SName;
			cin >> SSurname;
			cout << "Введите имя и фамилию композитора (через пробел): " << endl;
			cin >> CName;
			cin >> CSurname;
			cout << "Введите день, месяц и год выхода (через пробел): " << endl;
			cin >> d;
			cin >> m;
			cin >> y;
			cout << "Введите сборы фильма: " << endl;
			cin >> money;
			new_film.SetFilmName(FName);
			new_film.SetDirName(DName);
			new_film.SetDirSurname(DSurname);
			new_film.SetScrName(SName);
			new_film.SetScrSurname(SSurname);
			new_film.SetComName(CName);
			new_film.SetComSurname(CSurname);
			new_film.Setday(d);
			new_film.Setmonth(m);
			new_film.Setyear(y);
			new_film.Setmoney(money);
			if (films.AddFilm(new_film))
			{
				cout << "Фильм добавлен" << endl;
			}
			else
				cout << "Такой фильм уже существует" << endl;
			break;
		case 2:
			cout << "Ведите номер фильма в списке, данные которого вы хотите изменить: ";
			cin >> ind;
			cout << "Введите название фильма (добавьте / в конце названия): ";
			getline(cin, FName, '/');
			cout << "Введите имя и фамилию режиссера (через пробел): ";
			cin >> DName;
			cin >> DSurname;
			cout << "Введите имя и фамилию сценариста (через пробел): ";
			cin >> SName;
			cin >> SSurname;
			cout << "Введите имя и фамилию композитора(через пробел): ";
			cin >> CName;
			cin >> CSurname;
			cout << "Введите день, месяц и год выхода (через пробел): ";
			cin >> d;
			cin >> m;
			cin >> y;
			cout << "Введите сборы фильма: ";
			cin >> money;
			system("cls");
			if ((ind >= 0) && (ind <= films.SizeLibrary()))
			{
				films.EditFilm(ind - 1, FName, DName, DSurname, SName, SSurname, CName, CSurname, d, m, y, money);
				cout << "Фильм изменен";
			}
			else
				cout << "Неверный номер" << endl;
			break;
		case 3:
			cout << "Введите год выхода фильма: ";
			cin >> y;
			cout << "Введите название фильма (добавьте / в конце названия): ";
			getline(cin, FName, '/');
			system("cls");
			ind = films.FindByYearAndName(y, FName);
			if (ind != -1)
			{
				cout << "Результат поиска:" << endl;
				films[ind].PrintFilm();
			}
			else
				cout << "По вашему запросу ничего не найдено" << endl;
			break;
		case 4:
			cout << "Введите фамилию режиссера: ";
			cin >> DSurname;
			tmp_films = films.ChooseByDirector(DSurname);
			system("cls");
			if (tmp_films.size() != 0)
			{
				cout << "Фильмы выбранного режиссера: " << endl;
				for (int i = 0;i < tmp_films.size();i++)
				{
					cout << endl;
					tmp_films[i].PrintFilm();
				}
			}
			else
				cout << "Фильмы не найдены...";
			break;
		case 5:
			cout << "Введите год: ";
			cin >> y;
			system("cls");
			tmp_films = films.ChooseByYear(y);
			if (tmp_films.size() != 0)
			{
				cout << "Фильмы выбранного года: " << endl;
				for (int i = 0;i < tmp_films.size();i++)
				{
					cout << endl;
					tmp_films[i].PrintFilm();
				}
			}
			else
				cout << "Фильмы не найдены...";
			break;
		case 6:
			cout << "Введите количество фильмов для выборки: ";
			cin >> count;
			system("cls");
			if ((count > 0) && (count <= films.SizeLibrary()))
			{
				films.SortByMoney();
				tmp_films = films.ChooseByMoney(count, 0);
				if (tmp_films.size() != 0)
				{
					cout << "Фильмы с наибольшими сборами: " << endl;
					for (int i = 0;i < tmp_films.size();i++)
					{
						cout << endl;
						tmp_films[i].PrintFilm();
					}
				}
				else
					cout << "Фильмы не найдены...";
				films.SortByNameAndYear();
			}
			else
				cout << "Недопустимое количество фильмов";
			break;
		case 7:
			cout << "Введите количество фильмов для выборки: ";
			cin >> count;
			cout << "Введите год: ";
			cin >> y;
			system("cls");
			if ((count > 0) && (count <= films.SizeLibrary()) && (y > 0))
			{
				tmp_films = films.ChooseByMoney(count, y);
				if (tmp_films.size() != 0)
				{
					cout << "Фильмы с наибольшими сборами в выбранном году: " << endl;
					for (int i = 0;i < tmp_films.size();i++)
					{
						cout << endl;
						tmp_films[i].PrintFilm();
					}
				}
				else
					cout << "Фильмы не найдены...";
			}
			else
				cout << "Недопустимые данные";
			break;
		case 8:
			cout << "Текущее число фильмов: " << films.SizeLibrary();
			break;
		case 9:
			cout << "Ведите номер фильма в списке, данные которого вы хотите удалить: ";
			cin >> ind;
			system("cls");
			if ((ind >= 0) && (ind <= films.SizeLibrary()))
			{
				films.DeleteFilm(ind - 1);
				cout << "Фильм удален";
			}
			else
				cout << "Неверный номер";
			break;
		case 10:
			films.SaveFile();
			cout << "Фильмотека сохранена";
			break;
		case 11:
			if (films.ReadFile())
			{
				cout << "Фильмотека считана";
				for (int i = 0;i < films.SizeLibrary();i++)
				{
					cout << endl;
					films[i].PrintFilm();
				}
			}
			else
				cout << "Ошибка при чтении файла";
			break;
		}
		cout << endl << "0 - завершить" << endl << "1 - вернуться к выбору операции" << endl;
		cin >> t;
		if (t != 1)
			break;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");
	Options();
	system("cls");
	system("pause");
	return 0;
}