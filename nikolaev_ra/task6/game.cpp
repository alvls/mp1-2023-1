#include "game.h"

void Game::set_n(int _n) {
    Game::n = _n;
}

int Game::get_n() const {
    return n;
}

bool Game::isValidValue(int val) {
    std::string strVal = std::to_string(val); 
    if (strVal.length() != n) {
        return false;
    } else if ((strVal[0] == '0' && strVal.length() != 1) ||
                                strVal.length() != std::unordered_set<char>(strVal.begin(), strVal.end()).size()) {
        return false;
    }
    return true;
}

bool Game::isValid_n(int n) {
    return !(n < MIN_N || n > MAX_N);
}

int Game::getValue() const {
    return value;
}

void Game::setValue(int _value) {
    value = _value;
}
