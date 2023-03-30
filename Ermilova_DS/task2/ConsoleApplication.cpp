#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class dynamic_array
{
	int size;
	double* arr;
public:
	dynamic_array() {
		size = 0;
		arr = NULL;
	}
	dynamic_array(const dynamic_array& a) {
		size = a.size;
		if (size) {
			arr = new double[size];
			for (int i = 0; i < size; i++)
				arr[i] = a.arr[i];
		}
		else
			arr = NULL;
	}
	dynamic_array(int isize) {
		size = isize;
		if (size)
			arr = new double[size];
		else
			arr = NULL;
	}
	void resize(int nsize) {
		if (nsize != size) {
			double* temp = new double[nsize];
			double tsize = size;
			if (size > nsize)
				tsize = nsize;
			for (int i = 0; i < tsize; i++)
				temp[i] = arr[i];
			delete[] arr;
			size = nsize;
			arr = temp;
		}
	}
	int get_size() {
		return size;
	}

	void set_size(int size)
	{
		this->size = size;
		resize(size);
	}

	void out_put() {
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << "\n";
	}

	int array_size() {
		return size;
	}

	string input_index(int i, double value) {
		arr[i] = value;
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

	bool is_ordered() {
		bool a = true;
		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				a = false;
			}
		}
		return a;

	}


	dynamic_array subarray() {
		dynamic_array temp;
		if (size) {
			int tsize = size / 2;
			temp.size = tsize;
			temp.arr = new double[tsize];

			for (int i = 0; i < tsize; i++)
				temp.arr[i] = arr[1 + 2 * i];
		}
		return temp;
	}

	~dynamic_array() {
		if (size)
			delete[] arr;
	}
};


int main()
{
	int size, choice = 999;
	cout << "Enter the array size" << endl;
	cin >> size;

	dynamic_array a(size);
	a.set_size(size);


	while (choice != 0) {
		cout << "Press 1 to enter array size\nPress 2 to find out the size of the array\nPress 3 to set an array element by its index\nPress 4 to get array element by its index\nPress 5 to find the minimum element of the array\nPress 6 to check if the array is sorted\nPress 7 to extract from the array a subarray with elements at odd indices\nPress 8 to display the array\nPress 0 to exit\n" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Enter the array size" << endl;
			cin >> size;
			a.resize(size);
			break;
		}
		case 2:
		{
			cout << a.array_size() << "\n" << endl;
			break;
		}

		case 3:
		{
			int i;
			double value;
			cout << "Enter the element index" << endl;
			cin >> i;
			cout << "Write elements:";
			cin >> value;
			cout << a.input_index(i, value) << endl;
			break;
		}

		case 4:
		{
			int i;
			cout << "Enter the element index" << endl;
			cin >> i;
			cout << a.output_index(i) << "\n" << endl;
			break;
		}

		case 5:
		{
			cout << a.min_element() << "\n" << endl;
			break;
		}

		case 6:
		{
			cout << a.is_ordered() << "\n" << endl;
			break;
		}

		case 7:
		{
			a.subarray();
			break;
		}

		case 8:
		{
			a.out_put();
			break;
		}

		default:
			break;
		}
	}

	system("pause");
	return 0;
}