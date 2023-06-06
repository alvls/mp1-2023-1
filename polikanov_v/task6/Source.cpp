#include <cstdlib>
#include <iostream>

#include "GameProcess.h"
#include "Player.h"
#include "Computer.h"

void cinCleaner() {

    int i;
    do {
        i = getchar();
    } while (i != EOF && i != '\n');
}

void mainMenu() {
    while (true) {
        std::cout << " What would you like to do?\n" << std::endl;
        std::cout << " 1) Play the game" << std::endl;
        std::cout << " 2) Exit the program" << std::endl;

        char whatToDo = '0';

        while ((whatToDo != '1') && (whatToDo != '2')) {
            std::cout << "\n Enter the action (1-2): ";
            std::cin >> whatToDo;
            cinCleaner();

            if (whatToDo == '1') {
                char cont = '0';
                do {
                    GameProcess game;
                    Player player(&game);
                    Computer computer(&game);
                    system("cls");
                    int n;
                    do {
                        std::cout << " Enter n: ";
                        std::cin >> n;
                        cinCleaner();
                        if (!player.chooseN(n)) std::cout << " Check the entered n value and try again!\n" << std::endl;
                    } while (!player.chooseN(n));

                    computer.guessRandomNumber();
                    system("cls");
                    int guess = -1;
                    while (true) {
                        std::cout << " Enter the guess: ";
                        std::cin >> guess;
                        cinCleaner();

                        std::string strGuess = std::to_string(guess);
                        while (strGuess.length() != game.getN() || (strGuess[0] == '0' && strGuess.length() != 1) ||
                            strGuess.length() != std::set<char>(strGuess.begin(), strGuess.end()).size()) {
                            std::cout << " Check the entered value and try again!\n" << std::endl;
                            std::cout << " Enter the guess: ";
                            std::cin >> guess;
                            strGuess = std::to_string(guess);
                            cinCleaner();
                        }

                        if (game.getGuessedValue() == guess) {
                            std::cout << "\n You win!\nCongratulations!" << std::endl;
                            break;
                        }
                        else {
                            std::pair<int, int> bullsAndCows = computer.IdentifyBullsAndCows(guess);
                            std::cout << " Number of bulls: " << bullsAndCows.first << std::endl;
                            std::cout << " Number of cows: " << bullsAndCows.second << std::endl;
                            std::cout << " \n";
                        }
                    }
                    std::cout << "\n\n Maybe we'll play again?" << std::endl;
                    std::cout << " Enter 'y' if yes, and any other character otherwise to return to the menu: ";
                    std::cin >> cont;
                    cinCleaner();
                } while (cont == 'y');
            }
            else if (whatToDo == '2') {
                system("pause");
                exit(0);
            }
            else {
                std::cout << "\n Check the entered data and try again!" << std::endl;
            }
        }
        system("cls");
    }
}

int main() {
    srand(time(0));
    std::cout << "\n Welcome to the \"Bulls and Cows\" game!\n" << std::endl;
    std::cout << " This game is about guessing the numbers that the computer guesses." << std::endl;
    std::cout << " If you guessed the number up to the position, you have found a \"bull\"." << std::endl;
    std::cout << " If you guessed the number that is in the number, you have found a \"cow\"." << std::endl;

    mainMenu();

    return 0;
}