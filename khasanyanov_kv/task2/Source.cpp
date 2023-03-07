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
	void wrong()
	{
		cout << "Wrong size" << endl;
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
		else
			wrong();
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
	void set_size(int size)
	{
		this->size = size;
		arr = new int[size];
		pull(arr, 0, size);
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
	static vec sum_of_vectors(vec a, vec b)
	{
		int S = a.get_size(), item;
		vec answer(S);
		if (a.get_size() == b.get_size())
		{
			for (int i = 0; i < S; i++)
			{
				item = a.get_item(i) + b.get_item(i);
				answer.push(i, item);
			}
		}
		else
			cout << "Different length";
		return answer;
	}
	int composition_with(vec a)
	{
		int answer=0;
		if (a.get_size() == size)
		{
			for (int i = 0; i < size; i++)
			{
				answer += a.get_item(i) * arr[i];
			}
		}
		else
			cout << "Different length";
		return answer;
	}
};






int main()
{
	vec v(5, 10), n(5, 3), d;
	cout << v.get_size()<<endl;
	v.push(1, 5);
	v.print();
	cout << v.length()<< endl;
	vec::sum_of_vectors(v,n).print();
	cout<<v.composition_with(n)<<endl;
	d.set_size(4);
	d.print();
	system("PAUSE");
	return 0;
	
}