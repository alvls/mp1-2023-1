#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <conio.h>
#include <string>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

#define actions_count 10
#define count_of_functions 11

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

class Taylor_series
{
	typedef double (*built_in_functions)(double);
	typedef double (Taylor_series::* own_functions)(double, int);
	int count;
	int number;
	double result;
	int counter;
	built_in_functions *function;
	own_functions *function_of_teylor_series;
	string *series_of_functions;
public:
	Taylor_series()
	{
		counter = 0;
		result = 0;
		number = 0;
		count = 0;
		function = new built_in_functions[count_of_functions];
		function[0] = exp; function[1] = sin; function[2] = cos;  function[3] = asin; function[4] = log; function[5] = sqrt; function[6] = atan; function[7] = sinh; function[8] = cosh; function[9] = asinh; function[10] = atanh;
		function_of_teylor_series = new own_functions[count_of_functions];
		function_of_teylor_series[0] = &Taylor_series::exponent; function_of_teylor_series[1] = &Taylor_series::sine; function_of_teylor_series[2] = &Taylor_series::cosine; function_of_teylor_series[3] = &Taylor_series::arcsine; function_of_teylor_series[4] = &Taylor_series::logarithm; function_of_teylor_series[5] = &Taylor_series::square_root; function_of_teylor_series[6] = &Taylor_series::arctangent; function_of_teylor_series[7] = &Taylor_series::hyperbolic_sine; function_of_teylor_series[8] = &Taylor_series::hyperbolic_cosine; function_of_teylor_series[9] = &Taylor_series::hyperbolic_arcsine; function_of_teylor_series[10] = &Taylor_series::hyperbolic_arctanget;
		series_of_functions = new string[count_of_functions];
		series_of_functions[0] = { "1 + x/1! + x^2/2! + x^3/3! + ... + x^n/n!" }; series_of_functions[1] = { "x - x^3/3! + x^5/5! - x^7/7! + ... + (-1)^n*x^(2n+1)/(2n+1)!" }; series_of_functions[2] = { "x - x^2/2! + x^4/4! - x^6/6! + ... + (-1)^n*x^(2n)/(2n)!" }; series_of_functions[3] = { "x + 1*x^3/(2*3) + 1*3*x^5/(2*4*5) + 1*3*5*x^7/(2*4*6*7) + ... + (2n)!*x^(2n+1)/(2^(2n)*(n!)^2*(2n+1))" }; series_of_functions[4] = { "x - x^2/2 + x^3/3 - x^4/4 + ... + (-1)^n*x^(n+1)/(n+1)" }; series_of_functions[5] = { "1 + 1*x/2 - 1*1*x^2/(2*4) + 1*1*3*x^3/(2*4*6) - ... + (-1)^(n+1)*(2n)!*x^n/(2^(2n)*(2n-1)*(n!)^2)" }; series_of_functions[6] = { "x - x^3/3 + x^5/5 - x^7/7 + ... + (-1)^(n-1)*x^(2n-1)/(2n-1)" }; series_of_functions[7] = { "x + x^3/3! + x^5/5! + x^7/7! + ... + x^(2n+1)/(2n+1)!" }; series_of_functions[8] = { "x + x^2/2! + x^4/4! + x^6/6! + ... + x^(2n)/(2n)!" }; series_of_functions[9] = { "x - 1*x^3/(2*3) + 1*3*x^5/(2*4*5) - 1*3*5*x^7/(2*4*6*7) + ... + (-1)^n*(2n)!*x(2n+1)/(2^(2n)*(n!)^2*(2n+1))" }; series_of_functions[10] = {"x + x^3/3 + x^5/5 + x^7/7 + ... + x^(2n+1)/(2n+1)"};
	}

	Taylor_series(const Taylor_series& s)
	{
		counter = 0;
		result = 0;
		number = s.number;
		count = s.count;
		function = new built_in_functions[count_of_functions];
		function_of_teylor_series = new own_functions[count_of_functions];
		series_of_functions = new string[count_of_functions];
		for (int i = 0; i < count_of_functions; i++)
		{
			function[i] = s.function[i];
			function_of_teylor_series[i] = s.function_of_teylor_series[i];
			series_of_functions[i] = s.series_of_functions[i];
		}
	}

	void input_function(int index)
	{
		number = index - 1;
	}

	int output_function()
	{
		return(number + 1);
	}

	void input_count_of_terms(int i)
	{
		count = i;
	}

	int output_count_of_terms()
	{
		return(count);
	}

	string output_of_series()
	{
		return(series_of_functions[number]);
	}

	double output_term_of_series(double x, int i)
	{
		return((this->*function_of_teylor_series[number])(x, i - 1));
	}

