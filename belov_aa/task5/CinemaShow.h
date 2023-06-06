#pragma once

#include <stdexcept>
#include <string>
#include <map>

#include "Common.h"

using namespace std;

class CinemaShow
{
private:
    typedef pair<unsigned int, unsigned int> seat_location;

    const string name;
    const Hall& hall;
    const Prices prices;
    map<seat_location, SeatInfo> seats;

public:
    CinemaShow(string name, Hall& hall, Prices prices)
        : name(name)
        , hall(hall)
        , prices(prices)
    {}

    string get_name() const
    {
        return name;
    }

    Hall get_hall() const
    {
        return hall;
    }

    vector<SeatInfo*> get_booked()
    {
        std::vector<SeatInfo*> result;
        for (auto it = seats.begin(); it != seats.end(); ++it) {
            result.push_back(&it->second);
        }
        return result;
    }

    SeatInfo& book_seat(unsigned int row, unsigned int num, string person, SeatType seat_type)
    {
        if (!hall.has_seat(row, num))
        {
            throw invalid_argument("“акого места не существует");
        }

        auto loc = seat_location(row, num);
        if (seats.count(loc))
        {
            throw runtime_error("Ёто место уже зан€то");
        }

        seats.insert({ loc, {
            row,
            num,
            person,
            seat_type,
            prices.at(seat_type)
        } });

        return seats[loc];
    }

    bool query_seat(unsigned int row, unsigned int num, SeatInfo* result)
    {
        auto loc = seat_location(row, num);
        if (!seats.count(loc))
        {
            return false;
        }

        *result = seats[loc];
        return true;
    }
};