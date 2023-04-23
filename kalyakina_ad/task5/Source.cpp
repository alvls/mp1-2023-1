#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <conio.h>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER '\r'

int choice_in_menu(vector <string> list_for_choice)
{
	int selected = 1;
	char c;
	int i;

	do
	{
		std::cout << list_for_choice[0] << endl;
		for (i = 1; i < __min(list_for_choice.size(), 10); i++)
		{
			if (i == selected)
				std::cout << " > ";
			else std::cout << "   ";
			std::cout << i << ".  " << list_for_choice[i] << endl;
		}
		for (; i < list_for_choice.size(); i++)
		{
			if (i == selected)
				std::cout << " > ";
			else std::cout << "   ";
			std::cout << i << ". " << list_for_choice[i] << endl;
		}
		switch ((c = _getch()))
		{
		case KEY_UP:
			if (selected > 1)
				selected--;
			break;
		case KEY_DOWN:
			if (selected < list_for_choice.size() - 1)
				selected++;
			break;
		default: break;
		}
		system("cls");
	} while (c != KEY_ENTER);
	return(selected);
}

class Processing_center
{
protected:
	struct information_about_credit
	{
		bool existence;
		int sum_now = 0;
		int remaining_period = 0;
		int percent = 0;
		int monthly_payment = 0;
		bool implementation_of_payment = 0;
		string description;

		void operator+=(int sum)
		{
			if (implementation_of_payment)
				sum_now -= sum;
			else
				sum_now -= sum - sum_now * percent / 1200;
			monthly_payment = sum_now * percent / 1200 + sum_now / remaining_period;
			implementation_of_payment = true;
		}
	};

	struct authorization
	{
		string _payroll_account_number;
		string _password;
	};

	struct client
	{
		string FIO;
		string payroll_account_number;
		int sum_on_payroll_account_number;
		information_about_credit clients_credit;
		string password;

		bool operator< (authorization client)
		{
			return (payroll_account_number < client._payroll_account_number);
		}

		bool operator== (authorization client)
		{
			return((payroll_account_number == client._payroll_account_number) && (password == client._password));
		}
	};

	vector <client> base_of_clients;
	client new_client;

	Processing_center(string path)
	{
		reading_of_information(path);
	}

private:
	void reading_of_information(string path)
	{
		string line;
		fstream reading(path);
		while (!reading.eof())
		{
			getline(reading, new_client.FIO);
			getline(reading, new_client.payroll_account_number);
			getline(reading, new_client.password);
			getline(reading, line);
			new_client.sum_on_payroll_account_number = stoi(line);
			getline(reading, line);
			if (line == "0\0")
				new_client.clients_credit.existence = false;
			else
			{
				new_client.clients_credit.existence = true;
				getline(reading, new_client.clients_credit.description);
				getline(reading, line);
				new_client.clients_credit.sum_now = stoi(line);
				getline(reading, line);
				new_client.clients_credit.remaining_period = stoi(line);
				getline(reading, line);
				new_client.clients_credit.percent = stoi(line);
				new_client.clients_credit.implementation_of_payment = false;
				new_client.clients_credit.monthly_payment = count_of_monthly_payment(new_client.clients_credit.sum_now,
					new_client.clients_credit.percent, new_client.clients_credit.remaining_period);
			}
			getline(reading, line);
			base_of_clients.push_back({ new_client });
		}
		reading.close();
	}

