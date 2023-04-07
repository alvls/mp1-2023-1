#include <locale.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// Вспомогательные структуры
struct date
{
	int day;
	int month;
	int year;
};
struct observation {
	string username=" ";
	date D;
	double weight=0;
};

class scales {
	vector < observation> history;
	int len = 0;
	string family[5] = { "Add","Add","Add","Add","Add" };
	int usercode = 0;
	double kg=0;
	date D;
public:
	// Работа с акаунтами пользователей
	scales(string user) {
		family[usercode] = user;
	}
	void setuser(string user) {
		for (int i = 0; i < 5; i++) {
			if (user == family[i]) {
				usercode = i;
			}
		}
	}
	void adduser(string user) {
		for (int i = 0; i < 5; i++) {
			if (family[i]=="Add") {
				family[i] = user;
				usercode = i;
				return;
			}
		}
		cout << "Количество пользователей превышено\n";
	}
	string getuser() {
		return family[usercode];
	}
	// Установление даты
	void getdate() {
		cout << D.day<<" день " << D.month<<" месяц " << D.year <<" год "<< endl;
		return;
	}
	void setdate(int d,int mo,int y) {
		D.day = d;
		D.month = mo;
		D.year = y;
	}
	// Создание замера 
	void setobser(double w) {
		observation T;
		len = history.size() - 1;
		if (history.size() > 0) {
			if (history[history.size()-1].username == family[usercode]) {
				if (history[history.size()-1].D.day == D.day) {
					if (history[len].D.month == D.month) {
						if (history[len].D.year == D.year) {
							history.pop_back();
						}
					}
				}
			}
		}
		T.username = family[usercode];
		T.D = D;
		T.weight = w;
		history.push_back(T);
	}
	// Поиск
	double findobser(int number) {
		return history[number].weight;
	}
	double findavvalue(int mod, int mounth, int y) {
		double value = 0;
		int counter = 0;
		for (int i = 0; i < history.size(); i++) {
			if (history[i].username == family[usercode]) {
				if (mod == 1){
					if ((history[i].D.month == mounth) && (history[i].D.month == y)) {
						value += history[i].weight;
						counter += 1;
					}
				}
				else {
					value += history[i].weight;
					counter += 1;
				}
			}
		}
		if (counter > 0)
			return value / counter;
		else
			return -1;
	}
	double findmin(int mod, int mounth, int year) {
		double minweight = 1000000000;
		for (int i = 0; i < history.size(); i++) {
			cout << history[i].weight << "    "<<i << endl;
			if (history[i].username == family[usercode]) {
				if ((mod == 1)) {
					if ((history[i].D.month == mounth) && (history[i].D.month == year)) {
						if (history[i].weight < minweight) {
							minweight = history[i].weight;
						}
					}
				}
				else {
					if (history[i].weight < minweight) {
						minweight = history[i].weight;
					}
				}
			}
		}
		return minweight;
	};
	double findmax(int mod, int mounth, int year) {
		double maxweight=0;
		for (int i = 0; i < history.size(); i++) {
			if (history[i].username == family[usercode]) {
				if ((mod == 1)){
					if ((history[i].D.month == mounth) && (history[i].D.month == year)) {
						if (history[i].weight > maxweight) {
							maxweight = history[i].weight;

						}
					}
				}
				else {
					if (history[i].weight > maxweight) {
						maxweight = history[i].weight;
					
					}
				}
			}
		}
		return maxweight;
	}
	void savefile() {
		ofstream out;          
		out.open("123.txt");
		for (int i = 0; i < history.size(); i++) {
			out << "Запись номер " << i << endl;
			out << history[i].username << endl;
			out << history[i].D.day<<" день "<<history[i].D.month<<" месяц "<<history[i].D.year<<" год" << endl;
			out << history[i].weight << endl;
		}
		out.close();
	}
	void openfile() {
		ifstream in("123.txt");
		string name,x="12";
		int d, m, y;
		double w;
		observation T;
		int i = 0;
		while (getline(in, name))
		{
			getline(in, name);
			in >> d >> m >> y;
			in >> w;
			T.username = name;
			T.D.day = d;
			T.D.month = m;
			T.D.year = y;
			T.weight = w;
			history.push_back(T);
			i++;
		}
		in.close();
	}
};

void main() {
	setlocale(LC_ALL, "Russian");
	string username;
	cout << "Введите имя первого пользователя\n";
	cin >> username;
	scales W(username);
	int ans, flag = 1;
	int number, day, mounth, year;
	int mod;
	double w = 0;
	int m=0,y=0;
	observation tmp;
	mounth = 0;
	while (flag) {
		cout << "1)  Добавить нового пользователя\n";
		cout << "2)  Выбрать пользователя\n";
		cout << "3)  Узнать пользователя\n";
		cout << "4)  Установить дату наблюдений\n";
		cout << "5)  Узнать установленную дату\n";
		cout << "6)  Задать наблюдение\n";
		cout << "7)  Узнать размер выбранного наблюдения\n";
		cout << "8)  Найти средний вес члена семьи в выбранном месяце или за всю историю наблюдений\n";
		cout << "9)  Найти минимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался\n";
		cout << "10) Найти максимальный вес члена семьи в выбранном месяце или за всю историю наблюдений и дату, когда он наблюдался\n";
		cout << "11) Cохранить историю наблюдений в файл\n";
		cout << "12) Cчитать историю наблюдений из файла\n";
		cout << "13) Выйти \n";
		cin >> ans;
		switch (ans)
		{
		case 1:
			cout << "Введите имя \n";
			cin >> username;
			W.adduser(username);
			break;
		case 2:
			cout << "Введите имя \n";
			cin >> username;
			W.setuser(username);
			break;
		case 3:
			cout << W.getuser() << endl;
		case 4:
			cout << "Введите день месяц и год\n";
			cin >>  day >> mounth >> year;
			W.setdate( day, mounth, year);
			break;
		case 5:
			W.getdate();
			break;
		case 6:
			cout << "Введите вес\n";
			cin >> w;
			W.setobser(w);
			break;
		case 7:
			cout << "Введите номер наблюдения\n";
			cin >> number;
			cout << W.findobser(number) << endl;
			break;
		case 8:
			cout << "1) За месяц"<< endl;
			cout << "2) За все время" << endl;
			cin >> mod;
			if (mod == 1) {
				cout << "Введите номер месяца и года\n";
				cin >> m;
				cin >> y;
			}
			cout << W.findavvalue(mod, m,y)<<endl;
			break;
		case 9:
			cout << "1) За месяц" << endl;
			cout << "2) За все время" << endl;
			cin >> mod;
			if (mod == 1) {
				cout << "Введите номер месяца и года\n";
				cin >> m;
				cin >> y;
			}
			cout << W.findmin(mod, m, y)<<endl;
			break;
		case 10:
			cout << "1) За месяц" << endl;
			cout << "2) За все время" << endl;
			cin >> mod;
			if (mod == 1) {
				cout << "Введите номер месяца и года\n";
				cin >> m;
				cin >> y;
			}
			cout << W.findmax(mod, m, y)<<endl;
			break;
		case 11:
			W.savefile();
			break;
		case 12:
			W.openfile();
			break;
		case 13:
			flag = 0;
			break;
		default:
			break;
		}
		
	}

	system("pause");
}