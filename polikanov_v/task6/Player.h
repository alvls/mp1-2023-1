#pragma once
#include "GameProcess.h"

class Player {
private:
    GameProcess* game;

public:
    Player(GameProcess* game);

    bool chooseN(int n);
};