#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;


class Matrix {

public:
	Matrix(int n, int m) : n(n), m(m) { //¬место: this->i = i;
	
		values_control(n, m);
		creating();
	}

	Matrix(const Matrix& source) : n(source.n), m(source.m) {

		matr = new int[n * m];
		copy(source.matr, &source.matr[n * m], matr);
	}

	Matrix operator +(const Matrix& plus) const {

		if (n != plus.n || m != plus.m)
		{
			throw invalid_argument("invalid values");
		}

		Matrix result(n, m);

		for (int k = 0; k < (result.n * result.m); k++)
		{
			result.matr[k] = matr[k] + plus.matr[k];
		}

		return result;
	}

	bool set_size(int new_n, int new_m) {

		values_control(new_n, new_m);

		delete[] matr;
		n = new_n;
		m = new_m;
		creating();

		return true;
	}

	pair<int, int> get_size() const {

		return pair<int, int>(n, m);
	}

	bool change_element(int i, int j, int new_value) {

		indexes_control(i, j);
		matr[(i - 1) * m + j - 1] = new_value;
		
		return true;
	}

	int get_element(int i, int j) const {

		indexes_control(i, j);
		return matr[(i - 1) * j + j - 1];
	}

	bool diagonal_domination() {

		int k = 1, sum = 0, diagonal = 0;
		int size = n * m;

		for (k = 1; k <= size; k++)
		{
			sum += matr[k - 1];
			if (k % m == 0)
			{
				if (abs(matr[diagonal]) < abs(sum - matr[diagonal]))
				{
					return false;
				}
				
				diagonal += n + 1;
				sum = 0;
			}
		}

		return true;
	}

	friend ostream& operator <<(ostream& stream, Matrix& matrix) {

		stream << "Size: " << matrix.n << "x" << matrix.m << endl;
		stream << "Diagonal domination(1 - true, 0 - false): " << matrix.diagonal_domination() << endl;
		stream << "Matrix:" << endl;

		int k, size = matrix.n * matrix.m;
		for (k = 1; k <= size; k++)
		{
			stream << matrix.matr[k - 1] << "  ";
			if (k % matrix.m == 0)
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
	int n, m;   //ћожно было обойтись и без переменной, отвечающей за количесвто столбцов (т.к. матрица квадратна€),
	int* matr; //но € решил сделать с ней, чтобы класс мог работать не только с квадратными матрицами (если убрать контроль ввода)

	void creating() {

		matr = new int[n * m];

		int size = n * m;
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

	void indexes_control(int i, int j) const {

		if (i < 1 || i > n || j < 1 || j > m)
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
