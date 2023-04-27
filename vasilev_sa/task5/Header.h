#include <iostream>
#include <iomanip>

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
  int tm_day;  // ��� �� 1 �� 31
  int tm_mon;   // ������ �� 1 �� 11
  Railway_data(): tm_day(0), tm_mon(0) {}
  Railway_data(int day, int mon): tm_day(day), tm_mon(mon) {}

  // ���������� ����������� ����������
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

  // ���������� ������������ ����������
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