	double result_of_series(double x)
	{
		result = 0;
		for (counter = 0; counter < count; counter++)
		{
			result += (this->*function_of_teylor_series[number])(x, counter);
		}
		return(result);
	}

	double deflection(double x)
	{
		return(abs(function[number](x)-result_of_series(x)));
	}
private:
	double factorial(int n)
	{
		double factor = 1.0;
		for (; n > 1; n--)
			factor *= n;
		return factor;
	}

	double exponent(double x, int i)
	{
		if (i < 25)
			return (pow(x, i) / factorial(i));                             //calculation of exact value of factorial
		else
			return (pow(x, i) / (sqrt(2 * M_PI * i) * pow(i / M_E, i)));   //calculation of the approximate value of the factorial using Stirling formula
	}

	double sine(double x, int i)
	{
		while (x > 2 * M_PI)
			x -= 2 * M_PI;
		while (x < 0)
			x += 2 * M_PI;
		if (i < 25)
			return ((pow(-1, i)) * (pow(x, (2 * i + 1))) / factorial(2 * i + 1));
		else
			return ((pow(-1, i)) * (pow(x, (2 * i + 1))) / (sqrt(2 * M_PI * (2 * i + 1)) * pow((2 * i + 1) / M_E, (2 * i + 1))));
	}

	double cosine(double x, int i)
	{
		while (x >= 2 * M_PI)
			x -= 2 * M_PI;
		while (x < 0)
			x += 2 * M_PI;
		if (i < 25)
			return ((pow(-1, i)) * (pow(x, (2 * i))) / factorial(2 * i));
		else
			return ((pow(-1, i)) * (pow(x, (2 * i))) / (sqrt(2 * M_PI * (2 * i)) * pow((2 * i) / M_E, (2 * i))));
	}

	double arcsine(double x, int i)
	{
		if (i < 25)
			return (factorial(2 * i) / (pow(2, 2 * i) * pow(factorial(i), 2) * (2 * i + 1)) * pow(x, (2 * i + 1)));
		else
			return ((sqrt(2 * M_PI * (2 * i)) * pow((2 * i) / M_E, (2 * i))) / (pow(2, 2 * i) * pow((sqrt(2 * M_PI * i) * pow(i / M_E, i)), 2) * (2 * i + 1)) * pow(x, (2 * i + 1)));
	}

	double logarithm(double x, int i)
	{
		return (pow(-1, i) * pow(x, i + 1) / (i + 1));
	}

	double square_root(double x, int i)
	{
		if (i < 25)
			return (pow(-1, i) * factorial(2 * i) * pow(x, i) / ((1 - 2 * i) * pow(factorial(i), 2) * pow(4, i)));
		else
			return (pow(-1, i) * (sqrt(2 * M_PI * (2 * i)) * pow((2 * i) / M_E, (2 * i))) * pow(x, i) / ((1 - 2 * i) * pow((sqrt(2 * M_PI * i) * pow(i / M_E, i)), 2) * pow(4, i)));
	}

	double arctangent(double x, int i)
	{
		return (pow(-1, i) * pow(x, 2 * i + 1) / (2 * i + 1));
	}

	double hyperbolic_sine(double x, int i)
	{
		if (i < 25)
			return (pow(x, (2 * i + 1)) / factorial(2 * i + 1));
		else
			return (pow(x, (2 * i + 1)) / (sqrt(2 * M_PI * (2 * i + 1)) * pow((2 * i + 1) / M_E, (2 * i + 1))));
	}

	double hyperbolic_cosine(double x, int i)
	{
		if (i < 25)
			return (pow(x, (2 * i)) / factorial(2 * i));
		else
			return (pow(x, (2 * i)) / (sqrt(2 * M_PI * (2 * i)) * pow((2 * i) / M_E, (2 * i))));
	}

	double hyperbolic_arcsine(double x, int i)
	{
		if (i < 25)
			return (pow(-1, i) * factorial(2 * i) * pow(x, 2 * i + 1) / (pow(4, i) * pow(factorial(i), 2) * (2 * i + 1)));
		else
			return (pow(-1, i) * (sqrt(2 * M_PI * (2 * i)) * pow((2 * i) / M_E, (2 * i))) * pow(x, 2 * i + 1) / (pow(4, i) * pow((sqrt(2 * M_PI * i) * pow(i / M_E, i)), 2) * (2 * i + 1)));
	}

	double hyperbolic_arctanget(double x, int i)
	{
		return (pow(x, 2 * i + 1) / (2 * i + 1));
	}

public:
	~Taylor_series()
	{
		delete[] function;
		delete[] function_of_teylor_series;
		delete[] series_of_functions;
	}
};

