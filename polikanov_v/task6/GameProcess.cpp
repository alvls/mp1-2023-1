#include "GameProcess.h"

int GameProcess::getN() {
    return n;
}

void GameProcess::setN(int n) {
    this->n = n;
}

int GameProcess::getGuessedValue() {
    return guessedValue;
}

void GameProcess::setGuessedValue(int guessedValue) {
    this->guessedValue = guessedValue;
}