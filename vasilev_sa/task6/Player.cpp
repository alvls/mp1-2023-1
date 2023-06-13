#include <tuple>
#include <random>
#include <iostream>
#include "Player.h"
#include "Board.h"

Player::Player(bool computer) : isComputer(computer)
{
  ships.push_back(Ship(4));

  for (int i = 0; i < 2; i++)
    ships.push_back(Ship(3));

  for (int i = 0; i < 3; i++)
    ships.push_back(Ship(2));

  for (int i = 0; i < 4; i++)
    ships.push_back(Ship(1));
}

std::tuple<int, int, bool> Player::getShipPlacement() const
{
  int x, y, dir;
  std::cout << "������� ����� ������ ���������� X, Y � ����������� (0 - �������������, 1 - �����������): ";
  std::cin >> x >> y >> dir;
  return std::make_tuple(x, y, dir);
}

void Player::placeShips(bool randomGen)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, Board::SIZE - 1);
  std::uniform_int_distribution<> disBool(0, 1);

  for (auto& ship : ships)
  {
    bool isValidPlacement = false;

    while (!isValidPlacement)
    {
      int x, y;
      bool isHorizontal;
      if (randomGen)
      {
        x = dis(gen);
        y = dis(gen);
        isHorizontal = disBool(gen);
      }
      else
        std::tie(x, y, isHorizontal) = getShipPlacement();

      isValidPlacement = leftBoard.canPlaceShip(x, y, ship.size, isHorizontal);

      if (isValidPlacement)
        leftBoard.placeShip(ship, x, y, isHorizontal);
      else if (!randomGen)
      {
        std::cout << "������������ ������������ �������. ���������� ��� ���.\n";
        system("pause");
      }
    }
  }
  if (randomGen)
  {
    system("cls");
    std::cout << "�������� ��������������� ����������������� ��������: \n";
    leftBoard.displayBoard(true);
    system("pause");
    system("cls");
  }
}

bool Player::makeMove(Player& opponent) {
  int x, y;
  bool isHit = false;

  do
  {
    if (isComputer)
    {
      // ��������� ��������� ��������� ��� �������� ����������
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dis(0, Board::SIZE - 1);
      x = dis(gen);
      y = dis(gen);
    }
    else
    {
      std::cout << "��� ���. ������� ����������: ";
      std::cin >> x >> y;
    }

    // ��������, ��� �� ��� ������ ������� �� ���� �����������
    if ((isComputer && (leftBoard.grid[x][y] == Board::HIT || leftBoard.grid[x][y] == Board::MISS || leftBoard.grid[x][y] == Board::SUNK)) ||
      (!isComputer && (rightBoard.grid[x][y] == Board::HIT || rightBoard.grid[x][y] == Board::MISS || rightBoard.grid[x][y] == Board::SUNK)))
    {
      if (!isComputer)
      {
        std::cout << "�� ��� �������� �� ���� �����������. ���������� ��� ���.\n";
        system("pause");
      }
      continue; // ������� ������� ��� ������
    }
    system("cls");
    if (opponent.leftBoard.grid[x][y] == Board::SHIP)
    {
      opponent.leftBoard.markResult(x, y, true, opponent.ships, false);
      rightBoard.markResult(x, y, true, opponent.ships, true);
      isHit = true;
    }
    else
    {
      if (!isComputer)
        std::cout << ("������;(\n");
      opponent.leftBoard.markResult(x, y, false, opponent.ships, false);
      rightBoard.markResult(x, y, false, ships, true);
      isHit = false;
    }
  } while (isHit && (isComputer || (!isComputer && 0)));
  return isHit;
}

void Player::displayBoards() const
{
  if (isComputer)
  {
    return;
  }
  std::cout << "���� ������:\n";
  leftBoard.displayBoard(true);
  std::cout << "���� ����������:\n";
  rightBoard.displayBoard(false);
}
