#include <iostream>
#include <iomanip>

bool is_valid_date(int day, int mon)
{
  if (day < 1 || day > 31 || mon < 1 || mon > 12)
    return false;
  std::time_t now = std::time(nullptr);
  std::tm* local_time = std::localtime(&now);
  int curr_mon = local_time->tm_mon + 1;
  int curr_day = local_time->tm_mday;
  int mon_diff = mon - curr_mon;
  int day_diff = day - curr_day;
  int total_diff = mon_diff * 30 + day_diff;
  return total_diff >= 0 && total_diff < 30;
}

enum Vagon_type
{
  birdvagon = 1,
  pzkrt,
  cupe,
  sv,
};

enum Train_type
{
  birdtrain = 1,
  fasttrain,
  firmtrain,
};

struct Railway_data {
  int tm_day;  // дни от 1 до 31
  int tm_mon;   // месяцы от 1 до 11
  Railway_data(): tm_day(0), tm_mon(0) {}
  Railway_data(int day, int mon): tm_day(day), tm_mon(mon) {}

  // Перегрузка префиксного инкремента
  Railway_data& operator++() {
    if (tm_day == 31) {
      tm_day = 1;
      if (tm_mon == 11) {
        tm_mon = 0;
      }
      else {
        ++tm_mon;
      }
    }
    else {
      ++tm_day;
    }
    return *this;
  }

  // Перегрузка постфиксного инкремента
  Railway_data operator++(int) {
    Railway_data tmp(*this);
    ++(*this);
    return tmp;
  }


  Railway_data& operator=(const Railway_data data)
  {
    tm_day = data.tm_day;
    tm_mon = data.tm_mon;
    return *this;
  }

  bool operator==(const Railway_data& data)
  {
    return tm_day == data.tm_day && tm_mon == data.tm_mon;
  }
};

struct FIO
{
  std::string Last_name;
  std::string First_name;
  std::string Patronymic;
  FIO() :First_name(""), Last_name(""), Patronymic("") {}
  FIO(std::string f, std::string i, std::string o): First_name(i), Last_name(f), Patronymic(o) {}

  FIO& operator= (const FIO fio)
  {
    Last_name = fio.Last_name;
    First_name = fio.First_name;
    Patronymic = fio.Patronymic;
    return *this;
  }

  bool operator==(const FIO fio)
  {
    if (Last_name == fio.Last_name && First_name == fio.First_name && Patronymic == fio.Patronymic)
      return true;
    return false;
  }
};

std::ostream& operator<<(std::ostream& os, const Railway_data& data) {
  os << std::setfill('0') << std::setw(2) << data.tm_day << "."
    << std::setfill('0') << std::setw(2) << data.tm_mon;
  return os;
}

std::ostream& operator<<(std::ostream& os, const FIO& fio)
{
  os << fio.Last_name << " " << fio.First_name << " " << fio.Patronymic;
  return os;
}
