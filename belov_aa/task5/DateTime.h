#pragma once

#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

struct Time
{
    int hour;
    int minute;

    friend ostream& operator <<(ostream& out, const Time& time)
    {
        out << setw(2) << setfill('0') << time.hour << ":" 
            << setw(2) << setfill('0') << time.minute;
        return out;
    }

    bool operator <(const Time& other) const
    {
        if (hour < other.hour)
        {
            return true;
        }
        if (hour == other.hour)
        {
            return minute < other.minute;
        }
        return false;
    }

    bool operator <=(const Time& other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator >(const Time& other) const
    {
        return !(*this < other) && (*this != other);
    }

    bool operator >=(const Time& other) const
    {
        return !(*this < other);
    }

    bool operator ==(const Time& other) const
    {
        return hour == other.hour && minute == other.minute;
    }

    bool operator !=(const Time& other) const
    {
        return !(*this == other);
    }

    Time operator-(const Time& other) const
    {
        Time t = { hour - other.hour, minute - other.minute };
        if (t.minute < 0)
        {
            t.hour -= 1;
            t.minute = 60 - other.minute + minute;
        }
        return t;
    }
};

struct Date
{
    int day;
    int month;
    int year;

    friend ostream& operator <<(ostream& out, const Date& date)
    {
        out << setw(2) << setfill('0') << date.day << "." 
            << setw(2) << setfill('0') << date.month << "." << date.year;
        return out;
    }

    bool operator <(const Date& other) const
    {
        return (*this - other) < 0;
    }

    bool operator <=(const Date& other) const
    {
        return (*this < other) || (*this == other);
    }

    bool operator >(const Date& other) const
    {
        return !(*this < other) && (*this != other);
    }

    bool operator >=(const Date& other) const
    {
        return !(*this < other);
    }

    bool operator ==(const Date& other) const
    {
        return day == other.day
            && month == other.month
            && year == other.year;
    }

    bool operator !=(const Date& other) const
    {
        return !(*this == other);
    }

    int operator-(const Date& other) const
    {
        tm tm1 = { 0, 0, 0, day, month - 1, year - 1900 };
        tm tm2 = { 0, 0, 0, other.day, other.month - 1, other.year - 1900 };

        time_t time1 = mktime(&tm1);
        time_t time2 = mktime(&tm2);

        const int seconds_per_day = 60 * 60 * 24;

        return static_cast<int>(difftime(time1, time2) / seconds_per_day);
    }
};