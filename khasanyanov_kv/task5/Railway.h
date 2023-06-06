#include <iostream>
#include <string>
#include <vector>
#include <map>



using namespace std;
class Seat
{
public:
    enum class Place
    {
        Top,
        Bottom
    };
private:
    Place place;
    unsigned int number;
    string passenger;
    double cost = 500.0;
public:

    Seat(Place place, unsigned int number, double cost) : place(place), number(number) { this->cost *= cost; }

    Place get_place() const
    {
        return place;
    }

    double get_cost() const
    {
        return cost;
    }

    string get_passanger() const
    {
        return passenger;
    }

    unsigned int get_number() const
    {
        return number;
    }

    void set_passenger(string fio)
    {
        passenger = fio;
    }

    bool is_free() const
    {
        return passenger.empty();
    }

    void book(string fio)
    {
        passenger = fio;
    }

    friend ostream& operator<<(ostream& os, const Seat& s)
    {
        os << "Место номер: " << s.number << endl;
        os << "Статус: ";
        switch (s.is_free())
        {
        case 1:
            os << "Свободно" << endl;
            break;
        case 0:
            os << "Занято" << endl;
            os << "Пассажир: " << s.passenger << endl;
            break;
        }
        os << "Стоимость: " << s.cost << "руб.";
        return os;
    }

};

class Wagon
{
public:
    enum class Type
    {
        ReservedSeat,
        Coupe,
        SV,
        SV100
    };
private:
    Type type;
    vector<Seat> seats;
    unsigned int number;
    double k_Bcost = 1;
    double k_Tcost = 1;
    double k_cost = 1;

    Wagon(Type type, unsigned int number, unsigned int seatsTop, unsigned int seatsBottom, double k) : type(type), number(number)
    {
        k_cost = k;
        switch (type)
        {
        case Type::SV:
        case Type::SV100:
            for (unsigned int i = 0; i < seatsBottom + seatsTop; i++)
            {
                seats.push_back(Seat(Seat::Place::Bottom, i + 1, k_Bcost * k_cost));
            }
            break;
        case Type::Coupe:
            for (unsigned int i = 0; i < seatsBottom + seatsTop; i++)
            {
                k_Tcost = 3.0;
                k_Tcost = 2.5;
                if (i % 2 == 0)
                    seats.push_back(Seat(Seat::Place::Bottom, i + 1, k_Bcost * k_cost));
                else
                    seats.push_back(Seat(Seat::Place::Top, i + 1, k_Tcost * k_cost));
            }
            break;
        case Type::ReservedSeat:
            for (unsigned int i = 0; i < seatsBottom + seatsTop; i++)
            {
                k_Bcost = 2.25;
                k_Tcost = 2.0;
                if (i % 2 == 0)
                    seats.push_back(Seat(Seat::Place::Bottom, i + 1, k_Bcost * k_cost));
                else
                    seats.push_back(Seat(Seat::Place::Top, i + 1, k_Tcost * k_cost));
            }
            break;
        }
    }
public:

    Type get_type() const
    {
        return type;
    }

    unsigned int get_number() const
    {
        return number;
    }

    vector<Seat>& get_seats()
    {
        return seats;
    }

    static Wagon Create(Wagon::Type type, int number, double k)
    {

        switch (type)
        {
        case Type::ReservedSeat:
            return Wagon(Type::ReservedSeat, number, 27, 27, k);
        case Type::Coupe:
            return Wagon(Type::Coupe, number, 18, 18, k);
        case Type::SV:
            return Wagon(Type::SV, number, 0, 18, k);
        case Type::SV100:
            return Wagon(Type::SV100, number, 0, 100, k);
        default:
            throw exception("Unknown wagon type");
        }
    }
    unsigned int CountFreeSeats() const
    {
        unsigned int count = 0;
        for (auto s : seats)
        {
            if (s.is_free())
                count++;
        }
        return count;
    }

    void book_place(unsigned int num, string fio)
    {
        seats[num - 1].book(fio);
    }

    vector<unsigned int> free_places()
    {
        vector<unsigned int> res;
        for (auto s : seats)
        {
            if (s.is_free())
                res.push_back(s.get_number());
        }
        return res;
    }


    friend ostream& operator<<(ostream& os, const Wagon& v)
    {
        os << "Вагон номер: " << v.number << endl;
        os << "Тип вагона: ";
        switch (v.type)
        {
        case Type::ReservedSeat:
            os << "Плацкартный";
            break;
        case Type::Coupe:
            os << "Купейный";
            break;
        case Type::SV:
        case Type::SV100:
            os << "Сидячий";
            break;
        }
        os << endl;
        os << "Количество мест: " << v.seats.size() << endl;
        os << "Свободных мест: " << v.CountFreeSeats() << endl;
        os << "---------------------";
        return os;
    }
};

class Train
{
public:
    enum class Type
    {
        Lastochka,
        Branded,
        Express
    };
private:
    Type type;
    vector<Wagon> wagons;
    unsigned int number = 0;

    Train(Type type, unsigned int wagonCount) : type(type) {}
public:
    void set_number(unsigned int num)
    {
        number = num;
    }

