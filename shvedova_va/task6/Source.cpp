#include <iostream>
#include <locale>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <vector>
using namespace std;
enum TColor
{
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
	DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTMAGENTA, YELLOW, WHITE
};
void gotoxy(COORD c)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Console, c);
}
class Field
{
	short heigh;
	short width;
	vector<COORD> field;
public:
	Field(short _width, short _heigh)
	{
		heigh = _heigh;
		width = _width;
		COORD tmp;
		for (int i = 0; i < width + 2;i++)
		{
			tmp.X = i;
			tmp.Y = 0;
			field.push_back(tmp);
			tmp.Y = heigh + 1;
			field.push_back(tmp);
		}
		for (int i = 1;i < heigh + 1;i++)
		{
			tmp.Y = i;
			tmp.X = 0;
			field.push_back(tmp);
			tmp.X = width + 1;
			field.push_back(tmp);
		}
	}
	void ShowField()
	{
		system("cls");
		for (int i = 0;i < field.size();i++)
		{
			gotoxy(field[i]);
			cout << "#";
		}
	}
	short GetH() { return heigh; }
	short GetW() { return width; }
};
class Snake
{
	vector<COORD> snake;
	COORD food;
	COORD EndOfTail;
	COORD ShowInf;
	int l;
public:
	Snake(short w, short h, int _l)
	{
		short xHead = w / 2 + 1;
		short yHead = h / 2 + 1;
		for (int i = 0;i < 5;i++)
		{
			snake.push_back({ xHead, yHead });
			xHead++;
		}
		food.X = 1;
		food.Y = 1;
		EndOfTail.X = snake[4].X;
		EndOfTail.Y = snake[4].Y;
		ShowInf.X = 0;
		ShowInf.Y = h + 2;
		l = _l;
	}
	int GetLen() { return snake.size(); }
	bool FindFood()
	{
		if (snake[0].X == food.X && snake[0].Y == food.Y)
			return true;
		return false;
	}
	void EatFood() { snake.push_back(EndOfTail); }
	bool CheckSmash()
	{
		for (int i = 1;i < snake.size();i++)
			if ((snake[0].X == snake[i].X) && (snake[0].Y == snake[i].Y))
				return false;
		return true;
	}
	bool CheckBorder(short w, short h)
	{
		for (int i = 0;i < snake.size();i++)
			if (snake[0].X == w + 1 || snake[0].Y == 0 || snake[0].Y == h + 1 || snake[0].X == 0)
				return false;
		return true;
	}
	void RandFood(short w, short h)
	{
		bool p = false;
		bool f = true;
		do
		{
			food.X = 1 + rand() % w;
			food.Y = 1 + rand() % h;
			if (food.X != 0 && food.Y != 0 && food.X != w + 1 && food.Y != h + 1)
			{
				for (int i = 0;i < snake.size();i++)
					if (food.X == snake[i].X && food.Y == snake[i].Y)
					{
						f = false;
						break;
					}
				if (f)
					p = true;
			}
		} while (p != true);
	}
	void Move(int way)// 1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
	{
		COORD tmp = snake[0];
		COORD tTmp;
		EndOfTail = snake[snake.size() - 1];
		if (way == 1)
			snake[0].Y--;
		else if (way == 2)
			snake[0].Y++;
		else if (way == 3)
			snake[0].X--;
		else
			snake[0].X++;
		for (int i = 1;i < snake.size();i++)
		{
			tTmp = snake[i];
			snake[i] = tmp;
			tmp = tTmp;
		}
	}
	void ShowSnake()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		gotoxy(snake[0]);
		SetConsoleTextAttribute(hConsole, YELLOW);
		cout << "O";
		SetConsoleTextAttribute(hConsole, LIGHTGREEN);
		for (int i = 1;i < snake.size();i++)
		{
			gotoxy(snake[i]);
			cout << "O";
		}
		SetConsoleTextAttribute(hConsole, BLACK);
	}
	void ShowFood()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		gotoxy(food);
		SetConsoleTextAttribute(hConsole, RED);
		cout << "*";
		SetConsoleTextAttribute(hConsole, BLACK);
	}
	void ShowCurLen()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		gotoxy(ShowInf);
		SetConsoleTextAttribute(hConsole, WHITE);
		cout << "Текущая длина: " << snake.size() << "/" << l;
	}
};
class Game
{
	short heigh;
	short width;
	int MaxLen;
	int speed;
public:
	Game(short w, short h, int l, int s)
	{
		heigh = h;
		width = w;
		MaxLen = l;
		speed = 1000 / s;
	}
	bool play()// 1 - вверх, 2 - вниз, 3 - влево, 4 - вправо
	{
		Field field(width, heigh);
		Snake snake(width, heigh, MaxLen);
		int CurLen = 5;
		int dir = 3;
		int c;
		field.ShowField();
		snake.ShowSnake();
		snake.ShowCurLen();
		snake.RandFood(width, heigh);
		c = _getch();
		while (true)
		{
			if (_kbhit())
			{
				c = _getch();
				switch (c)
				{
				case 72:
					if (dir != 2)
						dir = 1;
					break;
				case 80:
					if (dir != 1)
						dir = 2;
					break;
				case 75:
					if (dir != 4)
						dir = 3;
					break;
				case 77:
					if (dir != 3)
						dir = 4;
					break;
				}
			}
			snake.Move(dir);
			if (snake.CheckBorder(width, heigh) && snake.CheckSmash())
			{
				if (snake.FindFood())
				{
					snake.EatFood();
					CurLen++;
					if (CurLen == MaxLen)
						return true;
					snake.RandFood(width, heigh);
				}
			}
			else
				return false;
			field.ShowField();
			snake.ShowFood();
			snake.ShowSnake();
			snake.ShowCurLen();
			Sleep(speed);
		}
		return true;
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	short w, h;
	int l, s;
	cout << "Введите ширину поля: ";
	cin >> w;
	cout << "Введите высоту поля: ";
	cin >> h;
	cout << "Введите длину Змейки: ";
	cin >> l;
	cout << "Введите скорость (например, от 5 до 10): ";
	cin >> s;
	srand(time(NULL));
	Game game(w, h, l, s);
	if (game.play())
	{
		system("cls");
		cout << "Победа!!!" << endl;
	}
	else
	{
		system("cls");
		cout << "Вы проиграли:(" << endl;
	}
	system("pause");
	return 0;
}