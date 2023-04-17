#include "CashMachine.h"
CashMachine::CashMachine() {}
void CashMachine::CreateClientBase(ProcessingCenter tmp)
{
	for (int i = 0;i < PrCenSize;i++)
		ClientBase.AddClient(tmp[i]);
}
int CashMachine::FindByCard(string card)
{
	if (card.length() != 4)
		throw (1);
	if ((card < "0001") || (card > "9999"))
		throw (1);
	for (int i = 0;i < PrCenSize;i++)
		if (ClientBase[i].GetCardNumber() == card)
			return i;
	throw (2);
}
bool CashMachine::CheckPIN(string p, int ind)
{
	if (ClientBase[ind].GetPIN() == p)
		return true;
	return false;
}
Client& CashMachine::InfAboutClient(int ind) { return ClientBase[ind]; }
bool CashMachine::CashOut(int ind, int sum)
{
	int tmp;
	int ss = sum;
	int c = 0;
	if ((sum >= 5000) && (ATM[5] != 0))
	{
		tmp = min(sum / 5000, ATM[5]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 5000;
			c += tmp;
			ATM[5] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 5000;
			c = BNCount;
			ATM[5] -= BNCount - c;
		}
	}
	if ((sum >= 2000) && (ATM[4] != 0) && (c < BNCount))
	{
		tmp = min(sum / 2000, ATM[4]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 2000;
			c += tmp;
			ATM[4] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 2000;
			c = BNCount;
			ATM[4] -= BNCount - c;
		}
	}
	if ((sum >= 1000) && (ATM[3] != 0) && (c < BNCount))
	{
		tmp = min(sum / 1000, ATM[3]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 1000;
			c += tmp;
			ATM[3] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 1000;
			c = BNCount;
			ATM[3] -= BNCount - c;
		}
	}
	if ((sum >= 500) && (ATM[2] != 0) && (c < BNCount))
	{
		tmp = min(sum / 500, ATM[2]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 500;
			c += tmp;
			ATM[2] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 500;
			c = BNCount;
			ATM[2] -= BNCount - c;
		}
	}
	if ((sum >= 200) && (ATM[1] != 0) && (c < BNCount))
	{
		tmp = min(sum / 200, ATM[1]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 200;
			c += tmp;
			ATM[1] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 200;
			c = BNCount;
			ATM[1] -= BNCount - c;
		}
	}
	if ((sum >= 100) && (ATM[0] != 0) && (c < BNCount))
	{
		tmp = min(sum / 100, ATM[0]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 100;
			c += tmp;
			ATM[0] -= tmp;
		}
		else
		{
			sum -= (BNCount - c) * 100;
			c = BNCount;
			ATM[0] -= BNCount - c;
		}
	}
	if (sum == 0)
	{
		ClientBase[ind].ChangeBalance(ss, 0);
		return true;
	}
	return false;
}
bool CashMachine::CashIn(int ind, int sum)
{
	int tmp;
	int ss = sum;
	int c = 0;
	if ((sum >= 5000) && (ATM[5] != MaxCassette))
	{
		tmp = min(sum / 5000, MaxCassette - ATM[5]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 5000;
			c += tmp;
			ATM[5] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 5000;
			c = BNCount;
			ATM[5] += BNCount - c;
		}
	}
	if ((sum >= 2000) && (ATM[4] != MaxCassette) && (c < BNCount))
	{
		tmp = min(sum / 2000, MaxCassette - ATM[4]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 2000;
			c += tmp;
			ATM[4] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 2000;
			c = BNCount;
			ATM[4] += BNCount - c;
		}
	}
	if ((sum >= 1000) && (ATM[3] != MaxCassette) && (c < BNCount))
	{
		tmp = min(sum / 1000, MaxCassette - ATM[3]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 1000;
			c += tmp;
			ATM[3] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 1000;
			c = BNCount;
			ATM[3] += BNCount - c;
		}
	}
	if ((sum >= 500) && (ATM[2] != MaxCassette) && (c < BNCount))
	{
		tmp = min(sum / 500, MaxCassette - ATM[2]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 500;
			c += tmp;
			ATM[2] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 500;
			c = BNCount;
			ATM[2] += BNCount - c;
		}
	}
	if ((sum >= 200) && (ATM[1] != MaxCassette) && (c < BNCount))
	{
		tmp = min(sum / 200, MaxCassette - ATM[1]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 200;
			c += tmp;
			ATM[1] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 200;
			c = BNCount;
			ATM[1] += BNCount - c;
		}
	}
	if ((sum >= 100) && (ATM[0] != MaxCassette) && (c < BNCount))
	{
		tmp = min(sum / 100, MaxCassette - ATM[0]);
		if (c + tmp <= BNCount)
		{
			sum -= tmp * 100;
			c += tmp;
			ATM[0] += tmp;
		}
		else
		{
			sum -= (BNCount - c) * 100;
			c = BNCount;
			ATM[0] += BNCount - c;
		}
	}
	if (sum == 0)
	{
		ClientBase[ind].ChangeBalance(ss, 1);
		return true;
	}
	return false;
}
CashMachine::~CashMachine() {}