    unsigned int get_number() const
    {
        return number;
    }

    Type get_type() const
    {
        return type;
    }

    vector<Wagon>& get_wagons()
    {
        return wagons;
    }
    static Train create(Type type, unsigned int num)
    {
        Train t = create(type);
        t.set_number(num);
        return t;
    }
    static Train create(Type type)
    {
        switch (type)
        {
        case Type::Lastochka:
        {
            Train train(Type::Lastochka, 8);
            for (unsigned int i = 0; i < 8; i++)
            {
                train.wagons.push_back(Wagon::Create(Wagon::Type::SV100, i + 1, 1));

            }
            return train;
        }
        case Type::Branded:
        {
            Train train(Type::Branded, 12);
            for (unsigned int i = 0; i < 2; i++)
                train.wagons.push_back(Wagon::Create(Wagon::Type::SV, i + 1, 1.5));
            for (unsigned int i = 2; i < 8; i++)
                train.wagons.push_back(Wagon::Create(Wagon::Type::Coupe, i + 1, 1.5));
            for (unsigned int i = 8; i < 12; i++)
                train.wagons.push_back(Wagon::Create(Wagon::Type::ReservedSeat, i + 1, 1.5));
            return train;
        }
        case Type::Express:
        {
            Train train(Type::Express, 12);
            for (unsigned int i = 0; i < 4; i++)
                train.wagons.push_back(Wagon::Create(Wagon::Type::Coupe, i + 1, 1.25));
            for (unsigned int i = 4; i < 12; i++)
                train.wagons.push_back(Wagon::Create(Wagon::Type::ReservedSeat, i + 1, 1.25));
            return train;
        }
        default:
        {
            throw exception("Unknown train type");
        }
        }
    }

    void book_place(unsigned int num_van, unsigned int num_place, string fio)
    {
        wagons[num_van - 1].book_place(num_place, fio);
    }

    unsigned int CountFreeSeats()
    {
        unsigned int count = 0;
        for (auto& v : wagons)
            count += v.CountFreeSeats();
        return count;
    }
};

struct Date
{
    int day = 9;
    int month = 5;
    int year = 1961;
    int days1[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int days2[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    Date() {}
    Date(int d, int m, int y)
    {

        if ((y < 1961) || (m > 12) || (m < 1))
            throw exception("Некорректная дата");
        else
        {
            year = y;
            month = m;
        }
        if (year % 4 == 0)
        {
            if ((d < 1) || (d > days2[month - 1]))
                throw exception("Некорректная дата");
            else day = d;
        }
        else
        {
            if ((d < 1) || (d > days1[month - 1]))
                throw exception("Некорректная дата");
            else day = d;
        }

    }
    friend ostream& operator<<(ostream& os, const Date& d)
    {
        if (d.day < 10)
            os << 0 << d.day;
        else
            os << d.day;
        os << ".";
        if (d.month < 10)
            os << 0 << d.month;
        else
            os << d.month;
        os << "." << d.year;
        return os;
    }
    bool operator==(const Date& d)
    {
        if ((day == d.day) && (month == d.month) && (year = d.year))
            return true;
        else
            return false;
    }
    Date operator++(int)
    {
        if (year % 4 == 0)
        {
            if (month < 12)
            {
                if (day < days2[month - 1])
                    day++;
                else
                {
                    day = 1;
                    month++;
                }

            }
            else if (month == 12)
            {
                if (day < days2[month - 1])
                    day++;
                else
                {
                    day = 1;
                    month = 1;
                    year++;
                }
            }
        }
        else
        {
            if (month < 12)
            {
                if (day < days1[month - 1])
                    day++;
                else
                {
                    day = 1;
                    month++;
                }

            }
            else if (month == 12)
            {
                if (day < days1[month - 1])
                    day++;
                else
                {
                    day = 1;
                    month = 1;
                    year++;
                }
            }
        }
        return *this;
    }
};
enum class Direction
{
    MSK_NN,
    NN_MSK
};

class GorkyRailway
{
    Date date;
    map<Direction, vector<Train>> trains;
public:
    GorkyRailway(Date d)
    {
        date = d;

        trains[Direction::NN_MSK] =
        {
            Train::create(Train::Type::Lastochka, 11),
            Train::create(Train::Type::Lastochka, 22),
            Train::create(Train::Type::Lastochka, 33),
            Train::create(Train::Type::Branded, 44),
            Train::create(Train::Type::Express, 55),
        };
        trains[Direction::MSK_NN] =
        {
            Train::create(Train::Type::Lastochka, 12),
            Train::create(Train::Type::Lastochka, 23),
            Train::create(Train::Type::Lastochka, 34),
            Train::create(Train::Type::Branded, 45),
            Train::create(Train::Type::Express, 56),
        };
    }

    vector<vector<Train>*> get_trains()
    {
        vector<vector<Train>*> vec;
        for (auto it = trains.begin(); it != trains.end(); ++it)
        {
            vec.push_back(&it->second);
        }
        return vec;
    }

    vector<Train>& get_trains(Direction dir)
    {
        return trains[dir];
    }

    Date get_date() const
    {
        return date;
    }
};

