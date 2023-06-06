#pragma once

#include <string>
#include <map>

enum class SeatType {
    Regular,
    VIP
};
std::map<SeatType, std::string> seat_type_names = {
    { SeatType::Regular, "Стандарт" },
    { SeatType::VIP, "VIP" }
};

typedef std::map<SeatType, double> Prices;

struct SeatInfo
{
    unsigned int row;
    unsigned int num;
    std::string booked_by;
    SeatType type;
    double price;
};

struct Hall
{
    unsigned int id;
    unsigned int rows;
    unsigned int seats_per_row;
    double base_price;

    std::map<SeatType, unsigned int> seats;

    bool has_seat(unsigned int row, unsigned int num) const
    {
        return (row < rows) && (num < seats_per_row);
    }
};