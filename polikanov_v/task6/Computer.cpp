#include "Computer.h"

Computer::Computer(GameProcess* game) {
    this->game = game;
}

void Computer::guessRandomNumber() {
    int length = game->getN();
    std::vector<int> digs;
    for (int i = 0; i < length; i++) {
        while (true) {
            int dig = rand() % 10;
            if (!(i == 0 && dig == 0)) {
                bool cond = false;
                for (int i : digs) {
                    if (i == dig) {
                        cond = true;
                    }
                }
                if (cond == false) {
                    digs.push_back(dig);
                    break;
                }
            }

        }

    }
    int result = 0;
    for (int i : digs) {
        result += i * pow(10, --length);
    }
    game->setGuessedValue(result);
}

std::pair<int, int> Computer::IdentifyBullsAndCows(int guess) {

    std::string strGuess = std::to_string(guess);
    int bulls = 0, cows = 0;

    std::string strGameVal = std::to_string(game->getGuessedValue());
    for (int i = 0; i < game->getN(); i++) {
        if (strGameVal[i] == strGuess[i]) {
            bulls++;
        }
        else {
            for (char j : strGameVal) {
                if (strGuess[i] == j) {
                    cows++;
                    break;
                }
            }
        }
    }
    return std::make_pair(bulls, cows);


}