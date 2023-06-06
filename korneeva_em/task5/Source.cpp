#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <sstream>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

enum class TrainType { LASTOCHKA, FIRMY, SKOROSTNOY };
enum class CarType { PLATZKART, KUPE, SV, SITTING };
enum class SeatType { UPPER, LOWER, SITTING };
enum class Status { FREE, RESERVED, SOLD };


class Ticket
{
private:
	string date = "";
	int trainNumber = 0;
	int carNumber = 0;
	int seatNumber = 0;
	string passengerName = "";
	string departureStation = "";
	string arrivalStation = "";

	TrainType trainType;
	CarType carType;
	SeatType seatType;

	int ticketPrice = 0;

public:
	Ticket(string _date, TrainType _trainType, CarType _carType, SeatType _seatType, string _departureStation, string _arrivalStation, string _passengerName = "-") :
		date(_date), trainNumber(0), carNumber(0), seatNumber(0), passengerName(_passengerName),
		departureStation(_departureStation), arrivalStation(_arrivalStation), trainType(_trainType), carType(_carType), seatType(_seatType), ticketPrice(0) {}

	void setDate(string _date)
	{
		this->date = _date;
	}
	void setTrainNumber(int _trainNumber)
	{
		this->trainNumber = _trainNumber;
	}
	void setCarNumber(int _carNumber)
	{
		this->carNumber = _carNumber;
	}
	void setSeatNumber(int _seatNumber)
	{
		this->seatNumber = _seatNumber;
	}
	void setPassengerName(string _passengerName)
	{
		this->passengerName = _passengerName;
	}
	void setDepartureStation(string _departureStation)
	{
		this->departureStation = _departureStation;
	}
	void setArrivalStation(string _arrivalStation)
	{
		this->arrivalStation = _arrivalStation;
	}
	void setTrainType(TrainType _trainType)
	{
		this->trainType = _trainType;
	}
	void setCarType(CarType _carType)
	{
		this->carType = _carType;
	}
	void setSeatType(SeatType _seatType)
	{
		this->seatType = _seatType;
	}
	void setTicketPrice(int _ticketPrice)
	{
		this->ticketPrice = _ticketPrice;
	}

 
	int getTrainNumber() const
	{
		return trainNumber;
	}   
	int getCarNumber() const
	{
		return carNumber;
	}    
	int getSeatNumber() const
	{
		return seatNumber;
	}
	int getTicketPrice() const
	{
		return ticketPrice;
	}
	string getPassengerName() const
	{
		return passengerName;
	}  
	string getDate() const
	{
		return date;
	}
	string getDepartureStation() const
	{
		return departureStation;
	}   
	string getArrivalStation() const
	{
		return arrivalStation;
	}   
	TrainType getTrainType() const
	{
		return trainType;
	}   
	CarType getCarType() const
	{
		return carType;
	}   
	SeatType getSeatType() const
	{
		return seatType;
	}
};

class Car
{
	CarType type;
	int carNumber;
	int seatsCount = 0;
	int reservedSeatsCount = 0;
	int soldSeatsCount = 0;
	int freeSeatsCount = 0;
	vector<pair<Status, string>> seats;
	vector<pair<SeatType, int>> seatTypes;

public:
	Car(CarType _type, int _carNumber) : type(_type), carNumber(_carNumber)
	{
		switch (type)
		{
		case CarType::PLATZKART:
			seatsCount = 54;
			seatTypes.resize(seatsCount);
			for (int i = 0; i < seatsCount; i++)
			{
				if (i < 27) 
				{
					seatTypes[i] = { SeatType::LOWER, 2500 };
				}
				else 
				{
					seatTypes[i] = { SeatType::UPPER, 2000 };
				}
			}
			break;

		case CarType::KUPE:
			seatsCount = 36;
			seatTypes.resize(seatsCount);
			for (int i = 0; i < seatsCount; i++)
			{
				if (i < 18) 
				{
					seatTypes[i] = { SeatType::LOWER, 5000 };
				}
				else 
				{
					seatTypes[i] = { SeatType::UPPER, 4800};
				}
			}
			break;

		case CarType::SV:
			seatsCount = 18;
			seatTypes.resize(seatsCount);
			for (int i = 0; i < seatsCount; i++)
			{
				seatTypes[i] = { SeatType::LOWER, 7000 };
			}
			break;

		case CarType::SITTING:
			seatsCount = 100;
			seatTypes.resize(seatsCount);
			for (int i = 0; i < seatsCount; i++)
			{
				seatTypes[i] = { SeatType::SITTING, 1200 };
			}
			break;
		}

		seats.resize(seatsCount);

		for (int i = 0; i < seatsCount; i++)
		{
			seats[i] = { Status::FREE, "" };
		}

		freeSeatsCount = seatsCount;
	}

