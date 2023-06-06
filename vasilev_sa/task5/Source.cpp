/*
class Ticket(-//-)
	* äàòà
	* íîìåð ïîåçäà
	* íîìåð âàãîíà
	* íîìåð ìåñòà
	* ÔÈÎ ïàññàæèðà
	* ñòàíöèÿ îòïðàâëåíèÿ
	* ñòàíöèÿ ïðèáûòèÿ

class Vagon(int Type)
  * int Number - íîìåð âàãîíà
	* int Type - òèï âàãîíà
	* vector<bool> Places true çàðåçåðâèðîâàíî èíà÷å false
	* int Size - êîëè÷åñòâî ìåñò
	* int Free_size - êîëè÷åñòâî ñâîáîäíûõ ìåñò

class Train(int Type)
	* int Number - íîìåð ïîåçäà
	* int Type - òèï ïîåçäà
	* Size - êîëè÷åñòâî âàãîíîâ
	* vector<Vagon> Vagons - Size îáúåêòîâ êëàññà Vagon;

class Railway(): âñå ïîåçäà è áèëåòû íà êîíêðåòíûé äåíü, çäåñü æå ñòîèìîñòü áèëåòîâ äëÿ âñåõ òèïîâ
	* Railway_data Data - ñîáñòâåííàÿ ñòðóêòóðà äëÿ õðàíåíèÿ äàòû
	* int Count_trains - êîëè÷åñòâî ïîåçäîâ
	* int Count_tickets - êîëè÷åñòâî çàðåçåðâèðîâàííûõ áèëåòîâ
	* vector<Train> Trains - Count_trains îáúåêòîâ êëàññà Train
	* vector<Ticket> Tickets - Count_tickets îáúåêòîâ êëàññà Ticket

class Data(): ðàñïèñàíèå íà 30 äíåé âïåðåä
	* int Size - êîëè÷åñòâî äíåé (ïî óìîë÷àíèþ 30)
	* vector<Railway> Railways - Size îáúåêòîâ êëàññà Railway

class Cassa(Data): ïîäêëþ÷åíèå ê Data, çàòåì ïîëó÷åíèå ïî óêàçàòåëÿì -> Railway -> Train -> Vagon -> Places
	* ïðèíÿòü äàííûå ïîêóïàòåëÿ: äàòó, ïîåçä, òèï âàãîíà (åñëè åñòü âûáîð), êîëè÷åñòâî áèëåòîâ êàæäîãî âîçìîæíîãî âèäà (åñëè åñòü âûáîð), ÔÈÎ ïàññàæèðîâ 
	* ïðîâåðèòü íàëè÷èå ñâîáîäíûõ ìåñò ïî çàïðîñó ïîêóïàòåëÿ (ïðè íåâîçìîæíîñòè âûäàòü âñå áèëåòû â îäíîì âàãîíå, ñ÷èòàòü çàêàç íåâûïîëíèìûì), 
	* çàðåçåðâèðîâàòü ìåñòà, 
	* ðàññ÷èòàòü îáùóþ ñòîèìîñòü áèëåòîâ, 
	* îòìåíèòü çàêàç áèëåòîâ, 
	* ñôîðìèðîâàòü áèëåòû (êàæäûé áèëåò âêëþ÷àåò: äàòó, íîìåð ïîåçäà, íîìåð âàãîíà, íîìåð ìåñòà, ÔÈÎ ïàññàæèðà, ñòàíöèÿ îòïðàâëåíèÿ, ñòàíöèÿ ïðèáûòèÿ).
*/

#pragma warning(disable : 4996)
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <sstream>
#include "Header.h"

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
	//êîíñòðóêòîð ïî óìîë÷àíèþ
	Ticket() : Cost(), Data(), Train_number(0), Vagon_number(0), Place_number(0), Name(), Departure_station(""), Arrival_station("") {}

	//êîíñòðóêòîð êëàññà
	Ticket(int cost, Railway_data data, int train_number, int vagon_number, int place_number, FIO name,std::string departure_station, std::string arrival_station) : Cost(cost), Data(data), Train_number(train_number), Vagon_number(vagon_number), Place_number(place_number), Name(name), Departure_station(departure_station), Arrival_station(arrival_station) {}

	//âåðíóòü äàòó
	Railway_data Get_data()
	{
		return Data;
	}

	//âåðíóòü ÔÈÎ
	FIO Get_name()
	{
		return Name;
	}

	//âåðíóòü öåíó
	int Get_price()
	{
		return Cost;
	}

	//âåðíóòü íîìåð ïîåçäà
	int Get_train_number()
	{
		return Train_number;
	}

	//âåðíóòü íîìåð âàãîíà
	int Get_vagon_number()
	{
		return Vagon_number;
	}

	//âåðíóòü íîìåð ìåñòà
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
	std::vector<bool> Places;
	int Size;
	int Free_size;
