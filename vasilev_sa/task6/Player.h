#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <random>
#include "Board.h"
#include "Ship.h"

class Player {
public:
  Player(bool computer = false);
  std::tuple<int, int, bool> getShipPlacement() const;
  void placeShips(bool randomGen);
  bool makeMove(Player& opponent);
  void displayBoards() const;

  Board leftBoard;
  Board rightBoard;
  std::vector<Ship> ships;
  bool isComputer;
};

#endif // PLAYER_H