	CarType getType() const
	{
		return type;
	}
	int getCarNumber() const
	{
		return carNumber;
	}
	int getSeatsCount() const
	{
		return seatsCount;
	}
	int getReservedSeatsCount() const
	{
		return reservedSeatsCount;
	}
	int getSoldSeatsCount() const
	{
		return soldSeatsCount;
	}
	int getFreeSeatsCount() const
	{
		return freeSeatsCount;
	}
	int getPrice(SeatType seatType) const
	{
		for (int i = 0; i < seatsCount; i++)
		{
			if (seatTypes[i].first == seatType)
			{
				return seatTypes[i].second;
			}
		}
	}

	bool hasSeat(int seatNumber) const
	{
		return seatNumber >= 1 && seatNumber <= seatsCount;
	}
	bool FreeSeatsCountOfType(const vector<int> _typeCounts) const
	{
		vector<int> freeSeats = { 0,0,0 };
		for (int i = 0; i < seatsCount; i++)
		{
			if (seats[i].first == Status::FREE)
				switch (seatTypes[i].first)
				{
				case SeatType::LOWER:
					freeSeats[0]++;
					break;
				case SeatType::UPPER:
					freeSeats[1]++;
					break;
				case SeatType::SITTING:
					freeSeats[2]++;
					break;
				}
		}
		if (freeSeats[0] >= _typeCounts[0] && freeSeats[1] >= _typeCounts[1] && freeSeats[2] >= _typeCounts[2])
		{
			return true;
		}
		return false;
	}

	int reserveSeat(string passengerName, SeatType seatType)
	{
		for (int i = 0; i < seatsCount; i++)
		{
			if ((seats[i].first == Status::FREE) && (seatTypes[i].first == seatType))
			{
				seats[i] = { Status::RESERVED, passengerName };
				reservedSeatsCount++;
				freeSeatsCount--;
				return ++i;
			}
		}
		return 0;
	}
	void unreserveSeat(int seatNumber)
	{
		if (!hasSeat(seatNumber))
		{
			throw invalid_argument("����� � �������� ������� �� ����������");
		}


		if (seats[seatNumber-1].first != Status::RESERVED)
		{
			throw logic_error("����� �� ���� ���������������");
		}

		seats[seatNumber-1] = { Status::FREE , ""};
		reservedSeatsCount--;
		freeSeatsCount++;
	}

	void sellSeat(int seatNumber)
	{
		seats[seatNumber - 1].first = Status::SOLD;
		reservedSeatsCount--;
		soldSeatsCount++;
	}
	void cancelSellSeat(int seatNumber)
	{
		if (!hasSeat(seatNumber))
		{
			throw invalid_argument("����� � �������� ������� �� ����������");
		}


		if (seats[seatNumber - 1].first != Status::SOLD)
		{
			throw logic_error("����� �� ���� �������");
		}

		seats[seatNumber - 1] = { Status::FREE , "" };
		soldSeatsCount--;
		freeSeatsCount++;
	}

	static string carTypeToString(CarType type)
	{
		switch (type) {
		case CarType::PLATZKART:
			return "��������";
		case CarType::KUPE:
			return "����";
		case CarType::SV:
			return "��";
		case CarType::SITTING:
			return "�������";
		}
	}
	void printSeatsInfo() const
	{
		string s = carTypeToString(type);
		cout << "����� � ������ ����� " << carNumber << " (" << s << ")" << endl;
		for (int i = 0; i < seatsCount; i++)
		{
			cout << "����� " << i + 1 << ": ";
			switch (seats[i].first)
			{
			case Status::FREE:
				cout << "��������" << endl;
				break;
			case Status::RESERVED:
				cout << "���������������:  " << seats[i].second << endl;
				break;
			case Status::SOLD:
				cout << "�������: " << seats[i].second << endl;
				break;
			}
		}
	}
};

