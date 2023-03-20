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
	Matrix(const Matrix& MM)
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
		cout << "������� �������:"<< endl;
		for (int i = 0;i < size;i++)
		{
			for (int j = 0;j < size;j++)
				cout << setw(4) << left << mt[i][j];
			cout << endl;
		}
	}
	 int GetSize()
	{
		 return size;
	}
	 void SetElement(int i, int j, int n)
	 {
		 mt[i][j] = n;
	 }
	int GetElement(int i, int j)
	{
		return mt[i][j];
	}
	bool PossibleIndex(int i, int j)
	{
		if ((i >= 0) && (i < size) && (j >= 0) && (j < size))
			return true;
		return false;
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
	void SumMatrix(const Matrix& m1, const Matrix& m2)
	{
		for (int i = 0;i < size;i++)
			for (int j = 0;j < size;j++)
				mt[i][j] = m1.mt[i][j] + m2.mt[i][j];
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
	int operation, n, t, i, j, el;
	cout << "������� ������ �������� �������: ";
	cin >> n;
	m1 = new Matrix(n);
	while(1)
	{
		system("cls");
		cout << "�������� ��������:\n1) �������� ������ �������\n2) ������ ������ �������\n3) ������ ������� ������� �� ��� ��������\n4) ������ ������� ������� �� ��� ��������\n5) ��������� �������� ������������� ������������\n6) ��������� ����� ���� ������\n7) ������� ������� ������� �� �����\n";
		cin >> operation;
		system("cls");
		switch (operation)
		{
		case 1:
			delete m1;
			cout << "������� ����� ������ �������: ";
			cin >> n;
			m1 = new Matrix(n);
			break;
		case 2:
			n = m1->GetSize();
			cout << "������ �������: " << n << endl;
			break;
		case 3:
			cout << "������� ����� ������: ";
			cin >> i;
			cout << "������� ����� �������: ";
			cin >> j;
			if (m1->PossibleIndex(i, j))

			{
				cout << "������� ����� �������� ��������: ";
				cin >> el;
				m1->SetElement(i, j, el);
				system("cls");
				cout << "����� �������� ������" << endl;
			}
			else
				cout << "������������ �����" << endl;
			break;
		case 4:
			cout << "������� ����� ������: ";
			cin >> i;
			cout << "������� ����� �������: ";
			cin >> j;
			if (m1->PossibleIndex(i, j))
			{
				el = m1->GetElement(i, j);
				cout << "�������� �������� � ��������� ���������: " << el << endl;
			}
			else
				cout << "������������ ������ ��������" << endl;
			break;
		case 5:
			if (m1->Diagonal())
				cout << "������� �������� ������������ �������������" << endl;
			else
				cout << "������� �� �������� ������������ �������������" << endl;
			break;
		case 6:
			m2 = new Matrix(n);
			m3 = new Matrix(n);
			cout << "������� �������� ������ �������-����������:" << endl;
			for (i = 0;i < n;i++)
			{
				for (j = 0;j < n;j++)
				{
					cout << "������� ����� �������� �������� m[" << i << "][" << j << "]: ";
					cin >> el;
					m2->SetElement(i, j, el);
					system("cls");
				}
			}
			cout << "����� �������� ������" << endl;
			system("cls");
			m3->SumMatrix(*m1, *m2);
			cout << "��������� �������� ������:" << endl;
			m3->PrintMatr();
			delete m2;
			delete m3;
			break;
		case 7:
			m1->PrintMatr();
			break;
		default:
			break;
		}
		cout << endl << "0 - ���������" << endl << "1 - ��������� � ������ ��������" << endl;
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
	system("cls");
	system("pause");
	return 0;
}