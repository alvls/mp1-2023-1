#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <locale>

using namespace std;

class Song
{
	string SongName;
	string Lyricist;
	string Composer;
	string Performer;
	string Album;
	int day;
	int month;
	int year;

public:

	Song() : SongName("-"), Lyricist("-"), Composer("-"), Performer("-"), Album("-"), day(0), month(0), year(0) {}

	Song(string _SongName, string _Lyricist, string _Composer, string _Performer, string _Album, int _day, int _month, int _year)
		: SongName(_SongName), Lyricist(_Lyricist), Composer(_Composer), Performer(_Performer), Album(_Album), day(_day), month(_month), year(_year) {}

	Song(string _SongName)
		: SongName(_SongName), Lyricist("-"), Composer("-"), Performer("-"), Album("-"), day(0), month(0), year(0) {}

	Song& operator=(const const Song& s)
	{
		if (this == &s)
			return *this;

		SongName = s.SongName;
		Lyricist = s.Lyricist;
		Composer = s.Composer;
		Performer = s.Performer;
		Album = s.Album;
		day = s.day;
		month = s.month;
		year = s.year;
		return *this;
	}

	bool operator>(const Song& s)
	{
		if (SongName > s.SongName)
			return true;

		else if (SongName < s.SongName)
			return false;

		else if (year > s.year)
			return true;

		return false;
	}

	bool operator<(const Song& s)
	{
		if (SongName < s.SongName)
			return true;

		else if (SongName > s.SongName)
			return false;

		else if (year < s.year)
			return true;

		return false;
	}

	bool operator==(const Song& s)
	{
		if ((SongName == s.SongName) && (Lyricist == s.Lyricist) && (Composer == s.Composer) && (Performer == s.Performer) &&
			(Album == s.Album) && (day == s.day) && (month == s.month) && (year == s.year))
			return true;
		return false;
	}

	void RenameSong(string _SongName, string _Lyricist, string _Composer, string _Performer, string _Album, int _day, int _month, int _year)
	{
		SongName = _SongName;
		Lyricist = _Lyricist;
		Composer = _Composer;
		Performer = _Performer;
		Album = _Album;
		day = _day;
		month = _month;
		year = _year;
	}

	string GetSongName() const
	{
		return SongName;
	}

	string GetLyricist() const
	{
		return Lyricist;
	}

	string GetComposer() const
	{
		return Composer;
	}

	string GetPerformer() const
	{
		return Performer;
	}

	string GetAlbum() const
	{
		return Album;
	}

	int GetDay()
	{
		return day;
	}

	int GetMonth()
	{
		return month;
	}

	int GetYear()
	{
		return year;
	}

	void SetSongName(string _SongName)
	{
		SongName = _SongName;
	}

	void SetLyricist(string _Lyricist)
	{
		Lyricist = _Lyricist;
	}

	void SetComposer(string _Composer)
	{
		Composer = _Composer;
	}

	void SetPerformer(string _Performer)
	{
		Performer = _Performer;
	}

	void SetAlbum(string _Album)
	{
		Album = _Album;
	}

	void SetDay(int _day)
	{
		month = _day;
	}

	void SetMonth(int _month)
	{
		month = _month;
	}

	void SetYear(int _year)
	{
		year = _year;
	}

	friend ostream& operator<<(ostream& os, const Song& a)
	{
		os << "��������: " << a.SongName << endl;
		os << "����� ������: " << a.Lyricist << endl;
		os << "����������: " << a.Composer << endl;
		os << "�����������: " << a.Performer << endl;
		os << "�������� �������: " << a.Album << endl;
		if ((a.day == 0) && (a.month == 0))
			os << "���� �������: " << a.year << endl;
		else
			os << "���� �������: " << a.day << "." << a.month << "." << a.year << endl;
		return os;
	}


};


class Songbook
{
	string name;
	vector<Song> songs;

public:
	Songbook() : name("����� �������") {}
	Songbook(string _name) : name(_name) {}
	Songbook(Songbook& other)
	{
		name = other.name;
		songs = other.songs;
	}

	string GetName()
	{
		return name;
	}

	vector<Song> GetSongs()
	{
		return songs;
	}

	void Sorting()
	{
		Song x;
		for (int i = 0; i < songs.size(); i++)
		{
			for (int j = 0; j < songs.size() - 1; j++)
			{
				if (songs[j] > songs[j + 1])
				{
					x = songs[j + 1];
					songs[j + 1] = songs[j];
					songs[j] = x;
				}
			}
		}
	}

	void Add(Song s)
	{
		songs.push_back(s);
		Sorting();
	}

