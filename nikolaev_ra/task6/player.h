#pragma once
#pragma once

#include "game.h"

class Player {
private:
    Game* game;

public:
    explicit Player(Game* _game);
    void choose_n(int n);
};