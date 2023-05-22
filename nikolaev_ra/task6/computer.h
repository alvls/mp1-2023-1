#pragma once
#pragma once

#include "game.h"

#include <cstdlib>
#include <cmath>
#include <vector>

class Computer {
private:
    static int hasValue(std::vector<int> items, int item);
    static int formValueFromVector(std::vector<int> items, int length);

    Game* game;

public:
    explicit Computer(Game* _game);
    int getRandomNumber();
    std::pair<int, int> getBullsAndCows(int guess);
};