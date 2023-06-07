/*
class Ticket(-//-)
* дата
* номер поезда
* номер вагона
* номер места
* ФИО пассажира
* станция отправления
* станция прибытия

class Vagon(int Type)
* int Number - номер вагона
* int Type - тип вагона
* vectorPlaces true зарезервировано иначе false
* int Size - количество мест
* int Free_size - количество свободных мест

class Train(int Type)
* int Number - номер поезда
* int Type - тип поезда
* Size - количество вагонов
* vectorVagons - Size объектов класса Vagon;

class Railway(): все поезда и билеты на конкретный день, здесь же стоимость билетов для всех типов
* Railway_data Data - собственная структура для хранения даты
* int Count_trains - количество поездов
* int Count_tickets - количество зарезервированных билетов
* vectorTrains - Count_trains объектов класса Train
* vectorTickets - Count_tickets объектов класса Ticket

class Data(): расписание на 30 дней вперед
* int Size - количество дней (по умолчанию 30)
* vectorRailways - Size объектов класса Railway

class Cassa(Data): подключение к Data, затем получение по указателям -> Railway -> Train -> Vagon -> Places
* принять данные покупателя: дату, поезд, тип вагона (если есть выбор), количество билетов каждого возможного вида (если есть выбор), ФИО пассажиров
* проверить наличие свободных мест по запросу покупателя (при невозможности выдать все билеты в одном вагоне, считать заказ невыполнимым),
* зарезервировать места,
* рассчитать общую стоимость билетов,
* отменить заказ билетов,
* сформировать билеты (каждый билет включает: дату, номер поезда, номер вагона, номер места, ФИО пассажира, станция отправления, станция прибытия).
*/

#pragma warning(disable : 4996)
#include #include #include #include #include #include #include "Header.h"

class Ticket
{
private:
int Cost;
Railway_data Data;
int Train_number;
int Vagon_number;
int Place_number;
FIO Name;
std::string Departure_station;
std::string Arrival_station;
public:
//конструктор по умолчанию
Ticket() : Cost(), Data(), Train_number(0), Vagon_number(0), Place_number(0), Name(), Departure_station(""), Arrival_station("") {}

//конструктор класса
Ticket(int cost, Railway_data data, int train_number, int vagon_number, int place_number, FIO name,std::string departure_station, std::string arrival_station) : Cost(cost), Data(data), Train_number(train_number), Vagon_number(vagon_number), Place_number(place_number), Name(name), Departure_station(departure_station), Arrival_station(arrival_station) {}

//вернуть дату
Railway_data Get_data()
{
return Data;
}

//вернуть ФИО
FIO Get_name()
{
return Name;
}

//вернуть цену
int Get_price()
{
return Cost;
}

//вернуть номер поезда
int Get_train_number()
{
return Train_number;
}

//вернуть номер вагона
int Get_vagon_number()
{
return Vagon_number;
}

//вернуть номер места
int Get_place_number()
{
return Place_number;
}
};

class Vagon
{
private:
int Number;
int Type;
std::vectorPlaces;
int Size;
int Free_size;
public:
//конструктор по умолчанию
Vagon()
{
Free_size = 0;
Number = 0;
Type = 0;
Size = 0;
}

//конструктор по номеру и типу вагона
Vagon(int number, int type) : Number(number), Type(type)
{
switch (Type)
{
case birdvagon:
Size = 100;
Free_size = 100;
break;
case pzkrt:
Size = 54;
Free_size = 54;
break;
case cupe:
Size = 36;
Free_size = 36;
break;
case sv:
Size = 18;
Free_size = 18;
break;
default:
Size = 0;
Free_size = 0;
}
for (int i = 0; i < Size; i++)
Places.push_back(0);
}

//вернуть количество свободных мест
int Get_free_size()
{
return Free_size;
}

//вернуть номер вагона
int Get_number()
{
return Number;
}

//вернуть тип вагона
int Get_type()
{
return Type;
}

//указать номер вагона
void Set_number(int number)
{
Number = number;
}

//проверить место в вагоне по индексу
bool Check_place(int index)
{
return Places.at(index);
}

//забронировать место по индексу
void Reserve_place(int index)
{
if (!Places.at(index))
{
Places.at(index) = 1;
Free_size--;
}
}

//разбронирровать место по индексу
void Anreserve_place(int index)
{
if (Places.at(index))
{
Places.at(index) = 0;
Free_size++;
}
}

//вывести на экран не забронированные места
void Print_suitable_places()
{
for (int i = 0; i < Size; i++)
if (!Places.at(i))
std::cout << "Место №" << i + 1 << std::endl;
}

//перегрузка операторов
Vagon& operator=(const Vagon& vagon)
{
if (Size < vagon.Size)
Places.resize(vagon.Size);
Number = vagon.Number;
Free_size = vagon.Free_size;
Type = vagon.Type;
Size = vagon.Size;
Places = vagon.Places;
for (int i = 0; i < Size; i++)
Places.at(i) = vagon.Places.at(i);
return *this;
}

bool operator==(const Vagon& vagon)
{
if (Size != vagon.Size)
return false;
if (Type != vagon.Type)
return false;
return true;
}
};

