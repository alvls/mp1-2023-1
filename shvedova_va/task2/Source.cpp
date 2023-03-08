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
		cout << "������� �������:"<< endl;
		for (int i = 0;i < size;i++)
		{
			for (int j = 0;j < size;j++)
				cout << setw(4) << left << mt[i][j];
			cout << endl;
		}
	}
	void GetSize()
	{
		cout << "������ �������: " << size << endl;
	}
	void AskElement(int option)
	{
		int i, j, n;
		if (option == 1)
		{
			cout << "������� ����� ������ 0 - " << size - 1 << ": ";
			cin >> i;
			cout << "������� ����� ������� 0 - " << size - 1 << ": ";
			cin >> j;
			if ((i >= 1) && (i <= size) && (j >= 1) && (j <= size))
			{
				cout << "������� ����� �������� ��������: ";
				cin >> n;
				mt[i][j] = n;
				system("cls");
				cout << "����� �������� ������" << endl;
			}
			else
				cout << "������������ �����" << endl;
		}
		else if (option == 2)
		{
			for (i = 0;i < size;i++)
			{
				for (j = 0;j < size;j++)
				{
					cout << "������� ����� �������� �������� m[" << i << "][" << j << "]: ";
					cin >> n;
					mt[i][j] = n;
					system("cls");
				}
			}
			cout << "����� �������� ������" << endl;
		}
		else
			cout << "������ ������������ �������" << endl;
	}
	void GetElement()
	{
		int i, j;
		cout << "������� ����� ������ 0 - " << size - 1 << ": ";
		cin >> i;
		cout << "������� ����� ������� 0 - " << size - 1 << ": ";
		cin >> j;
		if ((i >= 1) && (i <= size) && (j >= 1) && (j <= size))
			cout << "�������� �������� � ��������� ���������: " << mt[i][j] << endl;;
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
			m1->GetSize();
			break;
		case 3:
			cout << "1) ������ ���� �������\n2) ������ ��� �������� �������" << endl;
			cin >> option;
			system("cls");
			m1->AskElement(option);
			break;
		case 4:
			m1->GetElement();
			break;
		case 5:
			if (m1->Diagonal())
				cout << "������� �������� ������������ �������������" << endl;
			else
				cout << "������� �� �������� ������������ �������������" << endl;
			break;
		case 6:
			m2 = new Matrix(n);
			cout << "������� �������� ������ �������-����������:" << endl;
			m2->AskElement(2);
			system("cls");
			m2->SumMatrix(*m1);
			cout << "��������� �������� ������:" << endl;
			m2->PrintMatr();
			delete m2;
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
	system("pause");
	return 0;
}