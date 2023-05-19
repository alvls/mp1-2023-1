#pragma once

#include <string>
#include <memory>
#include <vector>

#include "GameScreen.h"
#include "GameObject.h"



class Game
{
private:
	GameScreen* screen;
	std::vector<std::unique_ptr<GameObject>> game_objects;

public:
	bool is_running;
	bool is_win;
	int score;
	int win_score;

	Rect field;
	Point food;

	Game(GameScreen* screen, Rect field, int win_score);

	void start();
	void stop();

	void on_stop();

	void repaint();
	GameScreen* get_screen();

	void drop_food();
};