#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include "Header.h"
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;
SMALL_RECT window;
COORD buf;

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13, LEFT = 75
};

enum  Menu {
   Date_time_session = 0, Available_sessions = 1, Check_availability = 2, Session_Search = 3, EXIT = 4
};

enum  Menu_2 {
   Reserve = 0, Сancellation_Reserve = 1
};

char Menu[5][50] = {
   "Дата и время сеанса",
   "Доступные сеансы",
   "Проверить наличие мест",
   "Поиск сеанса",
   "Выход"
};

char Menu_2[2][50] = {
   "Зарезервировать",
   "Отмена резервирования"
};

char Menu_3[2][50] = {
   "Обычные места",
   "VIP места"
};

int active_menu = 0, active_menu_2 = 0, active_menu_3 = 0;
#define SIZE 5
#define SIZE_2 2
#define SIZE_3 2

class Time
{
public:

   Time(int h = 0, int m = 0) : Hours(h), Minutes(m) {}

   void set_Hours(int h) { Hours = h; }
   void set_Minutes(int m) { Minutes = m; }
   int get_Hours() { return Hours; }
   int get_Minutes() { return Minutes; }

   void ShowTime(ostream& strm) const
   {
      strm << Hours << ":" << Minutes;
   }

   int minutes_dif(const Time& t)
   {
      return (t.Hours * 60 + t.Minutes) - (Hours * 60 + Minutes);
   }

   bool operator==(const Time& t)
   {
      if (Hours == t.Hours && Minutes == t.Minutes)
         return true;
      return false;
   }

private:

   int Hours;
   int Minutes;
   friend ostream& operator<<(ostream& strm, const Time& time);
   friend class Cinema;
   friend class Ticket_office;
};

ostream& operator<<(ostream& strm, const Time& time)
{
   time.ShowTime(strm);
   return strm;
}

class Date
{
public:

   Date(int day = 1, int month = 1) : Day(day), Month(month), Year(2023) {}

   void set_Day(int day)
   {
      Day = day;
      if (Day > duration_month[Month])
      {
         Day = Day - duration_month[Month];
         Month++;
      }
   }
   void set_Month(int month) { Month = month; }
   int get_Day() { return Day; }
   int get_Month() { return Month; }

   bool operator==(const Date& d)
   {
      if (Month == d.Month && Day == d.Day)
         return true;
      return false;
   }

private:

   int Day;
   int Month;
   int Year;
   string name_month[13] = {" ","Января", "Февраля", "Марта", "Апреля", "Мая", "Июня", "Июля", "Августа", "Сентября", "Октября", "Ноября", "Декабря"};
   int duration_month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   friend ostream& operator<<(ostream& out, const Date& date);
   friend class Cinema;
   friend class Ticket_office;
};

ostream& operator<<(ostream& out, const Date& date)
{
   out << date.Day << " " << date.name_month[date.Month] << " " << date.Year;
   return out;
}

class CinemaHall
{
public:

   CinemaHall(int n = 0, int srows = 0, int vrows = 0, int srs = 0, int vrs = 0, int sprice = 0, int vprice = 0)
   {
      Number = n;
      StandardRows = srows;
      VIPRows = vrows;
      StandardRowSeats = srs;
      VIPRowSeats = vrs;
      StandartPrice = sprice;
      VIPPrice = vprice;
      FreeSTseats = StandardRows * StandardRowSeats;
      FreeVIPseats = VIPRows * VIPRowSeats;
   }
   
   void set_Number(int n) { Number = n; }
   void set_StandardRows(int srows) { StandardRows = srows; }
   void set_VIPRows(int vrows) { VIPRows = vrows; }
   void set_StandardRowSeats(int srs) { StandardRowSeats = srs; }
   void set_VIPRowSeats(int vrs) { VIPRowSeats = vrs; }
   void set_StandartPrice(int sprice) { StandartPrice = sprice; }
   void set_VIPPrice(int vprice) { VIPPrice = vprice; }
   int get_Number() { return Number; }
   int get_StandardRows() { return StandardRows; }
   int get_VIPRows() { return VIPRows; }
   int get_StandardRowSeats() { return StandardRowSeats; }
   int get_VIPRowSeats() { return VIPRowSeats; }
   int get_StandartPrice() { return StandartPrice; }
   int get_VIPPrice() { return VIPPrice; }

