#include <iostream>
#include <ios>
#include <vector>
#include <string>
#include <clocale>
#include <fstream>
#include <ctime>
#include "Railway.h"
using namespace std;

class RailTicketOffice
{
	vector<GorkyRailway> raspisanie;
public:

	RailTicketOffice(Date date)
	{
		for (int i = 0; i < 30; i++, date++)
		{
			GorkyRailway r(date);
			raspisanie.push_back(r);
		}
	}
	vector<GorkyRailway> get_raspisanie() const { return raspisanie; }
	class Ticket
	{
		Direction direction;
		string passenger;
		Date date;
		unsigned int t_num;
		unsigned int w_num;
		unsigned int p_num;
		double cost;
		RailTicketOffice& office;
	public:
		Ticket(RailTicketOffice& to, Direction dir, Date d, string fio, unsigned int tn, unsigned int wn, unsigned int pn) :
			office(to), direction(dir), date(d), passenger(fio), t_num(tn), w_num(wn), p_num(pn)
		{
			cost = to.get_seat(d, tn, wn, pn).get_cost();
		}
		unsigned int get_tn() const { return t_num; }
		unsigned int get_wn() const { return w_num; }
		unsigned int get_pn() const { return p_num; }
		Direction get_direction() const { return direction; }
		double get_cost() const { return cost; }
		Date get_date() const { return date; }
		string get_passenger() { return passenger; }
		void set_passenger(string fio) { passenger = fio; }
		friend ostream& operator<<(ostream& os, const Ticket& t)
		{
			os << "Дата: " << t.date << "|";
			if(t.direction == Direction :: MSK_NN)
				os << " Маршрут: Москва - Нижний Новгород" << "|";
			else
				os << " Маршрут: Нижний Новгород - Москва" << "|";
			os << " Поезд номер:" << t.t_num << "|";
			os << " Вагон номер:" << t.w_num << "|";
			os << " Место номер:" <<t.p_num << "|";
			os << " Пассажир: " << t.passenger << "|";
			os << " Стоимость билета: " << t.cost << "руб";
			return os;
		}
		void remove()
		{
			office.remove_ticket(*this);
		}
	};
	Ticket buy_ticket(Direction dir, Date d, string fio, unsigned int tn, unsigned int wn, unsigned int pn)
	{
		Ticket tic(*this, dir, d, fio, tn, wn, pn);
		for (auto& r : raspisanie)
			if (r.get_date() == d)
			{
				for (auto& t : r.get_trains(dir))
					if ((t.get_number() == tn) && (t.get_wagons()[wn - 1].get_seats()[pn - 1].is_free()))
					{
						t.book_place(wn, pn, fio);
						break;
					}
			}
		return tic;
	}
	void buy_ticket(Ticket& tic)
	{
		for (auto r : raspisanie)
			if (r.get_date() == tic.get_date())
			{
				for (auto t : r.get_trains(tic.get_direction()))
					if ((t.get_number() == tic.get_tn()) && (t.get_wagons()[tic.get_wn() - 1].get_seats()[tic.get_pn() - 1].is_free()))
					{
						t.book_place(tic.get_wn(), tic.get_pn(), tic.get_passenger());
						break;
					}
			}
	}
	void remove_ticket(Ticket& tic)
	{
		tic.set_passenger("");
		buy_ticket(tic);
	}
	void remove_ticket(Direction dir, Date d, string fio, unsigned int tn, unsigned int wn, unsigned int pn)
	{
		buy_ticket(dir, d, "", tn, wn, pn);
	}
	Train& get_train(Date d, unsigned int n)
	{
		for (auto& r : raspisanie)
			if (r.get_date() == d)
			{
				for (vector<Train>* t : r.get_trains())
				{
					for (Train& tt : *t)
					{
						if (tt.get_number() == n)
							return tt;
					}
				}
			}
		throw exception("Нет поезда с указанным номером");
	}
	Wagon& get_wagon(Date d, unsigned int tn, unsigned int wn)
	{
		for (auto& w : get_train(d, tn).get_wagons())
		{
			if (w.get_number() == wn)
				return w;
		}
	}
	Seat& get_seat(Date d, unsigned int tn, unsigned int wn, unsigned int pn)
	{
		for (auto& p : get_wagon(d, tn, wn).get_seats())
		{
			if (p.get_number() == pn)
				return p;
		}
	}
	void book_place(Date date, unsigned int tn, unsigned int wn, unsigned int pn, string fio)
	{
		get_seat(date, tn, wn, pn).book(fio);
	}
	vector<unsigned int> FreeTrains(Train::Type type, Date d, unsigned int n, Direction dir) //узнаем номера поездов с нужным напрявлением и количеством мест
	{
		vector<unsigned int> res;
		for (auto& r : raspisanie)
			if (r.get_date() == d)
				for (auto t : r.get_trains(dir))
					if ((t.CountFreeSeats() >= n) && (t.get_type() == type))
						res.push_back(t.get_number());
		if (!res.empty())
			return res;
		else
			throw exception("Нет свободных мест");
	}
	vector<unsigned int> TrainFreePlases(Train t, Wagon::Type type, unsigned int n) //узнаем номера вагонов необходимого типа с заданным количесивом мест
	{
		vector<unsigned int> res;
		for (auto& v : t.get_wagons())
			if ((v.get_type() == type) && (v.CountFreeSeats() >= n))
				res.push_back(v.get_number());

		if (!res.empty())
			return res;
		else
			throw exception("Нет свободных мест");
	}
	vector<unsigned int> WagonFreePlases(Train t, unsigned int n)//узнаем номера свободных мест в нужном вагоне
	{
		vector<unsigned int> res;
		for (auto& w : t.get_wagons())
			if (w.get_number() == n)
				for (auto& p : w.get_seats())
					if (p.is_free())
						res.push_back(p.get_number());
		if (!res.empty())
			return res;
		else
			throw exception("Нет свободных мест");
	}
};

