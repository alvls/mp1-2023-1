#include <iostream>
using namespace std;
class temperature_converter
{
	double c;
	int temp;
public:
	double CelsiusTemperature;
	void inPut()
	{
		cout << "Введите текущую температуру. " << endl;
		cin >> CelsiusTemperature;
	}
	void MainPrint()
	{
		cout << "Чтобы узнать текущую температуры по шкале  Цельсия введите - 1." << endl;
		cout << "Чтобы узнать текущую температуру по шкале Фаренгейта введите - 2. " << endl;
		cout << "Чтобы узнать текущую температуру по шкале Кельвина введите - 3. " << endl;
		cout << "Чтобы узнать текущую температуру по шкале Ранкина введите - 4. " << endl;
		cout << "Чтобы обновить текущую температуру по шкале Цельсия введите - 5. " << endl;
	}
	void swap()
	{
		do
		{
			cout << "Введите номер преобразования. Чтобы закрыть консоль введите - 0." << endl;
			cin >> temp;
			if (temp > 5 || temp < 0)
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
			case 5:
				inPut();
				break;
			case 0:
				break;
			}
		} while (temp != 0);
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
	setlocale(LC_ALL, "ru");
	temperature_converter t;
	t.inPut();
	t.MainPrint();
	t.swap();
	system("pause");
}