class Train 
{
private:
	TrainType type;
	vector<Car> cars;

	int trainNumber;
	string departureStation;
	string arrivalStation;
	string date;

public:
	Train(TrainType _type, int _trainNumber, string _departureStation, string _arrivalStation, string _date)
		: type(_type), trainNumber(_trainNumber), departureStation(_departureStation), arrivalStation(_arrivalStation), date(_date)
	{
		switch (type) 
		{
		case TrainType::LASTOCHKA:
			for (int i = 0; i < 8; i++) {
				Car car(CarType::SITTING, i + 1);
				addCar(car);
			}
			break;

		case TrainType::FIRMY:
			for (int i = 0; i < 2; i++) {
				Car car(CarType::SV, i + 1);
				addCar(car);
			}
			for (int i = 2; i < 8; i++) {
				Car car(CarType::KUPE, i + 1);
				addCar(car);
			}
			for (int i = 8; i < 12; i++) {
				Car car(CarType::PLATZKART, i + 1);
				addCar(car);
			}
			break;

		case TrainType::SKOROSTNOY:
			for (int i = 0; i < 4; i++) {
				Car car(CarType::KUPE, i + 1);
				addCar(car);
			}
			for (int i = 4; i < 12; i++) {
				Car car(CarType::PLATZKART, i + 1);
				addCar(car);
			}
			break;
		}
	}

	TrainType getType() const
	{
		return type;
	}
	int getTrainNumber() const
	{
		return trainNumber;
	}
	int getCarsCount() const
	{
		return cars.size();
	}
	int getPrice(int carNumber, SeatType seatType)
	{
		return cars[carNumber].getPrice(seatType);
	}
	const string& getDepartureStation() const
	{
		return departureStation;
	}
	const string& getArrivalStation() const
	{
		return arrivalStation;
	}
	const string& getDepartureDate() const
	{
		return date;
	}

	void setDepartureDate(const string& date)
	{
		this->date = date;
	}
	void setDepartureStation(const string& _departureStation)
	{
		this->departureStation = _departureStation;
	}
	void setArrivalStation(const string& _arrivalStation)
	{
		this->arrivalStation = _arrivalStation;
	}
	
	void addCar(const Car& car)
	{
		cars.push_back(car);
	}
	bool hasCar(int carNumber) const
	{
		return carNumber >= 1 && carNumber <= getCarsCount();
	}
	int getFreeCarNumber(CarType carType, const vector<int> _typeCounts)
	{
		for (int i = 0; i < cars.size(); i++)
		{
			bool is = cars[i].FreeSeatsCountOfType(_typeCounts);

			if ((cars[i].getType() == carType) && (is))
			{
				return ++i;
			}
		}
		return 0;
	}
	
	int reserveTicket(int carNumber, SeatType seatType, const string& passengerName)
	{
		if (!hasCar(carNumber))
		{
			throw std::invalid_argument("����� � ����� ������� �� ����������");
		}

		return (cars[carNumber - 1].reserveSeat(passengerName, seatType));
	}
	void unreserveTicket(int carNumber, int seatNumber)
	{
		if (!hasCar(carNumber))
		{
			throw std::invalid_argument("����� � ����� ������� �� ����������");
		}

		cars[carNumber - 1].unreserveSeat(seatNumber);
	}
	void sellTicket(int carNumber, int seatNumber)
	{
		cars[carNumber - 1].sellSeat(seatNumber);
	}
	void cancelSellTicket(int carNumber, int seatNumber)
	{
		if (!hasCar(carNumber))
		{
			throw std::invalid_argument("����� � ����� ������� �� ����������");
		}

		cars[carNumber - 1].cancelSellSeat(seatNumber);
	}

