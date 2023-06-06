#include "player.h"
#include "game.h"

Player::Player(Game* _game)  : game(_game) {}

void Player::choose_n(int n) {
    if (Game::isValid_n(n)) { game->set_n(n); }
}