double input_of_x(int choice)
{
	double x;
	cout << "Введите x: ";
	cin >> x;
	while (!((fabs(x) <= 1) && ((choice == 4) || (choice == 6) || (choice == 7))) && !((fabs(x) < 1) && ((choice == 10) || (choice == 11) || (choice == 5))) && !((x == 1) && (choice == 5)) && !(choice == 1) && !(choice == 2) && !(choice == 3) && !(choice == 8) && !(choice == 9))
	{
		system("cls");
		cout << "Введенное значение x недопустимо для выбранной функции" << endl << endl;
		cout << "Ограничения:" << endl;
		cout << "arcsin(x): -1 <= x <= 1" << endl << "ln(1+x): -1 < x <= 1" << endl << "sqrt(1+x): -1 <= x <= 1" << endl << "arctg(x): -1 <= x <= 1" << endl << "arsh(x): -1 < x < 1" << endl << "arth(x): -1 < x < 1" << endl << endl;
		cout << "Введите x снова: ";
		cin >> x;
	}
	system("cls");
	if ((choice == 5) || (choice == 6))
		x += 1;
	return(x);
}

void begining_ending(Taylor_series w)
{
	int num;
	double x;
	string actions[actions_count] = { "Выберите действие:", "Задать (изменить) функцию", "Узнать функцию", "Задать текущее число членов ряда", "Узнать текущее число членов ряда", "Выдать формулу ряда для выбранной функции", "Выдать значение заданного члена ряда", "Рассчитать значение ряда в выбранной точке x", "Вывести отклонение значения ряда в выбранной точке от эталонного значения текущей функции в данной точке", "Выйти" };
	string functions[count_of_functions + 2] = { "Выберите функцию:", "exp(x)", "sin(x)", "cos(x)", "arcsin(x)", "ln(1+x)", "sqrt(1+x)", "arctg(x)", "sh(x)", "ch(x)", "arsh(x)", "arth(x)", "Выход" };
	cout << "Добрый день!" << endl;
	cout << "Вас приветствует программа для расчета значений некоторых функций при помощи разложения их в ряд Тейлора" << endl;
	cout << "ПРЕДУПРЕЖДЕНИЕ: изначальное количество членов ряда равно 0" << endl;
	cout << "Чтобы перемещаться по меню, используйте клавиши 'Вверх' и 'Вниз'. Для выбора из списка нажмите 'Enter'" << endl << endl;
	system("pause");
	system("cls");
	num = choise_in_menu(functions, count_of_functions + 2);
	if (num != count_of_functions + 1)
	{
		w.input_function(num);
		do
		{
			num = choise_in_menu(actions, actions_count);
			switch (num)
			{
			case 1:
				num = choise_in_menu(functions, count_of_functions + 2);
				if (num != count_of_functions + 1)
					w.input_function(num);
				else num = (-1);
				break;
			case 2:
				cout << "выбранная функция: " << functions[w.output_function()] << endl << endl;
				system("pause");
				break;
			case 3:
				cout << "Введите число членов ряда (для более корректной работы программы не более 150): ";
				cin >> num;
				while (num < 0)
				{
					system("cls");
					cout << "Число членов ряда введено некорректно" << endl;
					cout << "Пожалуйста, введите число заново: ";
					cin >> num;
				}
				w.input_count_of_terms(num);
				break;
			case 4:
				cout << "Текущее число членов ряда: " << w.output_count_of_terms() << endl << endl;
				system("pause");
				break;
			case 5:
				cout << "Формула ряда для выбранной функции:" << endl;
				cout << w.output_of_series() << endl << endl;
				system("pause");
				break;
			case 6:
				x = input_of_x(w.output_function());
				cout << "Введите номер члена (для более корректной работы программы не более 150): ";
				cin >> num;
				while (num < 0)
				{
					system("cls");
					cout << "Номер члена ряда введен некорректно" << endl;
					cout << "Пожалуйста, введите число заново: ";
					cin >> num;
				}
				system("cls");
				cout << "Значение заданного члена: " << w.output_term_of_series(x, num) << endl << endl;
				system("pause");
				break;
			case 7:
				x = input_of_x(w.output_function());
				cout << "Значение ряда в выбранной точке: " << w.result_of_series(x) << endl << endl;
				system("pause");
				break;
			case 8:
				x = input_of_x(w.output_function());
				cout << "Отклонение значения ряда в выбранной точке от эталонного значения текущей функции в данной точке: " << w.deflection(x) << endl << endl;
				system("pause");
				break;
			default:
				num = -1;
				break;
			}
			system("cls");
		} while (num != -1);
	}
	std::cout << "До свидания! Хорошего Вам дня)" << endl << endl;
	system("pause");
}

void main()
{
	setlocale(LC_ALL, "Russian");
	Taylor_series w;
	begining_ending(w);
}