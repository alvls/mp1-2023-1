#pragma once
#include <string>
using namespace std;
class Client
{
	string CardNumber;
	string FIO;
	size_t balance;
	string PIN;
	bool status = 1;
public:
	Client();
	Client(const string cn, const string fio, size_t b, const string p, bool s);
	Client(const Client& c);
	const string GetCardNumber();
	const string GetFIO();
	size_t GetBalance();
	const string GetPIN();
	bool GetStatus();
	void ChangeBalance(int nb, int side);
	void ChangeStatus(bool ns);
};