   void Place_Calculation()
   {
      FreeSTseats = StandardRows * StandardRowSeats;
      FreeVIPseats = VIPRows * VIPRowSeats;
   }

   bool operator==(const CinemaHall& h)
   {
      if (Number == h.Number)
         return true;
      return false;
   }

private:
   int Number;
   int StandardRows;
   int VIPRows;
   int StandardRowSeats;
   int VIPRowSeats;
   int FreeSTseats;
   int FreeVIPseats;
   int StandartPrice;
   int VIPPrice;
   friend ostream& operator<<(ostream& out, const CinemaHall& Hall);
   friend struct Film;
   friend class Cinema;
   friend class Ticket_office;
   friend ostream& operator<<(ostream& out, const Film& Film);
};

ostream& operator<<(ostream& out, const CinemaHall& Hall)
{
   out << "Зал: " << Hall.Number << endl;
   out << "Цена стандартного места: " << Hall.StandartPrice << " рублей" << endl;
   out << "Цена VIP места: " << Hall.VIPPrice << " рублей" << endl;
   return out;
}

struct Film
{
   string Name = "Film";
   CinemaHall Hall;
   Date ShowDate;
   Time ShowTime;
   int NumberHall = 0;
   int FreeSTseats = 0;
   int FreeVIPseats = 0;
   friend ostream& operator<<(ostream& out, const Film& Film);
   bool operator==(const Film& f)
   {
      if (Name == f.Name && ShowDate == f.ShowDate &&
         ShowTime == f.ShowTime && Hall == f.Hall && NumberHall == f.NumberHall && FreeSTseats == f.FreeSTseats && FreeVIPseats == f.FreeVIPseats)
         return true;
      return false;
   }
   void set_FreeSTseats(int st) { FreeSTseats = st; }
   void set_FreeVIPseats(int vp) { FreeVIPseats = vp; }
};

ostream& operator<<(ostream& out, const Film& Film)
{
   out << "Фильм: " << "'" << Film.Name << "'" << endl;
   out << "Дата: " << Film.ShowDate << endl;
   out << "Время начала: " << Film.ShowTime << endl;
   out << "Зал:" << Film.Hall.Number << endl;
   return out;
}

class Cinema
{
public:
   Cinema() {}

   Cinema(vector<Film> Films) { movie_sessions = Films; }

   void Creating_movie_session(string n, Time t, Date d, CinemaHall h)
   {
      Film movie_s;
      movie_s.Name = n;
      movie_s.ShowTime = t;
      movie_s.ShowDate = d;
      movie_s.Hall = h;
      movie_s.Hall.Place_Calculation();
      movie_s.FreeSTseats = movie_s.Hall.StandardRows * movie_s.Hall.StandardRowSeats;
      movie_s.FreeVIPseats = movie_s.Hall.VIPRows * movie_s.Hall.VIPRowSeats;
      movie_sessions.push_back(movie_s);
   }

   size_t getMovieSessions_count() { return movie_sessions.size(); }

   void Sessions_day_time(const Date& d, const Time& t)
   {
      int num = 0;
      bool fl = false;
      Date tmp_d = d;
      int beginning = d.Day;
      int end = d.Day + 3;
      for (; beginning < end; beginning++)
      {
         for (int i = 0; i < getMovieSessions_count(); i++)
         {
            if (movie_sessions[i].ShowDate == tmp_d)
            {
               if (fl)
               {
                  cout << num + 1 << ") ";
                  num++;
                  PrintMoviesession(i);
               }
               else
               {
                  if (movie_sessions[i].ShowTime.minutes_dif(t) < 10)
                  {
                     cout << num + 1 << ") ";
                     num++;
                     PrintMoviesession(i);
                  }
               }
            }
         }
         fl = true;
         tmp_d.set_Day(tmp_d.Day + 1);
      }
   }

