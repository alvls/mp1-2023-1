#pragma once

class Game;
#include "Game.h"

class GameObject
{
protected:
	Game& game;

public:
	GameObject(Game& game)
		: game(game)
	{}

	virtual void update() = 0;
	virtual void draw() = 0;

	virtual ~GameObject() {};
};