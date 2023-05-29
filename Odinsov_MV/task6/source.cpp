#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <string>
using namespace std;
class Randomnumber {
protected:
	int len;
	int number = 1;
public:
	Randomnumber(int n) :len(n) {
		srand(time(NULL));
		vector <int> figures = { 1,2,3,4,5,6,7,8,9 };
		int tmp1 = rand() % figures.size();
		int tmp2 = len - 1;
		int tmp3;
		number *= figures[tmp1] * pow(10, tmp2);
		tmp2--;
		figures.erase(figures.begin() + tmp1);
		figures.push_back(0);
		for (int i = 0; i < len - 1; i++) {
			int tmp1 = rand() % figures.size();
			tmp3 = pow(10, tmp2);
			number += figures[tmp1] * tmp3;
			tmp2--;
			figures.erase(figures.begin() + tmp1);
		}
	}

	virtual ~Randomnumber() = 0 {}
};
class bullandcow :Randomnumber {

public:
	bullandcow(int n) :Randomnumber(n) { }
	int bull(int ans) {
		int Bull = 0;
		string tmp1 = to_string(number);
		string tmp2 = to_string(ans);
		for (int i = 0; i < tmp1.size(); i++) {
			if (tmp1[i] == tmp2[i])
				Bull++;
		}
		return Bull;
	}
	int cow(int ans) {
		int Cow = 0;
		string tmp1 = to_string(number);
		string tmp2 = to_string(ans);
		for (int i = 0; i < tmp1.size(); i++) {
			for (int j = 0; j < tmp2.size(); j++) {
				if ((i != j) && (tmp1[i] == tmp2[j]))
					Cow++;
			}
		}
		return Cow;
	}
	bool is_win(int ans) {
		if (bull(ans) == to_string(ans).size())
			return true;
		return false;
	}
};
void main() {
	setlocale(LC_ALL, "Russian");
	cout << "Введите длину номера\n";
	int n;
	cin >> n;
	bullandcow M(n);
	int ans = -1;

	while (1)
	{
		cout << "Введите число с неповторяющимися цифрами\n";
		cin >> ans;
		cout << "Количество быков (цифры угаданные с позициями)" << M.bull(ans) << endl;
		cout << "Количество коров (цыфры угаданные на на своих позициях)" << M.cow(ans) << endl;
		if (M.is_win(ans)) {
			cout << "Ты победил";
			break;
		}

	}


	system("pause");
}