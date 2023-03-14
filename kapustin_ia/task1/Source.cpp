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
		cout << "����� ������ ������� ����������� �� �����  ������� ������� - 1." << endl;
		cout << "����� ������ ������� ����������� �� ����� ���������� ������� - 2. " << endl;
		cout << "����� ������ ������� ����������� �� ����� �������� ������� - 3. " << endl;
		cout << "����� ������ ������� ����������� �� ����� ������� ������� - 4. " << endl;
		cout << "����� ������� ������� ������� - 0. " << endl;
	}
	void swap(int temp)
	{
			if (temp > 4 || temp < 0)
			{
				cout << "������� ������������ ��������!" << endl;
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
		cout << "������� ����������� �� ����� �������: " << F << "�R" << endl;
	}
	void Fahr(double Celsius)
	{
		double F;
		Celsius = Celsius * 2;
		Celsius = Celsius - (Celsius * 0.1);
		Celsius = Celsius + 32;
		F = Celsius;
		cout << "������� ����������� �� ����� ����������: " << F << "�F" << endl;
	}
	void printC()
	{
		cout << "������� ����������� �� ����� �������: " << CelsiusTemperature << "�C" << endl;
	}
	void kelv(double Celsius)
	{
		double F;
		Celsius = Celsius + 273.15;
		F = Celsius;
		cout << "������� ����������� �� ����� ��������: " << F << "K" << endl;
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
		cout << "������� ����� ��������������." << endl;
		cin >> temp;
		t.swap(temp);
	} while (temp != 0);
	system("pause");
}