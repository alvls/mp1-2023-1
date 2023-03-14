#include <iostream>
using namespace std;
class temperature_converter
{
	double CelsiusTemperature;
	int temp;
public:

	temperature_converter(double t)
	{
		CelsiusTemperature = t;
	}
	void MainPrint()
	{
		cout << "Чтобы узнать текущую температуры по шкале  Цельсия введите - 1." << endl;
		cout << "Чтобы узнать текущую температуру по шкале Фаренгейта введите - 2. " << endl;
		cout << "Чтобы узнать текущую температуру по шкале Кельвина введите - 3. " << endl;
		cout << "Чтобы узнать текущую температуру по шкале Ранкина введите - 4. " << endl;
		cout << "Чтобы закрыть консоль введите - 0. " << endl;
	}
	void swap(int temp)
	{
			if (temp > 4 || temp < 0)
			{
				cout << "Введено некорректное значение!" << endl;
			}
			else 
				switch (temp)
				{
			case 1:
				printC();
				break;
			case 2:
				Fahr(CelsiusTemperature);
				break;
			case 3:
				kelv(CelsiusTemperature);
				break;
			case 4:
				Rankin(CelsiusTemperature);
				break;
			case 0:
				break;
			}
	}
	void Rankin(double Celsius)
	{
		double F;
		Celsius = (Celsius * 1.8) + 32 + 459.67;
		F = Celsius;
		cout << "Текущая температура по шкале Ранкина: " << F << "°R" << endl;
	}
	void Fahr(double Celsius)
	{
		double F;
		Celsius = Celsius * 2;
		Celsius = Celsius - (Celsius * 0.1);
		Celsius = Celsius + 32;
		F = Celsius;
		cout << "Текущая температура по шкале Фаренгейта: " << F << "°F" << endl;
	}
	void printC()
	{
		cout << "Текущая температура по шкале Цельсия: " << CelsiusTemperature << "°C" << endl;
	}
	void kelv(double Celsius)
	{
		double F;
		Celsius = Celsius + 273.15;
		F = Celsius;
		cout << "Текущая температура по шкале Кельвина: " << F << "K" << endl;
	}
};
int main()
{
	int temp;
	setlocale(LC_ALL, "ru");
	temperature_converter t(30);
	t.MainPrint();
	do
	{
		cout << "Введите номер преобразования." << endl;
		cin >> temp;
		t.swap(temp);
	} while (temp != 0);
	system("pause");
}