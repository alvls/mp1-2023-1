#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'


struct date
{
	int day = 0;
	int month = 0;
	int year = 0;
};

int choice_in_menu(vector <string> list_for_choice)
{
	int selected = 1;
	char c;

	do
	{
		std::cout << list_for_choice[0] << endl;
		for (int i = 1; i < list_for_choice.size(); i++)
		{
			if (i == selected)
				std::cout << " > ";
			else std::cout << "   ";
			std::cout << i << ". " << list_for_choice[i] << endl;
		}
		switch ((c = _getch()))
		{
		case KEY_UP:
			if (selected > 1)
				selected--;
			break;
		case KEY_DOWN:
			if (selected < list_for_choice.size() - 1)
				selected++;
			break;
		default: break;
		}
		system("cls");
	} while (c != KEY_ENTER);
	return(selected);
}

void input_new_date(date &desired_date)
{
	cout << "Введите год (4 цифры): ";
	cin >> desired_date.year;
	system("cls");
	cout << "Введите номер месяца: ";
	cin >> desired_date.month;
	while ((desired_date.month < 1) || (desired_date.month > 12))
	{
		system("cls");
		cout << "Номер месяца введен некорректно" << endl;
		cout << "Пожалуйста, введите номер месяца заново: ";
		cin >> desired_date.month;
	}
	system("cls");
	cout << "Введите день: ";
	cin >> desired_date.day;
	while ((desired_date.day < 1) ||
		(((desired_date.month < 8) && (desired_date.month % 2 == 1) || (desired_date.month > 7) && (desired_date.month % 2 == 0)) && (desired_date.day > 31)) ||
		(((desired_date.month < 8) && (desired_date.month % 2 == 0) || (desired_date.month > 7) && (desired_date.month % 2 == 1)) && (desired_date.day > 30)) ||
		((desired_date.month == 2) && ((desired_date.year % 4 != 0) && (desired_date.day > 28) || (desired_date.year % 4 == 0) && (desired_date.day > 29))))
	{
		system("cls");
		cout << "День введен некорректно" << endl;
		cout << "Пожалуйста, введите день заново: ";
		cin >> desired_date.day;
	}
	system("cls");
}

class Scales
{
	struct notice
	{
		date date_of_notice;
		float weight = 0.0;
	};

	struct family_member
	{
		string name;
		date date_of_begining;
		short index_of_begining = 0;
		vector <notice> journal_of_notices;
	};

	string path;
	family_member new_family_member;
	notice new_notice;
	vector <family_member> family;

public:

	Scales() = default;
	Scales(const Scales& s) = default;

	void insert_of_notice(int member, int i)
	{
		family[member].journal_of_notices.push_back(family[member].journal_of_notices[family[member].journal_of_notices.size()-1]);
		for (int j = family[member].journal_of_notices.size() - 3; j >= i; j--)
		{
			family[member].journal_of_notices[j + 1] = family[member].journal_of_notices[j];
		}
		family[member].journal_of_notices[i] = new_notice;
	}

	void input_of_begining(int member, date date_of_begining)
	{
		if ((family[member].date_of_begining.year > date_of_begining.year) || (family[member].date_of_begining.year == date_of_begining.year) && 
			(family[member].date_of_begining.month > date_of_begining.month) || (family[member].date_of_begining.year == date_of_begining.year) &&
			(family[member].date_of_begining.month == date_of_begining.month) && (family[member].date_of_begining.day > date_of_begining.day))
			throw(5);
		else
		{
			family[member].date_of_begining = date_of_begining;
			if (family[member].journal_of_notices.size() == 0)
				family[member].index_of_begining = 0;
			else
				while ((family[member].index_of_begining < family[member].journal_of_notices.size()) &&
					(family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.year < date_of_begining.year) ||
					((family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.year == date_of_begining.year) &&
						(family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.month < date_of_begining.month)) ||
					((family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.year == date_of_begining.year) &&
						(family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.month < date_of_begining.month) &&
						(family[member].journal_of_notices[family[member].index_of_begining].date_of_notice.day < date_of_begining.day)))
					family[member].index_of_begining++;
		}
	}

