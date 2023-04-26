#pragma once

#include "Common.h"
#include "Cinema.h"

class TicketOffice
{
private:
	Cinema& cinema;
	unsigned int ticket_sell_days;
	unsigned int ticket_sell_show_minutes;

	CinemaShow* find_show(Date date, Time t, string movie, unsigned int hall)
	{
		if (!cinema.shows.count(date))
		{
			throw runtime_error("Нет сеансов для выбранной даты");
		}

		Cinema::DaySchedule& schedule = cinema.shows[date];

		if (!schedule.count(t))
		{
			throw runtime_error("Нет сеансов в выбранное время и выбранную дату");
		}

		vector<CinemaShow>& shows = schedule[t];
		for (auto& show : shows)
		{
			if (show.get_hall().id == hall && show.get_name() == movie)
				return &show;
		}

		throw runtime_error("Сеансы по вашему запросу не найдены");
	}

	Date today()
	{
		// для демонстрации
		return { 26, 04, 2023 };
	}
	Time current_time()
	{
		// для демонстрации
		return { 12, 05 };
	}

public:
	TicketOffice(Cinema& cinema, unsigned int ticket_sell_days, unsigned int ticket_sell_show_minutes)
		: cinema(cinema)
		, ticket_sell_days(ticket_sell_days)
		, ticket_sell_show_minutes(ticket_sell_show_minutes)
	{}

	map<Date, Cinema::DaySchedule*> get_schedule()
	{
		Date today = this->today();
		map<Date, Cinema::DaySchedule*> schedule;
		for (auto it = cinema.shows.begin(); it != cinema.shows.end(); ++it)
		{
			if (it->first - today > ticket_sell_days)
				continue;
			schedule[it->first] = &it->second;
		}
		return schedule;
	}

	CinemaShow* verify_availability(Date date, Time t, string movie, unsigned int hall, SeatType seat_type, unsigned int count)
	{
		CinemaShow* show = nullptr;
		try
		{
			show = find_show(date, t, movie, hall);
		}
		catch (const std::exception e)
		{
			cerr << "Причина: " << e.what() << endl; // для отладки
			return nullptr;
		}

		if (!show)
		{
			return nullptr;
		}

		unsigned int left = show->get_hall().seats[seat_type];
		for (auto seat : show->get_booked())
		{
			if (left == 0)
			{
				return nullptr;
			}
			if (seat->type == seat_type)
			{
				left--;
			}
		}

		return left != 0 ? show : nullptr;
	}

	vector<SeatInfo*> book_seats(Date date, Time t, string movie, unsigned int hall,
		string person, SeatType seat_type, unsigned int count)
	{
		Date today = this->today();
		Time current_time = this->current_time();

		Time time_diff = current_time - t;
		if ((date - today > ticket_sell_days)
			|| (date == today && time_diff.hour == 0 && time_diff.minute > ticket_sell_show_minutes))
		{
			throw runtime_error("Билеты на этот сеанс больше не доступны");
		}



		CinemaShow* show = verify_availability(date, t, movie, hall, seat_type, count);

		if (!show)
		{
			throw runtime_error("Свободных мест по вашему запросу не найдено");
		}

		vector<SeatInfo*> result;

		SeatInfo trash;
		for (unsigned int row = 0; row < show->get_hall().rows; row++)
		{
			if (count == 0)
				break;
			for (unsigned int num = 0; num < show->get_hall().seats_per_row; num++)
			{
				if (show->query_seat(row, num, &trash))
					continue;
				result.push_back(&show->book_seat(row, num, person, seat_type));
				count--;
				if (count == 0)
					break;
			}
		}

		return result;
	}
};