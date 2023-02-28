#include <iostream>
#include <locale>
using namespace std;
class Time
{
private:
	int hours, minutes, seconds; 
public:
	Time()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	void SetTime()
	{
		int h, m, s;
		cout << "���� 0 - 23 (��� �������������� �����): ";
		cin >> h;
		if ((h >= 0) && (h < 24))
			hours = h;
		cout << "������ 0 - 59 (��� �������������� �����): ";
		cin >> m;
		if ((m >= 0) && (m < 60))
			minutes = m;
		cout << "������� 0 - 59 (��� �������������� �����): ";
		cin >> s;
		if ((s >= 0) && (s < 60))
			seconds = s;
	}
	void ToRightTime(int sec)
	{
		hours = sec / 3600;
		minutes = (sec - hours * 3600) / 60;
		seconds = sec - hours * 3600 - minutes * 60;
	}
	void PrintTime()
	{
		cout << hours << ":" << minutes / 10 << minutes % 10 << ":" << seconds / 10 << seconds % 10 << "\n";
	}
	void ChangeTime(int side, Time t)
	{
		int NewTime;
		if (side == 0)//����� � ������� �������
		{
			NewTime = (hours * 3600 + minutes * 60 + seconds) - (t.hours * 3600 + t.minutes * 60 + t.seconds);
			if (NewTime < 0)
				NewTime += 24 * 3600;
		}
		else//����� � ������� �������
		{
			NewTime = (hours * 3600 + minutes * 60 + seconds) + (t.hours * 3600 + t.minutes * 60 + t.seconds);
			if (NewTime > 86400)
				NewTime -= 24 * 3600;
		}
		ToRightTime(NewTime);
		cout << "����� ������� ��������\n����� ����� - ";
		PrintTime();
	}
	void TimeDiff(Time t)
	{
		int diff;
		diff = (hours * 3600 + minutes * 60 + seconds) - (t.hours * 3600 + t.minutes * 60 + t.seconds);
		//if (diff < 0)
			//diff += 24 * 3600;//���� ������� ����� �������� �������� � ������������� �������������, �� ���������� ������� �� ��������� �����
		ToRightTime(abs(diff));//���������� �������� ������� �� �������
		cout << "������� �� ������� - ";
		PrintTime();
	}
};
Time tSet;
void Operations()
{
	Time tOperation;
	int operation;
	int h1, m1, s1, dif, side;
	cout << "�������� ��������:\n1) ������ �����\n2) ��������� �������\n3) �������� �����\n4) ���������\n";
	cin >> operation;
	system("cls");
	switch (operation)
	{
	case 1:
		cout << "������� ����� - ";
		tSet.PrintTime();
		Operations();
		break;
	case 2:
		cout << "������� ����� ������ �������:\n";
		tOperation.SetTime();
		system("cls");
		tOperation.TimeDiff(tSet);
		Operations();
		break;
	case 3:
		cout << "������� ��������:\n";
		tOperation.SetTime();
		system("cls");
		cout << "0 - �������� ������� � ������� �������\n1 - �������� ������� � ������� �������\n";
		cin >> side;
		system("cls");
		tSet.ChangeTime(side, tOperation);
		Operations();
		break;
	case 4:
		break;
	default:
		Operations();
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	cout << "���������� �����:\n";
	tSet.SetTime();
	system("cls");
	Operations();
	system("pause");
	return 0;
}