#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <io.h>

using namespace std;

#define KEY_EXIT 27
#define KEY_ENTER 13
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_UP 72
#define KEY_ARROW_DOWN 80

int menu(char* menu[], int j) {
	CONSOLE_CURSOR_INFO structCursorInfo;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	SetConsoleTextAttribute(hStdOut, COLOR_BACKGROUND);
	int key = 0;
	int code = 0;
	COORD cursor;
	do {
		system("cls");
		if (code == KEY_ARROW_UP) key--;
		if (code == KEY_ARROW_DOWN) key++;
		if (key < 0) key = j - 1;
		if (key > j - 1) key = 0;
		SetConsoleTextAttribute(hStdOut, 9);
		for (int i = 0; i < j; i++) {
			cout << menu[i] << endl;
		}
		SetConsoleTextAttribute(hStdOut, 11);
		cursor.Y = key;
		cursor.X = 0;
		SetConsoleCursorPosition(hStdOut, cursor);
		cout << menu[key];
		if ((code = _getch()) == KEY_EXIT) {
			key = KEY_EXIT;
			break;
		}
	} while ((code = _getch()) != KEY_ENTER);
	return key;
}

class Matrix {
	int N;
	int** matr;
public:
	Matrix() {
		N = 0;
		matr = nullptr;
	}
	void MatrixSize(int size) {
		N = size;
	}
	int GetMatrixSize() {
		return N;
	}
	int GetElement(int i, int j) {
		return matr[i][j];
	}
	void SetElement(int i, int j, int a) {
		if ((i < 0) || (i >= N))
			return;
		if ((j < 0) || (j >= N))
			return;
		matr[i][j] = a;
	}
	bool Diagonal() {
		int sum = 0;
		int flag = 1;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (i != j) sum += matr[i][j];
			}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (abs(matr[i][i]) >= sum)
					flag = 1;
				else {
					return false;
					break;
				}
			} break;
		}
		if (flag) return true;
	}
	void firstMatrix() {
		matr = (int**) new int* [N];
		for (int i = 0; i < N; i++)
			matr[i] = (int*)new int[N];

		srand(time(NULL));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				matr[i][j] = 1 + rand() % 100;
			}
	}
	void secondMatrix(int a, int i, int j) {
		matr[i][j] = a;
	}
	int PrintMatr(int i, int j) {
		return matr[i][j];
	}
	Matrix SummTwoMatrix(Matrix& m1, Matrix& m2){
		Matrix m3;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				matr[i][j] = m1.matr[i][j] + m2.matr[i][j];
			}
		return m3;
	}
	~Matrix()
	{
		if (N > 0) {
			for (int i = 0; i < N; i++)
				delete[] matr[i];
		}
		delete[] matr;
	}
};

void main() {
	system("cls");
	char* menuu[6] = { (char*)"1. Задать размер матрицы", (char*)"2. Узнать размер матрицы", (char*)"3. Задать элемент матрицы по его индексам", (char*)"4. Узнать элемент матрицы по его индексам", (char*)"5. Диагональное преобладание матрицы", (char*)"6. Сложение двух матриц" };
	setlocale(LC_ALL, "Rus");
	Matrix m;
	Matrix m2;
	Matrix m3;
	int chose = 0;
	while (chose != KEY_EXIT) {
		chose = menu(menuu, 6);
		switch (chose) {
		case 0: {
			system("cls");
			cout << "Введите размер матрицы ";
			int size;
			cin >> size;
			m.MatrixSize(size);
			m2.MatrixSize(size);
			m3.MatrixSize(size);
			m.firstMatrix();
			m2.firstMatrix();
			m3.firstMatrix();
			int n = m.GetMatrixSize();
			
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			
			system("pause");
			break;
		}
		case 1: {
			system("cls");
			cout << "Размер матрицы = " << m.GetMatrixSize() << endl;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			cout << "Введите индексы элемента";
			int i, j, a;
			cin >> i >> j;
			cout << "Введите число ";
			cin >> a;
			m.SetElement(i, j, a);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			cout << "Введите i и j для поиска элемента";
			int i, j;
			cin >> i >> j;
			cout << m.GetElement(i, j) << endl;
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			if (m.Diagonal() == 0) cout << "Не обладает диагональным преобладанием" << endl;
			else cout << "Матрица с диагональным преобладанием" << endl;
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			int n = m.GetMatrixSize();
			cout << "Изначальная матрица: ";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			cout << "Введите значения матрицы";
			int a = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cin >> a;
					m2.secondMatrix(a, i, j);
				}
			}
			cout << endl;
			cout << "Ваша матрица: ";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m2.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			m3.SummTwoMatrix(m, m2);
			cout << "Результат: ";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m3.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			system("pause");
			break;
		}

		}
	}
}