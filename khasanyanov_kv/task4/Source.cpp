#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <ios>
#include <fstream>
#include "Header.h"

using namespace std;



class Song
{
	string name;
	string autor; //����� ������
	string compositor; //���������� ������
	string singer; //�����������
	string album;
	string date; // ���� ������� � ������� ��:��:��
public:
	Song() { name = ""; autor = ""; compositor = ""; singer = ""; album = ""; date = ""; }
	Song(string _name, string _autor, string _compositor, string _singer, string _album, string _date) : name(_name), autor(_autor), compositor(_compositor), singer(_singer), album(_album), date(_date) {}
	Song(string name) { this->name = name; autor = ""; compositor = ""; singer = ""; album = ""; date = "";}
	Song(const Song& other)
	{
		name = other.name;
		autor = other.autor;
		compositor = other.compositor;
		singer = other.singer;
		album = other.album;
		date = other.date;
	}
	string get_name() { return name; }
	string get_autor() { return autor; }
	string get_compositor() { return compositor; }
	string get_singer() { return singer; }
	string get_album() { return album; }
	string get_date() { return date; }
	void set_name(string s) { this->name = s; }
	void set_autor(string s) { this->autor = s; }
	void set_compositor(string s) { this->compositor = s; }
	void set_singer(string s) { this-> singer = s; }
	void set_album(string s) { this-> album = s; }
	void set_date(string s) { this-> date = s; }
	void rename(string _name, string _autor, string _compositor, string _singer, string _album, string _date)
	{
		name = _name;
		autor = _autor;
		compositor = _compositor;
		singer = _singer;
		album = _album;
		date = _date;
	}
	string get()
	{
		return name + "\t" + autor + "\t" + compositor + "\t" + singer + "\t" + album + "\t" + date;
	}

	bool operator<(const Song& a)
	{
		int min;
		if (name.size() < a.name.size())
			min = name.size();
		else
			min = a.name.size();
		for (int i = 0; i < min;i++)
		{
			if (name[i] < a.name[i])
				return true;
			else if (name[i] == a.name[i])
				continue;
			else
				return false;
		}
		return true;
	}

	bool operator>(const Song& a)
	{
		int min;
		if (name.size() < a.name.size())
			min = name.size();
		else
			min = a.name.size();
		for (int i = 0; i < min; i++)
		{
			if (name[i] > a.name[i])
				return true;
			else if (name[i] == a.name[i])
				continue;
			else
				return false;
		}
	}
	Song& operator=(const Song& a)
	{
		name = a.name;
		autor = a.autor;
		compositor = a.compositor;
		singer = a.singer;
		album = a.album;
		date = a.date;
		return *this;
	}

	bool operator==(Song& a)
	{
		if ((a.get_name() == name) && (a.get_autor() == autor) && (a.get_compositor() == compositor) && (a.get_singer() == singer) && (a.get_album() == album) && (a.get_date() == date))
			return true;
		else
			return false;
	}
}; 

void help_to_print(string param, int i)
{
	cout.setf(ios::left);
	cout << param << ":" << endl;
	if(i< 10)
		cout.width(3);
	else if(i < 100)
		cout.width(4);
	else if(i,1000)
		cout.width(5);
	else
		cout.width(6);
	cout << "�";
	cout.width(20);
	cout << "��������:";
	cout.width(20);
	cout << "�����:";
	cout.width(20);
	cout << "����������:";
	cout.width(20);
	cout << "�����������:";
	cout.width(20);
	cout << "������:";
	cout.width(10);
	cout << "����:" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}
