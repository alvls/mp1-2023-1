#include <iostream>
#include <string.h>
#include <locale.h>
using namespace std;
class strin {
	char* str;
	int size;
public:
	strin(const char* s) {
		size = strlen(s);
		str = new char[size + 1];
		strcpy(str, s);
	}
	void prstr() {
		cout << str;
	}
	int getsize() {
		return size;
	}
	char getsymb(int ind) {
		return str[ind];
	}
	char* changesimb(int ind, char ans) {
		str[ind] = ans;
		return str;
	}
	char* substring(int start, int finish) {
		char* str2;
		int l = finish - start + 1;
		str2 = new char[l + 1];
		memset(str2, '\0', l + 1);
		strncpy(str2, str + start, l);
		return str2;
	}
	bool ispalindrom() {
		for (int i = 0; i < size / 2; i++) {
			if (str[i] != str[size - i - 1]) {
				return false;
			}
		}
		return true;
	}
	int countsymb() {
		int c[40];
		int count = 0;
		for (int i = 0; i < size; i++) {
			c[i] = 1;
		}
		for (int i = 0; i < size; i++) {
			if ((int)str[i] >= 97 && (int)str[i] <= 122)
			{
				if (c[i] == 1) {
					count++;
				}
			}
			for (int j = i + 1; j < size; j++) {
				if (str[i] == str[j]) {
					c[j] = 0;
				}
			}
		}
		return count;
	}
	void changestr(char* s) {
		size = strlen(s);
		strcpy(str, s);

	}
	~strin() {
		delete[] str;
	}
};
void main() {
	char s1[40];
	int ind, flag = 1;
	int start, finish;
	int ans;
	char ans1;
	setlocale(LC_ALL, "Russian");
	cout << "Введите строку\n";
	cin >> s1;
	strin h(s1);
	while (flag) {
		cout << "1 Узнать строку \n";
		cout << "2 Узнать размер \n";
		cout << "3 Узнать символ по индексу \n";
		cout << "4 Изменить символ с указанным индексом \n";
		cout << "5 Выделить подстроку \n";
		cout << "6 Проверить является ли строка палиндромом \n";
		cout << "7 Узнать сколько символов латинского алфовита находиться в строке \n";
		cout << "8 Изменить строку \n";
		cout << "9 Выйти \n";
		cin >> ans;
		switch (ans) {
		case 1:
			h.prstr();
			break;
		case 2:
			cout << h.getsize() << "\n";
			break;
		case 3:
			cout << "Введите индекс\n";
			cin >> ind;
			cout << h.getsymb(ind) << "\n";
			break;
		case 4:
			cout << "Введите символ\n";
			cin >> ans1;
			cout << " \n";
			cout << "Введите индекс \n";
			cin >> ind;
			cout << h.changesimb(ind, ans1) << "\n";
			break;
		case 5:
			cout << "Введите начальный и конечный индекс\n";
			cin >> start;
			cin >> finish;
			cout << h.substring(start, finish) << "\n";
			break;
		case 6:
			cout << h.ispalindrom() << "\n";
			break;
		case 7:
			cout << h.countsymb() << "\n";
			break;
		case 8:
			cout << "Введите строку\n";
			cin >> s1;
			h.changestr(s1);
			break;
		case 9:
			flag = 0;
			break;
		}
	}
	system("pause");
}