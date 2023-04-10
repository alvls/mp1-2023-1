#include <iostream>

class Vector
{
private:
	int* arr;
	int size;
public:
	Vector(int x = 0, int y = 0)
	{
		if (x >= 1 && x <= 20)
		{
			size = x;
			arr = new int[size];
			for (int i = 0; i < size; i++)
				arr[i] = y;
		}
		else
		{
			size = 0;
			arr = nullptr;
		}
	}

	~Vector()
	{
		delete[] arr;
	}

	Vector(const Vector& another)
	{
		size = another.size;
		arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = another.arr[i];
	}

	Vector& operator = (const Vector& another)
	{
		size = another.size;
		delete[] arr;
		arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = another.arr[i];
		return *this;
	}

	Vector operator + (const Vector& another)
	{
		Vector r(*this);
		if (size != another.size)
			throw '+';
		for (int i = 0; i < size; i++)
			r.arr[i] = arr[i] + another.arr[i];
		return r;
	}

	Vector& operator += (const Vector& another)
	{
		if (size != another.size)
			throw '+';
		for (int i = 0; i < size; i++)
			arr[i] += another.arr[i];
		return *this;
	}

	Vector operator - (const Vector& another)
	{
		Vector r(*this);
		if (size != another.size)
			throw '-';
		for (int i = 0; i < size; i++)
			r.arr[i] = arr[i] - another.arr[i];
		return r;
	}

	Vector& operator -= (const Vector& another)
	{
		if (size != another.size)
			throw '-';
		for (int i = 0; i < size; i++)
			arr[i] -= another.arr[i];
		return *this;
	}

	Vector operator * (int another)
	{
		Vector r(*this);
		for (int i = 0; i < size; i++)
			r.arr[i] *= another;
		return r;
	}

	Vector& operator *= (int another)
	{
		for (int i = 0; i < size; i++)
			arr[i] *= another;
		return *this;
	}

	int operator * (const Vector& another)
	{
		int r = 0;
		if (size != another.size)
			throw "*";
		for (int i = 0; i < size; i++)
			r += arr[i] * another.arr[i];
		return r;
	}

	bool operator == (const Vector& another)
	{
		if (size != another.size)
		{
			return false;
		}
		for (int i = 0; i < size; i++)
		{
			if (arr[i] != another.arr[i])
				return false;
		}
		return true;
	}

	bool operator != (const Vector& another)
	{
		if (*this == another)
			return false;
		else
			return true;
	}
	//-----------------------------------------------------
	int Get_size()
	{
		return size;
	}

	int Get_from(int index)
	{
		return arr[index];
	}

	double Length()
	{
		double answer = 0.0;
		for (int i = 0; i < size; i++)
			answer += pow(arr[i], 2);
		return sqrt(answer);
	}

	void Append_arr(int index, int value)
	{
		arr[index] = value;
	}

	void Print()
	{
		std::cout << '{';
		for (int i = 0; i < size; i++)
		{
			std::cout << arr[i];
			if (i < size - 1)
				std::cout << "; ";
		}
		std::cout << '}' << std::endl;
	}
};

int main()
{
	try
	{
		Vector f(5, -10), s(5, 10), r1, r2, r3;
		int r4;
		r1 = f + s;
		r1.Print();
		r2 = f - s;
		r2.Print();
		r3 = f * 10;
		r3.Print();
		r4 = f * s;
		std::cout << r4 << std::endl;
	}
	catch (char c)
	{
		std::cout << "Error with size in operand of " << c << std::endl;
	}
	system("PAUSE");
	return 0;
}