   void PrintMoviesession(int i)
   {
      cout << movie_sessions[i].ShowDate << "   '" << movie_sessions[i].Name << "'" << "   Зал: " << movie_sessions[i].Hall.Number << "   Начало сеанса: " << movie_sessions[i].ShowTime << "\n\n";
   }
   
   Film& operator[](int i) { return movie_sessions[i]; }

private:
   vector <Film> movie_sessions;
   bool Acquired = false;
   friend class Ticket_office;
};

class Ticket_office
{
public:

   Ticket_office() {}

   Ticket_office(Date date, Time time, Cinema list, int tickets) :
      DatePurchase(date), TimePurchase(time), clist(list)
   {
      limitation = DatePurchase;
      limitation.set_Day(limitation.Day + 3);
   }
  
   void set_DatePurchase(Date d) { DatePurchase = d; }
   void set_TimePurchase(Time t) { TimePurchase = t; }
   void set_clist(Cinema list) { clist = list; }
   void set_session(const Film& Film)
   {
      session = Film;
      Strow = session.Hall.StandardRows;
      Viprow = session.Hall.VIPRows;
      Stnum = session.Hall.StandardRowSeats;
      Vipnum = session.Hall.VIPRowSeats;
   }
   Date get_DatePurchase() { return DatePurchase; }
   Time get_TimePurchase() { return TimePurchase; }
   int CheckFreePl(bool status, int ind)
   {
      if (status == true)
         return clist.movie_sessions[ind].FreeVIPseats;
      return clist.movie_sessions[ind].FreeSTseats;
   }

   int getSessionIndex(const Film& film)
   {
      for (int i = 0; i < clist.getMovieSessions_count(); i++)
      {
         if (clist[i] == film)
            return i;
      }
      return -1;
   }

   double CalculatePrice(bool status)
   {
      double price;
      if (status == true)
      {
         price = session.Hall.VIPPrice;
      }
      else
      {
         price = session.Hall.StandartPrice;
      }
      if (session.ShowTime.Hours < 12)
      {
         price *= 0.75;
      }
      if (session.ShowTime.Hours > 17)
      {
         price *= 1.5;
      }
      return price;
   }

   void PrintPlace(bool status, int ind)
   {
      int tmp, VIPplace, STplace;
      VIPplace = session.Hall.VIPRows * session.Hall.VIPRowSeats;
      STplace = session.Hall.StandardRows * session.Hall.StandardRowSeats;
      int row = 0, num = 0;
      if (status == true)
      {
         tmp = clist.movie_sessions[ind].FreeVIPseats;
         if (clist.Acquired == true)
         {
            for (; tmp < VIPplace; tmp++)
            {
               Vipnum--;
               if (Vipnum == 0)
               {
                  Vipnum = session.Hall.VIPRowSeats;
                  Viprow--;
               }
            }
         }
         clist.Acquired = false;
         for (; Viprow > 0;)
         {
            for (; Vipnum > 0;)
            {
               row = Viprow;
               num = Vipnum;
               Vipnum -= 1;
               break;
            }
            if (Vipnum == 0)
            {
               Vipnum = session.Hall.VIPRowSeats;
               Viprow--;
            }
            break;
         }
      }
      else
      {
         tmp = clist.movie_sessions[ind].FreeSTseats;
         if (clist.Acquired == true)
         {
            for (; tmp < STplace; tmp++)
            {
               Stnum--;
               if (Stnum == 0)
               {
                  Stnum = session.Hall.StandardRowSeats;
                  Strow--;
               }
            }
         }
         clist.Acquired = false;
         for (; Strow > 0;)
         {
            for (; Stnum > 0;)
            {
               row = Strow;
               num = Stnum;
               Stnum -= 1;
               break;
            }
            if (Stnum == 0)
            {
               Stnum = session.Hall.StandardRowSeats;
               Strow--;
            }
            break;
         }
      }
      cout << "ряд " << row << "  место " << num;
   }

