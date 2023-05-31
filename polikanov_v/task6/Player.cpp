#include "Player.h"

Player::Player(GameProcess* game) {
    this->game = game;
}

bool Player::chooseN(int n) {
    if (n < MIN_N || n > MAX_N) return false;
    game->setN(n);
    return true;
}