public:
	//êîíñòðóêòîð ïî óìîë÷àíèþ
	Vagon()
	{
		Free_size = 0;
		Number = 0;
		Type = 0;
		Size = 0;
	}

	//êîíñòðóêòîð ïî íîìåðó è òèïó âàãîíà
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

	//âåðíóòü êîëè÷åñòâî ñâîáîäíûõ ìåñò
	int Get_free_size()
	{
		return Free_size;
	}

	//âåðíóòü íîìåð âàãîíà
	int Get_number()
	{
		return Number;
	}

	//âåðíóòü òèï âàãîíà
	int Get_type()
	{
		return Type;
	}

	//óêàçàòü íîìåð âàãîíà
	void Set_number(int number)
	{
		Number = number;
	}

	//ïðîâåðèòü ìåñòî â âàãîíå ïî èíäåêñó
	bool Check_place(int index)
	{
		return Places.at(index);
	}

	//çàáðîíèðîâàòü ìåñòî ïî èíäåêñó
	void Reserve_place(int index)
	{
		if (!Places.at(index))
		{
			Places.at(index) = 1;
			Free_size--;
		}
	}

	//ðàçáðîíèððîâàòü ìåñòî ïî èíäåêñó
	void Anreserve_place(int index)
	{
		if (Places.at(index))
		{
			Places.at(index) = 0;
			Free_size++;
		}
	}

	//âûâåñòè íà ýêðàí íå çàáðîíèðîâàííûå ìåñòà
	void Print_suitable_places()
	{
		for (int i = 0; i < Size; i++)
			if (!Places.at(i))
				std::cout << "Ìåñòî ¹" << i + 1 << std::endl;
	}

	//ïåðåãðóçêà îïåðàòîðîâ
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
	std::vector<Vagon> Vagons;
	//íàéòè èíäåêñ âàãîíà ïî íîìåðó èëè âåðíóòü -1
	int Found_vagon(int number) 
	{
		for (int i = 0; i < Vagons.size(); i++)
			if (Vagons[i].Get_number() == number)
				return i;
		return -1;
	}
public:
	//êîíñòðóêòîð ïî óìîë÷àíèþ
	Train() : Number(0), Type(0), Size(0) {}

	//êîíñòðóêòîð ïî íîìåðó è òèïó âàãîíà
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

	//ïîëó÷èòü âàãîí ïî íîìåðó
	Vagon* Get_vagon(int number)
	{
		int index = Found_vagon(number);
		if (index == -1)
			return nullptr;
		return &Vagons.at(index);
	}

	//ïîëó÷èòü íîìåð ïîåçäà
	int Get_number()
	{
		return Number;
	}

	//ïîëó÷èòü òèï ïîåçäà
	int Get_type()
	{
		return Type;
	}

	//ïîëó÷èòü êîëè÷åñòâî âàãîíîâ â ïîåçäå
	int Get_size()
	{
		return Size;
	}

	//ïðîâåðÿåò åñòü ëè â ïîåçäå ïîäõîäÿùèå âàãîíû
	bool Check_free_vagons(int count_peoples)
	{
		for (int i = 0; i < Size; i++)
			if (Vagons.at(i).Get_free_size() > count_peoples)
				return true;
		return false;
	}

	//íàïå÷àòàòü â êîíñîëü âñå ïîäõîäÿùèå ïî óñëîâèÿì âàãîíû
	void Print_suitable_vagons(int vagon_type, int places_count)
	{
		for (Vagon i : Vagons)
			if (i.Get_free_size() >= places_count)
				std::cout << "Âàãîí ¹" << i.Get_number() << std::endl;
	}
	
	//ïåðåãðóçêà îïåðàòîðîâ
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
	std::vector<Train> Trains;
	std::vector<Ticket> Tickets;
