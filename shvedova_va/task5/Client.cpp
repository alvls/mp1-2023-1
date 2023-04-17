#include "Client.h"
Client::Client()
{
	Client::CardNumber = "1111";
	Client::FIO = "fio";
	Client::balance = 0;
	Client::PIN = "0000";
	Client::status = 1;
}
Client::Client(const string number, const string fio, size_t b, const string pin, bool s)
{
	Client::CardNumber = number;
	Client::FIO = fio;
	Client::balance = b;
	Client::PIN = pin;
	Client::status = s;
}
Client::Client(const Client& c) = default;
const string Client::GetCardNumber()
{
	return CardNumber;
}
const string Client::GetFIO()
{
	return FIO;
}
size_t Client::GetBalance()
{
	return balance;
}
const string Client::GetPIN()
{
	return PIN;
}
bool Client::GetStatus()
{
	return status;
}
void Client::ChangeBalance(int nb, int side)
{
	if (side == 1)
		Client::balance += nb;
	else
		Client::balance -= nb;
}
void Client::ChangeStatus(bool ns)
{
	Client::status = ns;
}