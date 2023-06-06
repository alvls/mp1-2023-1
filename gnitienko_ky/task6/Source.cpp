#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Score {
private:
    int bulls;
    int cows;
public:
    Score() : bulls(0), cows(0) {}
    int GetBulls() {
        return bulls;
    }
    int GetCows() {
        return cows;
    }
    void PlusBulls() {
        bulls++;
    }
    void PlusCows() {
        cows++;
    }
};

class Player {
public:
    virtual vector<int> makeGuess(int length) = 0;
};

class HumanPlayer : public Player {
public:
    vector<int> makeGuess(int length) override {
        vector<int> guess;
        cout << "Enter your guess: ";
        int num;
        cin >> num;
        while (num > 0 && guess.size() < length) {
            guess.insert(guess.begin(), num % 10);
            num /= 10;
        }
        while (guess.size() < length) {
            guess.insert(guess.begin(), 0);
        }
        return guess;
    }
};

class ComputerPlayer : public Player {
public:
    vector<int> makeGuess(int length) override {
        vector<int> guess = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        random_device rd;
        mt19937 g(rd());
        shuffle(guess.begin(), guess.end(), g);
        return guess;
    }
};

class Game {
private:
    Player& player1;
    Player& player2;

    vector<int> generateSecretNumber(int length) {
        vector<int> digits = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        random_device rd;
        mt19937 g(rd());
        shuffle(digits.begin(), digits.end(), g);
        return vector<int>(digits.begin(), digits.begin() + length);
    }

    Score checkGuess(vector<int>& guess, vector<int>& secretNumber, int length) {
        Score score;

        for (int i = 0; i < length; ++i) {
            if (guess[i] == secretNumber[i]) {
                score.PlusBulls();
            }
            else if (find(secretNumber.begin(), secretNumber.end(), guess[i]) != secretNumber.end()) {
                score.PlusCows();
            }
        }

        return score;
    }

public:
    Game(Player& player1, Player& player2) : player1(player1), player2(player2) {}

    void play() {
        int length;
        cout << "Enter the length of the number to be guessed: ";
        cin >> length;

        vector<int> secretNumber = generateSecretNumber(length);
        /*for (int i = 0; i < length; i++)
            cout << secretNumber[i];*/
        bool gameOver = false;
        int turn = 0;

        while (!gameOver) {
            system("cls");
            vector<int> guess;
            if (turn % 2 == 0) {
                guess = player1.makeGuess(length);
                cout << "User's score " << endl;
            }
            else {
                guess = player2.makeGuess(length);
                cout << "Computer's score " << endl;
            }

            Score score = checkGuess(guess, secretNumber, length);
            cout << "Bulls: " << score.GetBulls() << ", Cows: " << score.GetCows() << endl << endl;

            if (score.GetBulls() == length) {
                gameOver = true;
                cout << "Game over! Player " << (turn % 2) + 1 << " wins!" << endl;
                cout << "           _     _" << endl;
                cout << "          ||____||" << endl;
                cout << "          | o  o |" << endl;
                cout << "          |_____ |              *" << endl;
                cout << "moooooo   |*  *| |             ||" << endl;
                cout << "           ---- --------------- |" << endl;
                cout << "           |                   |" << endl;
                cout << "           | ________________  |" << endl;
                cout << "           | | |_|      |_|  | |" << endl;
                cout << "           |_|               |_|" << endl;
            }
            system("pause");
            turn++;
        }
    }

};

int main() {
    HumanPlayer humanPlayer;
    ComputerPlayer computerPlayer;
    Game game(humanPlayer, computerPlayer);
    game.play();
    return 0;
}