class Songbook
{
	string name;
	vector<Song> songs;
public:
	Songbook() { name = "���������� ��������"; }
	Songbook(string _name) : name(_name) {}
	Songbook(Songbook& other) { name = other.name; songs = other.songs; }
	void add(Song song)
	{
		songs.push_back(song);
	}
	void del(int index)
	{
		songs.erase(songs.begin() + index);
	}
	void del(Song song)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if (song == songs[i])
				songs.erase(songs.begin() + i);
		}
	}
	void del(string name_or_singer)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if ((songs[i].get_name() == name_or_singer) || (songs[i].get_singer() == name_or_singer))
				songs.erase(songs.begin() + i);
		}
	}
	int size() { return songs.size(); }
	string find(string name, string compositor_or_autor_or_singer)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if ((songs[i].get_name() == name) && ((songs[i].get_compositor() == compositor_or_autor_or_singer) || (songs[i].get_autor() == compositor_or_autor_or_singer) || (songs[i].get_singer() == compositor_or_autor_or_singer)))
				return songs[i].get();
			else
				continue;
		}
	}
	void print()
	{
		this->sort();
		cout << "***********************************************************************************************************************" << endl;
		help_to_print(name, songs.size());
		for (int i = 0; i < songs.size(); i++)
		{
			cout << i + 1 << ". ";
			cout.width(20);
			cout << songs[i].get_name();
			cout.width(20);
			cout << songs[i].get_autor();
			cout.width(20);
			cout << songs[i].get_compositor();
			cout.width(20);
			cout << songs[i].get_singer();
			cout.width(20);
			cout << songs[i].get_album();
			cout.width(10);
			cout << songs[i].get_date() << endl;
		}
		cout << "***********************************************************************************************************************" << endl;
	}

	

	void print_autor(string autor)
	{

		int count = 1;
		this->sort();
		cout << "***********************************************************************************************************************" << endl;
		help_to_print(autor, songs.size());
		for (int i = 0; i < songs.size(); i++)
		{
			if(songs[i].get_autor() == autor)
			{
				cout << count << ". ";
				cout.width(20);
				cout << songs[i].get_name();
				cout.width(20);
				cout << songs[i].get_autor();
				cout.width(20);
				cout << songs[i].get_compositor();
				cout.width(20);
				cout << songs[i].get_singer();
				cout.width(20);
				cout << songs[i].get_album();
				cout.width(10);
				cout << songs[i].get_date() << endl;
				count++;
			}
		}
		cout << "***********************************************************************************************************************" << endl;
	}

	void print_compositor(string compositor)
	{
		int count = 1;
		this->sort();
		cout << "***********************************************************************************************************************" << endl;
		help_to_print(compositor, songs.size());
		for (int i = 0; i < songs.size(); i++)
		{
			if (songs[i].get_compositor() == compositor)
			{
				cout << count << ". ";
				cout.width(20);
				cout << songs[i].get_name();
				cout.width(20);
				cout << songs[i].get_autor();
				cout.width(20);
				cout << songs[i].get_compositor();
				cout.width(20);
				cout << songs[i].get_singer();
				cout.width(20);
				cout << songs[i].get_album();
				cout.width(10);
				cout << songs[i].get_date() << endl;
				count++;
			}
		}
		cout << "***********************************************************************************************************************" << endl;
	}

	void print_singer(string singer)
	{
		int count = 1;
		this->sort();
		cout << "***********************************************************************************************************************" << endl;
		help_to_print(singer, songs.size());
		for (int i = 0; i < songs.size(); i++)
		{
			if (songs[i].get_singer() == singer)
			{
				cout << count << ". ";
				cout.width(20);
				cout << songs[i].get_name();
				cout.width(20);
				cout << songs[i].get_autor();
				cout.width(20);
				cout << songs[i].get_compositor();
				cout.width(20);
				cout << songs[i].get_singer();
				cout.width(20);
				cout << songs[i].get_album();
				cout.width(10);
				cout << songs[i].get_date() << endl;
				count++;
			}
		}
		cout << "***********************************************************************************************************************" << endl;
	}

	void print_album(string album)
	{
		int count = 1;
		this->sort();
		cout << "***********************************************************************************************************************" << endl;
		help_to_print(album, songs.size());
		for (int i = 0; i < songs.size(); i++)
		{
			if (songs[i].get_album() == album)
			{
				cout << count << ". ";
				cout.width(20);
				cout << songs[i].get_name();
				cout.width(20);
				cout << songs[i].get_autor();
				cout.width(20);
				cout << songs[i].get_compositor();
				cout.width(20);
				cout << songs[i].get_singer();
				cout.width(20);
				cout << songs[i].get_album();
				cout.width(10);
				cout << songs[i].get_date() << endl;
				count++;
			}
		}
		cout << "***********************************************************************************************************************" << endl;
	}

	void sort()
	{
		int i, j;
		Song x;
		for (i = 0; i < songs.size(); i++)
		{
			for (j = songs.size() - 1; j > i; j--)
			{
				if (songs[j - 1] > songs[j])
				{
					x = songs[j - 1];
					songs[j - 1] = songs[j];
					songs[j] = x;
				}
			}
		}
	}

	void save_to(string path)
	{
		ofstream fout;
		try
		{
			fout.open(path, ofstream::app);
			if (!fout.is_open())
				throw 1;
		}
		catch (int)
		{
			cout << "������ �������� �����" << endl;
			return;
		}
		fout.setf(ios::left);
		cout << "***********************************************************************************************************************" << endl;
		fout << name << ":" << endl;
		if (songs.size() < 10)
			fout.width(3);
		else if (songs.size() < 100)
			fout.width(4);
		else if (songs.size()< 1000)
			fout.width(5);
		else
			fout.width(6);
		fout << "�";
		fout.width(20);
		fout << "��������:";
		fout.width(20);
		fout << "�����:";
		fout.width(20);
		fout << "����������:";
		fout.width(20);
		fout << "�����������:";
		fout.width(20);
		fout << "������:";
		fout.width(10);
		fout << "����:" << endl;
		fout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < songs.size(); i++)
		{
			fout << i + 1 << ". ";
			fout.width(20);
			fout << songs[i].get_name();
			fout.width(20);
			fout << songs[i].get_autor();
			fout.width(20);
			fout << songs[i].get_compositor();
			fout.width(20);
			fout << songs[i].get_singer();
			fout.width(20);
			fout << songs[i].get_album();
			fout.width(10);
			fout << songs[i].get_date() << endl;
		}
		fout << "***********************************************************************************************************************" << endl;
		fout.close();
	}


	void get_from(string path)
	{
		ifstream fin;
		char ch;
		try
		{
			fin.open(path);
			if (!fin.is_open())
				throw 1;
		}
		catch (int)
		{
			cout << "������ �������� �����" << endl;
			return;
		}
		while (fin.get(ch))
		{
			cout << ch;
		}

		fin.close();
	}

	Songbook& operator=(const Songbook& other)
	{
		songs = other.songs;
		return *this;
	}
};


