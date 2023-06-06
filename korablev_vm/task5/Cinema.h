#include "Header.h"

struct Film
{
	string film_name = "film_name";
	MyDate session_date;
	MyTime start_time;
	Hall film_hall;
	int hall_number = 0;
	int free_base = 0;
	int free_vip = 0;
	friend ostream& operator<<(ostream& out, const Film& film);
	Film& operator=(const Film& copy);
	bool operator==(const Film& copy);
	void set_free_vip(int fr);
	void set_free_base(int fr);
	friend class TicketOffice;
	friend class Cinema;
};
void Film::set_free_base(int fr)
{
	free_base = fr;
}
void Film::set_free_vip(int fr)
{
	free_vip = fr;
}
bool Film::operator==(const Film& copy)
{
	if (film_name == copy.film_name && session_date == copy.session_date &&
		start_time == copy.start_time && film_hall == copy.film_hall && hall_number == copy.hall_number 
		&& free_base == copy.free_base && free_vip == copy.free_vip)
		return true;
	return false;
}
Film& Film::operator=(const Film& copy)
{
	if (film_name == copy.film_name && session_date == copy.session_date && start_time == copy.start_time &&
		film_hall == copy.film_hall && hall_number == copy.hall_number && free_base == copy.free_base && free_vip == copy.free_vip)
		return *this;
	film_name = copy.film_name;
	session_date = copy.session_date;
	start_time = copy.start_time;
	film_hall = copy.film_hall;
	hall_number = copy.hall_number;
	free_base = copy.free_base;
	free_vip = copy.free_vip;
	return *this;
}
ostream& operator<<(ostream& out, const Film& film)
{
	out << "/////////////////////////////////" << endl;
	out << "\t" << film.film_name << endl;
	out << "Дата: " << film.session_date << endl;
	out << "Время начала: " << film.start_time << endl;
	out << film.film_hall << endl;
	out << "Мест (стандартные): " << film.free_base << endl;
	out << "Мест (вип): " << film.free_vip << endl;
	out << "/////////////////////////////////" << endl;
	out << endl;
	return out;
}
class Cinema
{
	vector <Film> sessions;
	bool isBought = false;
	friend class TicketOffice;
public:
	Cinema() {}
	Cinema(vector<Film> films) { sessions = films; }
	~Cinema() {}
	void create_new_session(string _name, MyDate _date, MyTime _time, Hall _hall)
	{
		Film session{};
		session.film_name = _name;
		session.session_date = _date;
		session.start_time = _time;
		session.film_hall = _hall;
		session.film_hall.Construct();
		session.hall_number = session.film_hall.number;
		session.free_base = session.film_hall.base_rows * session.film_hall.base_rows_seats;
		session.free_vip = session.film_hall.vip_rows * session.film_hall.vip_rows_seats;
		sessions.push_back(session);
	}
	Film& operator[](int i) { return sessions[i]; }
	size_t get_sessions_count() { return sessions.size(); }
	void print_session_lite(int i)
	{
		size_t count = 13;
		if (sessions[i].film_name.size() > 15)
			count -= sessions[i].film_name.size() - 15;
		cout << sessions[i].session_date << " - " << sessions[i].film_name << "." << setw(count) << setfill(' ') << "Зал: "
			<< sessions[i].hall_number << ". Время: " << sessions[i].start_time << "\n\n";
	}
	void sessions_for_day_and_time(const MyDate& date, const MyTime& time)
	{
		bool flag = false;
		MyDate temp_date = date;
		int i; 
		int start = date.day;
		int finish = date.day + 3;
		int count = 0;
		for (; start < finish; start++)
		{
			for (i=0; i < get_sessions_count(); i++)
			{
				if (sessions[i].session_date == temp_date)
				{
					if (flag)
					{
						cout << count+1 << ") ";
						print_session_lite(i);
						count++;
					}
					else
					{
						if (sessions[i].start_time.minutes_different(time) < 10)
						{
							cout << count+1 << ") ";
							print_session_lite(i);
							count++;
						}
					}
				}
			}
			flag = true;
			temp_date.set_day(temp_date.day+1);
		}
	}
	void sessions_by_name(const MyDate& date, const MyTime& time, string fname)
	{
		bool flag = false;
		MyDate temp_date = date;
		int i, count=0;
		int start = date.day;
		int finish = date.day + 3;
		for (; start < finish; start++)
		{
			for (i = 0; i < get_sessions_count(); i++)
			{
				if (sessions[i].session_date == temp_date)
				{
					if (flag)
					{
						if (sessions[i].film_name == fname)
						{
							print_session_lite(i);
							count++;
						}
						
					}
					else
					{
						if (sessions[i].start_time.minutes_different(time) < 10)
						{
							if (sessions[i].film_name == fname)
							{
								print_session_lite(i);
								count++;
							}
						}
					}
				}
			}
			flag = true;
			temp_date.set_day(temp_date.day + 1);
		}
	}
	void sessions_by_hall(const MyDate& date, const MyTime& time, int num)
	{
		bool flag = false;
		MyDate temp_date = date;
		int i, count=0;
		int start = date.day;
		int finish = date.day + 3;
		for (; start < finish; start++)
		{
			for (i = 0; i < get_sessions_count(); i++)
			{
				if (sessions[i].session_date == temp_date)
				{
					if (flag)
					{
						if (sessions[i].hall_number == num)
						{
							print_session_lite(i);
							count++;
						}

					}
					else
					{
						if (sessions[i].start_time.minutes_different(time) < 10)
						{
							if (sessions[i].hall_number == num)
							{
								print_session_lite(i);
								count++;
							}
						}
					}
				}
			}
			flag = true;
			temp_date.set_day(temp_date.day + 1);
		}
	}
	void sessions_by_day(const MyDate& date)
	{
		int i, count=0;
		for (i = 0; i < get_sessions_count(); i++)
		{
			if (sessions[i].session_date == date)
			{
				cout << sessions[i];
				count++;
			}
		}
	}
};