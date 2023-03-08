#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>
#include <vector>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'
#define RSM_PhSM_count 7
#define BrSM_count 13
#define PhSM_country_count 5
#define actions_count 5
#define systems_of_measure_count 5

int choise_in_menu(std::string list_for_choise[], int max_number_of_choise)
{
	int selected = 1;
	char c;
	do
	{
		std::cout << list_for_choise[0] << std::endl;
		for (int i = 1; i < max_number_of_choise; i++)
		{
			if (i == selected)
				std::cout << " > ";
			else std::cout << "   ";
			std::cout << i << ". " << list_for_choise[i] << std::endl;
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

class Weight
{
	double meaning, conversed_meaning;
	std::string system_of_measures[systems_of_measure_count];
	std::string RSM_names[RSM_PhSM_count];
	std::string BrSM_names[BrSM_count];
	std::string PhSM_country[PhSM_country_count];
	std::string PhSM_names[RSM_PhSM_count];
public:
	Weight()
	{
		meaning = 0.0;
		conversed_meaning = 0.0;
		system_of_measures[0] = { "�������� ������� ��� ����:" }; system_of_measures[1] = { "������� ������� ���" }; system_of_measures[2] = { "���������� ������� ���" }; system_of_measures[3] = { "����������� ������� ���" }; system_of_measures[4] = { "�����" };
		RSM_names[0] = { "�������� ������� ���������:" }; RSM_names[1] = { "��������" }; RSM_names[2] = { "���" }; RSM_names[3] = { "����" }; RSM_names[4] = { "���" }; RSM_names[5] = { "��������" }; RSM_names[6] = { "�����" };
		BrSM_names[0] = { "�������� ������� ���������:" }; BrSM_names[1] = { "����" }; BrSM_names[2] = { "�����" }; BrSM_names[3] = { "�������� �������" }; BrSM_names[4] = { "��� (������� �������)" }; BrSM_names[5] = { "����� ����������� (������ ��� �������)" }; BrSM_names[6] = { "������� ����������� (�������)" }; BrSM_names[7] = { "������� (���� ���� ����)" }; BrSM_names[8] = { "���� (���� ���� ����)" }; BrSM_names[9] = { "����� �����������" }; BrSM_names[10] = { "����� �����" }; BrSM_names[11] = { "����� �������" }; BrSM_names[12] = { "�����" };
		PhSM_country[0] = { "��������, ����������� ������� ��� ����� ������ �� ������ ������������:" }; PhSM_country[1] = { "������" }; PhSM_country[2] = { "��������" }; PhSM_country[3] = { "��������������" }; PhSM_country[4] = { "�����" };
		PhSM_names[0] = { "�������� ������� ���������:" }; PhSM_names[1] = { "����" }; PhSM_names[2] = { "�����" }; PhSM_names[3] = { "������" }; PhSM_names[4] = { "�������" }; PhSM_names[5] = { "����" }; PhSM_names[6] = { "�����" };
	}
private:
	void conversation_to_Russian_system_of_measures_RSM()
	{
		int num = choise_in_menu(RSM_names, RSM_PhSM_count);
		if (num != 6)
		{
			std::cout << "������� ���������: " << RSM_names[num] << std::endl;
			std::cout << "��������: ";
		}
		switch (num)
		{
		case 1:
			conversed_meaning = meaning / 164;
			break;
		case 2:
			conversed_meaning = meaning / 16.4;
			break;
		case 3:
			conversed_meaning = meaning / 0.4095120375;
			break;
		case 4:
			conversed_meaning = meaning / 0.4095120375 * 32;
			break;
		case 5:
			conversed_meaning = meaning / 0.4095120375 * 96;
			break;
		case 6:
			conversed_meaning = -1;
			return;
		}
	}

	void conversation_to_British_system_of_measures_BrSM()
	{
		int num = choise_in_menu(BrSM_names, BrSM_count);
		if (num != 12)
		{
			std::cout << "������� ���������: " << BrSM_names[num] << std::endl;
			std::cout << "��������: ";
		}
		switch (num)
		{
		case 1:
			conversed_meaning = meaning / 0.45359237;
			break;
		case 2:
			conversed_meaning = meaning / 0.45359237 / 14;
			break;
		case 3:
			conversed_meaning = meaning / 0.45359237 / 25;
			break;
		case 4:
			conversed_meaning = meaning / 0.45359237 / 28;
			break;
		case 5:
			conversed_meaning = meaning / 0.45359237 / 100;
			break;
		case 6:
			conversed_meaning = meaning / 0.45359237 / 112;
			break;
		case 7:
			conversed_meaning = meaning / 0.45359237 / 5936;
			break;
		case 8:
			conversed_meaning = meaning / 0.45359237 / 47488;
			break;
		case 9:
			conversed_meaning = meaning / 0.45359237 / 2204.6;
			break;
		case 10:
			conversed_meaning = meaning / 0.45359237 / 2000;
			break;
		case 11:
			conversed_meaning = meaning / 0.45359237 / 2240;
			break;
		case 12:
			conversed_meaning = -1;
			return;
		}
	}

	void conversation_to_Pharmaceutical_system_of_measures_PhSM()
	{
		int num = choise_in_menu(PhSM_names, RSM_PhSM_count);
		if (num != 6)
		{
			std::cout << "������� ���������: " << PhSM_names[num] << std::endl;
			std::cout << "��������: ";
		}
		switch (num)
		{
		case 1:
			break;
		case 2:
			conversed_meaning *= 12;
			break;
		case 3:
			conversed_meaning *= 96;
			break;
		case 4:
			conversed_meaning *= 288;
			break;
		case 5:
			conversed_meaning *= 5760;
			break;
		case 6:
			conversed_meaning = -1;
			return;
		}
	}

	void choise_of_country_of_Pharmaceutical_system_of_measures_PhSM()
	{
		switch (choise_in_menu(PhSM_country, PhSM_country_count))
		{
		case 1:
			conversed_meaning = meaning / 0.358323;
			break;
		case 2:
			conversed_meaning = meaning / 0.350783;
			break;
		case 3:
			conversed_meaning = meaning / 0.373242;
			break;
		case 4:
			conversed_meaning = -1;
			return;
		}
		conversation_to_Pharmaceutical_system_of_measures_PhSM();
	}

public:

	double choise_of_system_of_measure()
	{
		switch (choise_in_menu(system_of_measures, systems_of_measure_count))
		{
		case 1:
			conversation_to_Russian_system_of_measures_RSM();
			break;
		case 2:
			conversation_to_British_system_of_measures_BrSM();
			break;
		case 3:
			choise_of_country_of_Pharmaceutical_system_of_measures_PhSM();
			break;
		case 4:
			return(-1);
		}
		return(conversed_meaning);
	}

	void insert_weight()
	{
		std::cout << "������� ������� ��� � �����������: ";
		std::cin >> meaning;
		while (meaning < 0)
		{
			system("cls");
			std::cout << "��� ������ �����������!" << std::endl;
			std::cout << "����������, ������� ������� ��� � ����������� ������: ";
			std::cin >> meaning;
		}
		system("cls");
		return;
	}

	double output_weight()
	{
		return(meaning);
	}
};

void begining_ending(Weight w)
{
	int num = 0;
	double final_meaning;
	std::string actions[actions_count] = { "��� �� ������ ������� � ������� �����:", "������ ������� ��� � �����������", "�������� ������� ��� � �����������", "��������� � ������ ������� ���������", "�����" };
	std::cout << "������ ����!" << std::endl;
	std::cout << "��� ������������ ��������� �����. � ������ ��� ��������� ��� �� ����������� � ������ ������� ���������, ������� ����� ������������ �����" << std::endl;
	std::cout << "����� ������������ �� ����, ����������� ������� '�����' � '����'. ��� ������ �� ������ ������� 'Enter'" << std::endl << std::endl;
	system("pause");
	system("cls");
	w.insert_weight();
	do
	{
		final_meaning = 0;
		num = choise_in_menu(actions, actions_count);
		switch (num)
		{
		case 1:
			final_meaning = w.output_weight();
			std::cout << "������� ��� � �����������: " << final_meaning << std::endl << std::endl;
			system("pause");
			system("cls");
			break;
		case 2:
			w.insert_weight();
			break;
		case 3:
			final_meaning = w.choise_of_system_of_measure();
			if (final_meaning == -1)
				num = -1;
			else
			{
				std::cout << final_meaning << std::endl << std::endl;
				system("pause");
				system("cls");
			}
			break;
		default:
			num = -1;;
		}
	} while (num != -1);
	std::cout << "�� ��������! �������� ��� ���)" << std::endl << std::endl;
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	Weight w;
	begining_ending(w);
}