   void PrintTickets(int cnt, bool status, int ind)
   {
      for (int i = 0; i < cnt; i++)
      {
         cout << "Фильм: " << "'" << session.Name << "'" << endl;
         cout << "Сеанс: " << session.ShowDate << "   " << session.ShowTime << endl;
         cout << "Кинотеатр: "<< "Небо, "<< "зал " << session.Hall.Number << endl;
         PrintPlace(status, ind);
         cout << "  зона ";
         if (status == true)
         {
            cout << " VIP" << endl;
            clist.movie_sessions[ind].FreeVIPseats--;
         }
         else
         {
            cout << " Обычная" << endl;
            clist.movie_sessions[ind].FreeSTseats--;
         }
         cout << "Стоимость билета: " << CalculatePrice(status) << " рублей" << "\n\n" << endl;
         itog += CalculatePrice(status);
      }
      cout << "Общая стоимость: " << itog << " рублей" << endl;
      cnt = 0;
      clist.Acquired = true;
      itog = 0;
   }

   void Print_Sessions()
   {
      clist.Sessions_day_time(DatePurchase, TimePurchase);
   }

   Film FindSession(Date d, Time t)
   {
      Film movie_session;
      vector<Film> list;
      Date date;
      Time time;
      int Hours, Minutes, Day, Month, Num, cnt = 0;
      string Name;
      Month = d.Month;
      do
      {
         system("cls");
         textcolor(MAGENTA);
         cout << "Введите дату сеанса(число 'пробел' месяц): ";
         cin >> Day;
         cin >> Month;
      } while (Day < d.Day || Day - d.Day > 2);
      system("cls");
      date.set_Day(Day);
      date.set_Month(Month);
      for (int i = 0; i < clist.getMovieSessions_count(); i++)
      {
         if (date == d)
         {
            if (clist.movie_sessions[i].ShowDate == date && clist.movie_sessions[i].ShowTime.minutes_dif(t) < 10)
            {
               list.push_back(clist.movie_sessions[i]);
               cout << clist.movie_sessions[i] << endl;
               cnt++;
            }
         }
         else
         {
            if (clist.movie_sessions[i].ShowDate == date)
            {
               list.push_back(clist.movie_sessions[i]);
               cout << clist.movie_sessions[i] << endl;
               cnt++;
            }
         }
      }
      if (cnt == 0)
      {
         movie_session.Name = "F";
         return movie_session;
      }
      if (cnt == 1)
      {
         return list[0];
      }
      cnt = 0;
      system("pause");
      cout << "\nВведите название сеанса: ";
      cin.ignore();
      getline(cin, Name);

      system("cls");
      for (int i = 0; i < list.size();)
      {
         if (list[i].Name == Name)
         {
            cout << list[i] << endl;
            cnt++;
            i++;
         }
         else
         {
            list.erase(list.begin() + i);
         }

      }
      system("pause");
      if (cnt == 0)
      {
         movie_session.Name = "F";
         return movie_session;
      }
      if (cnt == 1)
      {
         return list[0];
      }
      cnt = 0;
      cout << "\nВведите время сеанса(часы 'пробел' минуты): ";
      cin >> Hours;
      cin >> Minutes;
      system("cls");
      time.set_Hours(Hours);
      time.set_Minutes(Minutes);
      for (int i = 0; i < list.size();)
      {
         if (list[i].ShowTime == time) {
            cout << list[i] << endl;
            cnt++;
            i++;
         }
            
         else
         {
            list.erase(list.begin() + i);
         }
      }
      system("pause");
      if (cnt == 0)
      {
         movie_session.Name = "F";
         return movie_session;
      }
      if (cnt == 1)
      {
         return list[0];
      }
      cnt = 0;
      cout << "\nВведите номер зала: ";
      cin >> Num;
      system("cls");
      for (int i = 0; i < list.size();)
      {
         if (list[i].Hall.Number != Num)
            list.erase(list.begin() + i);
         else
         {
            cout << list[i];
            cnt++;
            i++;
         }
      }
      if (cnt == 1)
      {
         return list[0];
      }
      movie_session.Name = "F";
      return movie_session;
   }

