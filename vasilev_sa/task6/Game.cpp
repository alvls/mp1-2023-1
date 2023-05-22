#include "Game.h"
#include "Ship.h"
#include "Player.h"
#include "Player.h"
#include <Windows.h>
#include <iostream>

void Game::start()
{
  SetConsoleOutputCP(1251);
  SetConsoleCP(1251);
  Player player(false);
  Player computer(true);

  player.placeShips(true);
  computer.placeShips(true);

  Player* currentPlayer = &player;
  Player* opponent = &computer;

  while (true)
  {

    currentPlayer->displayBoards();
    bool hit = currentPlayer->makeMove(*opponent);
    currentPlayer->displayBoards(); // обновляем экран после хода
    if (hit)
    {
      // Если текущий игрок попал, то проверяем, остались ли корабли у противника
      bool hasShips = false;
      for (const auto& ship : opponent->ships)
      {
        if (!ship.sunk())
        {
          hasShips = true;
          break;
        }
      }
      // Если кораблей у противника не осталось, текущий игрок побеждает
      if (!hasShips)
      {
        system("cls");
        std::cout << (currentPlayer->isComputer ? "Компьютер выиграл!" : "Игрок выиграл!") << "\n";
        break;
      }
    }
    else
    {
      // Если текущий игрок промахнулся, ход переходит к противнику
      std::swap(currentPlayer, opponent);
      system("cls");
    }
  }
  system("pause");
}