	date output_of_begining(int member)
	{
		if (family[member].date_of_begining.day != 0)
			return(family[member].date_of_begining);
		else if (family[member].journal_of_notices.size() != 0)
			return(family[member].journal_of_notices[0].date_of_notice);
		else
			throw (1);

	}

	void input_of_notice(int member, date new_date, float weight)
	{
		int i;

		if (((family[member].date_of_begining.year > new_date.year) || (family[member].date_of_begining.year == new_date.year) &&
			(family[member].date_of_begining.month > new_date.month) || (family[member].date_of_begining.year == new_date.year) &&
			(family[member].date_of_begining.month == new_date.month) && (family[member].date_of_begining.day > new_date.day)) &&
			(family[member].journal_of_notices.size() != 0))
			throw(5);
		else
		{
			new_notice.date_of_notice = new_date;
			new_notice.weight = weight;
			if (family[member].journal_of_notices.size() == 0)
				family[member].journal_of_notices.push_back(new_notice);
			else
			{
				i = family[member].journal_of_notices.size() - 1;
				while ((i >= family[member].index_of_begining) && (new_notice.date_of_notice.year < family[member].journal_of_notices[i].date_of_notice.year))
					i--;
				while ((i >= family[member].index_of_begining) && (new_notice.date_of_notice.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_notice.date_of_notice.month < family[member].journal_of_notices[i].date_of_notice.month))
					i--;
				while ((i >= family[member].index_of_begining) && (new_notice.date_of_notice.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_notice.date_of_notice.month == family[member].journal_of_notices[i].date_of_notice.month) &&
					(new_notice.date_of_notice.day < family[member].journal_of_notices[i].date_of_notice.day))
					i--;


				if (i < family[member].index_of_begining)
					insert_of_notice(member, i + 1);
				else if ((new_notice.date_of_notice.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_notice.date_of_notice.month == family[member].journal_of_notices[i].date_of_notice.month) &&
					(new_notice.date_of_notice.day == family[member].journal_of_notices[i].date_of_notice.day))
					family[member].journal_of_notices[i] = new_notice;
				else if (i == family[member].journal_of_notices.size() - 1)
					family[member].journal_of_notices.push_back(new_notice);
				else
					insert_of_notice(member, i + 1);
			}
		}
	}