	void printCarInfo(int carIndex)
	{
		cars[carIndex].printSeatsInfo();
	}
	void printTrainInfo()
	{
		cout << "��� ������: ";
		switch (type) {
		case TrainType::LASTOCHKA:
			cout << "��������" << endl;
			break;
		case TrainType::FIRMY:
			cout << "���������" << endl;
			break;
		case TrainType::SKOROSTNOY:
			cout << "����������" << endl;
			break;
		}
		cout << "����� ������: " << trainNumber << endl;
		cout << "�������: " << departureStation << " - " << arrivalStation << endl;
		cout << "���� �����������: " << date << endl;
		cout << "���������� �������: " << getCarsCount() << endl << endl;
	}
};

class GorkyRailway
{
private:
	string departureDate;
	vector<Train> schedule;

public:
	GorkyRailway(string _departureDate) : departureDate(_departureDate)
	{
		schedule.push_back(Train(TrainType::LASTOCHKA, 15, "������", "������ ��������", departureDate));
		schedule.push_back(Train(TrainType::FIRMY, 22, "������", "������ ��������", departureDate));
		schedule.push_back(Train(TrainType::SKOROSTNOY, 43, "������", "������ ��������", departureDate));

		schedule.push_back(Train(TrainType::LASTOCHKA, 28, "������ ��������", "������", departureDate));
		schedule.push_back(Train(TrainType::FIRMY, 57, "������ ��������", "������", departureDate));
		schedule.push_back(Train(TrainType::SKOROSTNOY, 82, "������ ��������", "������", departureDate));
	}

	const string& getDate() const
	{
		return departureDate;
	}

	int getCarNumber(CarType carType, const vector<int> _typeCounts, int indexTrain)
	{
		return schedule[indexTrain].getFreeCarNumber(carType, _typeCounts);
	}
	int getTrainIndex(TrainType train, string _departureStation, string arrivalStation)
	{
		for (int i = 0; i < schedule.size(); i++)
		{
			if ((schedule[i].getType() == train) && (schedule[i].getDepartureStation() == _departureStation) && (schedule[i].getArrivalStation() == arrivalStation))
				return i;
		}
		return -1;
	}
	int getTrainNumber(TrainType train, string _departureStation, string arrivalStation)
	{
		for (int i = 0; i < schedule.size(); i++)
		{
			if ((schedule[i].getType() == train) && (schedule[i].getDepartureStation() == _departureStation) && (schedule[i].getArrivalStation() == arrivalStation))
				return schedule[i].getTrainNumber();
		}
		return 0;
	}	
	int getPrice(int trainIndex, int carNumber, SeatType seatType)
	{
		return schedule[trainIndex].getPrice(carNumber, seatType);
	}
	
	int reserveTicket(int trainIndex, int carNumber, SeatType seatType, const string& passengerName)
	{
		return (schedule[trainIndex].reserveTicket(carNumber, seatType, passengerName));
	}
	void sellTicket(int trainIndex, int carNumber, int seatNumber)
	{
		schedule[trainIndex].sellTicket(carNumber, seatNumber);
	}
	void cancelSellTicket(int trainIndex, int carNumber, int seatNumber)
	{
		schedule[trainIndex].cancelSellTicket(carNumber, seatNumber);
	}
	void unreserveTicket(int trainIndex, int carNumber, int seatNumber)
	{
		schedule[trainIndex].unreserveTicket(carNumber, seatNumber);
	}


	void printCarInfo(int trainIndex, int carNumber)
	{
		schedule[trainIndex].printCarInfo(carNumber-1);
	}
	void printSchedule()
	{
		cout << "-------------------------------------------" << endl;
		cout << "���������� �� " << departureDate << endl;
		cout << "-------------------------------------------" << endl;
		for (int i = 0; i < schedule.size(); i++)
			schedule[i].printTrainInfo();
	}
};

class RailwayTicketOffice
{
private:
	string currentDate;
	vector<GorkyRailway> trainSchedule;
	vector<Ticket> tickets;

	vector<int> TypeCounts;
	vector<pair<string, SeatType>> passengerNames;

