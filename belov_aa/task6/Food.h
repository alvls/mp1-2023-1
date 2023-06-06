#pragma once

#include "GameObject.h"

class Food : public GameObject
{
public:
	Food(Game& game)
		: GameObject(game)
	{}

	void update() override {}

	void draw() override
	{
		auto* screen = game.get_screen();

		screen->set_pixel_foreground(GameScreen::CYAN);

		screen->set_pixel(game.food.x, game.food.y, '*');

		screen->set_pixel_foreground(GameScreen::LIGHTGRAY);

	}
};