	void Rename(int index, string _SongName, string _Lyricist, string _Composer, string _Performer, string _Album, int _day, int _month, int _year)
	{
		songs[index].RenameSong(_SongName, _Lyricist, _Composer, _Performer, _Album, _day, _month, _year);
		Sorting();
	}

	Song& Search(string _SongName, string _Performer)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if ((songs[i].GetSongName() == _SongName) && ((songs[i].GetPerformer() == _Performer)))
				return songs[i];
		}
		throw exception("������ ���������� �� �������");
	}

	Songbook Lyricist_Songs(string _Lyricist)
	{
		Songbook result(_Lyricist);
		for (Song& song : songs)
		{
			if (song.GetLyricist() == _Lyricist)
				result.Add(song);
		}
		Sorting();
		return result;
	}

	Songbook Composer_Songs(string _Composer)
	{
		Songbook result(_Composer);
		for (Song& song : songs)
		{
			if (song.GetComposer() == _Composer)
				result.Add(song);
		}
		Sorting();
		return result;
	}

	Songbook Performer_Songs(string _Performer)
	{
		Songbook result(_Performer);
		for (Song& song : songs)
		{
			if (song.GetPerformer() == _Performer)
				result.Add(song);
		}
		Sorting();
		return result;
	}

	int GetSize()
	{
		return songs.size();
	}

	void Del(int index)
	{
		songs.erase(songs.begin() + index);
		Sorting();
	}

	void Del(Song s)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if (s == songs[i])
				songs.erase(songs.begin() + i);
		}
		Sorting();
	}

	bool FindSame(Song f)
	{
		for (int i = 0; i < songs.size(); i++)

			if (f == songs[i])
				return true;

		return false;
	}

	void ReadFile(string path)
	{
		ifstream sfile(path);
		if (!sfile.is_open())
		{
			throw exception("������ �������� �����");
			return;
		}
		Songbook a;
		sfile >> a;
		sfile.close();
	}

	void SaveFile(string path)
	{
		ofstream sfile(path);
		if (!sfile.is_open())
		{
			throw exception("������ �������� �����");
			return;
		}
		sfile << *this;
		sfile.close();
	}



	friend ostream& operator<<(ostream& os, const Songbook& a)
	{
		os << "�������� ���������: " << a.name << endl;
		for (int i = 0; i < a.songs.size(); i++)
		{
			os << "-----------------------------------------------" << endl;
			os << a.songs[i];

		}
		return os;
	}

	friend ofstream& operator<<(ofstream& os, const Songbook& a)
	{
		os << "�������� ���������: " << a.name << endl;
		for (int i = 0; i < a.songs.size(); i++)
		{
			os << "-----------------------------------------------" << endl;
			os << a.songs[i];

		}
		return os;
	}

	friend ifstream& operator>>(ifstream& in, const Songbook& a)
	{
		char ch;
		while (in.get(ch))
		{
			cout << ch;
		}

		return in;
	}

};




int main()
{
	setlocale(LC_ALL, "Russian");

	Songbook s("��� ��������");

	Song s1("25 � 10", "�.�����������", "�.�����������", "��������", "��������", 0, 0, 1982);
	Song s2("��������� ����", "�.���", "�.���, �.��������", "����", "������ �����", 0, 0, 1988);
	Song s3("������", "�.�������", "-", "�������", "������ ����", 14, 4, 2017);
	Song s4("������������", "�.��������", "-", "����� ����(!)", "��������-����", 2, 10, 2020);
	Song s5("����", "�.��������", "-", "����� ����(!)", "��.���.1", 24, 4, 2017);
	Song s6("�������� ����");
	
	s.Add(s1);
	s.Add(s2);
	s.Add(s3);
	s.Add(s4);
	s.Add(s5);
	s.Add(s6);

	cout << s1;
	system("PAUSE");

	system("cls");
	s.Rename(2, "�������� ����", "�.���", "-", "����", "׸���� ������", 0, 0, 1991);
	cout << s;
	system("PAUSE");

	system("cls");
	cout << "���������� ����� � ���������: " << s.GetSize() << endl;
	system("pause");
	s.Del(2);
	cout << "���������� ����� � ��������� ����� ��������: " << s.GetSize() << endl;
	system("pause");

	system("cls");
	cout << "����� �� �������� � �����������:" << endl;
	cout << (s.Search("������", "�������"));
	system("pause");

	system("cls");
	cout << "����� �� �����������:" << endl;
	cout << (s.Performer_Songs("����� ����(!)"));
	system("pause");
	
	system("cls");
	cout << "������ ��������� � ���� (�������� File.txt � ����� �������)" << endl;
	s.SaveFile("File.txt");

	cout << "������ ����������� ��������� (�� File.txt)" << endl;
	s.ReadFile("File.txt");
	system("PAUSE");
}