	int ticketCounts;
	int dayIndex;
	int trainIndex;
	bool isComplete;
	Status status;

public:
	RailwayTicketOffice(string _currentDate) : currentDate(_currentDate), isComplete(false), status(Status::FREE)
	{
		TypeCounts = {0,0,0};

		tm timeinfo = {};
		istringstream ss(currentDate);
		ss >> get_time(&timeinfo, "%d.%m.%y");

		for (int i = 0; i < 30; i++) 
		{
			timeinfo.tm_mday++;
			mktime(&timeinfo);

			char buffer[80];
			strftime(buffer, sizeof(buffer), "%d.%m.%y", &timeinfo);

			trainSchedule.push_back(GorkyRailway(buffer));
		}
	}

	void setPassengerNames(string name, SeatType _seatType)
	{
		passengerNames.push_back({ name, _seatType });
		switch (_seatType)
		{
			case SeatType::LOWER:
				TypeCounts[0]++;
				break;

			case SeatType::UPPER:
				TypeCounts[1]++;
				break;

			case SeatType::SITTING:
				TypeCounts[2]++;
				break;
		}
		ticketCounts++;
	}
	void setDetails(const string& date, TrainType trainType, CarType carType, string departureStation, string arrivalStation)
	{
		for (int i = 0; i < ticketCounts; i++)
		{
			tickets.push_back(Ticket(date, trainType, carType, passengerNames[i].second,
				departureStation, arrivalStation, passengerNames[i].first));
		}

		int trainNumber = 0;
		int carNumber = 0;

		for (int i = 0; i < 30; i++)
		{
			dayIndex = i;

			if (trainSchedule[i].getDate() == date)
			{
				trainNumber = trainSchedule[dayIndex].getTrainNumber(trainType, departureStation, arrivalStation);
				trainIndex = trainSchedule[dayIndex].getTrainIndex(trainType, departureStation, arrivalStation);
				carNumber = trainSchedule[dayIndex].getCarNumber(carType, TypeCounts, trainIndex);

				if (trainNumber > 0 && carNumber > 0)
				{
					isComplete = true;
					break;
				}
			}
		}

		for (int i = 0; i < ticketCounts; i++)
		{
			tickets[i].setTrainNumber(trainNumber);
			tickets[i].setCarNumber(carNumber);
			tickets[i].setTicketPrice(trainSchedule[dayIndex].getPrice(trainIndex, tickets[i].getCarNumber(), tickets[i].getSeatType()));
		}
	}
	void removePassengerByName(const string& name)
	{
		for (int i = 0; i < ticketCounts; i++)
		{
			if (tickets[i].getPassengerName() == name)
			{
				switch (tickets[i].getSeatType())
				{
				case SeatType::LOWER:
					TypeCounts[0]--;
					break;

				case SeatType::UPPER:
					TypeCounts[1]--;
					break;

				case SeatType::SITTING:
					TypeCounts[2]--;
					break;
				}
				tickets.erase(tickets.begin() + i);
				ticketCounts--;
			}
		}
	}

	bool checkingAvailable()
	{
		if (isComplete)
			return true;
		return false;
	}
	bool reserveSeats()
	{
		if (!checkingAvailable())
			return false;

		for (int i = 0; i < ticketCounts; i++)
		{
			tickets[i].setSeatNumber(trainSchedule[dayIndex].reserveTicket(trainIndex, tickets[i].getCarNumber(), tickets[i].getSeatType(), tickets[i].getPassengerName()));
		}

		status = Status::RESERVED;
		return true;
	}
	bool sellTickets()
	{
		if (status == Status::SOLD)
			return false;

		if ((status == Status::FREE) && reserveSeats())
		{
			for (int i = 0; i < ticketCounts; i++)
			{
				trainSchedule[dayIndex].sellTicket(trainIndex, tickets[i].getCarNumber(), tickets[i].getSeatNumber());
			}
			status = Status::SOLD;
			return true;
		}
		return false;
	}
	bool unreserveSeats()
	{
		if (status != Status::RESERVED)
			return false;

		for (int i = 0; i < ticketCounts; i++)
		{
			trainSchedule[dayIndex].unreserveTicket(trainIndex, tickets[i].getCarNumber(), tickets[i].getSeatNumber());
		}

		status = Status::FREE;
		return true;
	}
	bool cancelSellTicket()
	{
		if (status != Status::SOLD)
			return false;

		for (int i = 0; i < ticketCounts; i++)
		{
			trainSchedule[dayIndex].cancelSellTicket(trainIndex, tickets[i].getCarNumber(), tickets[i].getSeatNumber());
		}

		status = Status::FREE;
		return true;
	}