struct Zakaz
{
	string buyer;
	vector<RailTicketOffice::Ticket> tickets;
	Date date;
	double cost=0;
	Zakaz(string fio, Date d): buyer(fio), date(d) {}
	void add_ticket(RailTicketOffice::Ticket t) { tickets.push_back(t); cost += t.get_cost(); }
	friend ostream& operator<<(ostream& os, const Zakaz& z)
	{
		os << "***************************************************************************************************************************************************" << endl;
		os << "Кассовый чек по заказу" << endl;
		os << "Дата заказа: " << z.date << endl;
		os <<"Покупатель: " << z.buyer << endl;
		os << "Состав заказа:" << endl;
		for (int i = 0; i < z.tickets.size(); i++)
		{
			os << i + 1 << ")" << z.tickets[i] << endl;
		}
		os << "Итого к оплате: " << z.cost << "руб." << endl;
		os << "***************************************************************************************************************************************************";
		return os;
	}
	
	friend ofstream& operator<<(ofstream& os, const Zakaz& z)
	{
		os << "***************************************************************************************************************************************************" << endl;
		os << "Кассовый чек по заказу" << endl; 
		os << "Дата заказа: " << z.date<< endl ;
		os << "Покупатель: " << z.buyer << endl;
		os << "Состав заказа:" << endl;
		for (int i = 0; i < z.tickets.size(); i++)
		{
			os << i + 1 << ")" << z.tickets[i] << endl;
		}
		os << "Итого к оплате: " << z.cost << "руб." << endl;
		os << "***************************************************************************************************************************************************";
		return os;
	}
	void save(string path)
	{
		ofstream f(path);
		f << *this;
	}
	void remove()
	{
		for (auto& t : tickets)
			t.remove();
		cost = 0;
	}
};


void main() // отладка, тут будут далеко не все возможности кассы
{
	setlocale(LC_ALL, "ru");
	cout << 100 << endl;
	Train t = Train::create(Train::Type::Branded);
	cout << 200 << endl;
	Date today(20, 4, 2023);
	Zakaz z("Кирилл Хасаньянов", today);
	cout << 300 << endl;
	RailTicketOffice office(today);
	cout << 400 << endl;
	RailTicketOffice::Ticket tic(office, Direction::NN_MSK, today, "Кирилл", 55, 3, 14);
	RailTicketOffice::Ticket tic2(office, Direction::MSK_NN, today, "Артём", 12, 3, 77);
	office.buy_ticket(tic);
	office.buy_ticket(tic2);
	cout << tic << endl;
	z.add_ticket(tic);
	z.add_ticket(tic2);
	cout << z << endl;
	cout << 500 << endl;
	z.remove();
	Train tr = office.get_train(today, 55);
	cout << z.cost << endl;
	cout << 600 << endl;
	cout << tr.get_wagons()[2].get_seats()[13] << endl;
	cout << t.get_wagons()[1].CountFreeSeats() << endl;
	cout << t.CountFreeSeats() << endl;
	cout << t.get_wagons()[3].get_seats()[1].get_cost();
	z.save("File.txt");
	system("PAUSE");
}