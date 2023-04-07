#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;




class vec
{
private:
	int* arr;
	int size;
	bool check_size(int SIZE)
	{
		if ((SIZE > 20) || (SIZE < 1))
			return false;
		else
			return true;
	}
	void pull(int* arrive, int def, int SIZE)
	{
		for (int i = 0; i < SIZE; arrive[i] = def, i++) {};
	}
public:
	vec() {}
	vec(int a) : vec(a,0) {}
	vec(int a, int b)
	{		
		size = a;
		if (check_size(size))
		{
			arr = new int[size];
			pull(arr, b, size);
		}
	}
	vec(const vec& source)
	{
		size = source.size;
		arr = new int[size];
		memcpy(arr, source.arr, size * sizeof(int));
	}

	~vec()
	{
		delete[] arr;
	}

	int get_size()
	{
		return size;
	}

	void push(int index, int value)
	{
		arr[index] = value;
	}
	void print()
	{
		cout << '{'<< ' ';
		for (int i = 0; i < size; i++)
			cout << arr[i] << ' ';
		cout << '}' << endl;
	}
	int get_item(int index)
	{
		return arr[index];
	}
	double length()
	{
		int answer = 0;
		for (int i = 0; i<size;i++)
		{
			answer += arr[i] * arr[i];
		}
		return sqrt(answer);
	}

	vec operator +(const vec& a)
	{
		vec result(*this);
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				result.arr[i] = arr[i] + a.arr[i];
			}
		}
		return result;
	}
	vec& operator+=(const vec& a)
	{
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				arr[i] += a.arr[i];
			}
		}
		return *this;
	}
	vec operator -(const vec& a)
	{
		vec result(*this);
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				result.arr[i] = arr[i] - a.arr[i];
			}
		}
		return result;
	}

	vec& operator-=(const vec& a)
	{
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				arr[i] -= a.arr[i];
			}
		}
		return *this;
	}

	vec operator*(int a)
	{
		vec result(*this);
		for (int i = 0; i < size; i++)
		{
			result.arr[i] *= a;
		}
		return result;
	}
	int operator *(const vec& a)
	{
		int result = 0;
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				result += arr[i] * a.arr[i];
			}
		}
		return result;
	}

	vec& operator*=(int a)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] *= a;
		}
		return *this;
	}

	bool operator==(const vec& a)
	{
		if (size == a.size)
		{
			for (int i = 0; i < size; i++)
			{
				if (arr[i] == a.arr[i])
					continue;
				else
					return false;
			}
		}
		else
			return false;
		return true;
	}

	bool operator !=(const vec& a)
	{
		if (*this == a)
			return false;
		else
			return true;
	}
};






int main()
{
	vec v(5, 10), n(5, 3), c(v);
	cout << v.get_size() << endl;
	v.push(1, 5);
	(v += n).print();
	cout << (v * n) << endl;
	v.print();
	(v * 5).print();
	cout << v.length()<< endl;
	(v + n).print();
	system("PAUSE");
	return 0;
	
}