#include <iostream>
#include <locale.h>
using namespace std;
class scales {
	double weightkg;
	public:
		scales(void) {
			weightkg = 0.0;
		}
		void setkg(double weight) {
			weightkg = weight;
		}
		void getkg() {
			cout << weightkg;
			cout << "\n";
		}
		void getberkovets() {
			double weightberkovets = weightkg / 163.8;
			cout << weightberkovets;
			cout << "\n";
		}
		void getpuds() {
			double weightpuds = weightkg / 16.38;
			cout << weightpuds;
			cout << "\n";
		}
		void getfunt() {
			double weightfunt = weightkg / 0.4095;
			cout << weightfunt;
			cout << "\n";
		}


};
void main() {
	double ans_1;
	int ans_2,flag=1;
	setlocale(LC_ALL, "Russian");
	scales h;
	cout << "������� ��� � �����������\n";
	cin >> ans_1;
	h.setkg(ans_1);
	while (flag) {
		cout << "1 ������ ��� � � �����������\n";
		cout << "2 ������ ��� � ���������\n";
		cout << "3 ������ ��� � �����\n";
		cout << "4 ������ ��� � ������ ��������\n";
		cout << "5 ������� ��� � �����������\n";
		cout << "6 �����\n";
		cin >> ans_2;
		switch (ans_2)
		{
		case 1:
			h.getkg();
			break;
		case 2:
			h.getberkovets();
			break;
		case 3:
			h.getpuds();
			break;
		case 4:
			h.getfunt();
			break;
		case 5:
			cin >> ans_1;
			h.setkg(ans_1);
			break;
		case 6:
			flag = 0;
			break;
		}
	}
	system("pause");
}