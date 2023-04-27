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
	* int[] Places - true ��� false � ����������� �� 
class Train(int Type)
	* vector Vagons
class Railway(): ��� ������ � ������ �� ���������� ����, ����� �� ��������� ������� ��� ���� �����
	* vector Trains
	* vector Tickets
	* struct Cost
class Data(): ���������� �� 30 ���� ������ � dat �����, � ������ ������ ��������� �����������
	* vector Railways
class Cassa(): ��������� � Data -> Railway -> Train -> Vagon -> Places
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
#include "Header.h"
#include <Windows.h>
#include <sstream>

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
	Ticket() : Cost(), Data(), Train_number(0), Vagon_number(0), Place_number(0), Name(), Departure_station(""), Arrival_station("") {}

	Ticket(int cost, Railway_data data, int train_number, int vagon_number, int place_number, FIO name,std::string departure_station, std::string arrival_station) : Cost(cost), Data(data), Train_number(train_number), Vagon_number(vagon_number), Place_number(place_number), Name(name), Departure_station(departure_station), Arrival_station(arrival_station) {}


	Railway_data Get_data()
	{
		return Data;
	}

	FIO Get_name()
	{
		return Name;
	}

	int Get_price()
	{
		return Cost;
	}

	int Get_train_number()
	{
		return Train_number;
	}

	int Get_vagon_number()
	{
		return Vagon_number;
	}

	int Get_place_number()
	{
		return Place_number;
	}

	/*void Print_info()
	{
		std::cout << "����: " << Data << std::endl;
		std::cout << "����� �����: " << Train_number << std::endl;
		std::cout << "����� ������: " << Vagon_number << std::endl;
		std::cout << "����� �����: " << Place_number << std::endl;
		std::cout << "���: " << Name << std::endl;
		std::cout << "������� �����������: " << Departure_station << std::endl;
		std::cout << "������� ��������: " << Arrival_station << std::endl;
	}*/
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

	//�������� ��������� ����� � ������ �� �������
	void Reserve_place(int index)
	{
		if (!Places.at(index))
		{
			Places.at(index) = 1;
			Free_size--;
		}
	}

	void Anreserve_place(int index)
	{
		if (Places.at(index))
		{
			Places.at(index) = 0;
			Free_size++;
		}
	}

	//������� � ������� ����� ������
	/*void Print_vagon()
	{
		for (int i = 0; i < Size; i += 2)
			std::cout << "(" << (i + 1) << ") - " << Places.at(i) << "   |   " << "(" <<  (i + 2) << ") - " << Places.at(i + 1) << std::endl;
	}*/

	//������� � ������� ���������� ��� ����� (���, �����, �����)
	/*void Print_info()
	{
		std::string type;
		switch (Type)
		{
		case birdvagon:
			type = "��������";
			break;
		case pzkrt:
			type = "��������";
			break;
		case cupe:
			type = "����";
			break;
		case sv:
			type = "��";
			break;
		}
		std::cout << "    ����� �" << Number << " (" << Size << " ����, ��� " << type << ")" << std::endl;
	}*/

	//���������� ����������
	Vagon& operator=(const Vagon& vagon)
	{
		if (Size < vagon.Size)
			Places.resize(vagon.Size);
		Number = vagon.Number;
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

	//������� ����� ������
	/*void Set_number(int number)
	{
		Number = number;
	}*/

	//��������� ���� �� � ������ ���������� ������
	bool Check_free_vagons(int count_peoples)
	{
		for (int i = 0; i < Size; i++)
			if(Vagons.at(i).Get_free_size() > count_peoples)
				return true;
		return false;
	}
	
	//������� � ������� ���������� � ������ � ������� ������
	/*void Print_info()
	{
		std::string type;
		switch (Type)
		{
		case birdtrain:
			type = "��������";
			break;
		case firmtrain:
			type = "���������";
			break;
		case fasttrain:
			type = "������";
			break;
		}
		std::cout << "  ����� �" << Number << " ���: " << type << std::endl;
		for (int i = 0; i < Size; i++)
			Vagons.at(i).Print_info();
	}*/

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
	//����� ������ ������ �� ������ ��� ������� -1
	int Found_train(int number)
	{
		for (int i = 0; i < Count_trains; i++)
			if (Trains.at(i).Get_number() == number)
				return i;
		return -1;
	}
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

	int Total_price()
	{
		int result = 0;
		for (int i = 0; i < Count_tickets; i++)
			result += Tickets.at(i).Get_price();
		return result;
	}

	//������� � ������� ���������� � ��� (������ � ������)
	/*void Print_info()
	{
		std::cout << "���������� ��������� ������� �� "<< Data <<": " << Count_tickets << std::endl;
		if (Count_trains != 0)
			std::cout << "������ �� �������:" << std::endl;
		else
			std::cout << "� ���� ���� ������� ���" << std::endl;
		for (int i = 0; i < Count_trains; i++)
			Trains.at(i).Print_info();
	}*/

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

	//��������� ������������ �������� ����
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

	//�������� ���������� ���� �� ��� � ������
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

	//������� � ������� ���������� ��� ��� ��� ������
	/*void Print_info()
	{
		std::cout << "����������� �� �����" << std::endl;
		for (int i = 0; i < Size; i++)
			Railways.at(i).Print_info();
	}*/
};

class Cassa
{
	Data Calendar;
	bool Initialization = false;

