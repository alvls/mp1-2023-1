#include "game.h"
#include "player.h"
#include "computer.h"

#include <iostream>

// procedure for cleaning the input stream
void cleanCin()
{
    int c;
    do
        c = getchar();
    while (c != '\n' && c != EOF);
}

void greeting();
void menu();
void returnToMenu();
void programInfo();
void game();
void programExit();

void greeting() {
    std::cout << "Hello!\nWelcome to the game \"Bulls and Cows\":)\n" << std::endl;
}

void menu()
{

    std::cout << "What do you want to do?\n" << std::endl;
    std::cout << "1 - read the description of the program" << std::endl;
    std::cout << "2 - play the game" << std::endl;
    std::cout << "3 - exit the program" << std::endl;
    char act = '0';

    while ((act != '1') && (act != '2') && (act != '3'))
    {
        printf("\nChoose one of the items: ");
        std::cin >> act;
        cleanCin();
        switch (act)
        {
            case '1': programInfo();
                break;
            case '2': game();
                break;
            case '3': programExit();
                break;
            default:  std::cout << "\nAnd what did you mean by that?\nCheck the entered data and try again!" << std::endl;
                break;
        }
    }
}

void returnToMenu() {
    std::cout << "\nEnter any character to return to the menu: ";
    getchar();
    cleanCin();
    system("cls");
    menu();
}



void programInfo() {
    system("cls");
    std::cout << "This program implements the game \"Bulls and Cows\"." << std::endl;
    std::cout << "The computer generates a random number (you choose a length from 1 to 5), after "
                 "which you have to guess it by sequentially entering guesses." << std::endl;
    std::cout << "If the numbers match up to position, you have identified \"a bull\"." << std::endl;
    std::cout << "If the position doesn't match, but the number is in the hidden number, you've found"
                 "\"a cow\"." << std::endl;
    returnToMenu();
}

void programExit() {
    system("cls");
    std::cout << "Thank you for using this program!\nCome again :)" << std::endl;
    system("pause");
    exit(EXIT_SUCCESS);
}

void game() {
    char contWorking = 'y';
    do {
        system("cls");
        Game game{};
        Player player{&game};
        Computer computer{&game};

        int n;
        std::cout << "Enter n (from 1 to 5): ";
        std::cin >> n;
        cleanCin();
        while (!Game::isValid_n(n)) {
            std::cout << "The entered value n has an invalid length!" << std::endl;
            std::cout << "\nEnter n (from 1 to 5): ";
            std::cin >> n;
            cleanCin();
        }
        game.set_n(n);

        game.setValue(computer.getRandomNumber());

        int guess = -1;
        system("cls");
        while (game.getValue() != guess) {
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            cleanCin();
            if (!game.isValidValue(guess)) {
                std::cout << "The entered number is not in the correct format!\n" << std::endl;
            }
            else if (game.getValue() == guess) {
                std::cout << "\nCongratulations!\nYou guessed the number!" << std::endl;
                break;
            } else {
                auto bullsAndCows = computer.getBullsAndCows(guess);
                std::cout << "Number of bulls: " << bullsAndCows.first << std::endl;
                std::cout << "Number of cows: " << bullsAndCows.second << std::endl;
                std::cout << "\n";
            }
        }
        std::cout << "\n\nDo you want to play one more time?" << std::endl;
        std::cout << "If yes, enter 'y'. To exit game mode, enter any other character: " << std::endl;
        std::cin >> contWorking;
        cleanCin();
    } while (contWorking == 'y');
    returnToMenu();
}

int main(int argc, char* argv[]) {
    srand(time(0));
    greeting();
    menu();
    return EXIT_SUCCESS;
}