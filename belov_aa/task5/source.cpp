#include <iostream>
#include <stdexcept>
#include <locale>

#include "TicketOffice.h"
#include "Cinema.h"

using namespace std;

void book_and_print(TicketOffice& office, Date d, Time t, string movie, unsigned int hall, string person, SeatType seat_type, unsigned int count)
{
    auto seats = office.book_seats(d, t, movie, hall, person, seat_type, count);

    double sum = 0;
    unsigned int i = 0;

    cout << "---------- Чек ----------" << endl;
    for (auto seat : seats)
    {
        sum += seat->price;

        cout << ++i << ") " << movie << endl;
        cout << "Дата: " << d << endl;
        cout << "Время: " << t << endl;
        cout << "Номер зала: " << hall << endl;
        cout << "Ряд: " << seat->row + 1 << endl;
        cout << "Место: " << seat->num + 1 << endl;
        cout << "Тип места: " << seat_type_names[seat->type] << endl;
        cout << "Покупатель: " << person << endl;
        cout << "Стоимость: " << seat->price << " руб." << endl;
        cout << endl;
    }

    cout << "Итого: " << sum << " руб." << endl;
    cout << "-------------------------" << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    Cinema cinema;
    cinema.register_hall({ 1, 5, 5, 250.0f, {
        { SeatType::Regular, 20 },
        { SeatType::VIP, 5 },
    } });
    cinema.add_show({ 26, 04, 2023 }, { 12, 00 }, "Аватар 2: Путь воды", 1);
    cinema.add_show({ 26, 04, 2023 }, { 19, 40 }, "Человек-паук: Нет пути домой", 1);

    TicketOffice office(cinema, 3, 10);

    auto schedule = office.get_schedule();
    for (auto it_day = schedule.begin(); it_day != schedule.end(); ++it_day)
    {
        Cinema::DaySchedule* day = it_day->second;
        cout << "   Сеансы на " << it_day->first << endl;

        for (auto it_time = day->begin(); it_time != day->end(); ++it_time)
        {
            cout << " в " << it_time->first << ":" << endl;
            for (auto& show : it_time->second)
            {
                cout << show.get_name() << " (зал №" << show.get_hall().id << ")" << endl;
            }
        }
    }

    try
    {
        book_and_print(office, { 26, 04, 2023 }, { 12, 00 }, "Аватар 2: Путь воды", 1, "Artem Belov", SeatType::VIP, 2);
        book_and_print(office, { 26, 04, 2023 }, { 19, 40 }, "Человек-паук: Нет пути домой", 1, "Artem Belov", SeatType::Regular, 1);
    }
    catch (exception e)
    {
        cerr << e.what() << endl;
    }
    
    system("PAUSE");

}