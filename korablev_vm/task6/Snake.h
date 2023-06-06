#include "Header.h"
class Snake
{
private:
	COORD last_pos;
	vector<COORD> snake;
	Field* field;
	void show_body()
	{
		textcolor(LIGHTBLUE);
		for (const auto& tmp : snake)
		{
			gotoxy(tmp);
			cout << 'o';
		}
		textcolor(WHITE);
	}
	void show_head()
	{
		gotoxy(snake[0]);
		textcolor(BLUE);
		cout << '0';
		textcolor(WHITE);
	}
public:
	Snake(Field* fld) : field(fld)
	{
		for (int i = 0; i < INITIALSIZE; i++)
		{
			COORD tmppos = { short(field->return_width() / 2 + i), short(field->return_height() / 2) };
			snake.push_back(tmppos);
		}
		last_pos = snake[snake.size() - 1];
	}
	void change_pos(int x, int y)
	{
		last_pos = snake[snake.size() - 1];
		COORD tmp_coord = { short(snake[0].X + x), short(snake[0].Y + y) };
		snake.insert(snake.cbegin(), tmp_coord);
		snake.pop_back();
	}
	void move(int dir)
	{
		switch (dir)
		{
		case UP:
			change_pos(0, -1);
			break;
		case DOWN:
			change_pos(0, 1);
			break;
		case LEFT:
			change_pos(-1, 0);
			break;
		case RIGHT:
			change_pos(1, 0);
			break;
		}
	}
	bool collision_with_yourself()
	{
		COORD head = snake[0];
		for (size_t i = 1; i < snake.size(); i++)
			if (head.X == snake[i].X && head.Y == snake[i].Y)
				return true;
		return false;
	}
	void show_snake() { show_body(); show_head(); }
	void add_last_pos() { snake.push_back(last_pos); }
	size_t return_size() { return snake.size(); }
	COORD return_head() { return snake[0]; }
	Field* return_field() { return field; }
	vector<COORD> return_snake() { return snake; }
};
