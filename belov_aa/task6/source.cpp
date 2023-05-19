#include <iostream>

#include "Game.h"
#include "BufferedConsoleGameScreen.h"


int main()
{
	system("title Snake");

	GameScreen* screen = new BufferedConsoleGameScreen();
	
	while (true)
	{
		Game game(screen, { 5, 5, 20 ,50 }, 10);
		game.start();

		std::cin.ignore();
	}
	
	return EXIT_SUCCESS;
}