	float output_of_weight(int member, date new_date)
	{
		int i;

		if (family[member].journal_of_notices.size() == 0)
			throw(6);
		else
		{
			if ((family[member].journal_of_notices.size() > 0) && (family[member].date_of_begining.day == 0))
				family[member].date_of_begining = family[member].journal_of_notices[0].date_of_notice;
			if ((family[member].date_of_begining.year > new_date.year) || (family[member].date_of_begining.year == new_date.year) &&
				(family[member].date_of_begining.month > new_date.month) || (family[member].date_of_begining.year == new_date.year) &&
				(family[member].date_of_begining.month == new_date.month) && (family[member].date_of_begining.day > new_date.day))
				throw(5);
			else
			{
				i = family[member].journal_of_notices.size() - 1;
				while ((i >= family[member].index_of_begining) && (new_date.year < family[member].journal_of_notices[i].date_of_notice.year))
					i--;
				while ((i >= family[member].index_of_begining) && (new_date.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_date.month < family[member].journal_of_notices[i].date_of_notice.month))
					i--;
				while ((i >= family[member].index_of_begining) && (new_date.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_date.month == family[member].journal_of_notices[i].date_of_notice.month) &&
					(new_date.day < family[member].journal_of_notices[i].date_of_notice.day))
					i--;
				if ((new_date.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(new_date.month == family[member].journal_of_notices[i].date_of_notice.month) &&
					(new_date.day == family[member].journal_of_notices[i].date_of_notice.day))
					return (family[member].journal_of_notices[i].weight);
				else
					throw(2);
			}
		}
	}

	float output_of_average_value(int member, date period)
	{
		int i = 0;
		int counter = 0;
		double desired_value = 0.0;
		date date_of_begining;

		if (family[member].journal_of_notices.size() == 0)
			throw (6);
		else
		{
			date_of_begining = output_of_begining(member);
			if (period.month == 0)
				for (; counter < family[member].journal_of_notices.size(); counter++)
					desired_value += family[member].journal_of_notices[counter].weight;

			else if ((date_of_begining.year > period.year) || (date_of_begining.year == period.year) && (date_of_begining.month > period.month))
				throw(5);
			else
			{
				while ((i < family[member].journal_of_notices.size()) && (period.year > family[member].journal_of_notices[i].date_of_notice.year))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month > family[member].journal_of_notices[i].date_of_notice.month))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month == family[member].journal_of_notices[i].date_of_notice.month))
				{
					desired_value += family[member].journal_of_notices[i].weight;
					counter++;
					i++;
				}
			}
			if (desired_value == 0)
				throw(3);
			else
				return(desired_value / counter);
		}
	}

	double output_of_max(int member, date& period)
	{
		int i = 0;
		notice max;
		date date_of_begining;
		
		if (family[member].journal_of_notices.size() == 0)
			throw (6);
		else
		{
			date_of_begining = output_of_begining(member);
			if (period.month == 0)
				for (; i < family[member].journal_of_notices.size(); i++)
				{
					if (max.weight <= family[member].journal_of_notices[i].weight)
						max = family[member].journal_of_notices[i];
				}

			else if ((date_of_begining.year > period.year) || (date_of_begining.year == period.year) && (date_of_begining.month > period.month))
				throw(5);
			else
			{
				while ((i < family[member].journal_of_notices.size()) && (period.year > family[member].journal_of_notices[i].date_of_notice.year))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month > family[member].journal_of_notices[i].date_of_notice.month))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month == family[member].journal_of_notices[i].date_of_notice.month))
				{
					if (max.weight <= family[member].journal_of_notices[i].weight)
						max = family[member].journal_of_notices[i];
					i++;
				}
			}
			if (max.weight == 0)
				throw(3);
			else
			{
				period = max.date_of_notice;
				return(max.weight);
			}
		}
	}

	double output_of_min(int member, date& period)
	{
		int i = 0;
		notice min;
		min.weight = 10000;
		date date_of_begining;

		if (family[member].journal_of_notices.size() == 0)
			throw (6);
		else
		{
			date_of_begining = output_of_begining(member);
			if (period.month == 0)
				for (; i < family[member].journal_of_notices.size(); i++)
				{
					if (min.weight >= family[member].journal_of_notices[i].weight)
						min = family[member].journal_of_notices[i];
				}

			else if ((date_of_begining.year > period.year) || (date_of_begining.year == period.year) && (date_of_begining.month > period.month))
				throw(5);
			else
			{
				while ((i < family[member].journal_of_notices.size()) && (period.year > family[member].journal_of_notices[i].date_of_notice.year))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month > family[member].journal_of_notices[i].date_of_notice.month))
					i++;
				while ((i < family[member].journal_of_notices.size()) && (period.year == family[member].journal_of_notices[i].date_of_notice.year) &&
					(period.month == family[member].journal_of_notices[i].date_of_notice.month))
				{
					if (min.weight >= family[member].journal_of_notices[i].weight)
						min = family[member].journal_of_notices[i];
					i++;
				}
			}
			if (min.weight == 10000)
				throw(3);
			else
			{
				period = min.date_of_notice;
				return(min.weight);
			}
		}
	}

	void read_of_file(string path, vector <string>& v1, vector <string>& v2)
	{
		this->path = path;
		ifstream list_in(path);
		string line;
		string member = "";
		string new_weight_s;
		date new_date;
		double new_weight = 0.0;
		int i;

		if (list_in.is_open())
		{
			while (!list_in.eof())
			{
				getline(list_in, line);
				i = 0;
				member = "";
				new_date = { 0,0,0 };
				new_weight_s = "";
				while (line[i] == ' ')
					i++;
				while (line[i] != ' ')
				{
					member += line[i];
					i++;
				}
				member += '\0';
				while (line[i] == ' ')
					i++;
				while (line[i] != '.')
				{
					new_date.day = new_date.day * 10 + (line[i] - '0');
					i++;
				}
				while (line[i] == '.')
					i++;
				while (line[i] != '.')
				{
					new_date.month = new_date.month * 10 + (line[i] - '0');
					i++;
				}
				while (line[i] == '.')
					i++;
				while (line[i] != ' ')
				{
					new_date.year = new_date.year * 10 + (line[i] - '0');
					i++;
				}
				while (line[i] == ' ')
					i++;
				while (line[i] != '\0')
				{
					new_weight_s += line[i];
					i++;
				}
				new_weight = stof(new_weight_s);
				i = 0;
				while ((i < family.size()) && (family[i].name != member))
					i++;
				if (i == family.size())
					input_new_member_of_family(member, v1, v2);
				input_of_notice(i, new_date, new_weight);
			}
			list_in.close();
		}
		else
			throw (4);
	}

	void rewrite_of_file(string path)
	{
		if (path=="")
			path = this->path;
		ofstream list_out(path);
		if (!list_out.is_open())
			throw(4);
		for (int member = 0; member < family.size(); member++)
		{
			for (int i = family[member].index_of_begining; i < family[member].journal_of_notices.size(); i++)
			{
				list_out << family[member].name << ' ' << family[member].journal_of_notices[i].date_of_notice.day << '.' << 
					family[member].journal_of_notices[i].date_of_notice.month << '.' << family[member].journal_of_notices[i].date_of_notice.year << 
					' ' << setprecision(5) << family[member].journal_of_notices[i].weight << endl;
			}
		}
		list_out.close();
	}

	void input_new_member_of_family(string name_of_new_member, vector <string>& v1, vector <string>& v2)
	{
		new_family_member.name = name_of_new_member;
		family.push_back(new_family_member);
		v1.insert(v1.begin() + v1.size() - 1, name_of_new_member);
		v2.insert(v2.begin() + v2.size() - 2, name_of_new_member);
	}

	~Scales()
	{
		for (int i = 0; i < family.size(); i++)
		{
			family[i].journal_of_notices.clear();
			family[i].journal_of_notices.shrink_to_fit();
		}
		family.clear();
		family.shrink_to_fit();

	}
};