	void rewrite_of_information()
	{
		int i = 0;
		ofstream writing("Database(the last).txt");
		if (base_of_clients[i].clients_credit.existence)
		{
			if (base_of_clients[i].clients_credit.implementation_of_payment)
				writing << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl
				<< base_of_clients[i].password << endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 1 << endl
				<< base_of_clients[i].clients_credit.description << endl << base_of_clients[i].clients_credit.sum_now << endl
				<< base_of_clients[i].clients_credit.remaining_period - 1 << endl << base_of_clients[i].clients_credit.percent << endl;
			else
				writing << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl
				<< base_of_clients[i].password << endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 1 << endl
				<< base_of_clients[i].clients_credit.description << endl << base_of_clients[i].clients_credit.sum_now << endl
				<< base_of_clients[i].clients_credit.remaining_period << endl << base_of_clients[i].clients_credit.percent << endl;
		}
		else
			writing << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl << base_of_clients[i].password
			<< endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 0 << endl;
		for (; i < base_of_clients.size(); i++)
		{
			if (base_of_clients[i].clients_credit.existence)
			{
				if (base_of_clients[i].clients_credit.implementation_of_payment)
					writing << endl << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl
					<< base_of_clients[i].password << endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 1 << endl 
					<< base_of_clients[i].clients_credit.description << endl << base_of_clients[i].clients_credit.sum_now << endl 
					<< base_of_clients[i].clients_credit.remaining_period - 1 << endl << base_of_clients[i].clients_credit.percent << endl;
				else
					writing << endl << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl
					<< base_of_clients[i].password << endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 1 << endl
					<< base_of_clients[i].clients_credit.description << endl << base_of_clients[i].clients_credit.sum_now << endl
					<< base_of_clients[i].clients_credit.remaining_period << endl << base_of_clients[i].clients_credit.percent << endl;
			}
			else
				writing << endl << base_of_clients[i].FIO << endl << base_of_clients[i].payroll_account_number << endl << base_of_clients[i].password 
				<< endl << to_string(base_of_clients[i].sum_on_payroll_account_number) << endl << 0 << endl;
		}
		writing.close();
	}

protected:
	int count_of_monthly_payment(int sum, int percent, int remaining_period)
	{
		return(sum * percent / 1200 + sum / remaining_period);
	}

	~Processing_center()
	{
		rewrite_of_information();
	}
};

class Loan : public Processing_center
{
	struct avaliable_loan
	{
		int min_sum;
		int max_sum;
		int period;
		int percent;
		string description;
	};

	int number_of_authorization;
	vector <avaliable_loan> loans;

public:
	Loan(string path = "Database.txt") :Processing_center(path)
	{
		number_of_authorization = -1;
		loans.reserve(20);
		loans.push_back({ 0, 100000, 1, 22, "������ �� ����� �� 100 000 ������ �� ���� � 1 ��� ��� 22% �������" });
		loans.push_back({ 0, 100000, 2, 20, "������ �� ����� �� 100 000 ������ �� ���� � 2 ���� ��� 20% �������" });
		loans.push_back({ 0, 100000, 3, 18, "������ �� ����� �� 100 000 ������ �� ���� � 3 ���� ��� 18% �������" });
		loans.push_back({ 0, 100000, 5, 16, "������ �� ����� �� 100 000 ������ �� ���� � 5 ��� ��� 16% �������" });
		loans.push_back({ 0, 100000, 15, 12, "������ �� ����� �� 100 000 ������ �� ���� � 15 ��� ��� 12% �������" });
		loans.push_back({ 100000, 500000, 1, 20, "������ �� ����� �� 100 000 �� 500 000 ������ �� ���� � 1 ��� ��� 20% �������" });
		loans.push_back({ 100000, 500000, 2, 18, "������ �� ����� �� 100 000 �� 500 000 ������ �� ���� � 2 ���� ��� 18% �������" });
		loans.push_back({ 100000, 500000, 3, 16, "������ �� ����� �� 100 000 �� 500 000 ������ �� ���� � 3 ���� ��� 16% �������" });
		loans.push_back({ 100000, 500000, 5, 14, "������ �� ����� �� 100 000 �� 500 000 ������ �� ���� � 5 ��� ��� 14% �������" });
		loans.push_back({ 100000, 500000, 15, 10, "������ �� ����� �� 100 000 �� 500 000 ������ �� ���� � 15 ��� ��� 10% �������" });
		loans.push_back({ 500000, 1000000, 1, 19, "������ �� ����� �� 500 000 �� 1 000 000 ������ �� ���� � 1 ��� ��� 19% �������" });
		loans.push_back({ 500000, 1000000, 2, 17, "������ �� ����� �� 500 000 �� 1 000 000 ������ �� ���� � 2 ���� ��� 17% �������" });
		loans.push_back({ 500000, 1000000, 3, 15, "������ �� ����� �� 500 000 �� 1 000 000 ������ �� ���� � 3 ���� ��� 15% �������" });
		loans.push_back({ 500000, 1000000, 5, 13, "������ �� ����� �� 500 000 �� 1 000 000 ������ �� ���� � 5 ��� ��� 13% �������" });
		loans.push_back({ 500000, 1000000, 15, 9, "������ �� ����� �� 500 000 �� 1 000 000 ������ �� ���� � 15 ��� ��� 9% �������" });
		loans.push_back({ 1000000, 3000000, 1, 18, "������ �� ����� �� 1 000 000 �� 3 000 000 ������ �� ���� � 1 ��� ��� 18% �������" });
		loans.push_back({ 1000000, 3000000, 2, 16, "������ �� ����� �� 1 000 000 �� 3 000 000 ������ �� ���� � 2 ���� ��� 16% �������" });
		loans.push_back({ 1000000, 3000000, 3, 14, "������ �� ����� �� 1 000 000 �� 3 000 000 ������ �� ���� � 3 ���� ��� 14% �������" });
		loans.push_back({ 1000000, 3000000, 5, 12, "������ �� ����� �� 1 000 000 �� 3 000 000 ������ �� ���� � 5 ��� ��� 12% �������" });
		loans.push_back({ 1000000, 3000000, 15, 8, "������ �� ����� �� 1 000 000 �� 3 000 000 ������ �� ���� � 15 ��� ��� 8% �������" });
	}