class Train
{
private:
int Number;
int Type;
int Size;
std::vectorVagons;
//найти индекс вагона по номеру или вернуть -1
int Found_vagon(int number)
{
for (int i = 0; i < Vagons.size(); i++)
if (Vagons[i].Get_number() == number)
return i;
return -1;
}
public:
//конструктор по умолчанию
Train() : Number(0), Type(0), Size(0) {}

//конструктор по номеру и типу вагона
Train(int number, int type): Number(number), Type(type)
{
switch (type)
{
case birdtrain:
Size = 8;
for (int i = 0; i < 8; i++)
{
Vagon vagon(i + 1, birdvagon);
Vagons.push_back(vagon);
}
break;
case firmtrain:
Size = 12;
for (int i = 0; i < 12; i++)
{
if (i < 2)
Vagons.push_back(Vagon(i + 1, sv));
else if (i < 8)
Vagons.push_back(Vagon(i + 1, cupe));
else
Vagons.push_back(Vagon(i + 1, pzkrt));
}
break;
case fasttrain:
Size = 12;
for (int i = 0; i < 12; i++)
{if (i < 4)
Vagons.push_back(Vagon(i + 1, cupe));
else
Vagons.push_back(Vagon(i + 1, pzkrt));
}
break;
default:
Size = 0;
}
}

//получить вагон по номеру
Vagon* Get_vagon(int number)
{
int index = Found_vagon(number);
if (index == -1)
return nullptr;
return &Vagons.at(index);
}

//получить номер поезда
int Get_number()
{
return Number;
}

//получить тип поезда
int Get_type()
{
return Type;
}

//получить количество вагонов в поезде
int Get_size()
{
return Size;
}

//проверяет есть ли в поезде подходящие вагоны
bool Check_free_vagons(int count_peoples)
{
for (int i = 0; i < Size; i++)
if (Vagons.at(i).Get_free_size() > count_peoples)
return true;
return false;
}

//напечатать в консоль все подходящие по условиям вагоны
void Print_suitable_vagons(int vagon_type, int places_count)
{
for (Vagon i : Vagons)
if (i.Get_free_size() >= places_count)
std::cout << "Вагон №" << i.Get_number() << std::endl;
}

//перегрузка операторов
Train& operator=(const Train train)
{
if (Size < train.Size)
Vagons.resize(train.Size);
Number = train.Number;
Type = train.Type;
Size = train.Size;
for (int i = 0; i < Size; i++)
Vagons.at(i) = train.Vagons.at(i);
return *this;
}

bool operator==(const Train train)
{
if (Type != train.Type)
return false;
if (Size!= train.Size)
return false;
return true;
}
};