void begining_ending(Scales s)
{
	int num = 0;
	string name;
	date desired_date;
	double weight;
	string path;
	vector <string> actions = { "Выберите действие:", "Установить начальгую дату наблюдений", "Узнать начальгую дату наблюдений",
		"Задать наблюдение", "Узнать вес в выбранном наблюдении", "Найти средний вес члена семьи в выбранном месяце или за всю историю наблюдений",
		"Найти минимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался",
		"Найти максимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался",
		"Сохранить историю наблюдений в файл", "Считать историю наблюдений из файла", "Выйти" };
	vector <string> choice_of_member_1 = { "Выберите члена семьи:", "Выход" };
	vector <string> choice_of_member_2 = { "Выберите члена семьи:", "Новый член семьи", "Выход" };
	vector <string> choice_of_period = { "Выберите период для поиска:", "В определенном месяце", "За весь период", "Выход" };
	vector <string> choice_of_file_to_open = { "Выберите файл для считывания данных:", "По умолчанию ('List of notices.txt')", "Собственный", "Выход" };
	vector <string> choice_of_mode_of_output_to_file = { "Выберите спосо сохранения данных в файл:", "Создать новый файл",
		"Заменить тот, из которого считали", "Выход"};

	cout << "Добрый день!" << endl;
	cout << "Вас приветствует программа 'Напольные весы'" << endl;
	cout << "ПРЕДУПРЕЖДЕНИЕ: изначально программа не имеет данных" << endl;
	cout << "Чтобы перемещаться по меню, используйте клавиши 'Вверх' и 'Вниз'. Для выбора из списка нажмите 'Enter'" << endl << endl;
	system("pause");
	system("cls");
		do
		{
			name = "";
			desired_date = { 0, 0, 0 };
			weight = 0.0;
			try
			{
				num = choice_in_menu(actions);
				switch (num)
				{
				case 1:
					num = (choice_in_menu(choice_of_member_2));
					if (num == choice_of_member_2.size() - 1)
					{
						num = -1;
						break;
					}
					else if (num == choice_of_member_2.size() - 2)
					{
						cout << "Введите имя нового члена семьи (на английском): ";
						_flushall();
						cin >> name;
						s.input_new_member_of_family(name, choice_of_member_1, choice_of_member_2);
					}
					system("cls");
					input_new_date(desired_date);
					s.input_of_begining(num - 1, desired_date);
					break;
				case 2:
					if (choice_of_member_1.size() == 2)
						throw(7);
					else
					{
						num = choice_in_menu(choice_of_member_1);
						if (num == choice_of_member_1.size() - 1)
							num = -1;
						else
						{
							desired_date = s.output_of_begining(num - 1);
							cout << "Начальная дата наблюдений: " << desired_date.day << '.' << desired_date.month << '.'
								<< desired_date.year << endl << endl;
							system("pause");
							system("cls");
						}
					}
					break;
				case 3:
					num = choice_in_menu(choice_of_member_2);
					if (num == choice_of_member_2.size() - 1)
					{
						num = -1;
						break;
					}
					else if (num == choice_of_member_2.size() - 2)
					{
						cout << "Введите имя нового члена семьи (на английском): ";
						_flushall();
						cin >> name;
						s.input_new_member_of_family(name, choice_of_member_1, choice_of_member_2);
					}
					system("cls");
					input_new_date(desired_date);
					cout << "Введите вес: ";
					cin >> weight;
					while (weight <= 0)
					{
						system("cls");
						cout << "Вес введе некорректно" << endl;
						cout << "Пожалуйста, введите вес заново: ";
						cin >> weight;
					}
					system("cls");
					s.input_of_notice(num - 1, desired_date, weight);
					break;
				case 4:
					if (choice_of_member_1.size() == 2)
						throw(7);
					else
					{
						num = choice_in_menu(choice_of_member_1);
						if (num == choice_of_member_1.size() - 1)
							num = -1;
						else
						{
							input_new_date(desired_date);
							weight = s.output_of_weight(num - 1, desired_date);
							cout << "Вес в выбранном наблюдении: " << setprecision(5) << weight << endl << endl;
							system("pause");
							system("cls");
						}
					}
					break;
				case 5:
					if (choice_of_member_1.size() == 2)
						throw(7);
					else
					{
						num = choice_in_menu(choice_of_member_1);
						if (num == choice_of_member_1.size() - 1)
							num = -1;
						else
						{
							int i = choice_in_menu(choice_of_period);
							if (i == choice_of_period.size() - 1)
								num = -1;
							else
							{
								if (i == 1)
								{
									cout << "Введите год (4 цифры): ";
									cin >> desired_date.year;
									system("cls");
									cout << "Введите номер месяца: ";
									cin >> desired_date.month;
									while ((desired_date.month < 1) || (desired_date.month > 12))
									{
										system("cls");
										cout << "Номер месяца введен некорректно" << endl;
										cout << "Пожалуйста, введите номер месяца заново: ";
										cin >> desired_date.month;
									}
									system("cls");
								}
								weight = s.output_of_average_value(num - 1, desired_date);
								cout << "Средний веc за выбранный период: " << setprecision(5) << weight << endl << endl;
							}
						}
						system("pause");
					}
					break;
				case 6:
					if (choice_of_member_1.size() == 2)
						throw(7);
					else
					{
						num = choice_in_menu(choice_of_member_1);
						if (num == choice_of_member_1.size() - 1)
							num = -1;
						else
						{
							int i = choice_in_menu(choice_of_period);
							if (i == choice_of_period.size() - 1)
								num = -1;
							else
							{
								if (i == 1)
								{
									cout << "Введите год (4 цифры): ";
									cin >> desired_date.year;
									system("cls");
									cout << "Введите номер месяца: ";
									cin >> desired_date.month;
									while ((desired_date.month < 1) || (desired_date.month > 12))
									{
										system("cls");
										cout << "Номер месяца введен некорректно" << endl;
										cout << "Пожалуйста, введите номер месяца заново: ";
										cin >> desired_date.month;
									}
									system("cls");
								}
								weight = s.output_of_min(num - 1, desired_date);
								cout << "Минимальный веc за выбранный период: " << setprecision(5) << weight << endl;
								cout << "Дата, когда он последний раз наблюдался: " << desired_date.day << '.' << desired_date.month
									<< '.' << desired_date.year << endl << endl;
							}
						}
						system("pause");
					}
					break;
				case 7:
					if (choice_of_member_1.size() == 2)
						throw(7);
					else
					{
						num = choice_in_menu(choice_of_member_1);
						if (num == choice_of_member_1.size() - 1)
							num = -1;
						else
						{
							int i = choice_in_menu(choice_of_period);
							if (i == choice_of_period.size() - 1)
								num = -1;
							else
							{
								if (i == 1)
								{
									cout << "Введите год (4 цифры): ";
									cin >> desired_date.year;
									system("cls");
									cout << "Введите номер месяца: ";
									cin >> desired_date.month;
									while ((desired_date.month < 1) || (desired_date.month > 12))
									{
										system("cls");
										cout << "Номер месяца введен некорректно" << endl;
										cout << "Пожалуйста, введите номер месяца заново: ";
										cin >> desired_date.month;
									}
									system("cls");
								}
								weight = s.output_of_max(num - 1, desired_date);
								cout << "Максимальный веc за выбранный период: " << setprecision(5) << weight << endl;
								cout << "Дата, когда он последний раз наблюдался: " << desired_date.day << '.' << desired_date.month
									<< '.' << desired_date.year << endl << endl;
							}
						}
						system("pause");
					}
					break;
				case 8:
					num = choice_in_menu(choice_of_mode_of_output_to_file);
					if (num == choice_of_mode_of_output_to_file.size() - 1)
						num = -1;
					else
					{
						if (num == choice_of_mode_of_output_to_file.size() - 3)
						{
							cout << "Введите название нового файла (с форматом файла, например, 'List of notices.txt'): ";
							_flushall();
							getline(cin, path);
						}
						else
							path = "";
						system("cls");
						s.rewrite_of_file(path);
					}
					break;
				case 9:
					num = choice_in_menu(choice_of_file_to_open);
					if (num == choice_of_file_to_open.size() - 1)
						num = -1;
					else
					{
						if (num == choice_of_file_to_open.size() - 2)
						{
							cout << "Введите путь до файла: ";
							_flushall();
							getline(cin, path);
						}
						else
							path = "List of notices.txt";
						s.read_of_file(path, choice_of_member_1, choice_of_member_2);
					}
					break;
				default:
					num = -1;
					break;
				}
			}
			catch (int k)
			{
				switch (k)
				{
				case 1:
					cout << "Начальная дата неизвестна, поскольку она не была задана и не было внесено ни одного наблюдения" << endl << endl;
					break;
				case 2:
					cout << "Вес неизвестен, поскольку в данный день наблюдений не было" << endl << endl;
					break;
				case 3:
					cout << "Средний/минимальный/максимальный вес неизвестен, поскольку в данный период наблюдений не было" << endl << endl;
					break;
				case 4:
					cout << "Данные не были считаны/записаны, поскольку не удалось открыть файл" << endl << endl;
				case 5:
					cout << "Действие не было завершено, посскольку наблюдения начались позже введенной даты" << endl << endl;
					break;
				case 6: 
					cout << "Действие не было завершено, поскольку не было внесено ни оного наблюдения" << endl << endl;
					break;
				case 7: 
					cout << "Действие не может быть завершено, поскольку не задано ни одного члена семьи" << endl << endl;
					break;
				}
				system("pause");
			}
			system("cls");
		} while (num != -1);
	std::cout << "До свидания! Хорошего Вам дня)" << endl << endl;
	system("pause");
	actions.clear();
	actions.shrink_to_fit();
	choice_of_member_1.clear();
	choice_of_member_1.shrink_to_fit();
	choice_of_member_2.clear();
	choice_of_member_2.shrink_to_fit();
	choice_of_period.clear();
	choice_of_period.shrink_to_fit();
	choice_of_file_to_open.clear();
	choice_of_file_to_open.shrink_to_fit();
	choice_of_mode_of_output_to_file.clear();
	choice_of_mode_of_output_to_file.shrink_to_fit();
}

void main()
{
	setlocale(LC_ALL, "Russian");
	Scales s;
	begining_ending(s);
}