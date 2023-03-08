#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;

class dynamic_array
{
public:
	int size;
	double *arr;

	void Create_arr() {
		srand(time(NULL));
		arr = new double[size];
		for (int i = 0; i < size; i++)
			arr[i] = (rand() % 100) ;
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

	void array_size() {
		cout << "Array size:" << size;
		cout << "\n";
	}

	void input_index(int i) {
		cout << "Write elements:\n";
		cin >> arr[i];
		cout << "\n";
	}

	void output_index(int i) {
		cout << arr[i];
		cout << "\n";
	}

	void min_element() {
		double min = arr[0];
		for (int i = 0; i < size - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				min = arr[i + 1];
			}
		}
		cout << "Minimum array element: " << min << endl;
		cout << "\n";
	}

	void is_ordered() {
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
		cout << answer << endl;
		cout << "\n";
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
	int size, choice;
	cout << "Enter the array size" << endl;
	cin >> size;

	dynamic_array a;
	a.SetSize(size);

	cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
	cin >> choice;

	while (choice != 0) {
		switch (choice)
		{
		case 1:
		{
			a.array_size();
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 2:
		{
			int i;
			cout << "Enter the element index" << endl;
			cin >> i;
			a.input_index(i);
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 3:
		{
			int i;
			cout << "Enter the element index" << endl;
			cin >> i;
			a.output_index(i);
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 4:
		{
			a.min_element();
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 5:
		{
			a.is_ordered();
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 6:
		{	
			a.subarray();
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}

		case 7:
		{
			a.output();
			cout << "Press 1 to find out the size of the array\nPress 2 to set an array element by its index\nPress 3 to get array element by its index\nPress 4 to find the minimum element of the array\nPress 5 to check if the array is sorted\nPress 6 to extract from the array a subarray with elements at odd indices\nPress 7 to display the array\n" << endl;
			cin >> choice;
			break;
		}
		}
	}

	system("pause");
	return 0;
}