	int totalCost()
	{
		if (!checkingAvailable())
			throw logic_error("���������� ��������� �����");
		int cost = 0;

		for (int i = 0; i < tickets.size(); i++)
		{
			cost += tickets[i].getTicketPrice();
		}
		return cost;
	}

	void clearFields()
	{
		tickets.clear();
		TypeCounts = vector<int>(3, 0);
		passengerNames.clear();
		ticketCounts = 0;
		dayIndex = 0;
		trainIndex = 0;
		status = Status::FREE;
	}
	void cancelOrder()
	{
		switch (status)
		{
		case Status::SOLD:
			cancelSellTicket();
			clearFields();
			break;
		case Status::RESERVED:
			unreserveSeats();
			clearFields();
			break;
		case Status::FREE:
			clearFields();
			break;
		}
	}

	void printCarInfo()
	{
		trainSchedule[dayIndex].printCarInfo(trainIndex, tickets[0].getCarNumber());
	}
	void printTickets()
	{
		if (ticketCounts==0)
			cout << "��������� �� �������" << endl;
		for (int i = 0; i < tickets.size(); i++)
		{
			cout << "-----------------------------------------"<< endl;
			cout << "���� �����������: " << tickets[i].getDate() << endl;
			cout << "����� ������: " << tickets[i].getTrainNumber() << endl;
			cout << "����� ������: " << tickets[i].getCarNumber() << endl;
			cout << "����� �����: " << tickets[i].getSeatNumber() << endl;
			cout << "��� ���������: " << tickets[i].getPassengerName() << endl;
			cout << "������� �����������: " << tickets[i].getDepartureStation() << endl;
			cout << "������� ��������: " << tickets[i].getArrivalStation() << endl;
			cout << "��������� ������: " << tickets[i].getTicketPrice() << endl;
			cout << "-----------------------------------------" << endl;
		}
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");

	RailwayTicketOffice test("27.04.23");
	
	test.setPassengerNames("������ ������ �������������", SeatType::LOWER);
	test.setPassengerNames("������� ������ ������������", SeatType::UPPER);
	test.setPassengerNames("������� �������� ����������", SeatType::UPPER);
	test.setPassengerNames("���������� ����� ����������", SeatType::UPPER);
	test.setPassengerNames("����������� �������� ����������", SeatType::LOWER);
	
	test.setDetails("01.05.23", TrainType::FIRMY, CarType::KUPE, "������ ��������", "������");
	
	if (test.checkingAvailable())
		cout << "��������� ����� ���� � �������" << endl;
	else
		cout << "���������� ����������� �����" << endl;
	system("PAUSE");

	system("cls");
	if (test.reserveSeats())
		cout << "�� ��������������� �����" << endl;
	else 
		cout << "���������� ��������������� �����" << endl;
	test.printCarInfo();
	system("PAUSE");


	system("cls");
	if (test.unreserveSeats())
		cout << "�� �������� �������������� ����" << endl;
	else
		cout << "�������������� ���� �� ��������" << endl;
	test.printCarInfo();
	system("PAUSE");

	system("cls");
	test.removePassengerByName("����������� �������� ����������");
	cout << "��� ����� ���� ��������" << endl;
	if (test.sellTickets())
		cout << "�� ������ ��������� �����" << endl;
	else
		cout << "������� �� �������" << endl;
	test.printCarInfo();
	system("PAUSE");

	system("cls");
	test.printTickets();
	cout << endl << "�������� ����� �������: " << test.totalCost() << endl;
	system("PAUSE");

	system("cls");
	if (test.cancelSellTicket())
		cout << "�� �������� �������" << endl;
	else
		cout << "������� �� ��������" << endl;
	test.printCarInfo();
	system("PAUSE");

	system("cls");
	test.cancelOrder();
	test.printTickets();
	system("PAUSE");


}