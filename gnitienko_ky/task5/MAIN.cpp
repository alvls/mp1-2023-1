#include <iostream>
#include <string>
#include <unordered_map>
#include <Windows.h>
#include <conio.h>
#include <io.h>
#include "Header.h"

using namespace std;

class Client {
private:
	string card_number;
	string name;
	int balance;
	int PIN;
	int attempts;
public:
	Client() = default;
	Client(const string& card_number, const string& name, int balance, int pin_code)
		: card_number(card_number), name(name), balance(balance), PIN(pin_code), attempts(0) {}

	const string& GetCard() const { return card_number; }
	const string& GetName() { return name; }
	int GetBalance() { return balance; }
	int GetPIN() { return PIN; }
	void SetBalance(int _balance) { balance = _balance; }
	void increment_attempts() { attempts++; }
	bool is_blocked() { return attempts >= 3; }
	void nullAttempts() { attempts = 0; }
	int get_attempts() { return attempts; }
};

class ProcessingCenter {
private:
	unordered_map<string, Client> clients;
public:
	ProcessingCenter() = default;
	void add_client(const Client& client) {
		clients[client.GetCard()] = client;
	}

	Client find_client(const string& card_number) const {
		auto it = clients.find(card_number);
		if (it != clients.end()) {
			return it->second;
		}
		return Client();
	}

	bool Empty() {
		if (clients.empty()) {
			return true;
		}
		else return false;
	}

	bool client_exist(const string& card_number) const {
		if (clients.empty()) {
			return false;
		}
		auto client = clients.find(card_number);
		if (client == clients.end()) {
			return false;
		}
		else {
			return true;
		}
	}

	bool verify_pin_code(const string& card_number, int pin_code) {
		auto it = clients.find(card_number);
		if (it != clients.end() && it->second.GetPIN() == pin_code) {
			return true;
		}
		if (it != clients.end()) {
			it->second.increment_attempts();
		}
		return false;
	}
};

class ATM {
private:
	static constexpr int NumCassette = 6;
	static constexpr int MaxCapacity = 2000;
	static constexpr int MaxNotes = 40;
	static constexpr int kNoteValues[NumCassette] = { 100, 200, 500, 1000, 2000, 5000 };
	ProcessingCenter processing_center;
	bool is_card_inserted;
	Client current_client;
	bool is_blocked;
	int cassettes[NumCassette];
public:
	ATM() : processing_center(), is_card_inserted(false), current_client() {
		for (auto& cassette : cassettes) {
			cassette = 0.8 * MaxCapacity;
		}
	}

	void AddClient(Client& client) {
		processing_center.add_client(client);
	}

	void changeClient() {
		processing_center.add_client(current_client);
	}

	Client This() {
		return current_client;
	}

	bool insert_card(const string& card_number) {
		if (is_card_inserted) {
			return false;
		}
		current_client = processing_center.find_client(card_number);
		if (current_client.GetCard().empty()) {
			return false;
		}
		is_card_inserted = true;
		is_blocked = current_client.is_blocked();
		return true;
	}

	bool verify_pin_code(int pin_code) {
		if (!is_card_inserted || is_blocked) {
			return false;
		}
		if (processing_center.verify_pin_code(current_client.GetCard(), pin_code)) {
			current_client.nullAttempts();
			is_blocked = false;
			return true;
		}
		else {
			if (current_client.get_attempts() == 3) {
				block_card();
				is_card_inserted = false;
			}
			current_client.increment_attempts();
			return false;
		}
	}

	int print_balance() {
		if (!is_card_inserted || is_blocked) {
			return 0;
		}
		return current_client.GetBalance();
	}

	bool withdraw(int amount) {
		if (!is_card_inserted || is_blocked) {
			return false;
		}
		if (amount % 100 != 0) {
			return false;
		}
		int remaining_amount = amount;
		int remaining_notes = MaxNotes;
		for (int i = NumCassette - 1; i >= 0; i--) {
			int num_notes = min(cassettes[i], remaining_amount / kNoteValues[i]);
			num_notes = min(num_notes, remaining_notes);
			remaining_amount -= num_notes * kNoteValues[i];
			remaining_notes -= num_notes;
			cassettes[i] -= num_notes;

			if (remaining_amount == 0) {
				break;
			}
		}
		if (remaining_amount == 0) {
			if ((current_client.GetBalance() - amount) < 0) return false;
			current_client.SetBalance(current_client.GetBalance() - amount);
			return true;
		}
		else {
			for (int i = 0; i < NumCassette; i++) {
				cassettes[i] += (amount - remaining_amount) / kNoteValues[i];
			}
			return false;
		}
	}

	bool deposit(int amount) {
		if (!is_card_inserted || is_blocked) {
			return false;
		}
		if (amount % 100 != 0) {
			return false;
		}
		int remaining_amount = amount;
		for (int i = 0; i < NumCassette; i++) {
			int num_notes = min(MaxCapacity - cassettes[i], remaining_amount / kNoteValues[i]);
			cassettes[i] += num_notes;
			remaining_amount -= num_notes * kNoteValues[i];
			if (remaining_amount == 0) {
				break;
			}
		}
		if (remaining_amount == 0) {
			current_client.SetBalance(current_client.GetBalance() + amount);
			return true;
		}
		else {
			for (int i = 0; i < NumCassette; i++) {
				cassettes[i] -= (amount - remaining_amount) / kNoteValues[i];
			}
			return false;
		}
	}
	void eject_card(string& _card) {
		changeClient();
		is_card_inserted = false;
	}

	void block_card() {
		is_blocked = true;
	}
};

