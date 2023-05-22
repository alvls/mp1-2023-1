#include "computer.h"

int Computer::hasValue(std::vector<int> items, int val) {
    for (int item : items) {
        if (item == val) { return true; }
    }
    return false;
}

int Computer::formValueFromVector(std::vector<int> items, int length) {
    int result = 0;
    for (int item : items) {
        result += item * pow(10, --length);
    }
    return result;
}

Computer::Computer(Game* _game) : game(_game) {}

int Computer::getRandomNumber() {
    std::vector<int> digits;
    for (int i = 0; i < game->get_n(); i++) {
        while (true) {
            int digit = rand() % 10;
            if (!((i == 0 && digit == 0) || Computer::hasValue(digits, digit))) {
               digits.push_back(digit);
               break;
            }
        }
    }
    return formValueFromVector(digits, game->get_n());
}

std::pair<int, int> Computer::getBullsAndCows(int guess) {
    int bulls = 0;
    int cows = 0;
    if (game->isValidValue(guess)) {
        std::string strVal = std::to_string(game->getValue());
        std::string strGuess = std::to_string(guess);

        for (int i = 0; i < game->get_n(); i++) {
            if (strVal[i] == strGuess[i]) { bulls++; }
            // cows searching
            else {
                for (char item : strVal) {
                    if (strGuess[i] == item) {
                        cows++;
                        break;
                    }
                }
            }
        }
    }
    return std::make_pair(bulls, cows);
}





