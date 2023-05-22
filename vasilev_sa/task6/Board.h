#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Ship.h"

class Board {
public:
  Board();
  void markResult(int x, int y, bool isHit, std::vector<Ship>& ships, bool twice);
  bool isValidCell(int x, int y) const;
  bool canPlaceShip(int x, int y, int shipSize, bool isHorizontal) const;
  void placeShip(const Ship& ship, int x, int y, bool isHorizontal);
  void displayBoard(bool showShips) const;

  static const int SIZE = 10;
  static const char EMPTY = '-';
  static const char SHIP = 'S';
  static const char MISS = 'M';
  static const char HIT = 'H';
  static const char SUNK = 'X';

  char grid[SIZE][SIZE];
};

#endif // BOARD_H
