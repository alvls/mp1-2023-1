#include "Header.h"
class Game
{
private:
	Field field;
	Snake snake;
	Food food;
	int dir;
	int win_size;
	int score;
	int speed;
	void show_all()
	{
		field.show_field();
		food.show_food();
		snake.show_snake();
		show_info();
	}
	void hide_all() { std::system("cls"); }
	void show_info()
	{
		COORD pos = { 1, short(field.return_height() + 3) };
		gotoxy(pos);
		cout << endl << "Счет: " << score << "/" << win_size-INITIALSIZE << endl;
	}
	int return_end_status()
	{
		COORD head = snake.return_head();
		if (head.X == 0 || head.X == field.return_width() + 1 || head.Y == 0 || head.Y == field.return_height() + 1)
			return LOSE;
		if (snake.collision_with_yourself())
			return LOSE;
		if (head.X == food.return_food_coord().X && head.Y == food.return_food_coord().Y)
		{
			snake.add_last_pos();
			score++;
			if (snake.return_size() == win_size)
				return WIN;
			food.spawn_food();
		}
		return PLAY;
	}
	void get_actions()
	{
		if (_kbhit())
		{
			char c;
			do
			{
				switch (c = _getch())
				{
				case -32:
					break;
				case UPKEY:
					if (dir != DOWN)
						dir = UP;
					break;
				case DOWNKEY:
					if (dir != UP)
						dir = DOWN;
					break;
				case LEFTKEY:
					if (dir != RIGHT)
						dir = LEFT;
					break;
				case RIGHTKEY:
					if (dir != LEFT)
						dir = RIGHT;
					break;
				}
			} while (c == -32);
		}
		snake.move(dir);
	}
	void end_game(int status)
	{
		if (status == ST_LOSE)
		{
			gotoxy(snake.return_head());
			textcolor(LIGHTRED);
			cout << 'X';
			textcolor(WHITE);
			COORD end = { 0, short(field.return_height() + 4) };
			gotoxy(end);
			cout << "Неудача. Получится в следующий раз!\n\n";
		}
		if (status == ST_WIN)
		{
			hide_all();
			show_all();
			cout << endl << "Победа!" << endl;
		}
	}
public:
	Game(int _win, int _w, int _h, int _sp=200) : speed(_sp), field(_w, _h), snake(&field), food(&snake)
	{
		dir = LEFT;
		win_size = _win;
		score = 0;
	}
	void start_game()
	{
		int status = PLAY;
		field.draw_field();
		hide_all();
		show_all();
		Sleep(speed);
		while (true)
		{
			get_actions();
			status = return_end_status();
			if (status != PLAY)
				break;
			hide_all();
			show_all();
			Sleep(speed);
		}
		end_game(status);
	}
};
