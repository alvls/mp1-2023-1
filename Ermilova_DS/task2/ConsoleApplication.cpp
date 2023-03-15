#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class dynamic_array
{

	int size;
	double* arr;

public:
	void Create_arr() {
		srand(time(NULL));
		arr = new double[size];
		for (int i = 0; i < size; i++)
			arr[i] = (rand() % 100);
	}

	dynamic_array() : size(4) { Create_arr(); }
	dynamic_array(int size) : size(size) { Create_arr(); };

	~dynamic_array() {
		delete[] arr;
	}

	void SetSize(int size)
	{
		this->size = size;
	}

	void output() {
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int array_size() {
		return size;
	}

	string input_index(int i) {
		cout << "Write elements:";
		cin >> arr[i];
		return "\n";
	}

	double output_index(int i) {
		return arr[i];
	}

	double min_element() {
		double min = arr[0];
		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				min = arr[i + 1];
			}
		}
		return min;
	}

	string is_ordered() {
		string answer;
		bool a = true;
		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				a = false;
			}
		}
		if (a == false) {
			answer = "Array is not ordered";
		}
		else
		{
			answer = "Array is ordered";
		}
		return answer;

	}

	void DeleteElement(double* a, int j, int size)
	{
		for (int i = j; i < size - 1; i++)
		{
			a[i] = a[i + 1];
		}
	}

	void subarray() {
		int k = 0;
		for (int i = 0; i < size; i++)
		{
			if (i % 2 == 0)
			{
				DeleteElement(arr, i - k, size);
				k++;
			}
		}
		for (int i = 0; i < size - k; i++)
		{
			cout << arr[i] << " ";
		}
		size = size - k;
		cout << "\n";
	}
};


int main()
{
	int size, choice = 999;
	cout << "Enter the array size" << endl;
	cin >> size;

	dynamic_array a;
	a.SetSize(size);

	while (choice != 0) {
		cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\nPress 0 to exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << a.array_size() << "\n" << endl;
			break;
		}

		case 2:
		{
			int i;
			cout << "Enter the element index" << endl;
			cin >> i;
			cout << a.input_index(i) << endl;

			break;
		}

		case 3:
		{
			int i;
			cout << "Enter the element index" << endl;
			cin >> i;
			cout << a.output_index(i) << "\n" << endl;

			break;
		}

		case 4:
		{
			cout << a.min_element() << "\n" << endl;
			break;
		}

		case 5:
		{
			cout << a.is_ordered() << "\n" << endl;
			break;
		}

		case 6:
		{
			a.subarray();
			break;
		}

		case 7:
		{
			a.output();
			break;
		}
		default:
			break;
		}
	}

	system("pause");
	return 0;
}