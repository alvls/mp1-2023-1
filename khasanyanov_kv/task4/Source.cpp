#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <ios>
#include <fstream>

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
	Song(string name) { this->name = name; autor = ""; compositor = ""; singer = ""; album = ""; date = ""; }
	Song(const Song& other)
	{
		name = other.name;
		autor = other.autor;
		compositor = other.compositor;
		singer = other.singer;
		album = other.album;
		date = other.date;
	}
	string get_name()const { return name; }
	string get_autor()const { return autor; }
	string get_compositor() const { return compositor; }
	string get_singer()const { return singer; }
	string get_album()const { return album; }
	string get_date() const { return date; }
	void set_name(string s) { this->name = s; }
	void set_autor(string s) { this->autor = s; }
	void set_compositor(string s) { this->compositor = s; }
	void set_singer(string s) { this->singer = s; }
	void set_album(string s) { this->album = s; }
	void set_date(string s) { this->date = s; }
	void rename(string _name, string _autor, string _compositor, string _singer, string _album, string _date)
	{
		name = _name;
		autor = _autor;
		compositor = _compositor;
		singer = _singer;
		album = _album;
		date = _date;
	}

	bool operator<(const Song& a)
	{
		int min;
		if (name.size() < a.name.size())
			min = name.size();
		else
			min = a.name.size();
		for (int i = 0; i < min; i++)
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
	friend ostream& operator<<(ostream& os, const Song& song)
	{
		os << song.name << "\t" << song.autor << "\t" << song.compositor << "\t" << song.singer << "\t" << song.album << "\t" << song.date << endl;
		return os;
	}
};

