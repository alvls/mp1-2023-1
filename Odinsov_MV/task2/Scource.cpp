#include <iostream>
#include <locale.h>
#include <string.h>
using namespace std;
class strin {
	char* str;
	int size;
	public:
		strin(const char* s) {
			size = strlen(s);
			str = new char[size+1];
			strcpy(str, s);
		}
		void getstr() {
			cout << str<<"\n";
		}
		void getsize() {
			cout << size<<"\n";
		}
		void getsymb(int ind) {
			cout << str[ind];
			cout << "\n";
		}
		void changesimb(int ind, char ans) {
			str[ind] = ans;
			cout << str <<"\n";
		}
		char* substring(int start, int finish) {
			char* str2;
			int l = finish - start+1;
			str2 = new char[l + 1];
			memset(str2, '\0', l + 1);
			strncpy(str2, str+start, l);
			cout << str2 << "\n";
			return str2;
		}
		bool ispalindrom() {
			for (int i = 0; i < size / 2; i++) {
				if (str[i] != str[size - i - 1]) {
					cout << "No\n";
					return false;
				}
			}
			cout << "Yes\n";
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
					if (c[i] == 1){
						count++;
					}
				}
				for (int j = i + 1; j < size; j++) {
					if (str[i] == str[j]) {
						c[j] = 0;
					}
				}
			}
			cout << count << "\n";
			return count;
		}
		void changestr(char* s) {
			strcpy(str, s);
		}
		~strin() {
			delete[] str;
		}
};
void main() {
	char s1[40];
	int ind,flag=1;
	int start, finish;
	int ans;
	char ans1;
	setlocale(LC_ALL, "Russian");
	cout << "������� ������\n";
	cin >> s1;
	strin h(s1);
	while (flag) {
		cout << "1 ������� ������ \n";
		cout << "2 ������ ����� ������ \n";
		cout << "3 �������� ������ �� ��� ������� \n";
		cout << "4 �������� ������ ������ �� ��������� ������� \n";
		cout << "5 �������� ��������� �� ������ \n";
		cout << "6 ���������, �������� �� ������ ����������� \n";
		cout << "7 ����� ������� �������� ���������� �������� ��������� � ������ \n";
		cout << "8 �������� ������ \n";
		cout << "9 ����� \n";
		cin >> ans;
		switch (ans) {
		case 1:
			h.getstr();
			break;
		case 2:
			h.getsize();
			break;
		case 3:
			cout << "������� ������\n";
			cin >> ind;
			h.getsymb(ind);
			break;
		case 4:
			cout << "������� �� ����� ������ �� ������ ��������\n";
			cin >> ans1;
			cout << "������� ������ \n";
			cin >> ind;
			h.changesimb(ind, ans1);
			break;
		case 5:
			cout << "������� ������ ������ � ����� ���������\n";
			cin >> start;
			cin >> finish;
			h.substring(start, finish);
			break;
		case 6:
			h.ispalindrom();
			break;
		case 7:
			h.countsymb();
			break;
		case 8:
			cout << "������� ������\n";
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