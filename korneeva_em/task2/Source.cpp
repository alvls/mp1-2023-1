#include <iostream>
#include <math.h>

using namespace std;

const int MAX_SIZE = 20;
const int MIN_SIZE = 1;

class Vector
{
private:
	int* arr;
	int size;
public:
	inline void validate_vector_size(int size)
	{
		if (size < MIN_SIZE || size > MAX_SIZE)
		{
			throw std::invalid_argument("Указанный размер вектора не соответствует допустимому диапазону (от 1 до 20)");
		}
	}

	inline void validate_vector_component(int size, int index)
	{
		if (index < MIN_SIZE || index > size)
		{
			throw std::invalid_argument("Указанный номер компоненты некорректен");
		}
	}

	Vector(int size) // Конструктор
	{
		validate_vector_size(size);
	
		this->size = size;
		arr = new int[size]();

	}
	
	Vector::~Vector() // Деструктор
	{
		delete[] arr;
	}


	Vector& operator=(const Vector& vec) // Оператор присваивания
	{
		if (this == &vec)
			return *this;

		if (size < vec.size)
		{
			delete[] arr;
			arr = new int[vec.size];
		}

		size = vec.size;

		for (int i = 0; i < size; i++)
			arr[i] = vec.arr[i];
	}

	void Print() // Вывод на консоль
	{
		cout << "Размер вектора: " << size << endl << "Компоненты вектора: ";

		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << " ";
		}

		cout << endl;
	}

	void ChangeSize(int new_size) // Задача размера вектора
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

	int GetSize() // Получение размера вектора
	{
		return size;
	}

	void SetComponent(int index, int component) // Изменение компоненты вектора по её номеру
	{
		inline void validate_vector_component(int size, int index);

		arr[--index] = component;
	}

	int GetComponent(int index) // Получение компоненты вектора по её номеру
	{
		inline void validate_vector_component(int size, int index);

		return arr[--index];
	}

	float Length() // Расчёт длины вектора
	{
		int sum = 0;

		for (int i = 0; i < size; i++)
		{
			sum += arr[i] * arr[i];
		}

		return sqrt(sum);
	}


	int ScalarProduct(const Vector& vec) // Расчёт скалярного произведения двух векторов
	{
		if (size != vec.size)
		{
			throw std::invalid_argument("Невозможно посчитать скалярное произведение двух векторов разного размера");
		}

		int scalar = 0;

		for (int i = 0; i < size; i++)
			scalar += arr[i] * vec.arr[i];

		return scalar;
	}

	void Sum(const Vector& vec, Vector& vec_sum) // Расчёт суммы двух векторов одного размера
	{
		if (size != vec.size)
		{
			throw std::invalid_argument("Невозможно посчитать сумму двух векторов разного размера");
		}

		delete[] vec_sum.arr;
		vec_sum.arr = new int[size];
		vec_sum.size = size;

		for (int i = 0; i < size; i++)
			vec_sum.arr[i] = arr[i] + vec.arr[i];
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
	

	cout <<"Первый вектор:" << endl;
	vec1.Print();

	cout << endl << "Второй вектор:" << endl;
	vec2.Print();


	vec1.ChangeSize(7);
	cout << endl << "1) Изменение размера первого вектора:" << endl;
	vec1.Print();
	vec1.ChangeSize(4);

	cout << endl << "2) Узнать размер первого вектора: " << vec1.GetSize() << endl;

	vec1.GetComponent(2);
	cout << endl << "3) Получить компоненту первого вектора по её номеру (номер = 2): " << vec1.GetComponent(2) << endl;

	cout << endl << "4) Вычисление длины первого вектора: " << vec1.Length() << endl;

	cout << endl << "5) Скалярное произведение двух векторов одного размера: " << vec1.ScalarProduct(vec2) << endl;

	Vector sum1(1);
	vec1.Sum(vec2, sum1);
	cout << endl << "6) Сумма двух векторов одного размера:" << endl;
	sum1.Print();
	
	cout << endl;

	system("pause");
}