class Railway
{
private:
Railway_data Data;
int Count_trains;
int Count_tickets;
std::vectorTrains;
std::vectorTickets;
public:
//конструктор по умолчанию
Railway() : Data(), Count_trains(0), Count_tickets(0) {}

//конструктор по дате
Railway(Railway_data data)
{
Data = data;
Count_trains = 0;
Count_tickets = 0;
}

//найти индекс поезда по номеру или вернуть -1
int Found_train(int number)
{
for (int i = 0; i < Count_trains; i++)
if (Trains.at(i).Get_number() == number)
return i;
return -1;
}

//написать в консоль все подходящие по параметрам поезда
void Print_suitable_trains(int train_type, int places_count)
{
for (Train i : Trains)
if (i.Get_type() == train_type && i.Check_free_vagons(places_count))
std::cout << "Поезд №" << i.Get_number() << std::endl;
}

//получить поезд по номеру
Train* Get_train(int number)
{
int index = Found_train(number);
if (index == -1)
return nullptr;
return &Trains.at(index);
}

//получить дату
Railway_data Get_data() const
{
return Data;
}

//получить количество поездов
int Get_count_trains()
{
return Count_trains;
}

//получить количество билетов
int Get_count_tickets()
{
return Count_tickets;
}

//добавить поезд
void Append_train(Train train)
{
Trains.push_back(train);
Count_trains++;
}

//добавить билет
void Append_ticket(Ticket ticket)
{
Tickets.push_back(ticket);
Count_tickets++;
}

//удалить билет по дате и номерам поезда, вагона и места
void Delete_ticket(int train, int vagon, int place)
{
for (int i = 0; i < Count_tickets; i++)
{
if (Tickets.at(i).Get_train_number() == train && Tickets.at(i).Get_vagon_number() == vagon && Tickets.at(i).Get_place_number() == place)
{
Tickets.erase(Tickets.begin() + i);
Count_tickets--;
return;
}
}
}

//проверить цену
int Check_price(int train_type, int vagon_type, int place_number)
{
switch (train_type)
{
case birdtrain:
return 1500;
case firmtrain:
switch (vagon_type)
{
case pzkrt:
if (place_number % 2 == 0)
return 1000; //нижнее
return 800;//верхнее
case cupe:
if (place_number % 2 == 0)
return 1200; //нижнее
return 1000;//верхнее
case sv:
return 1300;
}
break;
case fasttrain:
switch (vagon_type)
{
case pzkrt:
if (place_number % 2 == 0)
return 900; //нижнее
return 700; //верхнее
case cupe:
if (place_number % 2 == 0)
return 1100; //нижнее
return 900;//верхнее
case sv:
return 1200;
}
}
return 0;
}

//перегрузка операторов
Railway& operator=(const Railway railway)
{
if (Count_trains < railway.Count_trains)
Trains.resize(railway.Count_trains);
if (Count_tickets < railway.Count_tickets)
Tickets.resize(railway.Count_tickets);
Data = railway.Data;
Count_trains = railway.Count_trains;
for (int i = 0; i < Count_trains; i++)
Trains.at(i) = railway.Trains.at(i);
Count_tickets = railway.Count_tickets;
for (int i = 0; i < Count_tickets; i++)
Tickets.at(i) = railway.Tickets.at(i);
return *this;
}
};

class Data
{
private:
int Size;
std::vectorRailways;

public:
//конструктор по умолчаннию
Data()
{
std::time_t now = std::time(nullptr);
std::tm* local_time = std::localtime(&now);
int mon = local_time->tm_mon + 1;
int day = local_time->tm_mday;
Railway_data today(day, mon);
Size = 30;
for (int i = 0; i < Size; i++)
Railways.push_back(Railway(today++));
}

//получить конкретный Railway по дню и месяцу
Railway* Get_railway(int day, int mon)
{
if (!is_valid_date(day, mon)) {
std::cout << "Ошибка: некорректная дата" << std::endl;
return nullptr;
}

Railway_data rd(day, mon);
for (int i = 0; i < Size; i++)
if (Railways.at(i).Get_data() == rd)
return &Railways.at(i);

std::cout << "Ошибка: расписание на указанную дату отсутствует" << std::endl;
return nullptr;
}
};

