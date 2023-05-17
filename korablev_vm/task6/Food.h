#include "Header.h"
class Food
{
private:
	COORD food_coord;
	Snake* snake;
	bool unique_food()
	{
		vector<COORD> SnakeCopy = snake->return_snake();
		for (const auto& tmp : SnakeCopy)
			if (food_coord.X == tmp.X && food_coord.Y == tmp.Y)
				return false;
		return true;
	}
public:
	Food(Snake* _snake) : snake(_snake) { srand(int(time(NULL))); spawn_food(); }
	void food_update(Snake* _snake) { snake = _snake; }
	void spawn_food()
	{
		int width = snake->return_field()->return_width();
		int height = snake->return_field()->return_height();
		do
		{
			food_coord = { short(rand() % width+1), short(rand() % height + 1)};
		} while (!unique_food());
	}
	void show_food()
	{
		gotoxy(food_coord);
		textcolor(GREEN);
		cout << '$';
		textcolor(WHITE);
	}
	COORD return_food_coord() { return food_coord; }
};





