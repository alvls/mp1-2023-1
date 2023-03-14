#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>

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
	double meaning;
public:
	Weight()
	{
		meaning = 0.0;
	}

	double conversation_to_Russian_system_of_measures_RSM(int num)
	{
		switch (num)
		{
		case 1:
			return(meaning / 164);
		case 2:
			return(meaning / 16.4);
		case 3:
			return(meaning / 0.4095120375);
		case 4:
			return(meaning / 0.4095120375 * 32);
		case 5:
			return(meaning / 0.4095120375 * 96);
		case 6:
			return (- 1);
		}
	}

	double conversation_to_British_system_of_measures_BrSM(int num)
	{
		switch (num)
		{
		case 1:
			return(meaning / 0.45359237);
		case 2:
			return(meaning / 0.45359237 / 14);
		case 3:
			return(meaning / 0.45359237 / 25);
		case 4:
			return(meaning / 0.45359237 / 28);
		case 5:
			return(meaning / 0.45359237 / 100);
		case 6:
			return(meaning / 0.45359237 / 112);
		case 7:
			return(meaning / 0.45359237 / 5936);
		case 8:
			return(meaning / 0.45359237 / 47488);
		case 9:
			return(meaning / 0.45359237 / 2204.6);
		case 10:
			return(meaning / 0.45359237 / 2000);
		case 11:
			return(meaning / 0.45359237 / 2240);
		case 12:
			return(-1);
		}
	}

	double conversation_to_Pharmaceutical_system_of_measures_PhSM(int num, double coefficient)
	{
		switch (num)
		{
		case 1:
			return(coefficient * meaning);
		case 2:
			return(coefficient * meaning * 12);
		case 3:
			return(coefficient * meaning * 96);
		case 4:
			return(coefficient * meaning * 288);
		case 5:
			return(coefficient * meaning * 5760);
		case 6:
			return(-1);
		}
	}

	void insert_weight(double weight)
	{
		meaning = weight;
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
	double Ph_coefficient = 0.0;
	std::string actions[actions_count] = { "Что Вы хотите сделать с текущим весом:", "Узнать текущий вес в килограммах", "Изменить текущий вес в килограммах", "Перевести в другую единицу измерения", "Выйти" };
	std::string system_of_measures[systems_of_measure_count] = { "Выберите систему мер веса", "Русская система мер", "Британская система мер", "Аптекарская система мер", "Выход" };
	std::string RSM_names[RSM_PhSM_count] = { "Выберите единицу измерений:", "Берковец", "Пуд", "Фунт", "Лот", "Золотник", "Выход" };
	std::string BrSM_names[BrSM_count] = { "Выберите единицу измерений:", "Фунт", "Стоун", "Короткий квартер", "Тод (Длинный квартер)", "Малый хандредвейт (Центал или центнер)", "Большой хандредвейт (Квинтал)", "Челдрон (мера веса угля)", "Киль (мера веса угля)", "Тонна метрическая", "Тонна малая", "Тонна большая", "Выход" };
	std::string PhSM_country[PhSM_country_count] = { "Выберите, аптекарскую систему мер какой страны Вы хотите использовать:", "Россия", "Германия", "Великобритания", "Выход" };
	std::string PhSM_names[RSM_PhSM_count] = { "Выберите единицу измерений:", "Фунт", "Унция", "Драхма", "Скрупул", "Гран", "Выход" };
	std::cout << "Добрый день!" << std::endl;
	std::cout << "Вас приветствует конвертер весов. Я помогу Вам перевести вес из килограммов в другие единицы измерения, которые будут представлены позже" << std::endl;
	std::cout << "Чтобы перемещаться по меню, используйте клавиши 'Вверх' и 'Вниз'. Для выбора из списка нажмите 'Enter'" << std::endl << std::endl;
	system("pause");
	system("cls");
	std::cout << "Введите текущий вес в килограммах: ";
	std::cin >> final_meaning;
	while (final_meaning < 0)
	{
		system("cls");
		std::cout << "Вес введен некорректно!" << std::endl;
		std::cout << "Пожалуйста, введите текущий вес в килограммах заново: ";
		std::cin >> final_meaning;
	}
	system("cls");
	w.insert_weight(final_meaning);
	do
	{
		final_meaning = 0;
		num = choise_in_menu(actions, actions_count);
		switch (num)
		{
		case 1:
			final_meaning = w.output_weight();
			std::cout << "Текущий вес в килограммах: " << final_meaning << std::endl << std::endl;
			system("pause");
			system("cls");
			break;
		case 2:
			std::cout << "Введите текущий вес в килограммах: ";
			std::cin >> final_meaning;
			while (final_meaning < 0)
			{
				system("cls");
				std::cout << "Вес введен некорректно!" << std::endl;
				std::cout << "Пожалуйста, введите текущий вес в килограммах заново: ";
				std::cin >> final_meaning;
			}
			system("cls");
			w.insert_weight(final_meaning);
			break;
		case 3:
			switch (choise_in_menu(system_of_measures, systems_of_measure_count))
			{
			case 1:
				num = choise_in_menu(RSM_names, RSM_PhSM_count);
				final_meaning = w.conversation_to_Russian_system_of_measures_RSM(num);
				if (final_meaning != -1)
					std::cout << "Единица измерения: " << RSM_names[num] << std::endl;
				break;
			case 2:
				num = choise_in_menu(BrSM_names, BrSM_count);
				final_meaning = w.conversation_to_British_system_of_measures_BrSM(num);
				if (final_meaning != -1)
					std::cout << "Единица измерения: " << BrSM_names[num] << std::endl;
				break;
			case 3:
				switch (choise_in_menu(PhSM_country, PhSM_country_count))
				{
				case 1:
					Ph_coefficient = 0.358323;
					break;
				case 2:
					Ph_coefficient = 0.350783;
					break;
				case 3:
					Ph_coefficient = 0.373242;
					break;
				case 4:
					num = -1;
					return;
				}
				if (num != -1)
				{
					num = choise_in_menu(PhSM_names, RSM_PhSM_count);
					final_meaning = w.conversation_to_Pharmaceutical_system_of_measures_PhSM(num, Ph_coefficient);
					if (final_meaning != -1)
						std::cout << "Единица измерения: " << PhSM_names[num] << std::endl;
				}
				break;
			case 4:
				final_meaning = -1;
				break;
			}
			if (final_meaning == -1)
				num = -1;
			else
			{
				std::cout << "Значение: " << final_meaning << std::endl << std::endl;
				system("pause");
				system("cls");
			}
			break;
		default:
			num = -1;
		}
	} while (num != -1);
	std::cout << "До свидания! Хорошего Вам дня)" << std::endl << std::endl;
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	Weight w;
	begining_ending(w);
}