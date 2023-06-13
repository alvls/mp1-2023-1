#include "Stock.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class cashbox
{
	
private:
	stock& products;
public:
	vector <stock::product> check;
	cashbox(stock& st) : products(st) 
	{}
	void scanning(string barcode)
	{
		stock::product prod = products.checkinfo(barcode);
	}
	stock::product info(string barcode)
	{
		return products.checkinfo(barcode);
	}
	void addtocheck(string barcode)
	{
		bool found = false;
		for (int i = 0; i < check.size(); i++)
		{
			if (check[i].barcode == barcode)
			{
				check[i].count++;
				check[i].total_price_without_discount = check[i].price * check[i].count;
				check[i].total_price_with_discount = check[i].total_price_without_discount - check[i].total_price_without_discount / 100 * check[i].discount;
				found = true;
				return;
			}
		}
		if (!found)
		{

			stock::product temp = products.checkinfo(barcode);
			temp.count = 1;
			temp.total_price_without_discount = temp.price;
			temp.total_price_with_discount = temp.total_price_without_discount -  temp.total_price_without_discount / 100 * temp.discount;
			check.push_back(temp);
		}

	}
	void cashbox::deleteporudctFromCheck(string barcode)
	{
		for (int i = 0; i < check.size(); i++)
		{
			if (check[i].barcode == barcode)
			{
				if (check[i].count > 1)
				{
					check[i].count--;
					check[i].total_price_without_discount = check[i].total_price_without_discount - check[i].price;
					check[i].total_price_with_discount = check[i].total_price_without_discount - check[i].price / 100 * check[i].discount;
				}
				else
				{
					check.erase(check.begin() + i);
				}
				break;
			}
		}
	}
	int totalPrice_without_discount()
	{
		int Sum = 0;
		for (int i = 0; i < check.size(); i++)
		{
			Sum = Sum + check[i].total_price_without_discount;
		}
		return Sum;
	}
	int totalPrice_with_discount()
	{
		int Sum = 0;
		for (int i = 0; i < check.size(); i++)
		{
			Sum = Sum + ((check[i].price * check[i].count) - (check[i].count * check[i].price) / 100 * check[i].discount);
		}
		return Sum;
	}
	int total_discount()
	{
		int total = 0;
		for (int i = 0; i < check.size(); i++)
		{
			total = total + check[i].price * check[i].count / 100 * check[i].discount;
		}
		return total + 1;
	}
	int GetCheck()
	{
		cout << "                                             ЧЕК №                                 " << endl;
		cout << "                                   Имя ораганизации и тп.                       " << endl;
		cout << "Название:        Цена за ед. товара(Руб):          Кол-во(Шт):      Цена без скидки(Руб):" << endl;
		for (int i = 0; i < check.size(); i++)
		{
			cout << check[i].name << "                     " << check[i].price << "                          " << check[i].count << "                      " << check[i].total_price_without_discount << endl;
		}
		cout << "Общая стоимость товаров(Руб):" << " " << totalPrice_without_discount() << endl;
		cout << "Суммарная скидка составляет(Руб):" << " " << total_discount() << endl;
		cout << "Итоговая сумма к оплате(Руб):" << " " << totalPrice_without_discount() - total_discount() << endl;
		return 0;
	}
};
int main()
{
	setlocale(LC_ALL, "Russian");
	stock store;
	cashbox test(store);
	store.addprod("0001", "milk", 120, 20);
	store.addprod("0002", "bread", 35, 5);
	test.addtocheck("0001");
	test.addtocheck("0002");
	test.addtocheck("0002");
	test.addtocheck("0001");
	//test.deleteporudctFromCheck("0001");
	cout << test.GetCheck() << endl;
	system("pause");
	return 0;

 }