class Cassa
{
Data Calendar;
Railway Today_railway;
bool Initialization;

Railway_data Today_data;
int Train_type;
int Train_num;
int Vagon_type;
int Vagon_num;
int Places_count;
int Total_cost;
std::vector Names;
int Names_size;
std::vector Places;
int Places_size;
std::vector Prices;
int Prices_size;
std::string Departure_station;
std::string Arrival_station;
int Reserved_place_size;

public:
//конструктор класса
Cassa(Data data) : Calendar(data), Initialization(false), Today_data(), Train_type(0), Train_num(0), Vagon_type(0), Vagon_num(0), Places_count(0), Total_cost(0), Names_size(0), Places_size(0), Departure_station(""), Arrival_station(""), Reserved_place_size(0) {}

//получить данные пользователя и занести всё в базу Data Calendar
void Get_user_info()
{
if (Initialization)
return;
char ch;
int mon, day;
std::cout << "Введите день: ";
std::cin >> day;
while (ch = getchar() != '\n');
std::cout << "Введите месяц: ";
std::cin >> mon;
while (ch = getchar() != '\n');
if (!is_valid_date(day, mon))
{
std::cout << "Ошибка: неверная дата, либо рассписание на этот день отсутствует" << std::endl;
return;
}
Today_data = Railway_data(day, mon);
Today_railway = *Calendar.Get_railway(day, mon);

int station;
std::cout << "Выберите станцию отправления (1 - Нижний Новгород | 2 - Москва): ";
std::cin >> station;
if (station == 1)
{
Departure_station = "Нижний Новгород";
Arrival_station = "Москва";
}
else if (station == 2)
{
Departure_station = "Москва";
Arrival_station = "Нижний Новгород";
}
else
{
std::cout << "Ошибка: введено не корректное значение" << std::endl;
return;
}

std::cout << "Выберите тип поезда (1 - 'Ласточка' | 2 - Скорый| 3 - Фирменный): ";
std::cin >> Train_type;
while (ch = getchar() != '\n');
if (Train_type < 1 && Train_type > 3)
{
std::cout << "Ошибка: введено не корректное значение" << std::endl;
return;
}
switch (Train_type)
{
case birdtrain:
Vagon_type = birdvagon;
break;
case fasttrain:
case firmtrain:
std::cout << "Выберите тип вагона (2 - плацкарт | 3 - купе| 4 - св): ";
std::cin >> Vagon_type;
while (ch = getchar() != '\n');
if (Vagon_type < 2 && Vagon_type > 4)
{
std::cout << "Ошибка: введено не корректное значение" << std::endl;
return;
}
}

std::cout << "Введите количество пассажиров: ";
std::cin >> Places_count;
while (ch = getchar() != '\n');
if (Places_count <= 0 || Places_count > 100)
{
std::cout << "Ошибка: введено не корректное значение" << std::endl;
return;
}
Initialization = true;
for (int i = 0; i < Places_count; i++)
Reserve_place();
}

//проверить конкретное место в вагоне (только после одного Reserve_place)
void Check_free_place(int place_num)
{
if (!Initialization)
return;
if (Reserved_place_size < 1)
{
std::cout << "Сперва забронируйте хотябы одно место" << std::endl;
return;
}
Train train = *Today_railway.Get_train(Train_num);
Vagon vagon = *train.Get_vagon(Vagon_num);
if (train.Check_free_vagons(Places_count))
{
std::cout << "В поезде нет вагонов с подходящим количеством свободных мест" << std::endl;
return;
}
if (vagon.Get_free_size() < Places_count)
{
std::cout << "В вагоне нет нужного количества свободных мест" << std::endl;
return;
}
if (vagon.Check_place(place_num))
std::cout << "Занято" << std::endl;
else
std::cout << "Свободно" << std::endl;
}

//забронировать место в вагоне
void Reserve_place()
{
if (!Initialization)
{
std::cout << "Ошибка: касса не инициализирована" << std::endl;
return;
}
char ch;
if (Train_num == 0)
{
std::cout << "Выберите номер поезда из подходящих для вас" << std::endl;
Today_railway.Print_suitable_trains(Train_type, Places_count);
std::cout << "Ваш выбор: ";
std::cin >> Train_num;
while (ch = getchar() != '\n');

std::cout << "Выберите номер вагона из подходящих для вас" << std::endl;
Today_railway.Get_train(Train_num)->Print_suitable_vagons(Vagon_type, Places_count);
std::cout << "Ваш выбор: ";
std::cin >> Vagon_num;
while (ch = getchar() != '\n');
}
int Place_num;
std::cout << "Выберите номер места из подходящих для вас" << std::endl;
Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Print_suitable_places();
std::cout << "Ваш выбор: ";
std::cin >> Place_num;
while (ch = getchar() != '\n');
Place_num--;
int train_type = Today_railway.Get_train(Train_num)->Get_type();
int vagon_type = Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Get_type();
int cost = Today_railway.Check_price(train_type, vagon_type, Place_num);

std::string input;
std::cout << "Введите ваше ФИО в формате 'Фамилия Имя Отчество': ";
std::getline(std::cin, input);

std::string f_name, i_name, o_name;
std::istringstream iss(input);
iss >> f_name >> i_name >> o_name;

Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Reserve_place(Place_num);
std::cout << "Место забронировано" << std::endl;
FIO fio(f_name, i_name, o_name);
Names.push_back(fio);
Names_size++;
Places.push_back(Place_num + 1);
Places_size++;
Prices.push_back(cost);
Prices_size++;
Reserved_place_size++;
Today_railway.Append_ticket(Ticket(cost, Today_data, Train_num, Vagon_num, Place_num + 1, fio, Departure_station, Arrival_station));
}

//отменить бронь
void Cancel_ticket_order(int place_num)
{
if (!Initialization)
return;
if (!Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Check_place(place_num))
{
std::cout << "Место не забронировано" << std::endl;
}
else
{
Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Anreserve_place(place_num);
Today_railway.Delete_ticket(Train_num, Vagon_num, place_num);
for (int i = 0; i < Places.size(); i++)
if (Places.at(i) == place_num)
{
Places.erase(Places.begin() + i);
Places_size--;
Names.erase(Names.begin() + i);
Names_size--;
Prices.erase(Prices.begin() + i);
Prices_size--;
break;
}
std::cout << "Бронь с места снята" << std::endl;
}
}

//посчитать общую цену всех билетов
void Calculate_total_price()
{
if (!Initialization)
return;
Total_cost = 0;
for (int i : Prices)
Total_cost += i;
}

//выдать чек
void Generate_ticket()
{
if (!Initialization)
return;
std::cout << "______________БИЛЕТ______________" << std::endl;
std::cout << "Дата: " << Today_data;
std::cout << " Поезд №" << Train_num;
std::cout << " Вагон №" << Vagon_num << std::endl;

std::cout << "ФИО пассажиров:";
for (int i = 0; i < Names_size; i++)
{
if (i < Names.size() - 1)
std::cout << " " << Names.at(i) << ",";
else
std::cout << " " << Names.at(i) << std::endl;
}

std::cout << "Номера мест";
for (int i = 0; i < Places_size; i++)
{
if (i < Places.size() - 1)
std::cout << " " << Places.at(i) << ",";
else
std::cout << " " << Places.at(i) << std::endl;
}

std::cout << "Станция отправления: " << Departure_station << std::endl;
std::cout << "Станция прибытия: " << Arrival_station << std::endl;
if (Total_cost == 0)
Calculate_total_price();
std::cout << "Итоговая стоимость билетов: " << Total_cost << "р." << std::endl;
std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
}
};

