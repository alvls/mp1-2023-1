#include <iostream>
#include "Board.h"
#include "Ship.h"

Board::Board()
{
  for (int i = 0; i < SIZE; i++)
    for (int j = 0; j < SIZE; j++)
      grid[i][j] = EMPTY;
}

void Board::markResult(int x, int y, bool isHit, std::vector<Ship>& ships, bool twice)
{
  if (isValidCell(x, y))
  {
    if (isHit)
    {
      grid[x][y] = HIT;
      for (auto& ship : ships) {
        if (ship.containsCoordinate(x, y))
        {
          if (!twice)
            ship.hit();
          grid[x][y] = HIT;
          if (ship.sunk())
          {
            for (auto& coord : ship.coordinates)
              grid[coord.first][coord.second] = SUNK;
          }
          break;
        }
      }
    }
    else
    {
      grid[x][y] = MISS;
    }
  }
}

bool Board::isValidCell(int x, int y) const
{
  return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool Board::canPlaceShip(int x, int y, int shipSize, bool isHorizontal) const
{
  // Проверка на корректность координат
  if (!isValidCell(x, y))
  {
    return false;
  }

  // Проверка наличия корабля вокруг выбранных клеток
  int startX = x - 1;
  int startY = y - 1;
  int endX = x + 1;
  int endY = y + 1;

  if (isHorizontal)
  {
    endX += shipSize;
  }
  else
  {
    endY += shipSize;
  }

  for (int i = startX; i <= endX; i++)
    for (int j = startY; j <= endY; j++)
      if (isValidCell(i, j) && grid[i][j] == SHIP)
        return false;

  // Проверка доступности места для установки корабля
  for (int i = 0; i < shipSize; i++)
  {
    if (isHorizontal)
    {
      if (!isValidCell(x + i, y) || grid[x + i][y] != EMPTY)
      {
        return false;
      }
    }
    else
    {
      if (!isValidCell(x, y + i) || grid[x][y + i] != EMPTY)
      {
        return false;
      }
    }
  }

  return true;
}

void Board::placeShip(const Ship& ship, int x, int y, bool isHorizontal) {
  if (isHorizontal)
  {
    for (int i = x; i < x + ship.size; i++)
    {
      grid[i][y] = SHIP;
      ship.addCoordinate(i, y);
    }
  }
  else
  {
    for (int j = y; j < y + ship.size; j++)
    {
      grid[x][j] = SHIP;
      ship.addCoordinate(x, j);
    }
  }
}

void Board::displayBoard(bool showShips) const
{
  std::cout << "  ";
  for (int i = 0; i < SIZE; i++)
    std::cout << i << " ";
  std::cout << "\n";

  for (int i = 0; i < SIZE; i++)
  {
    std::cout << i << " ";
    for (int j = 0; j < SIZE; j++)
    {
      if (grid[i][j] == SHIP && !showShips)
        std::cout << EMPTY << " ";
      else
        std::cout << grid[i][j] << " ";
    }
    std::cout << "\n";
  }
}
