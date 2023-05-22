#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include "Display.h"
#include "Randomizer.h"
#include <cstdlib>
#include <cctype>
#include <ctime>
using namespace std;
class Game
{
private:
	Randomizer& randomizer;
	Display& display;
public:
	Game(Randomizer& randomizer, Display& display) : randomizer(randomizer), display(display) {}
	void Game::Gameplay()
	{
		bool playAgain = true;
		int answer;
		pair<int, int> result;
		Display display;
		Randomizer rndcount;
		int VvedennoeChislo;
		int attempts = 0;
		int RandomnoeChislo = 0;
		while (playAgain)
		{
			RandomnoeChislo = 0;
			int g = display.number_of_digits();
			if (RandomnoeChislo == 0)
			{
				RandomnoeChislo = rndcount.generator(g);
				attempts = 0;
			}
				do
				{
					VvedennoeChislo = display.input(g); 
					result = rndcount.checkGuess(VvedennoeChislo, g);
					display.coincidences(result.first, result.second);
					cout << RandomnoeChislo << endl; 
					attempts++;

				} while (result.second != g);
				if (result.second == g)
				{
					display.show_win(RandomnoeChislo, attempts); 
				}
				answer = display.New_gameORnot();
				if (answer == 2)
				{
					playAgain = false;
				}
		}
	}
 };
int main()
{
	setlocale(LC_ALL, "Russian");
	Randomizer randomizer;
	Display display;
	Game game(randomizer, display);
	game.Gameplay();
	system("pause");
	return 0;
}