public:
	//êîíñòðóêòîð ïî óìîë÷àíèþ
	Railway() : Data(), Count_trains(0), Count_tickets(0) {}

	//êîíñòðóêòîð ïî äàòå
	Railway(Railway_data data)
	{
		Data = data;
		Count_trains = 0;
		Count_tickets = 0;
	}

	//íàéòè èíäåêñ ïîåçäà ïî íîìåðó èëè âåðíóòü -1
	int Found_train(int number)
	{
		for (int i = 0; i < Count_trains; i++)
			if (Trains.at(i).Get_number() == number)
				return i;
		return -1;
	}

	//íàïèñàòü â êîíñîëü âñå ïîäõîäÿùèå ïî ïàðàìåòðàì ïîåçäà
	void Print_suitable_trains(int train_type, int places_count)
	{
		for (Train i : Trains)
			if (i.Get_type() == train_type && i.Check_free_vagons(places_count))
				std::cout << "Ïîåçä ¹" << i.Get_number() << std::endl;
	}

	//ïîëó÷èòü ïîåçä ïî íîìåðó
	Train* Get_train(int number)
	{
		int index = Found_train(number);
		if (index == -1)
			return nullptr;
		return &Trains.at(index);
	}

	//ïîëó÷èòü äàòó
	Railway_data Get_data() const
	{
		return Data;
	}

	//ïîëó÷èòü êîëè÷åñòâî ïîåçäîâ
	int Get_count_trains()
	{
		return Count_trains;
	}

	//ïîëó÷èòü êîëè÷åñòâî áèëåòîâ
	int Get_count_tickets()
	{
		return Count_tickets;
	}

	//äîáàâèòü ïîåçä
	void Append_train(Train train)
	{
		Trains.push_back(train);
		Count_trains++;
	}

	//äîáàâèòü áèëåò
	void Append_ticket(Ticket ticket)
	{
		Tickets.push_back(ticket);
		Count_tickets++;
	}

	//óäàëèòü áèëåò ïî äàòå è íîìåðàì ïîåçäà, âàãîíà è ìåñòà
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

	//ïðîâåðèòü öåíó
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
					return 1000; //íèæíåå
				return 800;//âåðõíåå
			case cupe:
				if (place_number % 2 == 0)
					return 1200; //íèæíåå
				return 1000;//âåðõíåå
			case sv:
				return 1300;
			}
			break;
		case fasttrain:
			switch (vagon_type)
			{
			case pzkrt:
				if (place_number % 2 == 0)
					return 900; //íèæíåå
				return 700; //âåðõíåå
			case cupe:
				if (place_number % 2 == 0)
					return 1100; //íèæíåå
				return 900;//âåðõíåå
			case sv:
				return 1200;
			}
		}
		return 0;
	}

	//ïåðåãðóçêà îïåðàòîðîâ
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
	std::vector<Railway> Railways;

