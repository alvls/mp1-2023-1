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
public:
	int N;
	int** matr;
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
	char* menuu[6] = { (char*)"1. ������ ������ �������", (char*)"2. ������ ������ �������", (char*)"3. ������ ������� ������� �� ��� ��������", (char*)"4. ������ ������� ������� �� ��� ��������", (char*)"5. ������������ ������������ �������", (char*)"6. �������� ���� ������" };
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
			cout << "������� ������ ������� ";
			int size;
			cin >> size;
			m.MatrixSize(size);
			m2.MatrixSize(size);
			m3.MatrixSize(size);
			m.matr = (int**) new int* [m.N];
			for (int i = 0; i < m.N; i++)
				m.matr[i] = (int*)new int[m.N];
			m2.matr = (int**) new int* [m.N];
			for (int i = 0; i < m.N; i++)
				m2.matr[i] = (int*)new int[m.N];
			m3.matr = (int**) new int* [m.N];
			for (int i = 0; i < m.N; i++)
				m3.matr[i] = (int*)new int[m.N];

			srand(time(NULL));
			for (int i = 0; i < m.N; i++)
				for (int j = 0; j < m.N; j++) {
					m.matr[i][j] = 1 + rand() % 100;
				}
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
			cout << "������ ������� = " << m.GetMatrixSize() << endl;
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			cout << "������� ������� ��������";
			int i, j, a;
			cin >> i >> j;
			cout << "������� ����� ";
			cin >> a;
			m.SetElement(i, j, a);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			cout << "������� i � j ��� ������ ��������";
			int i, j;
			cin >> i >> j;
			cout << m.GetElement(i, j) << endl;
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			if (m.Diagonal() == 0) cout << "�� �������� ������������ �������������" << endl;
			else cout << "������� � ������������ �������������" << endl;
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			int n = m.GetMatrixSize();
			cout << "����������� �������: ";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			cout << "������� �������� �������";
			int a = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cin >> a;
					m2.matr[i][j] = a;
				}
			}
			cout << endl;
			cout << "���� �������: ";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (j % n == 0) cout << endl;
					cout << m2.PrintMatr(i, j) << " ";
				}
			}
			cout << endl;
			m3.SummTwoMatrix(m, m2);
			cout << "���������: ";
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