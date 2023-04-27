/*
class Ticket(-//-)
	* ����
	* ����� ������
	* ����� ������
	* ����� �����
	* ��� ���������
	* ������� �����������
	* ������� ��������

class Vagon(int Type)
  * int Number - ����� ������
	* int Type - ��� ������
	* vector<bool> Places true ��������������� ����� false
	* int Size - ���������� ����
	* int Free_size - ���������� ��������� ����

class Train(int Type)
	* int Number - ����� ������
	* int Type - ��� ������
	* Size - ���������� �������
	* vector<Vagon> Vagons - Size �������� ������ Vagon;

class Railway(): ��� ������ � ������ �� ���������� ����, ����� �� ��������� ������� ��� ���� �����
	* Railway_data Data - ����������� ��������� ��� �������� ����
	* int Count_trains - ���������� �������
	* int Count_tickets - ���������� ����������������� �������
	* vector<Train> Trains - Count_trains �������� ������ Train
	* vector<Ticket> Tickets - Count_tickets �������� ������ Ticket

class Data(): ���������� �� 30 ���� ������
	* int Size - ���������� ���� (�� ��������� 30)
	* vector<Railway> Railways - Size �������� ������ Railway

class Cassa(Data): ����������� � Data, ����� ��������� �� ���������� -> Railway -> Train -> Vagon -> Places
	* ������� ������ ����������: ����, �����, ��� ������ (���� ���� �����), ���������� ������� ������� ���������� ���� (���� ���� �����), ��� ���������� 
	* ��������� ������� ��������� ���� �� ������� ���������� (��� ������������� ������ ��� ������ � ����� ������, ������� ����� ������������), 
	* ��������������� �����, 
	* ���������� ����� ��������� �������, 
	* �������� ����� �������, 
	* ������������ ������ (������ ����� ��������: ����, ����� ������, ����� ������, ����� �����, ��� ���������, ������� �����������, ������� ��������).
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
	//����������� �� ���������
	Ticket() : Cost(), Data(), Train_number(0), Vagon_number(0), Place_number(0), Name(), Departure_station(""), Arrival_station("") {}

	//����������� ������
	Ticket(int cost, Railway_data data, int train_number, int vagon_number, int place_number, FIO name,std::string departure_station, std::string arrival_station) : Cost(cost), Data(data), Train_number(train_number), Vagon_number(vagon_number), Place_number(place_number), Name(name), Departure_station(departure_station), Arrival_station(arrival_station) {}

	//������� ����
	Railway_data Get_data()
	{
		return Data;
	}

	//������� ���
	FIO Get_name()
	{
		return Name;
	}

	//������� ����
	int Get_price()
	{
		return Cost;
	}

	//������� ����� ������
	int Get_train_number()
	{
		return Train_number;
	}

	//������� ����� ������
	int Get_vagon_number()
	{
		return Vagon_number;
	}

	//������� ����� �����
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
	//����������� �� ���������
	Vagon()
	{
		Free_size = 0;
		Number = 0;
		Type = 0;
		Size = 0;
	}

	//����������� �� ������ � ���� ������
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

	//������� ���������� ��������� ����
	int Get_free_size()
	{
		return Free_size;
	}

	//������� ����� ������
	int Get_number()
	{
		return Number;
	}

	//������� ��� ������
	int Get_type()
	{
		return Type;
	}

	//������� ����� ������
	void Set_number(int number)
	{
		Number = number;
	}

	//��������� ����� � ������ �� �������
	bool Check_place(int index)
	{
		return Places.at(index);
	}

	//������������� ����� �� �������
	void Reserve_place(int index)
	{
		if (!Places.at(index))
		{
			Places.at(index) = 1;
			Free_size--;
		}
	}

	//��������������� ����� �� �������
	void Anreserve_place(int index)
	{
		if (Places.at(index))
		{
			Places.at(index) = 0;
			Free_size++;
		}
	}

	//������� �� ����� �� ��������������� �����
	void Print_suitable_places()
	{
		for (int i = 0; i < Size; i++)
			if (!Places.at(i))
				std::cout << "����� �" << i + 1 << std::endl;
	}

	//���������� ����������
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
	//����� ������ ������ �� ������ ��� ������� -1
	int Found_vagon(int number) 
	{
		for (int i = 0; i < Vagons.size(); i++)
			if (Vagons[i].Get_number() == number)
				return i;
		return -1;
	}
public:
	//����������� �� ���������
	Train() : Number(0), Type(0), Size(0) {}

	//����������� �� ������ � ���� ������
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

	//�������� ����� �� ������
	Vagon* Get_vagon(int number)
	{
		int index = Found_vagon(number);
		if (index == -1)
			return nullptr;
		return &Vagons.at(index);
	}

	//�������� ����� ������
	int Get_number()
	{
		return Number;
	}

	//�������� ��� ������
	int Get_type()
	{
		return Type;
	}

	//�������� ���������� ������� � ������
	int Get_size()
	{
		return Size;
	}

	//��������� ���� �� � ������ ���������� ������
	bool Check_free_vagons(int count_peoples)
	{
		for (int i = 0; i < Size; i++)
			if (Vagons.at(i).Get_free_size() > count_peoples)
				return true;
		return false;
	}

	//���������� � ������� ��� ���������� �� �������� ������
	void Print_suitable_vagons(int vagon_type, int places_count)
	{
		for (Vagon i : Vagons)
			if (i.Get_free_size() >= places_count)
				std::cout << "����� �" << i.Get_number() << std::endl;
	}
	
	//���������� ����������
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
	//����������� �� ���������
	Railway() : Data(), Count_trains(0), Count_tickets(0) {}

	//����������� �� ����
	Railway(Railway_data data)
	{
		Data = data;
		Count_trains = 0;
		Count_tickets = 0;
	}

	//����� ������ ������ �� ������ ��� ������� -1
	int Found_train(int number)
	{
		for (int i = 0; i < Count_trains; i++)
			if (Trains.at(i).Get_number() == number)
				return i;
		return -1;
	}

	//�������� � ������� ��� ���������� �� ���������� ������
	void Print_suitable_trains(int train_type, int places_count)
	{
		for (Train i : Trains)
			if (i.Get_type() == train_type && i.Check_free_vagons(places_count))
				std::cout << "����� �" << i.Get_number() << std::endl;
	}

	//�������� ����� �� ������
	Train* Get_train(int number)
	{
		int index = Found_train(number);
		if (index == -1)
			return nullptr;
		return &Trains.at(index);
	}

	//�������� ����
	Railway_data Get_data() const
	{
		return Data;
	}

	//�������� ���������� �������
	int Get_count_trains()
	{
		return Count_trains;
	}

	//�������� ���������� �������
	int Get_count_tickets()
	{
		return Count_tickets;
	}

	//�������� �����
	void Append_train(Train train)
	{
		Trains.push_back(train);
		Count_trains++;
	}

	//�������� �����
	void Append_ticket(Ticket ticket)
	{
		Tickets.push_back(ticket);
		Count_tickets++;
	}

	//������� ����� �� ���� � ������� ������, ������ � �����
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

	//��������� ����
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
					return 1000; //������
				return 800;//�������
			case cupe:
				if (place_number % 2 == 0)
					return 1200; //������
				return 1000;//�������
			case sv:
				return 1300;
			}
			break;
		case fasttrain:
			switch (vagon_type)
			{
			case pzkrt:
				if (place_number % 2 == 0)
					return 900; //������
				return 700; //�������
			case cupe:
				if (place_number % 2 == 0)
					return 1100; //������
				return 900;//�������
			case sv:
				return 1200;
			}
		}
		return 0;
	}

	//���������� ����������
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
	//����������� �� ����������
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

	//�������� ���������� Railway �� ��� � ������
	Railway* Get_railway(int day, int mon) 
	{
		if (!is_valid_date(day, mon)) {
			std::cout << "������: ������������ ����" << std::endl;
			return nullptr;
		}

		Railway_data rd(day, mon);
		for (int i = 0; i < Size; i++)
			if (Railways.at(i).Get_data() == rd)
				return &Railways.at(i);

		std::cout << "������: ���������� �� ��������� ���� �����������" << std::endl;
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
	//����������� ������
	Cassa(Data data) : Calendar(data), Initialization(false), Today_data(), Train_type(0), Train_num(0), Vagon_type(0), Vagon_num(0), Places_count(0), Total_cost(0), Names_size(0), Places_size(0), Departure_station(""), Arrival_station(""), Reserved_place_size(0) {}

	//�������� ������ ������������ � ������� �� � ���� Data Calendar
	void Get_user_info()
	{
		if (Initialization)
			return;
		char ch;
		int mon, day;
		std::cout << "������� ����: ";
		std::cin >> day;
		while (ch = getchar() != '\n');
		std::cout << "������� �����: ";
		std::cin >> mon;
		while (ch = getchar() != '\n');
		if (!is_valid_date(day, mon))
		{
			std::cout << "������: �������� ����, ���� ����������� �� ���� ���� �����������" << std::endl;
			return;
		}
		Today_data = Railway_data(day, mon);
		Today_railway = *Calendar.Get_railway(day, mon);

		int station;
		std::cout << "�������� ������� ����������� (1 - ������ �������� | 2 - ������): ";
		std::cin >> station;
		if (station == 1)
		{
			Departure_station = "������ ��������";
			Arrival_station = "������";
		}
		else if (station == 2)
		{
			Departure_station = "������";
			Arrival_station = "������ ��������";
		}
		else
		{
			std::cout << "������: ������� �� ���������� ��������" << std::endl;
			return;
		}

		std::cout << "�������� ��� ������ (1 - '��������' | 2 - ������| 3 - ���������): ";
		std::cin >> Train_type;
		while (ch = getchar() != '\n');
		if (Train_type < 1 && Train_type > 3)
		{
			std::cout << "������: ������� �� ���������� ��������" << std::endl;
			return;
		}
		switch (Train_type)
		{
		case birdtrain:
			Vagon_type = birdvagon;
			break;
		case fasttrain:
		case firmtrain:
			std::cout << "�������� ��� ������ (2 - �������� | 3 - ����| 4 - ��): ";
			std::cin >> Vagon_type;
			while (ch = getchar() != '\n');
			if (Vagon_type < 2 && Vagon_type > 4)
			{
				std::cout << "������: ������� �� ���������� ��������" << std::endl;
				return;
			}
		}
		
		std::cout << "������� ���������� ����������: ";
		std::cin >> Places_count;
		while (ch = getchar() != '\n');
		if (Places_count <= 0 || Places_count > 100)
		{
			std::cout << "������: ������� �� ���������� ��������" << std::endl;
			return;
		}
		Initialization = true;
		for (int i = 0; i < Places_count; i++)
			Reserve_place();
	}

	//��������� ���������� ����� � ������ (������ ����� ������ Reserve_place)
	void Check_free_place(int place_num)
	{
		if (!Initialization)
			return;
		if (Reserved_place_size < 1)
		{
			std::cout << "������ ������������ ������ ���� �����" << std::endl;
			return;
		}
		Train train = *Today_railway.Get_train(Train_num);
		Vagon vagon = *train.Get_vagon(Vagon_num);
		if (train.Check_free_vagons(Places_count))
		{
			std::cout << "� ������ ��� ������� � ���������� ����������� ��������� ����" << std::endl;
			return;
		}
		if (vagon.Get_free_size() < Places_count)
		{
			std::cout << "� ������ ��� ������� ���������� ��������� ����" << std::endl;
			return;
		}
		if (vagon.Check_place(place_num))
			std::cout << "������" << std::endl;
		else
			std::cout << "��������" << std::endl;
	}

	//������������� ����� � ������
	void Reserve_place()
	{
		if (!Initialization)
		{
			std::cout << "������: ����� �� ����������������" << std::endl;
			return;
		}
		char ch;
		if (Train_num == 0)
		{
			std::cout << "�������� ����� ������ �� ���������� ��� ���" << std::endl;
			Today_railway.Print_suitable_trains(Train_type, Places_count);
			std::cout << "��� �����: ";
			std::cin >> Train_num;
			while (ch = getchar() != '\n');

			std::cout << "�������� ����� ������ �� ���������� ��� ���" << std::endl;
			Today_railway.Get_train(Train_num)->Print_suitable_vagons(Vagon_type, Places_count);
			std::cout << "��� �����: ";
			std::cin >> Vagon_num;
			while (ch = getchar() != '\n');
		}
		int Place_num;
		std::cout << "�������� ����� ����� �� ���������� ��� ���" << std::endl;
		Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Print_suitable_places();
		std::cout << "��� �����: ";
		std::cin >> Place_num;
		while (ch = getchar() != '\n');
		Place_num--;
		int train_type = Today_railway.Get_train(Train_num)->Get_type();
		int vagon_type = Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Get_type();
		int cost = Today_railway.Check_price(train_type, vagon_type, Place_num);

		std::string input;
		std::cout << "������� ���� ��� � ������� '������� ��� ��������': ";
		std::getline(std::cin, input);

		std::string f_name, i_name, o_name;
		std::istringstream iss(input);
		iss >> f_name >> i_name >> o_name;
			
		Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Reserve_place(Place_num);
		std::cout << "����� �������������" << std::endl;
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

	//�������� �����
	void Cancel_ticket_order(int place_num)
	{
		if (!Initialization)
			return;
		if (!Today_railway.Get_train(Train_num)->Get_vagon(Vagon_num)->Check_place(place_num))
		{
			std::cout << "����� �� �������������" << std::endl;
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
			std::cout << "����� � ����� �����" << std::endl;
		}
	}

	//��������� ����� ���� ���� �������
	void Calculate_total_price()
	{
		if (!Initialization)
			return;
		Total_cost = 0;
		for (int i : Prices)
			Total_cost += i;
	}
	
	//������ ���
	void Generate_ticket()
	{
		if (!Initialization)
			return;
		std::cout << "______________�����______________" << std::endl;
		std::cout << "����: " << Today_data;
		std::cout << " ����� �" << Train_num;
		std::cout << " ����� �" << Vagon_num << std::endl;
		
		std::cout << "��� ����������:";
		for (int i = 0; i < Names_size; i++)
		{
			if (i < Names.size() - 1)
				std::cout << " " << Names.at(i) << ",";
			else
				std::cout << " " << Names.at(i) << std::endl;
		}

		std::cout << "������ ����";
		for (int i = 0; i < Places_size; i++)
		{
			if (i < Places.size() - 1)
				std::cout << " " << Places.at(i) << ",";
			else
				std::cout << " " << Places.at(i) << std::endl;
		}		

		std::cout << "������� �����������: " << Departure_station << std::endl;
		std::cout << "������� ��������: " << Arrival_station << std::endl;
		if (Total_cost == 0)
			Calculate_total_price();
		std::cout << "�������� ��������� �������: " << Total_cost << "�." << std::endl;
		std::cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << std::endl;
	}
};

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//������� ������ ������ data, � ������� ���������� 30 ���� (Railway) ������ ������� �� ��� ������� ���������
	Data data;
  //��������� ���� "���� ������", ������ � ������������ ��� ������ (���������� ������ Railway ����)
	data.Get_railway(27, 04)->Append_train(Train(1, birdtrain));
	data.Get_railway(27, 04)->Append_train(Train(2, birdtrain));
	data.Get_railway(27, 04)->Append_train(Train(3, birdtrain));
	data.Get_railway(27, 04)->Append_train(Train(4, birdtrain));
	data.Get_railway(27, 04)->Append_train(Train(5, fasttrain));
	data.Get_railway(27, 04)->Append_train(Train(6, fasttrain));
	data.Get_railway(27, 04)->Append_train(Train(7, fasttrain));
	data.Get_railway(27, 04)->Append_train(Train(8, firmtrain));
	data.Get_railway(27, 04)->Append_train(Train(9, firmtrain));

	//"����������" � ����� ����� data, � ������� ����� ��������
	Cassa cassa(data);
	//�������� ���������� ������������ � ������� ������
	cassa.Get_user_info();
	//������� ����� � ������� ����� 2 � ����� ��������� ������
	cassa.Cancel_ticket_order(2);
	//������������� �����
	cassa.Generate_ticket();
	system("pause");
}
