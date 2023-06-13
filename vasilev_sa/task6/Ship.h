#ifndef SHIP_H
#define SHIP_H

#include <vector>

class Ship {
public:
  int size;
  std::vector<std::pair<int, int>> coordinates;
  int hits = 0;

  Ship(int s);
  void addCoordinate(int x, int y) const;
  bool containsCoordinate(int x, int y) const;
  void hit();
  bool sunk() const;
};

#endif //SHIP_H