public:
	//êîíñòðóêòîð ïî óìîë÷àííèþ
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

	//ïîëó÷èòü êîíêðåòíûé Railway ïî äíþ è ìåñÿöó
	Railway* Get_railway(int day, int mon) 
	{
		if (!is_valid_date(day, mon)) {
			std::cout << "Îøèáêà: íåêîððåêòíàÿ äàòà" << std::endl;
			return nullptr;
		}

		Railway_data rd(day, mon);
		for (int i = 0; i < Size; i++)
			if (Railways.at(i).Get_data() == rd)
				return &Railways.at(i);

		std::cout << "Îøèáêà: ðàñïèñàíèå íà óêàçàííóþ äàòó îòñóòñòâóåò" << std::endl;
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
	std::vector <FIO> Names;
	int Names_size;
	std::vector <int> Places;
	int Places_size;
	std::vector <int> Prices;
	int Prices_size;
	std::string Departure_station;
	std::string Arrival_station;
	int Reserved_place_size;

public:
	//êîíñòðóêòîð êëàññà
	Cassa(Data data) : Calendar(data), Initialization(false), Today_data(), Train_type(0), Train_num(0), Vagon_type(0), Vagon_num(0), Places_count(0), Total_cost(0), Names_size(0), Places_size(0), Departure_station(""), Arrival_station(""), Reserved_place_size(0) {}

	//ïîëó÷èòü äàííûå ïîëüçîâàòåëÿ è çàíåñòè âñ¸ â áàçó Data Calendar
	void Get_user_info()
	{
		if (Initialization)
			return;
		char ch;
		int mon, day;
		std::cout << "Ââåäèòå äåíü: ";
		std::cin >> day;
		while (ch = getchar() != '\n');
		std::cout << "Ââåäèòå ìåñÿö: ";
		std::cin >> mon;
		while (ch = getchar() != '\n');
		if (!is_valid_date(day, mon))
		{
			std::cout << "Îøèáêà: íåâåðíàÿ äàòà, ëèáî ðàññïèñàíèå íà ýòîò äåíü îòñóòñòâóåò" << std::endl;
			return;
		}
		Today_data = Railway_data(day, mon);
		Today_railway = *Calendar.Get_railway(day, mon);

		int station;
		std::cout << "Âûáåðèòå ñòàíöèþ îòïðàâëåíèÿ (1 - Íèæíèé Íîâãîðîä | 2 - Ìîñêâà): ";
		std::cin >> station;
		if (station == 1)
		{
			Departure_station = "Íèæíèé Íîâãîðîä";
			Arrival_station = "Ìîñêâà";
		}
		else if (station == 2)
		{
			Departure_station = "Ìîñêâà";
			Arrival_station = "Íèæíèé Íîâãîðîä";
		}
		else
		{
			std::cout << "Îøèáêà: ââåäåíî íå êîððåêòíîå çíà÷åíèå" << std::endl;
			return;
		}

		std::cout << "Âûáåðèòå òèï ïîåçäà (1 - 'Ëàñòî÷êà' | 2 - Ñêîðûé| 3 - Ôèðìåííûé): ";
		std::cin >> Train_type;
		while (ch = getchar() != '\n');
		if (Train_type < 1 && Train_type > 3)
		{
			std::cout << "Îøèáêà: ââåäåíî íå êîððåêòíîå çíà÷åíèå" << std::endl;
			return;
		}
		switch (Train_type)
		{
		case birdtrain:
			Vagon_type = birdvagon;
			break;
		case fasttrain:
		case firmtrain:
			std::cout << "Âûáåðèòå òèï âàãîíà (2 - ïëàöêàðò | 3 - êóïå| 4 - ñâ): ";
			std::cin >> Vagon_type;
			while (ch = getchar() != '\n');
			if (Vagon_type < 2 && Vagon_type > 4)
			{
				std::cout << "Îøèáêà: ââåäåíî íå êîððåêòíîå çíà÷åíèå" << std::endl;
				return;
			}
		}
		
		std::cout << "Ââåäèòå êîëè÷åñòâî ïàññàæèðîâ: ";
		std::cin >> Places_count;
		while (ch = getchar() != '\n');
		if (Places_count <= 0 || Places_count > 100)
		{
			std::cout << "Îøèáêà: ââåäåíî íå êîððåêòíîå çíà÷åíèå" << std::endl;
			return;
		}
		Initialization = true;
		for (int i = 0; i < Places_count; i++)
			Reserve_place();
	}

	//ïðîâåðèòü êîíêðåòíîå ìåñòî â âàãîíå (òîëüêî ïîñëå îäíîãî Reserve_place)
	void Check_free_place(int place_num)
	{
		if (!Initialization)
			return;
		if (Reserved_place_size < 1)
		{
			std::cout << "Ñïåðâà çàáðîíèðóéòå õîòÿáû îäíî ìåñòî" << std::endl;
			return;
		}
		Train train = *Today_railway.Get_train(Train_num);
		Vagon vagon = *train.Get_vagon(Vagon_num);
		if (train.Check_free_vagons(Places_count))
		{
			std::cout << "Â ïîåçäå íåò âàãîíîâ ñ ïîäõîäÿùèì êîëè÷åñòâîì ñâîáîäíûõ ìåñò" << std::endl;
			return;
		}
		if (vagon.Get_free_size() < Places_count)
		{
			std::cout << "Â âàãîíå íåò íóæíîãî êîëè÷åñòâà ñâîáîäíûõ ìåñò" << std::endl;
			return;
		}
		if (vagon.Check_place(place_num))
			std::cout << "Çàíÿòî" << std::endl;
		else
			std::cout << "Ñâîáîäíî" << std::endl;
	}

	//çàáðîíèðîâàòü ìåñòî â âàãîíå
	void Reserve_place()
	{
		if (!Initialization)
		{
			std::cout << "Îøèáêà: êàññà íå èíèöèàëèçèðîâàíà" << std::endl;
			return;
		}
		char ch;
		if (Train_num == 0)
		{
			std::cout << "Âûáåðèòå íîìåð ïîåçäà èç ïîäõîäÿùèõ äëÿ âàñ" << std::endl;
			Today_railway.Print_suitable_trains(Train_type, Places_count);
			std::cout << "Âàø âûáîð: ";
			std::cin >> Train_num;
			while (ch = getchar() != '\n');

			std::cout << "Âûáåðèòå íîìåð âàãîíà èç ïîäõîäÿùèõ äëÿ âàñ" << std::endl;
			Today_railway.Get_train(Train_num)->Print_suitable_vagons(Vagon_type, Places_count);
			std::cout << "Âàø âûáîð: ";
			std::cin >> Vagon_num;
			while (ch = getchar() != '\n');
		}
		int Place_num;
		std::cout << "Âûáåðèòå íîìåð ìåñòà èç ïîäõîäÿùèõ äëÿ âàñ" << std::endl;
		Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Print_suitable_places();
		std::cout << "Âàø âûáîð: ";
		std::cin >> Place_num;
		while (ch = getchar() != '\n');
		Place_num--;
		int train_type = Today_railway.Get_train(Train_num)->Get_type();
		int vagon_type = Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Get_type();
		int cost = Today_railway.Check_price(train_type, vagon_type, Place_num);

		std::string input;
		std::cout << "Ââåäèòå âàøå ÔÈÎ â ôîðìàòå 'Ôàìèëèÿ Èìÿ Îò÷åñòâî': ";
		std::getline(std::cin, input);

		std::string f_name, i_name, o_name;
		std::istringstream iss(input);
		iss >> f_name >> i_name >> o_name;
			
		Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Reserve_place(Place_num);
		std::cout << "Ìåñòî çàáðîíèðîâàíî" << std::endl;
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

	//îòìåíèòü áðîíü
	void Cancel_ticket_order(int place_num)
	{
		if (!Initialization)
			return;
		if (!Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Check_place(place_num))
		{
			std::cout << "Ìåñòî íå çàáðîíèðîâàíî" << std::endl;
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
			std::cout << "Áðîíü ñ ìåñòà ñíÿòà" << std::endl;
		}
	}

	//ïîñ÷èòàòü îáùóþ öåíó âñåõ áèëåòîâ
	void Calculate_total_price()
	{
		if (!Initialization)
			return;
		Total_cost = 0;
		for (int i : Prices)
			Total_cost += i;
	}
	
	//âûäàòü ÷åê
	void Generate_ticket()
	{
		if (!Initialization)
			return;
		std::cout << "______________ÁÈËÅÒ______________" << std::endl;
		std::cout << "Äàòà: " << Today_data;
		std::cout << " Ïîåçä ¹" << Train_num;
		std::cout << " Âàãîí ¹" << Vagon_num << std::endl;
		
		std::cout << "ÔÈÎ ïàññàæèðîâ:";
		for (int i = 0; i < Names_size; i++)
		{
			if (i < Names.size() - 1)
				std::cout << " " << Names.at(i) << ",";
			else
				std::cout << " " << Names.at(i) << std::endl;
		}

		std::cout << "Íîìåðà ìåñò";
		for (int i = 0; i < Places_size; i++)
		{
			if (i < Places.size() - 1)
				std::cout << " " << Places.at(i) << ",";
			else
				std::cout << " " << Places.at(i) << std::endl;
		}		

		std::cout << "Ñòàíöèÿ îòïðàâëåíèÿ: " << Departure_station << std::endl;
		std::cout << "Ñòàíöèÿ ïðèáûòèÿ: " << Arrival_station << std::endl;
		if (Total_cost == 0)
			Calculate_total_price();
		std::cout << "Èòîãîâàÿ ñòîèìîñòü áèëåòîâ: " << Total_cost << "ð." << std::endl;
		std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
	}
};

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//ñîçäàåì îáúåêò êëàññà data, â êîòîðîì ñîäåðæàòñÿ 30 äíåé (Railway) âïåðåä íà÷èíàÿ ñî äíÿ çàïóñêà ïðîãðàììû
	Data data;
  //çàïîëíÿåì íàøó "áàçó äàííûõ", çàíåñÿ â îïðåäåëåííûå äíè ïîåçäà (èçíà÷àëüíî êàæäûé Railway ïóñò)
	data.Get_railway(27, 06)->Append_train(Train(1, birdtrain));
	data.Get_railway(27, 06)->Append_train(Train(2, birdtrain));
	data.Get_railway(27, 06)->Append_train(Train(3, birdtrain));
	data.Get_railway(27, 06)->Append_train(Train(4, birdtrain));
	data.Get_railway(27, 06)->Append_train(Train(5, fasttrain));
	data.Get_railway(27, 06)->Append_train(Train(6, fasttrain));
	data.Get_railway(27, 06)->Append_train(Train(7, fasttrain));
	data.Get_railway(27, 06)->Append_train(Train(8, firmtrain));
	data.Get_railway(27, 06)->Append_train(Train(9, firmtrain));

	//"ïîäêëþ÷àåì" ê íàøåé êàññå data, ñ êîòîðîé áóäåì ðàáîòàòü
	Cassa cassa(data);
	//ïîëó÷èòü èíôîðìàöèþ ïîëüçîâàòåëÿ è ñîçäàòü áèëåòû
	cassa.Get_user_info();
	//óäàëèòü áèëåò ñ íîìåðîì ìåñòà 2 â ðàíåå âûáðàííîì âàãîíå
	cassa.Cancel_ticket_order(2);
	//ñãåíåðèðîâàòü áèëåò
	cassa.Generate_ticket();
	system("pause");
}
