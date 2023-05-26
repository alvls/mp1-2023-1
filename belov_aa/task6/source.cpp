#include <iostream>

#include "Game.h"
#include "BufferedConsoleGameScreen.h"

const int FIELD_X = 5;
const int FIELD_Y = 5;

int main()
{
  system("title Snake");

  //
  int width, height;
  std::cout << "Enter field width and height: ";
  std::cin >> width >> height;

  int win_size;
  std::cout << "Enter snake length to win: ";
  std::cin >> win_size;

  std::cin.ignore();
  //

  auto screen = BufferedConsoleGameScreen();

  while (true)
  {
    Game game(&screen,
      { FIELD_X, FIELD_Y, FIELD_X + width, FIELD_Y + height }, 
      win_size);
    game.start();

    std::cin.ignore();
  }

  return EXIT_SUCCESS;
}