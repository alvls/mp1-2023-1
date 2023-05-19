#include <algorithm>
#include <ctime>
#include <Windows.h>

#include "Game.h"
#include "Border.h"
#include "Score.h"
#include "Snake.h"
#include "Food.h"

Game::Game(GameScreen* screen, Rect field, int win_score)
	: screen(screen)
	, field(field)
	, is_running(false)
	, score(5)
	, is_win(false)
	, win_score(win_score)
{
	srand(time(nullptr));

	drop_food();

	game_objects.push_back(std::unique_ptr<GameObject>(new Border(*this)));
	game_objects.push_back(std::unique_ptr<GameObject>(new Score(*this)));
	game_objects.push_back(std::unique_ptr<GameObject>(new Snake(*this)));
	game_objects.push_back(std::unique_ptr<GameObject>(new Food(*this)));
}

void Game::start()
{
	is_running = true;

	while (is_running)
	{
		for (auto& obj : game_objects)
		{
			obj->update();
		}

		repaint();
		Sleep(100);
	}

	on_stop();
}

void Game::stop()
{
	is_running = false;
}

void Game::on_stop()
{
	game_objects.clear();

	//screen->clear();
	std::string str = is_win ? "You have won!" : "You lose :(";
	screen->set_pixel_foreground(GameScreen::LIGHTMAGENTA);
	screen->write(
		(field.left + field.right - str.length()) / 2,
		field.bottom + 2,
		str);
	screen->flush();
}

void Game::repaint()
{
	screen->clear();
	for (auto& obj : game_objects)
	{
		obj->draw();
	}
	screen->flush();
}

GameScreen* Game::get_screen()
{
	return screen;
}

void Game::drop_food()
{
	food.x = field.left + (rand() % (field.right - field.left - 1)) + 1;
	food.y = field.top + (rand() % (field.bottom - field.top - 1)) + 1;
}