class Songbook
{
	string name;
	vector<Song> songs;
public:
	Songbook() { name = "���������� ��������"; }
	Songbook(string _name) : name(_name) {}
	Songbook(Songbook& other) { name = other.name; songs = other.songs; }
	string get_name() { return name; }
	vector<Song> get_songs() { return songs; }
	void add(Song song)
	{
		songs.push_back(song);
		sort(songs);
	}
	void del(int index)
	{
		songs.erase(songs.begin() + index);
		sort(songs);
	}
	void del(Song song)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if (song == songs[i])
				songs.erase(songs.begin() + i);
		}
		sort(songs);
	}
	void del(string name_or_singer)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if ((songs[i].get_name() == name_or_singer) || (songs[i].get_singer() == name_or_singer))
				songs.erase(songs.begin() + i);
		}
		sort(songs);
	}
	int size() { return songs.size(); }
	void rename(Song a, string _name, string _autor, string _compositor, string _singer, string _album, string _date)
	{
		a.rename(_name, _autor, _compositor, _singer, _album, _date);
		sort(songs);
	}
	Song& find(string name, string compositor_or_autor_or_singer)
	{
		for (int i = 0; i < songs.size(); i++)
		{
			if ((songs[i].get_name() == name) && ((songs[i].get_compositor() == compositor_or_autor_or_singer) || (songs[i].get_autor() == compositor_or_autor_or_singer) || (songs[i].get_singer() == compositor_or_autor_or_singer)))
				return songs[i];
		}
		throw exception("����� �� �������");
	}
	void sort(vector<Song> vec)
	{
		int i, j;
		Song x;
		for (i = 0; i < vec.size(); i++)
		{
			for (j = vec.size() - 1; j > i; j--)
			{
				if (vec[j - 1] > vec[j])
				{
					x = vec[j - 1];
					vec[j - 1] = vec[j];
					vec[j] = x;
				}
			}
		}
	}

	Songbook autor_songs(string autor)
	{
		Songbook result(autor);
		for (Song& song : songs)
		{
			if (song.get_autor() == autor)
				result.add(song);
		}
		sort(result.get_songs());
		return result;
	}

	Songbook compositor_songs(string compositor)
	{
		Songbook result(compositor);
		for (Song& song : songs)
		{
			if (song.get_compositor() == compositor)
				result.add(song);
		}
		sort(result.get_songs());
		return result;
	}

	Songbook singer_songs(string singer)
	{
		Songbook result(singer);
		for (Song& song : songs)
		{
			if (song.get_singer() == singer)
				result.add(song);
		}
		sort(result.get_songs());
		return result;
	}

	Songbook album_songs(string album)
	{
		Songbook result(album);
		for (Song& song : songs)
		{
			if (song.get_album() == album)
				result.add(song);
		}
		sort(result.get_songs());
		return result;
	}

	friend ostream& operator<<(ostream& out, const Songbook& sb)
	{
		out.setf(ios::left);
		out << "***********************************************************************************************************************" << endl;
		out << sb.name << ":" << endl;
		if (sb.songs.size() < 10)
			out.width(3);
		else if (sb.songs.size() < 100)
			out.width(4);
		else if (sb.songs.size() < 1000)
			out.width(5);
		else
			out.width(6);
		out << "�";
		out.width(20);
		out << "��������:";
		out.width(20);
		out << "�����:";
		out.width(20);
		out << "����������:";
		out.width(20);
		out << "�����������:";
		out.width(20);
		out << "������:";
		out.width(10);
		out << "����:" << endl;
		out << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < sb.songs.size(); i++)
		{
			out << i + 1 << ". ";
			out.width(20);
			out << sb.songs[i].get_name();
			out.width(20);
			out << sb.songs[i].get_autor();
			out.width(20);
			out << sb.songs[i].get_compositor();
			out.width(20);
			out << sb.songs[i].get_singer();
			out.width(20);
			out << sb.songs[i].get_album();
			out.width(10);
			out << sb.songs[i].get_date() << endl;
		}
		out << "***********************************************************************************************************************" << endl;

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Songbook& sb)
	{
		out.setf(ios::left);
		out << "***********************************************************************************************************************" << endl;
		out << sb.name << ":" << endl;
		if (sb.songs.size() < 10)
			out.width(3);
		else if (sb.songs.size() < 100)
			out.width(4);
		else if (sb.songs.size() < 1000)
			out.width(5);
		else
			out.width(6);
		out << "�"; out.width(20);
		out << "��������:"; out.width(20);
		out << "�����:"; out.width(20);
		out << "����������:"; out.width(20);
		out << "�����������:"; out.width(20);
		out << "������:"; out.width(10);
		out << "����:" << endl;
		out << "-----------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < sb.songs.size(); i++)
		{
			out << i + 1 << ". ";
			out.width(20);
			out << sb.songs[i].get_name();
			out.width(20);
			out << sb.songs[i].get_autor();
			out.width(20);
			out << sb.songs[i].get_compositor();
			out.width(20);
			out << sb.songs[i].get_singer();
			out.width(20);
			out << sb.songs[i].get_album();
			out.width(10);
			out << sb.songs[i].get_date() << endl;
		}
		out << "***********************************************************************************************************************" << endl;

		return out;
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
		fout << *this;
		fout.close();
	}

	friend ifstream& operator >>(ifstream& in, const Songbook& sb)
	{
		char ch;
		while (in.get(ch))
		{
			cout << ch;
		}

		return in;
	}

	void load(string path)
	{
		ifstream fin(path);
		if (!fin.is_open())
		{
			cout << "������ �������� �����" << endl;
			return;
		}
		Songbook sb;
		fin >> sb;
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
	cout << test.autor_songs("������� ��������");
	system("PAUSE");
	system("cls");
	cout << test;
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
	cout << test1;
	system("PAUSE");
	system("cls");
	cout << test.singer_songs("��� �������");
	system("PAUSE");
	system("cls");
	test.save_to("File.txt");
	test.load("File.txt");
	system("PAUSE");
	system("cls");
	test1.save_to("File1.txt");
	test1.load("File1.txt");
	system("PAUSE");
	system("cls");
	test1.load("sds");
	system("PAUSE");
}