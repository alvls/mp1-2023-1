#include "Header.h"

class TicketOffice
{
    MyTime purchase_time;
    MyDate purchase_date;
    MyDate stop_day;
    Cinema list;
    int b_row = 0, b_number = 0, v_row = 0, v_number = 0, count = 0;
    double cost = 0;
    Film chosen_session;
    int count_tickets = 1;
public:
    TicketOffice() {}
    TicketOffice(MyTime _pt, MyDate _pd, Cinema lst, int cn_tckts): 
        purchase_time(_pt), purchase_date(_pd), list(lst), count_tickets(cn_tckts)
    {
        stop_day = purchase_date;
        stop_day.set_day(stop_day.day + 3);
    }
    void null_cost() { cost = 0; }
    void set_purchase_time(MyTime time) { purchase_time = time; }
    void set_purchase_date(MyDate date) { purchase_date = date; }
    void set_new_list(Cinema _list) { list = _list; }
    void set_chosen_session(const Film& film) 
    { 
        chosen_session = film;
        v_row = chosen_session.film_hall.vip_rows;
        v_number = chosen_session.film_hall.vip_rows_seats;
        b_row = chosen_session.film_hall.base_rows;
        b_number = chosen_session.film_hall.base_rows_seats;
    }
    void print_enable_sessions()
    {
        list.sessions_for_day_and_time(purchase_date, purchase_time);
    }
    void print_sessions_by_hall(int num)
    {
        list.sessions_by_hall(purchase_date, purchase_time, num);
    }
    int check_free_place(bool vip_status, int index)
    {
        if (vip_status == true)
            return list.sessions[index].free_vip;
        return list.sessions[index].free_base;
    }
    int return_session_index(const Film& film)
    {
        for (int i = 0; i < list.get_sessions_count(); i++)
        {
            if (list[i] == film)
                return i;
        }
        return -1;
    }
    void sessions_by_date(const MyDate& date)
    {
        list.sessions_by_day(date);
    }
    void sessions_by_name(string fname)
    {
        list.sessions_by_name(purchase_date, purchase_time, fname);
    }
    void print_tickets(int count, bool vip_status, int index)
    {
        cout << "\t\tКинотеатр ПИНЖФИЛЬМ" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << "\t" << chosen_session.film_name << endl;
            cout << "Дата: " << chosen_session.session_date << endl;
            cout << "Время: " << chosen_session.start_time << endl;
            cout << "Зал: " << chosen_session.hall_number << endl;
            cout << "Зона: ";
            if (vip_status == true)
            {
                cout << "VIP" << endl;
                list.sessions[index].free_vip--;
            }
            else
            {
                cout << "Общая" << endl;
                list.sessions[index].free_base--;
            }
            print_place(vip_status, index);
            cout << "Цена билета: " << calculate_price(vip_status) << "\n\n";
            cost += calculate_price(vip_status);
        }
        cout << "Общая стоимость заказа = " << cost << endl;
        count = 0;
        list.isBought = true;
    }
    void list_plus_place(bool vip,int index, int count)
    {
        if (vip == true)
        {
            list.sessions[index].free_vip = list.sessions[index].free_vip + count;
        }
        else
        {
            list.sessions[index].free_base = list.sessions[index].free_base + count;
        }
    }
    double calculate_price(bool vip_status)
    {
        double price;
        price = chosen_session.film_hall.price;
        if (vip_status == true)
        {
            price = price * 1.5;
        }
        if (chosen_session.start_time.hours < 12)
        {
            price = price * 0.75;
        }
        if (chosen_session.start_time.hours > 18)
        {
            price = price * 1.5;
        }
        return price;
    }
    void print_place(bool vip_status, int index)
    {
        int temp, v_place, b_place, t_count = 0;
        v_place = chosen_session.film_hall.vip_rows * chosen_session.film_hall.vip_rows_seats;
        b_place = chosen_session.film_hall.base_rows * chosen_session.film_hall.base_rows_seats;
        int row = 0, number = 0;
        if (vip_status == true)
        {
            temp = list.sessions[index].free_vip+1;
            if (list.isBought==true)
            {
                for (; temp < v_place; temp++)
                {
                    v_number--;
                    count += 1;
                    if (v_number == 0)
                    {
                        v_number = chosen_session.film_hall.vip_rows_seats;
                        count = 0;
                        v_row--;
                    }
                }
            }
            list.isBought = false;
            for (; v_row > 0;)
            {
                for (; v_number > 0;)
                {
                    row = v_row;
                    number = v_number;
                    v_number -= 1;
                    count += 1;
                    break;
                }
                if (v_number == 0)
                {
                    v_number = chosen_session.film_hall.vip_rows_seats;
                    count = 0;
                    v_row--;
                }
                break;
            }
        }
        else
        {
            temp = list.sessions[index].free_base + 1;
            if (list.isBought == true)
            {
                for (; temp < b_place; temp++)
                {
                    b_number--;
                    count += 1;
                    if (b_number == 0)
                    {
                        b_number = chosen_session.film_hall.base_rows_seats;
                        count = 0;
                        b_row--;
                    }
                }
            }
            list.isBought = false;
            for (; b_row > 0;)
            {
                for (; b_number > 0;)
                {
                    row = b_row;
                    number = b_number;
                    b_number -= 1;
                    count += 1;
                    break;
                }
                if (b_number == 0)
                {
                    b_number = chosen_session.film_hall.base_rows_seats;
                    count = 0;
                    b_row--;
                }
                break;
            }
        }
        cout << "Ряд: " << row << "\tМесто: " << number << endl;
    }
    Film find_session(MyDate t_day, MyTime t_time)
    {
        setlocale(LC_ALL, "Rus");
        Film session;
        Cinema manager = list;
        vector<Film> temp_list;
        MyDate s_day;
        MyTime s_time;
        int day, month, hr, min, number, cn = 0;
        string name;
        month = t_day.month;
        do
        {
            system("cls");
            cout << "Введите число сеанса (не раньше дня покупки, не позже 3 дней)" << endl;
            cin >> day;
        } while (day < t_day.return_day() || day - t_day.return_day() > 2);
        system("cls");
        s_day.set_day(day);
        s_day.set_month(month);
        for (int i = 0; i < list.get_sessions_count(); i++)
        {
            if (s_day == t_day)
            {
                if (list.sessions[i].session_date == s_day && list.sessions[i].start_time.minutes_different(t_time) < 10)
                {
                    temp_list.push_back(list.sessions[i]);
                    cout << list.sessions[i] << endl;
                    cn++;
                }
            }
            else
            {
                if (list.sessions[i].session_date == s_day)
                {
                    temp_list.push_back(list.sessions[i]);
                    cout << list.sessions[i] << endl;
                    cn++;
                }
            }
        }
        system("pause");
        if (cn == 0)
        {
            session.film_name = "fail";
            return session;
        }
        if (cn == 1)
        {
            return temp_list[0];
        }
        cn = 0;
        cout << "\nВведите название сеанса: ";
        cin.ignore();
        getline(cin, name); 
        system("cls");
        for (int i = 0; i < temp_list.size();)
        {
            if (temp_list[i].film_name == name)
            {
                cout << temp_list[i];
                cn++;
                i++;
            }
            else
                temp_list.erase(temp_list.begin() + i);
        }
        if (cn == 0)
        {
            session.film_name = "fail";
            return session;
        }
        if (cn == 1)
        {
            return temp_list[0];
        }
        cn = 0;
        cout << "Введите время сеанса: ";
        cin >> hr;
        cin >> min;
        s_time.set_hours(hr);
        s_time.set_minutes(min);
        for (int i = 0; i < temp_list.size();)
        {
            if (temp_list[i].start_time != s_time)
                temp_list.erase(temp_list.begin() + i);
            else
            {
                cout << temp_list[i];
                cn++;
                i++;
            }
        }
        system("pause");
        system("cls");
        if (cn == 0)
        {
            session.film_name = "fail";
            return session;
        }
        if (cn == 1)
        {
            return temp_list[0];
        }
        cn = 0;
        cout << "Введите номер зала ";
        cin >> number;
        for (int i = 0; i < temp_list.size();)
        {
            if (temp_list[i].hall_number != number)
                temp_list.erase(temp_list.begin() + i);
            else
            {
                cout << temp_list[i];
                cn++;
                i++;
            }
        }
        if (cn == 1)
        {
            system("pause");
            return temp_list[0];
        }
        session.film_name = "fail";
        return session;
    }
};