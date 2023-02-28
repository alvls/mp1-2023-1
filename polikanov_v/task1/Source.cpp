#include <iostream>
#include <string>
#include <locale.h>
using namespace std;



class TemperatureConverter {

	double degC = 0;

	public:

		TemperatureConverter() {
		}

		TemperatureConverter(double degC) {
			this->degC = degC;
		}

		void set_degC(double degC) {
			this->degC = degC;
		}

		double get_degC() {
			return degC;
		}

		double toDegF() {			
			return (degC * 1.8) + 32;
		}

		double toDegK() {

			return degC + 273.15;
		}

		double toDegReo() {

			return degC * 0.8;
		}

		void printAllDegrees() { // надеюсь, что имено это означает "уметь выводить себя на консоль"
			cout << "Температура в цельсиях: " << degC << endl;
			cout << "Температура в кельвинах: " << this->toDegK() << endl;
			cout << "Температура в фаренгейтах: " << this->toDegF() << endl;
		}
};

void main() {
	setlocale(LC_ALL, "Russian");

	TemperatureConverter converter;

	converter.set_degC(38.2);
	cout << converter.toDegF() << endl;
	cout << converter.get_degC() << endl;
	converter.set_degC(36.6);
	cout << converter.get_degC() << endl;
	cout << "Выздоровел" << endl;
	converter.printAllDegrees();
	
	system("PAUSE");
}