   void Adding_places(int ind, bool status, int cnt)
   {
      if (status == true)
      {
         clist.movie_sessions[ind].FreeVIPseats = clist.movie_sessions[ind].FreeVIPseats + cnt;
      }
      else
      {
         clist.movie_sessions[ind].FreeSTseats = clist.movie_sessions[ind].FreeSTseats + cnt;
      }
   } 

private:
   Date DatePurchase;
   Time TimePurchase;
   Date limitation;
   double itog = 0;
   Cinema clist;
   int Strow = 0, Viprow = 0, Stnum= 0, Vipnum = 0; 
   Film session;
};


Cinema movie_theater_sessions;
void Create_movie_theater_sessions()
{
   Date date(1, 4);
   Date date_2(1, 4);
   Date date_3(1, 4);
   Date date_4(1, 4);
   Time time;
   string name;
   CinemaHall hall_1(1, 5, 5, 10, 5, 250, 500);
   CinemaHall hall_2(2, 5, 5, 10, 5, 250, 500);
   int i = date.get_Day();
   int j = date_2.get_Day();
   int m = date_3.get_Day();
   int n = date_4.get_Day();
   int d = i + 30;
   name = "Вызов";
   for (i; i < d; i++)
   {
      if (i % 2 != 0)
      {
         time.set_Hours(10);
         time.set_Minutes(50);
         movie_theater_sessions.Creating_movie_session(name, time, date, hall_1);
         time.set_Hours(12);
         time.set_Minutes(30);
         movie_theater_sessions.Creating_movie_session(name, time, date, hall_2);
      }
      else
      {
         time.set_Hours(9);
         time.set_Minutes(15);
         movie_theater_sessions.Creating_movie_session(name, time, date, hall_1);
         time.set_Hours(11);
         time.set_Minutes(10);
         movie_theater_sessions.Creating_movie_session(name, time, date, hall_2);
      }
      date.set_Day(date.get_Day() + 1);
   }
   name = "Поехавшая";
   for (j; j < d; j++)
   {
      if (j % 2 != 0)
      {
         time.set_Hours(12);
         time.set_Minutes(50);
         movie_theater_sessions.Creating_movie_session(name, time, date_2, hall_1);
         time.set_Hours(14);
         time.set_Minutes(30);
         movie_theater_sessions.Creating_movie_session(name, time, date_2, hall_2);
      }
      else
      {
         time.set_Hours(11);
         time.set_Minutes(15);
         movie_theater_sessions.Creating_movie_session(name, time, date_2, hall_1);
         time.set_Hours(13);
         time.set_Minutes(10);
         movie_theater_sessions.Creating_movie_session(name, time, date_2, hall_2);
      }
      date_2.set_Day(date_2.get_Day() + 1);
   }
   name = "Три мушкетера";
   for (m; m < d; m++)
   {
      if (m % 2 != 0)
      {
         time.set_Hours(14);
         time.set_Minutes(50);
         movie_theater_sessions.Creating_movie_session(name, time, date_3, hall_1);
         time.set_Hours(16);
         time.set_Minutes(30);
         movie_theater_sessions.Creating_movie_session(name, time, date_3, hall_2);
      }
      else
      {
         time.set_Hours(13);
         time.set_Minutes(15);
         movie_theater_sessions.Creating_movie_session(name, time, date_3, hall_1);
         time.set_Hours(15);
         time.set_Minutes(10);
         movie_theater_sessions.Creating_movie_session(name, time, date_3, hall_2);
      }
      date_3.set_Day(date_3.get_Day() + 1);
   }

   name = "Форсаж 10";
   for (n; n < d; n++)
   {
      if (n % 2 != 0)
      {
         time.set_Hours(16);
         time.set_Minutes(50);
         movie_theater_sessions.Creating_movie_session(name, time, date_4, hall_1);
         time.set_Hours(18);
         time.set_Minutes(30);
         movie_theater_sessions.Creating_movie_session(name, time, date_4, hall_2);
         time.set_Hours(18);
         time.set_Minutes(30);
         movie_theater_sessions.Creating_movie_session(name, time, date_4, hall_1);
      }
      else
      {
         time.set_Hours(15);
         time.set_Minutes(15);
         movie_theater_sessions.Creating_movie_session(name, time, date_4, hall_1);
         time.set_Hours(17);
         time.set_Minutes(10);
         movie_theater_sessions.Creating_movie_session(name, time, date_4, hall_2);
      }
      date_4.set_Day(date_4.get_Day() + 1);
   }
}

