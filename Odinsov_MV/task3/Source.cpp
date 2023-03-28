#include <iostream>
#include <string.h>
#include <locale.h>
#include <math.h>
using namespace std;

class rTeler {
	int NumberFunction,n;
	double x;
public:
	rTeler(int number,double point, int N) {
		NumberFunction = number;
		x = point;
		n = N;
	}
	friend long double fact(long int n);
	void setfunction(int number) {
		NumberFunction = number;
	}
	char* getfunction(){
		if (NumberFunction == 1) {
			return "sin(x)\n";
		}
		if (NumberFunction == 2) {
			return "cos(x)\n";
		}
		if (NumberFunction == 3) {
			return "exp(x)\n";
		}
		return "Error";
	}
	void setN(int N) {
		n = N;
	}
	int getN() {
		return n;
	}
	char* getformula() {
		if (NumberFunction == 1) {
			return "sin(x)=x-(x^3)/3!+(x^5)/5!+....((-1)^n*x^(2n+1))/(2n+1)!\n";
		}
		if (NumberFunction == 2) {
			return "cos(x)=1-x^2/2!+x^4/4!+...((-1)^n*x^(2n))/(2n)!\n";
		}
		if (NumberFunction == 3) {
			return "exp(x)=1+x/1!+(x^2)/2!+...+(x^n)/n!\n";
		}
		return "Error";
	}
	long double getelem(int N) {
		long double elem = 0,del;
		if (NumberFunction == 1) {
			del = fact(2 * N + 1);
			elem = (pow(-1, N) * pow(x, 2 * N + 1)) / del;
			return elem;

		}
		if (NumberFunction == 2) {
			del = fact(2 * N);
			elem = (pow(-1, N) * pow(x, 2 * N)) / del;
			return elem;
		}
		if (NumberFunction == 3) {
			del = fact(N);
			elem = pow(x,N) / del;
			return elem;
		}
		return -1;
	}
	long double getrT() {
		long double del, rT=0;
		if (NumberFunction == 1) {
			for (int tmp = 0; tmp < n; tmp++) {
				rT += getelem(tmp);
			}
			return rT;
		}
		if (NumberFunction == 2) {
			for (int tmp = 0; tmp < n; tmp++) {
				rT += getelem(tmp);
			}
			return rT;
		}
		if (NumberFunction == 3) {
			for (int tmp = 0; tmp < n; tmp++) {
				rT +=  getelem(tmp);
			}
			return rT;
		}
		return -1;
	}
	long double getdiff() {
		if (NumberFunction == 1) {
			return abs(sin(x)-getrT());
		}
		if (NumberFunction == 2) {
			return abs(cos(x) - getrT());
		}
		if (NumberFunction == 3) {
			return abs(exp(x) - getrT());
		}
		return -1;
	}
};

long double fact(long int n) {
	long double N = 1;
	for (long int i = 1; i <= n; i++) {
		N *= i;
	}
	return N;
}
void main() {
	setlocale(LC_ALL, "Russian");
	int ans1,ans2,N,flag=1;
	double x;
	cout << "Выберите функцию\n";
	cout << " 1)  синус\n";
	cout << " 2)  косинус\n";
	cout << " 3)  экспонента\n";
	cin >> ans1;
	cout << "Введите точку и количество элементов в ряде Тейлора\n";
	cin >> x;
	cin >> N;
	rTeler T(ans1, x, N);
	while (flag) {
		cout << "1) задать текущую функцию\n";
		cout << "2) узнать текущую функцию\n";
		cout << "3) задать текущее число членов ряда\n";
		cout << "4) узнать текущее число членов ряда\n";
		cout << "5) выдать формулу ряда для выбранной функции\n";
		cout << "6) выдать значение заданного члена ряда\n";
		cout << "7) рассчитать значение ряда в выбранной точке x\n";
		cout << "8) вывести отклонение значения ряда в выбранной точке от эталонного\n";
		cout << "9) выйти\n";
		cin >> ans2;
		switch (ans2)
		{
		case 1:
			cout << "Выберите функцию\n";
			cout << " 1)  синус\n";
			cout << " 2)  косинус\n";
			cout << " 3)  экспонента\n";
			cin >> ans1;
			T.setfunction(ans1);
			break;
		case 2:
			cout << T.getfunction();
			break;
		case 3:
			cout << "Введите количество\n";
			cin >> N;
			T.setN(N);
			break;
		case 4:
			cout << T.getN();
			break;
		case 5:
			cout << T.getformula();
			break;
		case 6:
			cout << "Введите номер элемнта\n";
			cin >> N;
			printf("%.20Lf\n", T.getelem(N));
			break;
		case 7:
			printf("%.20lf\n", T.getrT());
			break;
		case 8:
			printf("%.20lf\n", T.getdiff());
			break;
		case 9:
			flag = 0;
			break;
		default:
			break;
		}
	}
	system("pause");
}