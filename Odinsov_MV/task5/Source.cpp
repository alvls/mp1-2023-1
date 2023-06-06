#include <locale.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;
double deg(int N, double number) {
	for (int i = 0; i < N; i++) {
		number *= number;
	}
	return number;
}
struct Credit
{
	int have_credit = 0;
	int credit_term=0;
	int sum=0;
	int persent = 0;

};
struct account
{
	string account_number;
	string surname;
	string name;
	string patronymic;
	int check;
	Credit credit;
	string password;
};

class processing_center {
protected:
	vector <account> client_base;
};

class bank : public processing_center {
	int client=-1;
public:
	string newaccount(string F, string I, string O, int money, string passw) {
		account new_user;
		string number = to_string(client_base.size() + 1);
		if (client_base.size() > 9999) {
			throw string("Количество аккаунтов достигло предела\n");

		}
		while (number.length() < 4) {
			char ch = '0';
			number.insert(number.begin(), ch);
		}
		new_user.account_number = number;
		new_user.surname = F;
		new_user.surname = I;
		new_user.surname = O;
		new_user.check = money;
		if (passw.length() < 3) {

			throw string("Пароль слишком короткий \n");

		}
		new_user.password = passw;

		client_base.push_back(new_user);
		return number;
	}
	int p(int summ, int year) {
		int p = 8;
		if (year == 1)
			p++;
		if (year == 2)
			p += 2;
		if (year == 3)
			p += 3;
		if (year == 5)
			p += 4;
		if (year == 15)
			p += 5;
		if (p == 8)
			throw "Недопустимый срок кредита\n";
		if (summ <= 100000)
			p += 1;
		if ((summ <= 500000) && (summ > 100000))
			p += 2;
		if ((summ > 500000) && (summ <= 1000000))
			p += 3;
		if ((summ <= 3000000) && (summ > 1000000))
			p += 4;
		if (summ > 3000000)
			throw "Недопустимая сумма кредита \n";
		return p;
	}
	void authorization(string number,string pass ) { 
		
		for (int i = 0; i < client_base.size(); i++) {
			if ((number == client_base[i].account_number)) {

				if (pass == client_base[i].password) {
					client = i;
					
					return;
			}
			}
		}
		throw string("Неверный логин или пароль \n");
	
	}
	bool is_kredit() {
		
		if (client != -1) {
			return (client_base[client].credit.have_credit != 0);
		}
		else {
			throw string("Авторизация не была произведена\n");
		}
	}
	void show_information() {
		cout << "Вы можете выбрать кредит на 1,2,3,5,15 лет\n";
		cout << "Диапазоны сумм: до 100 тыс, от 100 до 500 тыс, от 500 тыс до 1 млн, от 1 до 3 млн\n";
		cout << "Процентная ставка рассчитывается как 8+(1-5 в зависимости от срока)+(1-4 в зависимости от суммы)\n";
		cout << "Чем больше срок или сумма, тем выше ставка\n";
	}
	Credit credit_status() {
		Credit credit;
		if (client != -1)
			return client_base[client].credit;
		else {
			throw string("Авторизация не была произведена\n");
		}
			
	}
	int can_get_kredit(int year, int summ) {
		double pl = summ / (year*12);
		double proc = (((summ - (pl )) * p(summ, year)) / 12.0) / 100.0;
		if (6 * pl + proc < client_base[client].check) {
			return 1;
		}
		else
			return 0;
	}
	void get_credit(int year,int summ) {
		if (can_get_kredit(year, summ) == 1) {
			client_base[client].credit.credit_term =12* year;
			client_base[client].credit.sum = summ;
			client_base[client].credit.persent = p(summ, year);
			client_base[client].credit.have_credit = 1;
		}
	}
	void get_pay() {
		double pl = client_base[client].credit.sum / client_base[client].credit.credit_term;
		double proc = (((client_base[client].credit.sum - (pl)) * client_base[client].credit.persent) / 12.0) / 100.0;
		client_base[client].check = client_base[client].check - pl - proc;
		client_base[client].credit.credit_term = client_base[client].credit.credit_term-1;
		client_base[client].credit.sum = client_base[client].credit.sum- pl - proc;
	}
	void credit_end() {
		if (client_base[client].check >= client_base[client].credit.sum) {
			client_base[client].check = client_base[client].check - client_base[client].credit.sum;
			client_base[client].credit.sum = 0;
			client_base[client].credit.credit_term = 0;
			client_base[client].credit.have_credit = 0;
			client_base[client].credit.persent = 0;
		}
	}

};
void main() {
	setlocale(LC_ALL, "Russian");
	bank B;
	int flag = 1;
	int money = 0;
	string f, i, o,pass,number;
	int ans;
	Credit tmp;
	try {
		cout << "Введите ФИО\n";
		cin >> f >> i >> o;
		cout << "Введите текущий счет\n";
		cin >> money;
		cout << "Введите пароль (пароль должен содержать более 3 символов)\n";
		cin >> pass;
		cout <<"Номер аккаунта: "<<B.newaccount(f, i, o, money, pass)<<endl;
		while (flag) {
			cout << "1)  Создать новый акаунт\n"; // +
			cout << "2)  Авторизироваться\n";     // +
			cout << "3)  Показать информацию о доступных кредитах\n"; //+
			cout << "4)  Узнать о наличи кредита\n"; // +
			cout << "5)  Проверить возможность получения выбранного кредита\n"; //+
			cout << "6)  Получить выбранный кредит\n"; //+
			cout << "7)  Показать текущее состояние кредита\n"; //+
			cout << "8)  Погасить начисления по кредиту\n"; //+
			cout << "9)  Досрочно погасить кредит\n";
			cout << "10) Выход\n"; //+
			cin >> ans;
			switch (ans)
			{
			case 1:
				cout << "Введите ФИО\n";
				cin >> f >> i >> o;
				cout << "Введите текущий счет\n";
				cin >> money;
				cout << "Введите пароль (пароль должен содержать более 3 символов)\n";
				cin >> pass;
				B.newaccount(f, i, o, money, pass);
				break;
			case 2:
				cout << "Введите номер счета\n";
				cin >> number;
				cout << "Введите пароль\n";
				cin >> pass;
				B.authorization(number, pass);
				break;
			case 3:
				B.show_information();
				break;
			case 4:
				if (B.is_kredit())
					cout << "У вас есть кредит\n";
				else
					cout << "У вас нет кредита \n";
				break;
			case 5:
				int y, s;
				cout << "Введите сумму и срок кредита\n";
				cin >> s >> y;
				if (B.can_get_kredit(y, s) == 1)
					cout << "Кредит может быть одобрен\n";
				else
					cout << "Кредит не может быть одобрен\n";
				break;
			case 6:
				int ye, su;
				cout << "Введите сумму и срок кредита\n";
				cin >> su >> ye;
				B.get_credit( ye, su);
				break;
			case 7:
				tmp = B.credit_status();
				cout << "Срок " << tmp.credit_term << endl;
				cout << "Долг " << tmp.sum << endl;
				cout << "Процент в год " << tmp.persent << endl;
				break;
			case 8:
				B.get_pay();
				break;
			case 9:
				B.credit_end();
				break;
			case 10:
				flag = 0;
				break;
			default:
				break;
			}
		}
	}
	catch(string s){
		cout << s;
		
	}
	system("pause");
}