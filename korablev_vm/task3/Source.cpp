#include "Header.h"
#include "Integral.h"
/*Разработать класс Расчет интегралов.
Класс должен позволять вычислять приближенное значение интеграла от произвольной функции одной переменной, заданной в виде функции языка C++.
Интеграл необходимо вычислять в заданных пределах интегрирования, используя методы левых, правых и средних прямоугольников.
Класс должен содержать необходимые служебные методы (конструкторы, деструктор и пр.).
Класс должен предоставлять следующие операции: 1) задать текущую функцию, 2) задать пределы интегрирования,
3) узнать пределы интегрирования, 4) задать число отрезков метода прямоугольников, 5) выбрать метод вычисления,
6) вычислить значение интеграла выбранным методом, 7) вывести результат вычисления на экран.*/

void main()
{
	setlocale(LC_ALL, "Rus");
	system("title Калькулятор интегралов");
	hello();
	string str_func[] = { "\t\t Выберите желаемую функцию:", "> (x)", "> exp(x)", "> sin(x)", "> cos(x)", "> tan(x)", "> atan(x)", "> sqrt(x)"};
	string str_mtd[] = { "\t\t Выберите метод", "> Метод правых прямоугольников", "> Метод левых прямоугольников", "> Метод средних прямоугольников"};
	string str_exit[] = { "\t\t Выберите дальнейшее действие", "> Новое вычисление", "> Выйти из программы" };
	Integral integ;
	int choice_num_func, choice_num_metod, choice_exit_menu;
	double answer=0;
	double* lims;
	Fx choice_function = line;
	en_side choice_metod;
	while (1)
	{
		choice_num_func = menu_mode(str_func, 8);
		switch (choice_num_func)
		{
		case _line:
			choice_function = line;
			break;
		case _exp:
			choice_function = exp;
			break;
		case _sin:
			choice_function = sin;
			break;
		case _cos:
			choice_function = cos;
			break;
		case _tan:
			choice_function = tan;
			break;
		case _atan:
			choice_function = atan;
			break;
		case _sqrt:
			choice_function = sqrt;
			break;
		}
		integ.set_func(choice_function);
		lims = get_lim(); 
		integ.set_lim(lims[0], lims[1]);
		choice_num_metod = menu_mode(str_mtd, 4);
		switch (choice_num_metod)
		{
		case 1:
			choice_metod = _right;
			break;
		case 2:
			choice_metod = _left;
			break;
		case 3:
			choice_metod = _mid;
			break;
		default:
			cout << "Произошла непредвиденная ошибка" << endl;
			system("pause");
			break;
		}
		integ.set_mtd(choice_metod);
		integ.set_seg(get_segment());
		answer = integ.return_answ();
		if ((lims[0] || lims[1] < 0) && (choice_num_func == _sqrt))
			cout << "Квадратный корень берется только от неотрицательных чисел" << endl;
		else
			cout << "Ответ: " << answer << endl;
		system("pause");
		choice_exit_menu = menu_mode(str_exit, 3);
		switch (choice_exit_menu)
		{
		case _ex_file:
			exit_prog();
			break;
		default:
			break;
		}
	}
}
