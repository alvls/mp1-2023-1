#pragma once
#include "ProcessingCenter.h"
#define PrCenSize 6
#define StrSize 4
#define MaxGetSum 200000
#define BNCount 40
#define MaxCassette 2000
class CashMachine
{
	ProcessingCenter ClientBase;
	vector <int> ATM = { 1600,1600,1600,1600,1600,1600 };
public:
	CashMachine();
	void CreateClientBase(ProcessingCenter tmp);
	int FindByCard(string card);
	bool CheckPIN(string p, int ind);
	Client& InfAboutClient(int ind);
	bool CashOut(int ind, int sum);
	bool CashIn(int ind, int sum);
	~CashMachine();
};