	Railway_data Today_data;
	int Train_type;
	int Vagon_type;
	int Tickets_count;
	int Total_cost;
	std::vector <FIO> Names;
	std::vector <int> Places;
	std::string Departure_station;
	std::string Arrival_station;

public:
	Railway Today_railway;
	Cassa(Data data) { Calendar = data; }

	void Get_user_info()
	{
		if (Initialization)
			return;
		char ch;
		int mon, day;
		std::cout << "������� �����: ";
		std::cin >> mon;
		while (ch = getchar() != '\n');
		std::cout << "������� ����: ";
		std::cin >> day;
		while (ch = getchar() != '\n');
		Today_data = Railway_data(day, mon);
		Today_railway = *Calendar.Get_railway(day, mon);
				
		std::string input;
		std::string word1, word2;
		std::cout << "������� ������� �����������: ";
		std::getline(std::cin, input);
		std::istringstream iss(input);
		iss >> word1 >> word2;
		Departure_station = word1 + " " + word2;
		if (Departure_station == "������ ��������")
			Arrival_station = "������";
		else
			Arrival_station = "������ ��������";

		std::cout << "�������� ��� ������: ";
		std::cin >> Train_type;
		while (ch = getchar() != '\n');
		std::cout << "�������� ��� ������: ";
		std::cin >> Vagon_type;
		while (ch = getchar() != '\n');
		std::cout << "������� ���������� ����������: ";
		std::cin >> Tickets_count;
		while (ch = getchar() != '\n');
		Initialization = true;
	}

	void Check_free_place(int train_num, int vagon_num, int place_num)
	{
		if (!Initialization)
			return;
		Train train = *Today_railway.Get_train(train_num);
		Vagon vagon = *train.Get_vagon(vagon_num);
		if (train.Check_free_vagons(Tickets_count))
			std::cout << "� ������ ��� ������� � ���������� ����������� ��������� ����" << std::endl;
		if (vagon.Get_free_size() < Tickets_count)
			std::cout << "� ������ ��� ������� ���������� ��������� ����" << std::endl;
		if (vagon.Check_place(place_num))
			std::cout << "������" << std::endl;
		else
			std::cout << "��������" << std::endl;
	}

	void Reserve_place(int train_num, int vagon_num, int place_num)
	{
		if (!Initialization)
			return;
		if (Today_railway.Get_train(train_num)->Get_vagon(vagon_num)->Check_place(place_num))
			std::cout << "����� ��� �������������" << std::endl;
		else
		{
			char ch;
			int train_type = Today_railway.Get_train(train_num)->Get_type();
			int vagon_type = Today_railway.Get_train(train_num)->Get_vagon(vagon_num)->Get_type();
			int cost = Today_railway.Check_price(train_type, vagon_type, place_num);
			std::string f_name, i_name, o_name;
			std::cout << "���� �������: ";
			std::cin >> f_name;
			while (ch = getchar() != '\n');
			std::cout << "���� ���: ";
			std::cin >> i_name;
			while (ch = getchar() != '\n');
			std::cout << "���� ��������: ";
			std::cin >> o_name;
			while (ch = getchar() != '\n');
			
			Today_railway.Get_train(train_num)->Get_vagon(vagon_num)->Reserve_place(place_num);
			std::cout << "����� �������������" << std::endl;
			FIO fio(f_name, i_name, o_name);
			bool flag = false;
			for (FIO i : Names)
				if (i == fio)
					flag = true;
			if (!flag)
				Names.push_back(fio);
			Places.push_back(place_num);
			Today_railway.Append_ticket(Ticket(cost, Today_data, train_num, vagon_num, place_num, fio, Departure_station, Arrival_station));
		}
	}

	void Cancel_ticket_order(int train_num, int vagon_num, int place_num)
	{
		if (!Initialization)
			return;
		if (!Today_railway.Get_train(train_num)->Get_vagon(vagon_num)->Check_place(place_num))
		{
			std::cout << "����� �� �������������" << std::endl;
		}
		else
		{
			Today_railway.Get_train(train_num)->Get_vagon(vagon_num)->Anreserve_place(place_num);
			Today_railway.Delete_ticket(train_num, vagon_num, place_num);
			std::cout << "����� � ����� �����" << std::endl;
		}
	}

	void Calculate_total_price()
	{
		if (!Initialization)
			return;
		std::cout << "����� ������ �� ���������: " << Today_railway.Total_price() << "�." << std::endl;
	}
	
	void Generate_ticket(int train_num, int vagon_num, int place_num)
	{
		if (!Initialization)
			return;
		std::cout << "����: " << Today_data << std::endl;
		std::cout << "����� �����: " << train_num << std::endl;
		std::cout << "����� ������: " << vagon_num << std::endl;
		std::cout << "������ ����";
		for (int i : Places)
			std::cout << " | " << i;
		std::cout << std::endl;

		std::cout << "���";
		for (FIO i : Names)
			std::cout << " | " << i;
		std::cout << std::endl;

		std::cout << "������� �����������: " << Departure_station << std::endl;
		std::cout << "������� ��������: " << Arrival_station << std::endl;
	}
};

int main()
{
	SetConsoleOutputCP(1251); // ��������� ��������� ��� ������
	SetConsoleCP(1251); // ��������� ��������� ��� �����

	Data data;
	data.Get_railway(27, 04)->Append_train(Train(1, birdtrain));
	Cassa cassa(data);
	cassa.Get_user_info();
	system("pause");

	cassa.Reserve_place(1, 1, 2);

	cassa.Calculate_total_price();
	cassa.Generate_ticket(1, 1, 1);
	system("pause");
}
