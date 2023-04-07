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
		cout << "�������� ������: " << FilmName << endl;
		cout << "�����c��: " << DirName << " " << DirSurname << endl;
		cout << "���������: " << ScrName << " " << ScrSurname << endl;
		cout << "����������: " << ComName << " " << ComSurname << endl;
		cout << "���� ������: " << day << "." << month << "." << year << endl;
		cout << "�����: " << money << " ���." << endl;
	}
};
class FilmLibrary
{
	vector <Film> library;
public:
	FilmLibrary() {}
	int SizeLibrary() { return library.size(); }//������ ����� �������
	void DeleteFilm(int index) { library.erase(library.begin() + index); }//�������� ������
	void SortByNameAndYear()//���������� �� ����� ��� ����
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
	void SortByMoney()//���������� �� ������
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
	bool AddFilm(const Film& f)//���������� ������
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
		int _day, int _month, int _year, int _money)//��������� ������ ������
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
	int FindByYearAndName(int y, string n)//����� ������ �� �������� � ����
	{
		Film tmp;
		for (int i = 0;i < library.size();i++)
		{
			if ((library[i].GetYear() == y) && (library[i].GetFilmName() == n))
				return i;
		}
		return -1;
	}
	vector <Film> ChooseByDirector(string DirectorSur)//����� ������� �� ���������
	{
		vector <Film> DirFilms;
		for (int i = 0;i < library.size();i++)
			if (library[i].GetDirSurname() == DirectorSur)
				DirFilms.push_back(library[i]);
		return DirFilms;
	}
	vector <Film> ChooseByYear(int year)//����� ������� �� ����
	{
		vector <Film> YearFilms;
		for (int i = 0;i < library.size();i++)
			if (library[i].GetYear() == year)
				YearFilms.push_back(library[i]);
		return YearFilms;
	}
	vector <Film> ChooseByMoney(int count, int year)//�������� ����� ������� � ����������� ������� (� � ������� ����)
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
	bool ReadFile()//�� ������� ����� "Films.txt"
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
	void SaveFile()//�� ������� ����� "Films.txt"
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
		cout << "1) �������� �����" << endl << "2) �������� ������ ���������� ������" << endl << "3) ����� ����� �� �������� � ����" << endl << "4) ������ ��� ������ ��������� ���������" << endl
			<< "5) ������ ��� ������, �������� � ������ � ��������� ����" << endl << "6) ������ �������� ����� ������� � ����������� �������" << endl << "7) ������ �������� ����� ������� � ����������� ������� � ��������� ����" << endl
			<< "8) ������ ������� ����� �������" << endl << "9) ������� �����" << endl << "10) ��������� ���������� � ����" << endl << "11) ������� ���������� �� �����" << endl;
		cin >> operation;
		system("cls");
		switch (operation)
		{
		case 1:
			cout << "������� �������� ������ (�������� / � ����� ��������): ";
			getline(cin, FName, '/');
			cout << "������� ��� � ������� ��������� (����� ������): " << endl;
			cin >> DName;
			cin >> DSurname;
			cout << "������� ��� � ������� ���������� (����� ������): " << endl;
			cin >> SName;
			cin >> SSurname;
			cout << "������� ��� � ������� ����������� (����� ������): " << endl;
			cin >> CName;
			cin >> CSurname;
			cout << "������� ����, ����� � ��� ������ (����� ������): " << endl;
			cin >> d;
			cin >> m;
			cin >> y;
			cout << "������� ����� ������: " << endl;
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
				cout << "����� ��������" << endl;
			}
			else
				cout << "����� ����� ��� ����������" << endl;
			break;
		case 2:
			cout << "������ ����� ������ � ������, ������ �������� �� ������ ��������: ";
			cin >> ind;
			cout << "������� �������� ������ (�������� / � ����� ��������): ";
			getline(cin, FName, '/');
			cout << "������� ��� � ������� ��������� (����� ������): ";
			cin >> DName;
			cin >> DSurname;
			cout << "������� ��� � ������� ���������� (����� ������): ";
			cin >> SName;
			cin >> SSurname;
			cout << "������� ��� � ������� �����������(����� ������): ";
			cin >> CName;
			cin >> CSurname;
			cout << "������� ����, ����� � ��� ������ (����� ������): ";
			cin >> d;
			cin >> m;
			cin >> y;
			cout << "������� ����� ������: ";
			cin >> money;
			system("cls");
			if ((ind >= 0) && (ind <= films.SizeLibrary()))
			{
				films.EditFilm(ind - 1, FName, DName, DSurname, SName, SSurname, CName, CSurname, d, m, y, money);
				cout << "����� �������";
			}
			else
				cout << "�������� �����" << endl;
			break;
		case 3:
			cout << "������� ��� ������ ������: ";
			cin >> y;
			cout << "������� �������� ������ (�������� / � ����� ��������): ";
			getline(cin, FName, '/');
			system("cls");
			ind = films.FindByYearAndName(y, FName);
			if (ind != -1)
			{
				cout << "��������� ������:" << endl;
				films[ind].PrintFilm();
			}
			else
				cout << "�� ������ ������� ������ �� �������" << endl;
			break;
		case 4:
			cout << "������� ������� ���������: ";
			cin >> DSurname;
			tmp_films = films.ChooseByDirector(DSurname);
			system("cls");
			if (tmp_films.size() != 0)
			{
				cout << "������ ���������� ���������: " << endl;
				for (int i = 0;i < tmp_films.size();i++)
				{
					cout << endl;
					tmp_films[i].PrintFilm();
				}
			}
			else
				cout << "������ �� �������...";
			break;
		case 5:
			cout << "������� ���: ";
			cin >> y;
			system("cls");
			tmp_films = films.ChooseByYear(y);
			if (tmp_films.size() != 0)
			{
				cout << "������ ���������� ����: " << endl;
				for (int i = 0;i < tmp_films.size();i++)
				{
					cout << endl;
					tmp_films[i].PrintFilm();
				}
			}
			else
				cout << "������ �� �������...";
			break;
		case 6:
			cout << "������� ���������� ������� ��� �������: ";
			cin >> count;
			system("cls");
			if ((count > 0) && (count <= films.SizeLibrary()))
			{
				films.SortByMoney();
				tmp_films = films.ChooseByMoney(count, 0);
				if (tmp_films.size() != 0)
				{
					cout << "������ � ����������� �������: " << endl;
					for (int i = 0;i < tmp_films.size();i++)
					{
						cout << endl;
						tmp_films[i].PrintFilm();
					}
				}
				else
					cout << "������ �� �������...";
				films.SortByNameAndYear();
			}
			else
				cout << "������������ ���������� �������";
			break;
		case 7:
			cout << "������� ���������� ������� ��� �������: ";
			cin >> count;
			cout << "������� ���: ";
			cin >> y;
			system("cls");
			if ((count > 0) && (count <= films.SizeLibrary()) && (y > 0))
			{
				tmp_films = films.ChooseByMoney(count, y);
				if (tmp_films.size() != 0)
				{
					cout << "������ � ����������� ������� � ��������� ����: " << endl;
					for (int i = 0;i < tmp_films.size();i++)
					{
						cout << endl;
						tmp_films[i].PrintFilm();
					}
				}
				else
					cout << "������ �� �������...";
			}
			else
				cout << "������������ ������";
			break;
		case 8:
			cout << "������� ����� �������: " << films.SizeLibrary();
			break;
		case 9:
			cout << "������ ����� ������ � ������, ������ �������� �� ������ �������: ";
			cin >> ind;
			system("cls");
			if ((ind >= 0) && (ind <= films.SizeLibrary()))
			{
				films.DeleteFilm(ind - 1);
				cout << "����� ������";
			}
			else
				cout << "�������� �����";
			break;
		case 10:
			films.SaveFile();
			cout << "���������� ���������";
			break;
		case 11:
			if (films.ReadFile())
			{
				cout << "���������� �������";
				for (int i = 0;i < films.SizeLibrary();i++)
				{
					cout << endl;
					films[i].PrintFilm();
				}
			}
			else
				cout << "������ ��� ������ �����";
			break;
		}
		cout << endl << "0 - ���������" << endl << "1 - ��������� � ������ ��������" << endl;
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