#pragma once

#include "GameObject.h"

class Border : public GameObject
{
public:
	Border(Game& game) 
		: GameObject(game)
	{}

	void update() override {}

	void draw() override 
	{
        auto* screen = game.get_screen();

        screen->set_pixel_background(GameScreen::WHITE);
        for (int x = game.field.left; x <= game.field.right; x++)
        {
            screen->set_pixel(x, game.field.top, ' ');
            screen->set_pixel(x, game.field.bottom, ' ');
        }
		for (int y = game.field.top; y <= game.field.bottom; y++)
		{
			screen->set_pixel(game.field.left, y, ' ');
			screen->set_pixel(game.field.left - 1, y, ' ');
			screen->set_pixel(game.field.right, y, ' ');
			screen->set_pixel(game.field.right + 1, y, ' ');
		}
        screen->set_pixel_background(GameScreen::BLACK);
    }

};