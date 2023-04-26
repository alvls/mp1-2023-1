#pragma once

#include <vector>
#include <map>

#include "DateTime.h"
#include "CinemaShow.h"

using namespace std;

struct Cinema
{
	typedef map<Time, vector<CinemaShow>> DaySchedule;

	vector<Hall> halls;
	map<Date, DaySchedule> shows;

	void register_hall(Hall hall)
	{
		for (auto& h : halls)
		{
			if (h.id == hall.id)
				throw invalid_argument("Зал с таким номером уже зарегистрирован");
		}
		halls.push_back(hall);
	}

	void add_show(Date d, Time t, string name, unsigned int hall_id)
	{
		Hall* hall = nullptr;
		for (auto& h : halls)
		{
			if (h.id == hall_id)
				hall = &h;
		}
		if (!hall)
		{
			throw invalid_argument("Зал с таким номером не найден");
		}

		double price = hall->base_price;
		if (t.hour < 12)
		{
			price *= 0.75f;
		}
		else if (t.hour >= 18)
		{
			price *= 1.5f;
		}

		Prices prices = {
			{ SeatType::Regular, price },
			{ SeatType::VIP, price * 1.5f }
		};

		shows[d][t].push_back(CinemaShow(name, *hall, prices));
	}
};