void main()
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Кинотеатр");
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   int variable_x;
   char ch;
   clrscr();
   variable_x = (window.Left + window.Right) / 30;
   textcolor(MAGENTA);
   gotoxy(variable_x + 44, wherey() + 5);
   cout << "Добро пожаловать в Кинотеатр" << endl;
   gotoxy(variable_x + 31, wherey() + 3);
   cout << "Здесь вы сможете зарезервировать билеты на сеанс в кино" << endl;
   gotoxy(variable_x + 18, wherey() + 1);
   cout << "Расписание доступно с 1 по 30 апреля, но билет можно купить лишь за 3 дня до сеанса" << endl;
   gotoxy(variable_x + 33, wherey() + 1);
   cout << "За одну операцию нельзя резервировать более 5 мест" << endl;
   gotoxy(variable_x + 15, wherey() + 1);
   cout << "Для начала вам необходимо ввести дату и время, после чего можно работать с другими пунктами" << endl;
   gotoxy(variable_x + 37, wherey() + 1);
   system("pause");

   int Hours, Minutes, Day, Month, Place_cnt, flag, ind, flag_1, fl, stat;
   string Name_Film;
   Ticket_office cashier;
   Date date;
   Time time;
   Film film;
   bool status;

   textcolor(MAGENTA);
   system("cls");

   Create_movie_theater_sessions();
   cashier.set_clist(movie_theater_sessions);

   while (1) {
      hidecursor();
      system("cls");
      for (int i = 0; i < SIZE; i++) {
         if (i == active_menu)
            textcolor(GREEN);
         else
            textcolor(YELLOW);
         cout << Menu[i] << "\n";
      }
      ch = _getch();
      if (ch == -32)
         ch = _getch();

      switch (ch)
      {
      case UP:
         if (active_menu > 0)
            active_menu--;
         break;
      case DOWN:
         if (active_menu < SIZE - 1)
            active_menu++;
         break;
      case ENTER:
         system("cls");
         switch (active_menu)
         {
         case Date_time_session:
            textcolor(MAGENTA);
            cout << "Введите дату(число 'пробел' месяц): ";
            cin >> Day;
            cin >> Month;
            date.set_Day(Day);
            date.set_Month(Month);
            cout << "Введите время(часы 'пробел' минуты): ";
            cin >> Hours;
            cin >> Minutes;
            time.set_Hours(Hours);
            time.set_Minutes(Minutes);
            cashier.set_DatePurchase(date);
            cashier.set_TimePurchase(time);
            break;

         case Available_sessions:
            textcolor(MAGENTA);
            cout << "Доступные сеансы:\n" << endl;
            cashier.Print_Sessions();
            system("pause");
            break;

         case Check_availability:
            film = cashier.FindSession(date, time);
            if (film.Name != "F")
            {
               ind = cashier.getSessionIndex(film);
               cashier.set_session(movie_theater_sessions[ind]);

               fl = 1;
               while (fl) {
                  system("cls");
                  for (int i = 0; i < SIZE_3; i++) {
                     if (i == active_menu_3)
                        textcolor(GREEN);
                     else
                        textcolor(YELLOW);
                     cout << Menu_3[i] << "\n";

                  }
                  ch = _getch();
                  if (ch == -32)
                     ch = _getch();

                  switch (ch)
                  {
                  case UP:
                     if (active_menu_3 > 0)
                        active_menu_3--;
                     break;
                  case DOWN:
                     if (active_menu_3 < SIZE_3 - 1)
                        active_menu_3++;
                     break;
                  case LEFT:
                     fl = 0;
                     break;
                  case ENTER:
                     stat = active_menu_3;
                     if (stat == 1)
                        status = true;
                     else
                        status = false;
                     system("cls");
                     textcolor(MAGENTA);
                     cout << "На данный сеанс осталось " << cashier.CheckFreePl(status, ind) << " мест" << endl;
                     fl = 0;
                     system("pause");

                  }
               }
            }
            else
            {
               system("cls");
               textcolor(RED);
               cout << "Сеансов не найдено" << endl;
               textcolor(MAGENTA);
               system("pause");
            }
            break;

         case Session_Search:
            film = cashier.FindSession(date, time);
            if (film.Name != "F")
            {
               ind = cashier.getSessionIndex(film);
               cashier.set_session(movie_theater_sessions[ind]);
               flag = 1;

               while (flag) {
                  system("cls");
                  for (int i = 0; i < SIZE_3; i++) {
                     if (i == active_menu_3)
                        textcolor(GREEN);
                     else
                        textcolor(YELLOW);
                     cout << Menu_3[i] << "\n";

                  }
                  ch = _getch();
                  if (ch == -32)
                     ch = _getch();

                  switch (ch)
                  {
                  case UP:
                     if (active_menu_3 > 0)
                        active_menu_3--;
                     break;
                  case DOWN:
                     if (active_menu_3 < SIZE_3 - 1)
                        active_menu_3++;
                     break;
                  case LEFT:
                     flag = 0;
                     break;
                  case ENTER:
                     stat = active_menu_3;
                     if (stat == 1)
                        status = true;
                     else
                        status = false;
                     do
                     {
                        textcolor(MAGENTA);
                        system("cls");
                        cout << "Введите количество мест: ";
                        cin >> Place_cnt;
                     } while (Place_cnt < 1 || Place_cnt > 5);
                     system("cls");
                     if (Place_cnt <= cashier.CheckFreePl(status, ind))
                     {
                        cashier.PrintTickets(Place_cnt, status, ind);
                        system("pause");
                        flag_1 = 1;
                        while (flag_1) {
                           system("cls");
                           for (int i = 0; i < SIZE_2; i++) {
                              if (i == active_menu_2)
                                 textcolor(GREEN);
                              else
                                 textcolor(YELLOW);
                              cout << Menu_2[i] << "\n";

                           }
                           ch = _getch();
                           if (ch == -32)
                              ch = _getch();

                           switch (ch)
                           {
                           case UP:
                              if (active_menu_2 > 0)
                                 active_menu_2--;
                              break;
                           case DOWN:
                              if (active_menu_2 < SIZE_2 - 1)
                                 active_menu_2++;
                              break;
                           case LEFT:
                              flag_1 = 0;
                              break;
                           case ENTER:
                              switch (active_menu_2) 
                              {
                              case Reserve:
                                 flag_1 = 0;
                                 break;

                              case Сancellation_Reserve:
                                 cashier.Adding_places(ind, status, Place_cnt);
                                 flag_1 = 0;
                                 break;
                              }
                              flag = 0;
                           }
                        }
                     }
                     else 
                     {
                        system("cls");
                        textcolor(RED);
                        cout << "На данный сеанс осталось " << cashier.CheckFreePl(status, ind) << " мест" << endl;
                        textcolor(MAGENTA);
                        system("pause");
                     }
                  }
               }
            }
            else
            {
               system("cls");
               cout << "Сеансов не найдено" << endl;
               system("pause");
            }
            break;

         case EXIT:
            exit(0);
            break;

         }
      }
   }
}