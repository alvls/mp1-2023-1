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
	int** matr2;
	int** matr3;
public:
	Matrix() {
		N = 0;
		matr = NULL;
		matr2 = NULL;
		matr3 = NULL;
	}
	void MatrixSize() {
		cin >> N;
	}
	int GetMatrixSize() {
		return N;
	}
	int GetElement() {
		int i, j;
		cin >> i >> j;
		return matr[i][j];
	}
	void SetElement() {
		int i, j;
		cin >> i >> j;
		if ((i < 0) || (i >= N))
			return;
		if ((j < 0) || (j >= N))
			return;
		cin >> matr[i][j];
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
				if (j % N == 0) cout << endl;
				cout << matr[i][j] << " ";
			}
	}
	void SummTwoMatrix() {
		int** matr2 = (int**) new int* [N];
		for (int i = 0; i < N; i++)
			matr2[i] = (int*)new int[N];

		cout << "Введите значения матрицы" << endl;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				cin >> matr2[i][j];
			}
		cout << "Ваша матрица выглядит так: ";
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (j % N == 0) cout << endl;
				cout << matr2[i][j] << " ";
			}
		cout << endl;
		cout << "Изначальная матрица: ";
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				if (j % N == 0) cout << endl;
				cout << matr[i][j] << " ";
			}
		cout << endl;

		int** matr3 = (int**) new int* [N];
		for (int i = 0; i < N; i++)
			matr3[i] = (int*)new int[N];
		cout << "Результат: ";
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				matr3[i][j] = matr[i][j] + matr2[i][j];
				if (j % N == 0) cout << endl;
				cout << matr3[i][j] << " ";
			}

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
	int chose = 0;

	while (chose != KEY_EXIT) {
		chose = menu(menuu, 6);
		switch (chose) {
		case 0: {
			system("cls");
			cout << "Введите размер матрицы ";
			m.MatrixSize();
			m.firstMatrix();
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
			m.SetElement();
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			cout << "Введите i и j для поиска элемента";
			cout << m.GetElement() << endl;
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
			m.SummTwoMatrix();
			system("pause");
			break;
		}

		}
	}
}