int main()
{
SetConsoleOutputCP(1251);
SetConsoleCP(1251);

//создаем объект класса data, в котором содержатся 30 дней (Railway) вперед начиная со дня запуска программы
Data data;
//заполняем нашу "базу данных", занеся в определенные дни поезда (изначально каждый Railway пуст)
data.Get_railway(27, 06)->Append_train(Train(1, birdtrain));
data.Get_railway(27, 06)->Append_train(Train(2, birdtrain));
data.Get_railway(27, 06)->Append_train(Train(3, birdtrain));
data.Get_railway(27, 06)->Append_train(Train(4, birdtrain));
data.Get_railway(27, 06)->Append_train(Train(5, fasttrain));
data.Get_railway(27, 06)->Append_train(Train(6, fasttrain));
data.Get_railway(27, 06)->Append_train(Train(7, fasttrain));
data.Get_railway(27, 06)->Append_train(Train(8, firmtrain));
data.Get_railway(27, 06)->Append_train(Train(9, firmtrain));

//"подключаем" к нашей кассе data, с которой будем работать
Cassa cassa(data);
//получить информацию пользователя и создать билеты
cassa.Get_user_info();
//удалить билет с номером места 2 в ранее выбранном вагоне
cassa.Cancel_ticket_order(2);
//сгенерировать билет
cassa.Generate_ticket();
system("pause");
}