	bool is_avaliable(int sum, int percent, int remaining_period)
	{
		int sum_of_payment = 0;
		for (int i = 0; i < 6; i++)
		{
			sum_of_payment += count_of_monthly_payment(sum, percent, remaining_period);
			sum -= sum / remaining_period;
			remaining_period--;
		}
		return(base_of_clients[number_of_authorization].sum_on_payroll_account_number >= sum_of_payment);
	}

	void authorization_of_client(string _payroll_account_number, string _password)
	{
		int i = 0;
		authorization present_client = { _payroll_account_number, _password };
		while (base_of_clients[i] < present_client)
			i++;
		if (base_of_clients[i] == present_client)
			number_of_authorization = i;
		else throw(1);
	}

	void output_of_information_about_avaliable_loans(vector <string>& avaliable_for_client_loans)
	{
		int i;
		if (number_of_authorization == -1)
			throw (2);
		else
		{
			if (base_of_clients[number_of_authorization].clients_credit.existence)
				throw(5);
			else
			{
				if (avaliable_for_client_loans.size() > 0)
					avaliable_for_client_loans.clear();
				for (i = 0; i < loans.size(); i++)
					if (is_avaliable(loans[i].min_sum, loans[i].percent, loans[i].period * 12))
						avaliable_for_client_loans.push_back(loans[i].description);
			}
		}
	}

