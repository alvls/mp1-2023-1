#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

#define actions_count 10

int choise_in_menu(std::string list_for_choise[], int max_number_of_choise)
{
	int selected = 1;
	char c;
	do
	{
		std::cout << list_for_choise[0] << endl;
		for (int i = 1; i < max_number_of_choise; i++)
		{
			if (i == selected)
				std::cout << " > ";
			else std::cout << "   ";
			std::cout << i << ". " << list_for_choise[i] << endl;
		}
		switch ((c = _getch()))
		{
		case KEY_UP:
			if (selected > 1)
				selected--;
			break;
		case KEY_DOWN:
			if (selected < max_number_of_choise - 1)
				selected++;
			break;
		default: break;
		}
		system("cls");
	} while (c != KEY_ENTER);
	return(selected);
}

class String
{
	int lower_case[26];
	int upper_case[26];
	char str[41];
	int size;
	int code_of_letter;
	string choise_of_case[4];
	int count_of_letters;
	int counter;
	char substring[41];
public:
	String()
	{
		size = 0;
		memset(lower_case, 0, 26 * sizeof(int));
		memset(upper_case, 0, 26 * sizeof(int));
		code_of_letter = 0;
		choise_of_case[0] = { "��������, ��� �� ������ ��������� ��������:" }; choise_of_case[1] = { "� ������ ��������" }; choise_of_case[2] = { "��� ����� ��������" }; choise_of_case[3] = { "�����" };
		count_of_letters = 0;
		counter = 0;
	}

	void input_string(const char* ss)
	{
		for (size = 0; ss[size] != '\0'; size++)
			str[size] = ss[size];
		str[size] = '\0';
	}

	int output_lenght()
	{
		return (size);
	}

	char output_letter(int index)
	{
		return(str[index]);
	}

	void change_letter(int index)
	{
		cin >> str[index];
	}

	char* select_a_substring(int index_of_begining, int lenght_of_substring)
	{
		for (counter = index_of_begining; counter < index_of_begining + lenght_of_substring; counter++)
			substring[counter - index_of_begining] = str[counter];
		substring[lenght_of_substring] = '\0';
		return (substring);
	}

	bool check_of_palindrom()
	{
		counter = 0;
		while ((counter <= size / 2) && (str[counter] == str[size - counter - 1]))
			counter++;
		return (counter > size / 2);
	}

	int check_of_different()
	{
		count_of_letters = 0;
		for (counter = 0; counter <= size; counter++)
		{
			code_of_letter = (int)(str[counter]);
			if ((code_of_letter > 96) && (code_of_letter < 123))
			{
				lower_case[code_of_letter - 97]++;
			}
			else if ((code_of_letter > 64) && (code_of_letter < 91))
				upper_case[code_of_letter - 65]++;
		}
		switch (choise_in_menu(choise_of_case, 4))
		{
		case 1:
			for (counter = 0; counter < 26; counter++)
			{
				if (lower_case[counter] > 0)
				{
					count_of_letters++;
					lower_case[counter] = 0;
				}
				if (upper_case[counter] > 0)
				{
					count_of_letters++;
					upper_case[counter] = 0;
				}
			}
			break;
		case 2:
			for (counter = 0; counter < 26; counter++)
				if ((lower_case[counter] > 0) || (upper_case[counter] > 0))
				{
					count_of_letters++;
					lower_case[counter] = upper_case[counter] = 0;
				}
			break;
		case 3:
			count_of_letters = -1;
			break;
		}
		return (count_of_letters);
	}

	void output_string()
	{
		cout << "������� ������: " << str << endl << endl;
		system("pause");
		system("cls");
	}

	~String()
	{
		size = 0;
		count_of_letters = 0;
		count_of_letters = 0;
		counter = 0;
	}
};

void begining_ending(String w)
{
	int index = 0;
	char* substring;
	int lenght_or_substring;
	int num = 0;
	char* k = new char[41];
	string actions[actions_count] = { "�������� ��������:", "������ ������", "������ ����� ������", "�������� ������ ������ �� ��� �������", "�������� ������ ������ �� ��������� �������", "�������� ��������� �� ������", "���������, �������� �� ������ ����������� (� ������ ��������)", "�����, ������� ������ �������� ���������� �������� ���������� � ������", "������� ������� ������", "�����"};
	cout << "������ ����!" << endl;
	cout << "��������������: ����������� ������ ������, ������� ������� � ����� ��������" << endl;
	cout << "����� ������������ �� ����, ����������� ������� '�����' � '����'. ��� ������ �� ������ ������� 'Enter'" << endl << endl;
	system("pause");
	system("cls");
	do
	{
		num = choise_in_menu(actions, actions_count);
		switch (num)
		{
		case 1:
			cout << "������� ������ (�� 0 �� 40 ��������): ";
			cin.getline(k, 40);
			w.input_string(k);
			system("cls");
			break;
		case 2:
			cout << "����� ������: " << w.output_lenght() << endl << endl;
			system("pause");
			system("cls");
			break;
		case 3:
			cout << "������� ������: ";
			cin >> index;
			if ((index > -1) && (index < w.output_lenght()))
				cout << endl << "������ � ������ ��������: " << w.output_letter(index) << endl << endl;
			else cout << endl << "��������� ������ ������� �� ������� ������" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			cout << "������� ������: ";
			cin >> index;
			if ((index > -1) && (index < w.output_lenght()))
			{
				cout << endl << "������� ������: ";
				w.change_letter(index);
				while (getchar() != '\n');
			}
			else
			{
				cout << endl << "��������� ������ ������� �� ������� ������" << endl << endl;
				system("pause");
			}
			system("cls");
			break;
		case 5:
			cout << "������� ������, � �������� ������ ��������� ��������� � ����� ��������� ��������������: ";
			cin >> index >> lenght_or_substring;
			if ((index > -1) && ((index + lenght_or_substring - 1) < w.output_lenght()))
			{
				substring = w.select_a_substring(index, lenght_or_substring);
					cout << "���������� ���������: " << substring << endl << endl;
			}
			else cout << "��������� �������� ������� �� ������� ������" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 6:
			if (w.check_of_palindrom())
				cout << "������ �������� �����������" << endl << endl;
			else cout << "������ �� �������� �����������" << endl << endl;
			system("pause");
			system("cls");
			break;
		case 7:
			num = w.check_of_different();
			if (num != -1)
			{
				cout << "���������� ������ �������� ���������� �������� � ������: " << num << endl << endl;
				system("pause");
				system("cls");
			}
			break;
		case 8:
			w.output_string();
			break;
		default:
			num = -1;
			break;
		}
	} while (num != -1);
	delete[] k;
	std::cout << "�� ��������! �������� ��� ���)" << endl << endl;
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	String w;
	begining_ending(w);
}