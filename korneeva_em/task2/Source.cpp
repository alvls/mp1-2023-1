#include <iostream>
#include <math.h>

using namespace std;

const int MAX_SIZE = 20;
const int MIN_SIZE = 1;

inline void validate_vector_size(int size)
{
	if (size < MIN_SIZE || size > MAX_SIZE)
	{
		throw std::invalid_argument("��������� ������ ������� �� ������������� ����������� ��������� (�� 1 �� 20)");
	}
}

inline void validate_vector_component(int size, int index)
{
	if (index < MIN_SIZE || index > size)
	{
		throw std::invalid_argument("��������� ����� ���������� �����������");
	}
}

class Vector
{
private:
	int* arr;
	int size;
public:
	Vector(int size) // �����������
	{
		validate_vector_size(size);
	
		this->size = size;
		arr = new int[size]();

	}
	
	Vector::~Vector() // ����������
	{
		delete[] arr;
	}


	Vector& operator=(const Vector& vec) // �������� ������������
	{
		if (this == &vec)
			return *this;

		if (size != vec.size)
		{
			delete[] arr;
			arr = new int[vec.size];
		}

		size = vec.size;

		for (int i = 0; i < size; i++)
			arr[i] = vec.arr[i];
	}

	Vector(const Vector& vec) // ����������� �����������
	{

		arr = new int[vec.size];
		size = vec.size;

		for (int i = 0; i < size; i++)
			arr[i] = vec.arr[i];
	}

	void Print() // ����� �� �������
	{
		cout << "������ �������: " << size << endl << "���������� �������: ";

		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}

		cout << endl;
	}

	void ChangeSize(int new_size) // ������ ������� �������
	{
		validate_vector_size(new_size);

		if (new_size == size)
			return;

		else 
		{
			int* new_arr = new int[new_size]();
			std::copy(arr, &arr[std::min(size, new_size)], new_arr);

			delete[] arr;
			arr = new_arr;

			size = new_size;

		}
	}

	int GetSize() // ��������� ������� �������
	{
		return size;
	}

	void SetComponent(int index, int component) // ��������� ���������� ������� �� � ������
	{
		validate_vector_component(size, index);

		arr[--index] = component;
	}

	int GetComponent(int index) // ��������� ���������� ������� �� � ������
	{
		validate_vector_component(size, index);

		return arr[--index];
	}

	float Length() // ������ ����� �������
	{
		int sum = 0;

		for (int i = 0; i < size; i++)
		{
			sum += arr[i] * arr[i];
		}

		return sqrt(sum);
	}


	int ScalarProduct(const Vector& vec) // ������ ���������� ������������ ���� ��������
	{
		if (size != vec.size)
		{
			throw std::invalid_argument("���������� ��������� ��������� ������������ ���� �������� ������� �������");
		}

		int scalar = 0;

		for (int i = 0; i < size; i++)
			scalar += arr[i] * vec.arr[i];

		return scalar;
	}

	Vector Sum(const Vector& vec) // ������ ����� ���� �������� ������ �������
	{
		if (size != vec.size)
		{
			throw std::invalid_argument("���������� ��������� ����� ���� �������� ������� �������");
		}

		Vector vec_sum(size);

		for (int i = 0; i < size; i++)
			vec_sum.arr[i]= arr[i] + vec.arr[i];

		return vec_sum;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int size1 = 4;
	Vector vec1(size1);

	vec1.SetComponent(1, 4);
	vec1.SetComponent(2, 6);
	vec1.SetComponent(3, 2);
	vec1.SetComponent(4, 1);

	int size2 = 4;
	Vector vec2(size2);

	vec2.SetComponent(1, 7);
	vec2.SetComponent(2, 3);
	vec2.SetComponent(3, 4);
	vec2.SetComponent(4, 2);
	

	cout <<"������ ������" << endl;
	vec1.Print();

	cout << endl << "������ ������" << endl;
	vec2.Print();


	vec1.ChangeSize(7);
	cout << endl << "1) ��������� ������� ������� �������:" << endl;
	vec1.Print();
	vec1.ChangeSize(4);

	cout << endl << "2) ������ ������ ������� �������: " << vec1.GetSize() << endl;

	vec1.GetComponent(2);
	cout << endl << "3) �������� ���������� ������� ������� �� � ������ (����� = 2): " << vec1.GetComponent(2) << endl;

	cout << endl << "4) ���������� ����� ������� �������: " << vec1.Length() << endl;

	cout << endl << "5) ��������� ������������ ���� �������� ������ �������: " << vec1.ScalarProduct(vec2) << endl;

	cout << endl << "6) ����� ���� �������� ������ �������:" << endl;
	(vec1.Sum(vec2)).Print();
	
	cout << endl;

	system("pause");
}

