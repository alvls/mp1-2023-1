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
		double getkg() {
			return weightkg;
		}
		double getberkovets() {
			double weightberkovets = weightkg / 163.8;
			return weightberkovets;
		}
		double getpuds() {
			double weightpuds = weightkg / 16.38;
			return weightpuds;
		}
		double getfunt() {
			double weightfunt = weightkg / 0.4095;
			return weightfunt;
		}
		void prall() {
			cout <<"� ����������� "<< weightkg << "\n";
			cout << "� ��������� " << weightkg / 163.8 << "\n";
			cout << "� �����" << weightkg / 16.38 << "\n";
			cout <<"� ������" << weightkg / 0.4095 << "\n";
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
		cout << "6 ������� ��� ���������� \n";
		cout << "7 �����\n";
		cin >> ans_2;
		switch (ans_2)
		{
		case 1:
			cout<<h.getkg()<<"\n";
			break;
		case 2:
			cout<<h.getberkovets()<<"\n";
			break;
		case 3:
			cout<<h.getpuds()<<"\n";
			break;
		case 4:
			cout<<h.getfunt()<<"\n";
			break;
		case 5:
			cin >> ans_1;
			h.setkg(ans_1);
			break;
		case 6:
			h.prall();
			break;
		case 7:
			flag = 0;
		}
	}
	system("pause");
}