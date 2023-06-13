#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class stock
{
public:

	struct product
	{
		string barcode;
		string name;
		double price;
		int discount;
		int count;
		int total_price_without_discount;
		int total_price_with_discount;
	};
	stock()
	{
		for (int i = 0; i < 10000; i++)
		{
			products[i] = product();
		}
	}
	product products[10000];
	void addprod(string barcode, string name, double price, int discount)
	{
		int ind = stoi(barcode) - 1;
		products[ind] = {barcode, name, price, discount };
	}
	const product& checkinfo(string barcode)
	{
		int ind = stoi(barcode) - 1;
		return products[ind];
	}
	stock(const stock& other)
	{
		copy(other.products, other.products + 10000, products);
	} 
	stock& operator=(const stock& other)
	{
		copy(other.products, other.products + 10000, products);
		return *this;
	}
};
