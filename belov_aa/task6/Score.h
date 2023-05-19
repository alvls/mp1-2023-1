#pragma once

#include "GameObject.h"
#include <string>

class Score : public GameObject
{
public:
    Score(Game& game)
        : GameObject(game)
    {}

    void update() override {}
    void draw() override
    {
        auto str = "Length: " + std::to_string(game.score);

        auto* screen = game.get_screen();
        screen->set_pixel_foreground(GameScreen::YELLOW);
        screen->write(
            (game.field.left + game.field.right - str.length()) / 2,
            game.field.top - 2,
            str);
        screen->set_pixel_foreground(GameScreen::LIGHTGRAY);
    }
};