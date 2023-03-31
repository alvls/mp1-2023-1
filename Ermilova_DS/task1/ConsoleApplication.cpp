#include <iostream>
#include <string>

using namespace std;

class Lenght_converter
{
	double meters = 0;

public:
	Lenght_converter()
	{
	}

	void SetMeters(double meters)
	{
		this->meters = meters;
	}

	double GetMeters()
	{
		return meters;
	}

	double GetFeets()
	{
		return meters * 3.28;
	}

	double GetArshins()
	{
		return meters * 1.41;
	}

	double GetFathoms()
	{
		return meters * 0.47;
	}

	double GetYards()
	{
		return meters * 1.09;
	}

	double GetMiles()
	{
		return meters * 0.00062;
	}
	void PrintAll()
	{
		cout << meters << " meters" << "\n";
		cout << meters * 3.28 << " feets" << "\n";
		cout << meters * 2.41 << " arshins" << "\n";
		cout << meters * 0.47 << " fathoms" << "\n";
		cout << meters * 1.09 << " yards" << "\n";
		cout << meters * 0.00062 << " miles" << "\n";

	}
};

int main()
{
	Lenght_converter user;
	int choice = 10000;
	double cnt_meters;
	cout << "Enter the number of meters" << endl;
	cin >> cnt_meters;
	user.SetMeters(cnt_meters);


	while (choice != 0) {
		cout << "Press 1 to display the number of meters\nPress 2 to convert meters to feet\nPress 3 to convert meters to arshins\nPress 4 to convert meters to fathoms\nPress 5 to convert meters to yards\nPress 6 to convert meters to miles\nPress 7 to display all values\nPress 0 to exit\n" << endl;
		cin >> choice;

		switch (choice)
		{

		case 1:
		{
			cout << user.GetMeters() << "\n";
			break;
		}
		case 2:
		{
			cout << user.GetFeets() << "\n";
			break;
		}
		case 3:
		{
			cout << user.GetArshins() << "\n";
			break;
		}
		case 4:
		{
			cout << user.GetFathoms() << "\n";
			break;
		}
		case 5:
		{
			cout << user.GetYards() << "\n";
			break;
		}
		case 6:
		{
			cout << user.GetMiles() << "\n";
			break;
		}
		case 7:
		{
			user.PrintAll();
			cout << "\n";
			break;
		}

		default:
			break;
		}
	}
}

