#include <iostream>
#include <cstdlib>
#include <string>

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
			printConsole("Incorrect size.\n");
			return false;
		}

		deleting(matr);
		i = new_i;
		j = new_j;
		creating();

		printConsole("The size was successfully changed.\n");
		return true;
	}

	void get_size() {

		printConsole("Size of matrix: " + to_string(i) + 'x' + to_string(j) + "\n");
	}

	bool change(int row, int col, int new_value) {

		row -= 1;
		col -= 1;

		if ((row >= 0 && row < i) && (col >= 0 && col < j))
		{
			matr[row][col] = new_value;

			printConsole("The element was successfully changed.\n");
			return true;
		}
		else
		{
			printConsole("Invalid indexes.\n");
			return false;
		}
	}

	int get_element(int row, int col) {

		row -= 1;
		col -= 1;

		if ((row >= 0 && row < i) && (col >= 0 && col < j))
		{
			printConsole("Element(" + to_string(row + 1) + ", " + to_string(col + 1) + "): " + to_string(matr[row][col]) + "\n");
			return  matr[row][col];
		}
		else
		{
			printConsole("Invalid indexes.\n");
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
				printConsole("This matrix is not diagonally dominant.\n");
				return false;
			}
		}
		printConsole("This matrix is diagonally dominant.\n");
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
				printConsole("Enter element(" + to_string(k + 1) + ", " + to_string(g + 1) + "): ");
				cin >> user_matr[k][g];

				if (!cin.good())
				{
					cin.clear();
					cin.ignore(cin.rdbuf()->in_avail());
					printConsole("Incorrect value.\n");
					
					deleting(user_matr);
					return;
				}
			}
		}

		printConsole("Sum of matrixes:\n");
		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				printConsole(to_string(matr[k][g] + user_matr[k][g]) + "  ");
			}

			printConsole("\n");
		}
		deleting(user_matr);
	}

	void print() 
	{
		for (k = 0; k < i; k++)
		{
			for (g = 0; g < j; g++)
			{
				printConsole(to_string(matr[k][g]) + "  ");
			}

			printConsole("\n");
		}
	}

	~Matrix() {

		deleting(matr);
	}

private:
	int i, j, k, g; //ћожно было обойтись и без переменной, отвечающей за количесвто столбцов (т.к. матрица квадратна€),
	int** matr;    //но € решил сделать с ней, чтобы класс мог работать не только с квадратными матрицами (если убрать контроль ввода)

	void printConsole(string line) {

		cout << line;
	}

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