	bool existence_of_loan()
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			return(base_of_clients[number_of_authorization].clients_credit.existence);
		}
	}

	bool checking_for_the_possibility_of_obtaining_the_selected_loan(string choice_of_loan, int sum)
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			int i;
			if ((choice_of_loan[0] >= '0') && (choice_of_loan[0] <= '9'))
				i = stoi(choice_of_loan);
			else
				for (i = 0; i < loans.size(); i++)
					if (loans[i].description == choice_of_loan)
						break;
			return((!existence_of_loan()) && (sum >= loans[i].min_sum) && (sum < loans[i].max_sum) && (is_avaliable(sum, loans[i].percent, 
				loans[i].period * 12)));
		}
	}

	bool get_of_new_loan(string choice_of_loan, int sum)
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			int i;
			for (i = 0; i < loans.size(); i++)
				if (loans[i].description == choice_of_loan)
					break;
			if (checking_for_the_possibility_of_obtaining_the_selected_loan(to_string(i), sum))
			{
				base_of_clients[number_of_authorization].sum_on_payroll_account_number += sum;
				base_of_clients[number_of_authorization].clients_credit.existence = true;
				base_of_clients[number_of_authorization].clients_credit.percent = loans[i].percent;
				base_of_clients[number_of_authorization].clients_credit.sum_now = sum;
				base_of_clients[number_of_authorization].clients_credit.remaining_period = loans[i].period * 12;
				base_of_clients[number_of_authorization].clients_credit.implementation_of_payment = true;
				base_of_clients[number_of_authorization].clients_credit.description = loans[i].description;
				base_of_clients[number_of_authorization].clients_credit.monthly_payment = count_of_monthly_payment(sum, loans[i].percent,
					loans[i].period * 12);
				return(true);
			}
			else
				return(false);
		}
	}

	string output_of_loan_status()
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			information_about_credit present_client = base_of_clients[number_of_authorization].clients_credit;
			if (!present_client.existence)
				return("� ��� ��� �������");
			else
				return(present_client.description + ". �������� ��������� (� ������) " + to_string(present_client.sum_now) + " �� ������ (� �������) "
					+ to_string(present_client.remaining_period) + ". ��������� ������������ ������ �������� (� ������): "
					+ to_string(present_client.monthly_payment) + '\0');
		}
	}

	bool input_of_monthly_payment(int sum)
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			if (!base_of_clients[number_of_authorization].clients_credit.existence)
				return(false);
			else if ((base_of_clients[number_of_authorization].sum_on_payroll_account_number < sum)
				&& (base_of_clients[number_of_authorization].sum_on_payroll_account_number
					< base_of_clients[number_of_authorization].clients_credit.sum_now))
				return(false);
			else if (base_of_clients[number_of_authorization].clients_credit.implementation_of_payment
				&& (sum <= base_of_clients[number_of_authorization].clients_credit.sum_now))
			{
				base_of_clients[number_of_authorization].clients_credit += (sum);
				base_of_clients[number_of_authorization].sum_on_payroll_account_number -= sum;
				return(true);
			}
			else if (base_of_clients[number_of_authorization].clients_credit.implementation_of_payment)
			{
				base_of_clients[number_of_authorization].sum_on_payroll_account_number
					-= base_of_clients[number_of_authorization].clients_credit.sum_now;
				base_of_clients[number_of_authorization].clients_credit = { false, 0, 0, 0, 0, true, "" };
				return(true);
			}
			else if (sum >= base_of_clients[number_of_authorization].clients_credit.sum_now +
				base_of_clients[number_of_authorization].clients_credit.sum_now *
				base_of_clients[number_of_authorization].clients_credit.percent / 1200)
			{
				base_of_clients[number_of_authorization].sum_on_payroll_account_number
					-= base_of_clients[number_of_authorization].clients_credit.sum_now
					+ base_of_clients[number_of_authorization].clients_credit.sum_now
					* base_of_clients[number_of_authorization].clients_credit.percent / 1200;
				base_of_clients[number_of_authorization].clients_credit = { false, 0, 0, 0, 0, true, "" };
				return(true);
			}
			else if (sum >= base_of_clients[number_of_authorization].clients_credit.monthly_payment)
			{
				base_of_clients[number_of_authorization].clients_credit += sum;
				base_of_clients[number_of_authorization].sum_on_payroll_account_number -= sum;
				return(true);
			}
			else return(false);
		}
	}

	bool pay_off_the_loan_in_full()
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			if (!base_of_clients[number_of_authorization].clients_credit.existence)
				return(false);
			else if (base_of_clients[number_of_authorization].clients_credit.sum_now
					> base_of_clients[number_of_authorization].sum_on_payroll_account_number)
				return(false);
			else
			{
				if (base_of_clients[number_of_authorization].clients_credit.implementation_of_payment)
					base_of_clients[number_of_authorization].sum_on_payroll_account_number
					-= base_of_clients[number_of_authorization].clients_credit.sum_now;
				else
					base_of_clients[number_of_authorization].sum_on_payroll_account_number
					-= base_of_clients[number_of_authorization].clients_credit.sum_now
					+ base_of_clients[number_of_authorization].clients_credit.sum_now
					* base_of_clients[number_of_authorization].clients_credit.percent / 1200;
				base_of_clients[number_of_authorization].clients_credit = { false, 0, 0, 0, 0, true, "" };
				return(true);
			}
		}
	}

	void change_a_month(int wage, int cost)
	{
		if (number_of_authorization == -1)
			throw(2);
		else
		{
			if (!base_of_clients[number_of_authorization].clients_credit.implementation_of_payment)
				throw(4);
			else
			{
				if (base_of_clients[number_of_authorization].sum_on_payroll_account_number + wage < cost)
					throw(3);
				else
				{
					base_of_clients[number_of_authorization].clients_credit.implementation_of_payment = false;
					base_of_clients[number_of_authorization].clients_credit.remaining_period--;
					base_of_clients[number_of_authorization].sum_on_payroll_account_number += wage - cost;
				}
			}
		}
	}

	void output_of_sum_on_payroll_account_number_and_monthly_payment(int& _sum_on_payroll_account_number, int& _monthly_payment)
	{
		_sum_on_payroll_account_number = base_of_clients[number_of_authorization].sum_on_payroll_account_number;
		if (base_of_clients[number_of_authorization].clients_credit.implementation_of_payment)
			_monthly_payment = 0;
		else
			_monthly_payment = base_of_clients[number_of_authorization].clients_credit.monthly_payment;
	}

	~Loan()
	{

	}
};

