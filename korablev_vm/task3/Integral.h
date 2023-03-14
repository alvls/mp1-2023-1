#include "Header.h"

class Integral
{
private:
	double lim[2]; //левый и правый предел интегировани€
	int seg; //количество отрезков
	double answ;//итоговый ответ
	en_side mtd;//средние, правые или левые пр€моугольники
	Fx func;//функци€ из cmath + y=x дл€ удобства
	void find_answ()
	{
		int i=0;
		double x = lim[0], slag, n = (lim[1] - lim[0]) / seg;
		answ = 0;
		switch (mtd)
		{
		case _right:
			x += n;
			break;
		case _left:
			break;
		case _mid:
			for (i=0; i < seg; i++)
			{
				slag = func(x + (i + 0.5) * n);
				answ += slag;
			}
			answ *= n;
			return;
		}
		for (i=0; i < seg; i++)
		{
			slag = func(x + i * n);
			answ += slag;
		}
		answ *= n;
		return;
	}
public:
	Integral()
	{
		lim[0] = 0;
		lim[1] = 1;
		func = line;
		answ = 1;
		seg = 1;
		mtd = _left;
	}
	void set_lim(double l, double r)
	{
		lim[0] = l;
		lim[1] = r;
	}
	void set_seg(int seg)
	{
		this->seg = seg;
	}
	void set_func(Fx func)
	{
		this->func=func;
	}
	void set_mtd(en_side mtd)
	{
		this->mtd = mtd;
	}
	double* return_lim()
	{
		find_answ();
		return lim;
	}
	double return_answ()
	{
		find_answ();
		return answ;
	}
};