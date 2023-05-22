#include "Ship.h"

Ship::Ship(int s) : size(s) {}

void Ship::addCoordinate(int x, int y) const
{
  std::vector<std::pair<int, int>>& mutableCoordinates = const_cast<std::vector<std::pair<int, int>>&>(coordinates);
  mutableCoordinates.push_back(std::make_pair(x, y));
}

bool Ship::containsCoordinate(int x, int y) const
{
  for (const auto& coord : coordinates) {
    if (coord.first == x && coord.second == y) {
      return true;
    }
  }
  return false;
}

void Ship::hit()
{
  hits++;
}

bool Ship::sunk() const {
  return hits == size;
}