int input_of_payroll_account_number_and_password(string& _payroll_account_number, string& _password)
{
	vector <string> choice = { "�������� ��������:", "������ ����� ����������� ����� ������", "�����" };
	int i = 0;
	//cin.clear();
	//while (getchar() != '\n');
	while (i == 0)
	{
		cout << "������� ����� ����������� �����: ";
		getline(cin, _payroll_account_number);
		system("cls");
		if (_payroll_account_number.length() != 4)
		{
			if (choice_in_menu(choice) == 2) return(-1);
		}
		else
		{
			for (i = 0; i < 4; i++)
			{
				if ((_payroll_account_number[i] < '0') || (_payroll_account_number[i] > '9'))
					break;
			}
			if (i != 4)
			{
				i = 0;
				if (choice_in_menu(choice) == 2) return(-1);
			}
		}
	}
	cout << "������� ������: ";
	getline(cin, _password);
	system("cls");
	return(1);
}

void input_output(Loan& s)
{
	int num = 0;
	string payroll_account_number;
	string password;
	string path;
	int sum;
	int wage, cost;
	bool is_authorized = false;
	int i;
	int sum_on_payroll_account_number, monthly_payment;
	vector <string> credits;
	vector <string> actions = { "�������� ��������:", "������������ ������� ������������", "�������� ���������� � ��������� ������� ��������",
		"��������� ������� ������� � ����� �������", "��������� ����������� ��������� ���������� �������", "�������� ��������� ������",
		"�������� ������� ��������� �������", "�������� ���������� �� �������", "�������� �������� ������", "�������� �� ��������� �����", 
		"������ ����� �� ���������� �����", "�����" };


	while (!is_authorized)
	{
		num = input_of_payroll_account_number_and_password(payroll_account_number, password);
		is_authorized = true;
		try
		{
			if (num != -1)
				s.authorization_of_client(payroll_account_number, password);
		}
		catch (int)
		{
			is_authorized = false;
			cout << "�� ������� ����������� �������. ���������� ��������� ������� " << endl << endl;
			system("pause");
			system("cls");
		}
	}
	while (num != -1)
	{

		try
		{
			num = choice_in_menu(actions);
			switch (num)
			{
			case 1:
				is_authorized = false;
				while (!is_authorized)
				{
					num = input_of_payroll_account_number_and_password(payroll_account_number, password);
					is_authorized = true;
					try
					{
						if (num != -1)
							s.authorization_of_client(payroll_account_number, password);
					}
					catch (int)
					{
						is_authorized = false;
						cout << "�� ������� ����������� �������. ���������� ��������� ������� " << endl << endl;
						system("pause");
						system("cls");
					}
				}
				break;
			case 2:
				i = 1;
				s.output_of_information_about_avaliable_loans(credits);
				credits.insert(credits.begin(), "��� �������� ��������� �������:");
				cout << credits[0] << endl;
				for (; i < __min(credits.size(), 10); i++)
					cout << i << ".  " << credits[i] << endl;
				for (; i < credits.size(); i++)
					cout << i << ". " << credits[i] << endl;
				cout << endl;
				system("pause");
				system("cls");
				break;
			case 3:
				if (s.existence_of_loan())
					cout << "� ��� ���� ������������� ������. ��� ����� ��������� ���������� ��������� � ������ '�������� ������� ��������� �������'" 
					<< endl << endl;
				else
					cout << "� ��� ��� �������������� �������" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 4:
				s.output_of_information_about_avaliable_loans(credits);
				credits.insert(credits.begin(), "�������� ������:");
				i = choice_in_menu(credits);
				cout << "��� �����: " << credits[i] << endl;
				cout << "������� �����, �� ������� �� ������ �� ����� ������ (� ������): ";
				cin >> sum;
				while (getchar() != '\n');
				system("cls");
				if (s.checking_for_the_possibility_of_obtaining_the_selected_loan(credits[i], sum))
					cout << "�� ������ �������� ��������� ������" << endl << endl;
				else
					cout << "�� �� ������ �������� ��������� ������. ���������, ���������� �� ����� �� ����� ����� ��� ������ 6 ������ "
					<< "�� ������� � ����� �� �� ����� �� ��������� �� ��������� ���������� ��� ����� �������" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 5:
				s.output_of_information_about_avaliable_loans(credits);
				credits.insert(credits.begin(), "�������� ������:");
				i = choice_in_menu(credits);
				cout << "��� �����: " << credits[i] << endl;
				cout << "������� �����, �� ������� �� ������ �� ����� ������ (� ������): ";
				cin >> sum;
				while (getchar() != '\n');
				system("cls");
				if (s.get_of_new_loan(credits[i], sum))
					cout << "��������� ������ ������� ��������" << endl << endl;
				else
					cout << "������ �� ��� ��������. ���������, ���������� �� ����� �� ����� ����� ��� ������ 6 ������ "
					<< "�� ������� � ����� �� �� ����� �� ��������� �� ��������� ���������� ��� ����� �������" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 6:
				cout << s.output_of_loan_status() << endl << endl;
				system("pause");
				system("cls");
				break;
			case 7:
				s.output_of_sum_on_payroll_account_number_and_monthly_payment(sum_on_payroll_account_number, monthly_payment);
				cout << "����� �� ����� ���������� ����� (�  ������): " << sum_on_payroll_account_number << endl;
				if (monthly_payment != 0)
					cout << "����� ������������� ������� � ���� ������ (� ������): " << monthly_payment << endl;
				cout << "������� ����� �������, ������� �� ������ ������ (� ������): ";
				cin >> sum;
				while (getchar() != '\n');
				system("cls");
				if (s.input_of_monthly_payment(sum))
					cout << "������ ������� ������" << endl << endl;
				else
					cout << "������ �� ��� ������. ���������, �����, ������� �� ����������� ������, ���������� �� ��� ����, ����� �������� "
					<< "����������� ����������, � ����������� �� � ��� ����� �� ���������� �����, ����� ������ �������� ������" << endl << endl;
				system("pause");
				system("cls");
				break;
			case 8:
				if (s.pay_off_the_loan_in_full())
					cout << "������ ��� ������� �������" << endl << endl;
				else
					cout << "������ �� ��� �������. ���������, ����������� �� � ��� ����� �� ���������� �����, ����� ������ �������� ������" 
					<< endl << endl;
				system("pause");
				system("cls");
				break;
			case 9:
				cout << "������� ����� ���������� ����� �� ��������� ����� (� ������): ";
				cin >> wage;
				cout << "������� ����� ������ �� ��������� ����� (� ������): ";
				cin >> cost;
				while (getchar() != '\n');
				s.change_a_month(wage, cost);
				system("cls");
				break;
			case 10:
				s.output_of_sum_on_payroll_account_number_and_monthly_payment(sum_on_payroll_account_number, monthly_payment);
				cout << "����� �� ����� ���������� ����� ���������� (� ������): " << sum_on_payroll_account_number << endl << endl;
				system("pause");
				system("cls");
				break;
			default:
				num = -1;
				break;
			}
		}
		catch (int k)
		{
			switch (k)
			{
			case 2:
				cout << "�� ������� ��������� ��������, ��������� ������ �� ��� �����������" << endl << endl;
				break;
			case 3:
				cout << "�� ������� ��������� ��������, ��������� ����� ���������� �����/������ ���� ������ ����������� "
					<< "� ����� �� ���������� ����� ����� ������ 0" << endl << endl;
				break;
			case 4:
				cout << "�� ������� ��������� ��������, ��������� �� ���� �������� ����������� ���������� �� �������" << endl << endl;
				break;
			case 5:
				cout << "��� �� �������� �� ���� ������, ��������� ���������� ��� �� ��������" << endl << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	}

}

void main()
{
	setlocale(LC_ALL, "Russian");
	string path;
	vector <string> file = { "�������� ���� ��� ���������� ���������� ����", "�������� ����", "���� � ���������� �����������", "�����" };
	cout << "������ ����!" << endl;
	cout << "��� ������������ ��������� '������'" << endl;
	cout << "����� ������������ �� ����, ����������� ������� '�����' � '����'. ��� ������ �� ������ ������� 'Enter'" << endl << endl;
	system("pause");
	system("cls");
	switch (choice_in_menu(file))
	{
	case 1:
		path = "Database.txt";
		break;
	case 2:
		path = "Database(the last).txt";
		break;
	default:
		cout << "�� ��������! �������� ��� ���)" << endl << endl;
		system("pause");
		return;
	}
	Loan s(path);
	input_output(s);
	cout << "�� ��������! �������� ��� ���)" << endl << endl;
	system("pause");
}