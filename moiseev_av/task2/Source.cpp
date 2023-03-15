#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Matrix {

public:
	Matrix(int i, int j) : i(i), j(j) { //¬место: this->i = i;
	
		values_control(i, j);
		creating();
	}

	Matrix(const Matrix& source) : i(source.i), j(source.j) {

		matr = new int[i * j];
		copy(source.matr, &source.matr[i * j], matr);
	}

	Matrix operator +(const Matrix& plus) const {

		if (i != plus.i || j != plus.j)
		{
			throw invalid_argument("invalid values");
		}

		Matrix result(i, j);

		for (int k = 0; k < (result.i * result.j); k++)
		{
			result.matr[k] = matr[k] + plus.matr[k];
		}

		return result;
	}

	bool set_size(int new_i, int new_j) {

		values_control(new_i, new_j);

		delete[] matr;
		i = new_i;
		j = new_j;
		creating();

		return true;
	}

	pair<int, int> get_size() const {

		return pair<int, int>(i, j);
	}

	bool change_element(int row, int col, int new_value) {

		indexes_control(row, col);
		matr[(row - 1) * j + col - 1] = new_value;
		
		return true;
	}

	int get_element(int row, int col) const {

		indexes_control(row, col);
		return matr[(row - 1) * j + col - 1];
	}

	bool diagonal_domination() {

		int k = 1, sum = 0, diagonal = 0;
		int size = i * j;

		for (k = 1; k <= size; k++)
		{
			sum += matr[k - 1];
			if (k % j == 0)
			{
				if (abs(matr[diagonal]) < abs(sum - matr[diagonal]))
				{
					return false;
				}
				
				diagonal += i + 1;
				sum = 0;
			}
		}

		return true;
	}

	friend ostream& operator <<(ostream& stream, Matrix& matrix) {

		stream << "Size: " << matrix.i << "x" << matrix.j << endl;
		stream << "Diagonal domination(1 - true, 0 - false): " << matrix.diagonal_domination() << endl;
		stream << "Matrix:" << endl;

		int k, size = matrix.i * matrix.j;
		for (k = 1; k <= size; k++)
		{
			stream << matrix.matr[k - 1] << "  ";
			if (k % matrix.j == 0)
			{
				stream << endl;
			}
		}

		return stream;
	}

	~Matrix() {

		delete[] matr;
	}

private:
	int i, j;   //ћожно было обойтись и без переменной, отвечающей за количесвто столбцов (т.к. матрица квадратна€),
	int* matr; //но € решил сделать с ней, чтобы класс мог работать не только с квадратными матрицами (если убрать контроль ввода)

	void creating() {

		matr = new int[i * j];

		int size = i * j;
		for (int k = 0; k < size; k++)
		{
			matr[k] = rand() % 10;
		}
	}

	void values_control(int i, int j) const {

		if (i != j || i < 2 || j < 2 || i > 8 || j > 8)
		{
			throw invalid_argument("invalid values");
		}
	}

	void indexes_control(int row, int col) const {

		if (row < 1 || row > i || col < 1 || col > j)
		{
			throw invalid_argument("invalid indexes");
		}
	}
};


int main()
{
	Matrix m1(2, 2);
	
	m1.set_size(4, 4);
	m1.change_element(1, 1, 22);
	m1.change_element(2, 2, 30);
	m1.change_element(3, 3, 12);
	m1.change_element(4, 4, 15);

	Matrix m2(m1);

	Matrix m3 = m1 + m2 + m2;

	cout << m1 << endl <<  m2 << endl << m3 << endl;

	cout << m2.get_element(1, 4) << endl;

	return EXIT_SUCCESS;
}
