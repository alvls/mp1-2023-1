#include <iostream>
#include <string>

using namespace std;

class Lenght_converter
{
public:

	double meters, coefficient;
	string name;

	void SetMeters(int meters)
	{
		this->meters = meters;
	}

	double Getcnt(double coefficient)
	{
		return meters * coefficient;
	}
	void Print() 
	{
		cout<<Getcnt(coefficient)<< " " << name << endl;
	}
};

int main()
{
	int cnt_meters, choice;
	cout << "Enter the number of meters" << endl;
	cin >> cnt_meters;
	cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
	cin >> choice;


	while (choice != 0) {
		switch (choice)
		{

		case 1:
		{
			Lenght_converter meters;
			meters.SetMeters(cnt_meters);
			meters.name = "meters";
			meters.coefficient = 1;
			meters.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
		case 2:
		{
			Lenght_converter feets;
			feets.SetMeters(cnt_meters);
			feets.name = "feets";
			feets.coefficient = 3.28;
			feets.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
		case 3:
		{
			Lenght_converter arshins;
			arshins.SetMeters(cnt_meters);
			arshins.name = "arshins";
			arshins.coefficient = 1.41;
			arshins.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
		case 4:
		{
			Lenght_converter fathoms;
			fathoms.SetMeters(cnt_meters);
			fathoms.name = "fathoms";
			fathoms.coefficient = 0.47;
			fathoms.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
		case 5:
		{
			Lenght_converter yards;
			yards.SetMeters(cnt_meters);
			yards.name = "yards";
			yards.coefficient = 1.09;
			yards.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
		case 6:
		{
			Lenght_converter miles;
			miles.SetMeters(cnt_meters);
			miles.name = "miles";
			miles.coefficient = 0.00062;
			miles.Print();

			cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 0 to exit\n" << endl;
			cin >> choice;
			break;
		}
	
		default:
			break;
		}
	}
}


