#include <iostream>
#include <cstdlib>

using namespace std;


class Matrix {

public:
	Matrix()
	{
		i = j = 2;
		k = g = 0;
		creating();
	}

	bool set_size(int new_i, int new_j) {

		if ((new_i != new_j) || (new_i > 8) || (new_i < 2))
		{
			cout << "Incorrect size." << endl;
			return false;
		}

		deleting(matr);
		i = new_i;
		j = new_j;
		creating();

		cout << "The size was successfully changed." << endl;
		return true;
	}

	void get_size() {

		cout << "Size of matrix: " << i << 'x' << j << endl;
	}

	bool change(int row, int col, int new_value) {

		row -= 1;
		col -= 1;

		if ((row >= 0 && row < i) && (col >= 0 && col < j))
		{
			matr[row][col] = new_value;

			cout << "The element was successfully changed." << endl;
			return true;
		}
		else
		{
			cout << "Invalid indexes." << endl;
			return false;
		}
	}

	int get_element(int row, int col) {

		row -= 1;
		col -= 1;

		if ((row >= 0 && row < i) && (col >= 0 && col < j))
		{
			cout << "Element(" << row + 1 << ", " << col + 1  << "): " << matr[row][col] << endl;
			return  matr[row][col];
		}
		else
		{
			cout << "Invalid indexes." << endl;
			return 0;
		}
	}

	bool diagonal_domination() {

		int sum;

		for (k = 0; k < i; k++)
		{
			sum = 0;
			for (g = 0; g < i; g++)
			{
				sum += matr[k][g];
			}

			if (abs(matr[k][k]) < abs(sum - matr[k][k]))
			{
				cout << "This matrix is not diagonally dominant." << endl;
				return false;
			}
		}
		cout << "This matrix is diagonally dominant." << endl;
		return true;
	}

	void sum_of_matrixes() {

		int** user_matr;
		user_matr = new int* [i];

		for (k = 0; k < i; k++)
		{
			user_matr[k] = new int[j];
		}

		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				cout << "Enter element(" << k + 1 << ", " << g + 1 << "): ";
				cin >> user_matr[k][g];

				if (!cin.good())
				{
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					cout << "Incorrect value." << endl;
					
					deleting(user_matr);
					return;
				}
			}
		}

		cout << "Sum of matrixes:" << endl;
		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				cout << matr[k][g] + user_matr[k][g] << "  ";
			}
			cout << endl;
		}
		deleting(user_matr);
	}

	void print() 
	{
		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				cout << matr[k][g] << "  ";
			}
			cout << endl;
		}
	}

	~Matrix() {

		deleting(matr);
	}

private:
	int i, j, k, g; //ћожно было обойтись и без переменной, отвечающей за количесвто столбцов (т.к. матрица квадратна€),
	int** matr;    //но € решил сделать с ней, чтобы класс мог работать не только с квадратными матрицами (если убрать контроль ввода)

	void deleting(int** matrix) {

		for (k = 0; k < i; k++)
		{
			delete[] matrix[k];
		}
		delete[] matrix;
	}

	void creating() {

		matr = new int* [i];

		for (k = 0; k < i; k++)
		{
			matr[k] = new int[j];
		}

		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				matr[k][g] = rand() % 10;
			}
		}
	}
};


void main()
{
	Matrix m;

	m.get_size();

	m.print();

	m.set_size(4, 4);

	m.get_size();

	m.print();

	m.change(1, 1, 30);
	m.change(2, 2, 12);
	m.change(3, 3, 45);
	m.change(4, 4, 22);

	m.print();

	m.get_element(3, 4);

	m.diagonal_domination();

	m.sum_of_matrixes();
}