void main()
{
	setlocale(LC_ALL, "ru");
	Song a("����� �������", "������� ��������", "������ �����������", "���� ������", "����� ���", "21.05.1975");
	Song b("������", "������ ����������", "������ �������", "��� �������", "������", "15.11.1968"); 
	Song c("����� � ����", "����� ��������", "����� ��������", "���� ������", "��� ����� ������", "10.09.1980");
	Song d("���� ������", "����� ��������", "����� ����������", "������ ������", "���� ������", "01.08.1979");
	Song e("������� � ��������", "�������� ��������", "�������� ��������", "�������� ��������", "-", "29.10.2000");
	Song f("������ �����", "�������� ��������", "�������� ��������", "�������� ��������", "�� ��� �������", "23.11.1972");
	Song g("��, ���� �� �����", "��������� ������", "������ ������", "����� ������", "������� �����", "14.02.2004");
	Song h("�, �����, �����", "������� ���������", "��������� ��������", "������� ��������", "������� ����", "09.10.2017");
	Song i("��� ������", "������� ��������", "������ ��������", "��� �������", "�����-��� ���������", "01.05.2005");

	
	
	Songbook test("��������");
	test.add(a);
	test.add(b);
	test.add(c);
	test.add(d);
	test.add(e);
	test.add(f);
	test.add(g);
	test.add(h);
	test.add(i);
	test.print();
	system("PAUSE");
	system("cls");
	Songbook test1("�������");
	test1 = test;
	test1.del("����� � ����");
	test1.del(e);
	test1.del(f);
	test1.del(g);
	test1.del(h);
	test1.del(i);
	test1.print();
	system("PAUSE");
	system("cls");
	test.print_singer("��� �������");
	system("PAUSE");
	system("cls");
	test.save_to("File.txt");
	test.get_from("File.txt");
	system("PAUSE");
	system("cls");
	test1.save_to("File1.txt");
	test1.get_from("File1.txt");
	system("PAUSE");
	system("cls");
	test1.get_from("sds");
	system("PAUSE");
}