#include "Header.h"

class Integral
{
private:
	double lim[2]; //левый и правый предел интегирования
	int seg; //количество отрезков
	double answ;//итоговый ответ
	en_side mtd;//средние, правые или левые прямоугольники
	Fx func;//функция из cmath + y=x для удобства
	void find_answ()
	{
		int i;
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
			//реализация
			return;
		default:
			cout << "Возникла непредвиденная ошибка" << endl;
			system("pause");
		}
		for (i = 0; i < n; i++)
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
	void set_lim(double r, double l)
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