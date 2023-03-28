#include <iostream>
using namespace std;
class temperature_converter
{
	double CelsiusTemperature;
	int temp;
public:
	temperature_converter()
	{}
	temperature_converter(double t)
	{
		CelsiusTemperature = t;
	}

	void temper_c(double new_cels_t)
	{
		CelsiusTemperature = new_cels_t;
	}
	double outC()
	{
		return(CelsiusTemperature);
	}
	double rankin()
	{
		return((CelsiusTemperature * 1.8) + 32 + 459.67);
	}
	double fahr()
	{
		return((9 * CelsiusTemperature) / 5 + 32);
	}
	double kelv()
	{
		return(CelsiusTemperature + 273.15);
	}
	void outall()
	{
		cout << "Температура в градусах Цельсия " << CelsiusTemperature << endl;
		cout << "Температура в градусах Кельвина " << kelv() << endl;
		cout << "Температура в градусах Фаренгейта " << fahr() << endl;
		cout << "Температура по шклае Ранкина " << rankin() << endl;
	}
};
    void  main()
	{
	setlocale(LC_ALL, "ru");
	temperature_converter t;
	t.temper_c(30);
	t.outall();
	system("pause");
}