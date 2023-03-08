#include <iostream>
#include <locale>
#include <iomanip>
#include <cmath>
using namespace std;
class Matrix
{
private:
	int** mt;
	int size;
public:
	Matrix()
	{
		size = 0;
		mt = nullptr;
	}
	Matrix(int n)
	{
		size = n;
		mt = new int* [size];
		for (int i = 0;i < size;i++)
		{
			mt[i] = new int [size];
			for (int j = 0;j < size;j++)
				mt[i][j] = 0;
		}
	}
	Matrix(Matrix& MM)
	{
		size = MM.size;
		mt = new int* [size];
		for (int i = 0;i < size;i++)
			mt[i] = new int[size];
		for (int i = 0;i < size;i++)
			for (int j = 0;j < size;j++)
				mt[i][j] = MM.mt[i][j];
	}
	void PrintMatr()
	{
		cout << "Текущая матрица:"<< endl;
		for (int i = 0;i < size;i++)
		{
			for (int j = 0;j < size;j++)
				cout << setw(4) << left << mt[i][j];
			cout << endl;
		}
	}
	void GetSize()
	{
		cout << "Размер матрицы: " << size << endl;
	}
	void AskElement(int option)
	{
		int i, j, n;
		if (option == 1)
		{
			cout << "Введите номер строки 0 - " << size - 1 << ": ";
			cin >> i;
			cout << "Введите номер столбца 0 - " << size - 1 << ": ";
			cin >> j;
			if ((i >= 1) && (i <= size) && (j >= 1) && (j <= size))
			{
				cout << "Введите новое значение элемента: ";
				cin >> n;
				mt[i][j] = n;
				system("cls");
				cout << "Новое значение задано" << endl;
			}
			else
				cout << "Некорректный номер" << endl;
		}
		else if (option == 2)
		{
			for (i = 0;i < size;i++)
			{
				for (j = 0;j < size;j++)
				{
					cout << "Введите новое значение элемента m[" << i << "][" << j << "]: ";
					cin >> n;
					mt[i][j] = n;
					system("cls");
				}
			}
			cout << "Новые значения заданы" << endl;
		}
		else
			cout << "Выбран недопустимый вариант" << endl;
	}
	void GetElement()
	{
		int i, j;
		cout << "Введите номер строки 0 - " << size - 1 << ": ";
		cin >> i;
		cout << "Введите номер столбца 0 - " << size - 1 << ": ";
		cin >> j;
		if ((i >= 1) && (i <= size) && (j >= 1) && (j <= size))
			cout << "Значение элемента с заданными индексами: " << mt[i][j] << endl;;
	}
	bool Diagonal()
	{
		int s = 0;
		for (int i = 0;i < size;i++)
		{
			for (int j = 0;j < size;j++)
				if (j != i)
					s += mt[i][j];
			if (fabs(mt[i][i]) < fabs(s))
				return false;
		}
		return true;
	}
	void SumMatrix(const Matrix& m)
	{
		for (int i = 0;i < size;i++)
			for (int j = 0;j < size;j++)
				mt[i][j] += m.mt[i][j];
	}
	~Matrix()
	{
		for (int i = 0;i < size;i++)
			delete[] mt[i];
		delete[] mt;
	}
};
void Options()
{
	Matrix *m1, *m2, *m3;
	int operation, option, n, t;
	cout << "Задайте размер исходной матрицы: ";
	cin >> n;
	m1 = new Matrix(n);
	while(1)
	{
		system("cls");
		cout << "Выберете операцию:\n1) изменить размер матрицы\n2) узнать размер матрицы\n3) задать элемент матрицы по его индексам\n4) узнать элемент матрицы по его индексам\n5) проверить свойство диагонального преобладания\n6) вычислить сумму двух матриц\n7) вывести текущую матрицу на экран\n";
		cin >> operation;
		system("cls");
		switch (operation)
		{
		case 1:
			delete m1;
			cout << "Задайте новый размер матрицы: ";
			cin >> n;
			m1 = new Matrix(n);
			break;
		case 2:
			m1->GetSize();
			break;
		case 3:
			cout << "1) задать один элемент\n2) задать все элементы матрицы" << endl;
			cin >> option;
			system("cls");
			m1->AskElement(option);
			break;
		case 4:
			m1->GetElement();
			break;
		case 5:
			if (m1->Diagonal())
				cout << "Матрица обладает диагональным преобладанием" << endl;
			else
				cout << "Матрица не обладает диагональным преобладанием" << endl;
			break;
		case 6:
			m2 = new Matrix(n);
			cout << "Введите элементы второй матрицы-слагаемого:" << endl;
			m2->AskElement(2);
			system("cls");
			m2->SumMatrix(*m1);
			cout << "Результат сложения матриц:" << endl;
			m2->PrintMatr();
			delete m2;
			break;
		case 7:
			m1->PrintMatr();
			break;
		default:
			break;
		}
		cout << endl << "0 - завершить" << endl << "1 - вернуться к выбору операции" << endl;
		cin >> t;
		if (t != 1)
			break;
	}
	delete m1;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	Options();
	system("pause");
	return 0;
}