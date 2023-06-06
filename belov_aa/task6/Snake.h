#pragma once

#include "GameObject.h"

#include <vector>
#include <Windows.h>

class Snake : public GameObject
{
private:
	GameScreen::Key direction = GameScreen::Key::Left;

	std::vector<Point> body;
	bool dead = false;

	bool is_vertical(GameScreen::Key direction)
	{
		return (direction == GameScreen::Key::Up || direction == GameScreen::Key::Down);
	}
	bool is_vertical()
	{
		return is_vertical(direction);
	}

	int get_delta()
	{
		return (direction == GameScreen::Key::Up || direction == GameScreen::Key::Left)
			? -1 : 1;
	}

	bool check_self_collision()
	{
		auto& head = body[0];

		for (int i = 1; i < body.size(); i++)
		{
			if (head == body[i])
			{
				return true;
			}
		}

		return false;
	}

	void grow()
	{
		Point& p = body[body.size() - 1];
		bool vertical = is_vertical();
		int delta = -get_delta();
		body.push_back({
			p.x + (vertical ? 0 : delta),
			p.y + (vertical ? delta : 0)
			});
	}

public:
	Snake(Game& game)
		: GameObject(game)
	{
		body.push_back({
	  game.field.left + (rand() % (game.field.right - game.field.left - 1 - game.score)) + 1,
	  game.field.top + (rand() % (game.field.bottom - game.field.top - 1)) + 1
			});

		for (int i = 0; i < game.score - 1; i++)
		{
			grow();
		}
	}

	void update() override
	{
		auto key = game.get_screen()->get_pressed_key();
		if (key != GameScreen::Key::Unknown && (
			key == GameScreen::Key::Up
			|| key == GameScreen::Key::Right
			|| key == GameScreen::Key::Down
			|| key == GameScreen::Key::Left)
			&& is_vertical(key) != is_vertical())
		{
			direction = key;
		}

		bool vertical = is_vertical();
		int delta = get_delta();
		int dx = vertical ? 0 : delta, dy = vertical ? delta : 0;

		body.insert(body.begin(), {
			body[0].x + dx,
			body[0].y + dy
			});
		body.pop_back();

		if (body[0] == game.food)
		{
			game.score++;
			game.drop_food();
			grow();
			Beep(750, 100);

			if (game.score == game.win_score)
			{
				game.is_win = true;
				game.stop();
			}

		}

		auto& head = body[0];
		if (head.x == game.field.left
			|| head.x == game.field.right
			|| head.y == game.field.top
			|| head.y == game.field.bottom
			|| check_self_collision())
		{
			dead = true;
			game.is_win = false;
			game.stop();
			Beep(600, 100);
		}
	}

	void draw() override
	{
		bool vertical = is_vertical();

		game.get_screen()->set_pixel_foreground(GameScreen::GREEN);
		for (int i = 1; i < body.size(); i++)
		{
			game.get_screen()->set_pixel(body[i].x, body[i].y, 'o');
		}

		if (dead)
		{
			game.get_screen()->set_pixel_background(GameScreen::RED);
		}
		game.get_screen()->set_pixel_foreground(GameScreen::LIGHTGREEN);
		game.get_screen()->set_pixel(body[0].x, body[0].y, '8');

		game.get_screen()->set_pixel_background(GameScreen::BLACK);
		game.get_screen()->set_pixel_foreground(GameScreen::LIGHTGRAY);
	}
};