string CheckCard(ProcessingCenter& pr, bool flag) {
	string card;
a:
	card = "";
	cin >> card;
	if (card.size() != 4) {
		while (card.size() != 4) {
			cout << "Введите корректный номер карты: ";
			cin >> card;
		}
	}

	if (flag == true) {
		if (pr.client_exist(card) == true) {
			cout << "Пользователь с таким номером карты уже существует. Введите другой номер!" << endl;
			goto a;
		}
	}

	if (flag == false) {
		if (pr.client_exist(card) == false) {
			cout << "Пользователя не существует! Введите другой номер." << endl;
			goto a;
		}
	}

	return card;
}

int main() {
	setlocale(LC_CTYPE, "Rus");
	char* MainMenu[6] = { (char*)"ATM", (char*)"Проверить PIN", (char*)"Состояние счета", (char*)"Выдать наличные",
	(char*)"Пополнить счёт", (char*)"Вернуть карту" };
	char* GuestMenu[4] = { (char*)"", (char*)"Добавить клиента", (char*)"Найти клиента по номеру карты", (char*)"Перейти к операциям" };
	int guest = 0;
	ProcessingCenter pr;
	ATM atm;
	while (guest != KEY_EXIT) {
		guest = menu(GuestMenu, 4);
		switch (guest) {
		case 1: {
			system("cls");
			string card, name;
			int balance = 0, pin = 0;
			cout << "Введите данные клиента" << endl;
			cout << "Номер карты: ";
			card = CheckCard(pr, true);
			cout << "ФИО: ";
			cin.ignore();
			getline(cin, name);
			cout << "Состояние счета: ";
			cin >> balance;
			cout << "PIN-код: ";
			cin >> pin;
			while (pin < 1000 || pin >= 10000) {
				cout << "Введите корректный PIN: ";
				cin >> pin;
			}
			Client man(card, name, balance, pin);
			pr.add_client(man);
			atm.AddClient(man);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			if (pr.Empty() == true) {
				cout << "Для начала добавьте клиента!" << endl; system("pause"); break;
			}
			string _card;
			Client man;
			cout << "Введите номер карты для поиска клиента: ";
			cin >> _card;
			if (_card.size() != 4) {
				while (_card.size() != 4) {
					cout << "Введите корректный номер карты: ";
					cin >> _card;
				}
			}
			man = pr.find_client(_card);
			if (man.is_blocked() == true) { cout << "Данная карта заблокирована!" << endl; system("pause"); break; }
			if (man.GetName() != "") {
				system("cls");
				cout << "Номер карты: ";
				cout << man.GetCard() << endl;
				cout << "ФИО: ";
				cout << man.GetName() << endl;
			}
			else cout << "Пользователь не найден!" << endl;
			system("pause");
			break;
		}
		case 3: {
			if (pr.Empty() == true) {
				system("cls");
				cout << "Для начала добавьте клиента!" << endl; system("pause"); break;
			}
			int choose = 0;
			string _card;
			int _pin = 0;
			Client man;
			system("cls");
			cout << "Вставьте карту!" << endl;
			cin >> _card;
			if (_card.size() != 4) {
				while (_card.size() != 4) {
					cout << "Введите корректный номер карты: ";
					cin >> _card;
				}
			}
			if (pr.client_exist(_card) == false) { cout << "Клиента с таким номером карты не существует!" << endl; break; }
			atm.insert_card(_card);
			man = atm.This();
			if (man.is_blocked() == true) { cout << "Данная карта заблокирована!" << endl; atm.eject_card(_card); system("pause"); break; }
			cout << "Введите pin-код: ";
			cin >> _pin;
			while (atm.verify_pin_code(_pin) == false && man.get_attempts() < 2) {
				man = atm.This();
				cout << "Неверный PIN! Осталось попыток " << 3 - man.get_attempts() << endl;
				cin >> _pin;
			}
			if (atm.verify_pin_code(_pin) == false) { cout << "Число попыток превысило 3. Карта заблокирована!!!" << endl; atm.eject_card(_card); system("pause");  break; }
			system("cls");
			while (choose != 5) {
				choose = menu(MainMenu, 6);
				system("cls");
				switch (choose) {
				case 1: {
					system("cls");
					cout << "Здравствуйте " << man.GetName() << "!" << endl;
					cout << "Вы выбрали проверку PIN-кода." << endl;
					cout << "Введите PIN" << endl;
					cin >> _pin;
					while (atm.verify_pin_code(_pin) == false) {
						cout << "Неверный PIN! Попробуйте еще раз" << endl;
						cin >> _pin;
					}
					cout << "Введен верный PIN-код. Поздравляем!!!" << endl;
					system("pause");
					break;
				}
				case 2: {
					system("cls");
					cout << "Текущий баланс = " << atm.print_balance() << endl;
					system("pause");
					break;
				}
				case 3: {
					system("cls");
					cout << "Введите сумму (Кратную 100), которую хотите снять: ";
					int summ = 0;
					cin >> summ;
					if (atm.withdraw(summ) == true)
						cout << "Заберите наличные" << endl;
					else cout << "Ошибка выдачи наличных" << endl;
					system("pause");
					break;
				}
				case 4: {
					system("cls");
					cout << "Зачислить на счет" << endl;
					cout << "Положите деньги (кратно 100): ";
					int sum;
					cin >> sum;
					if (atm.deposit(sum) == true)
						cout << "Зачисление прошло успешно" << endl;
					else cout << "Ошибка!" << endl;
					system("pause");
					break;
					break;
				}
				case 5: {
					system("cls");
					atm.eject_card(_card);
					cout << "Заберите свою карту" << endl;
					system("pause");
					break;
				}
				}
			}
			system("cls");
		}
		}
	}
}