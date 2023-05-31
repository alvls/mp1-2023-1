#pragma once
#include "GameProcess.h"

class Computer {
private:
    GameProcess* game;

public:
    Computer(GameProcess* game);

    void guessRandomNumber();
    std::pair<int, int> IdentifyBullsAndCows(int guess);
};