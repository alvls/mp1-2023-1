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
    currentPlayer->displayBoards(); // ��������� ����� ����� ����
    if (hit)
    {
      // ���� ������� ����� �����, �� ���������, �������� �� ������� � ����������
      bool hasShips = false;
      for (const auto& ship : opponent->ships)
      {
        if (!ship.sunk())
        {
          hasShips = true;
          break;
        }
      }
      // ���� �������� � ���������� �� ��������, ������� ����� ���������
      if (!hasShips)
      {
        system("cls");
        std::cout << (currentPlayer->isComputer ? "��������� �������!" : "����� �������!") << "\n";
        break;
      }
    }
    else
    {
      // ���� ������� ����� �����������, ��� ��������� � ����������
      std::swap(currentPlayer, opponent);
      system("cls");
    }
  }
  system("pause");
}