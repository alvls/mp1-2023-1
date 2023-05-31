#pragma once
 
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <set>
#include <stdexcept>
 
#define MIN_N 1
#define MAX_N 5
 
class GameProcess {
private:
    int n;
    int guessedValue;
 
public:
    void setN(int n);
    int getN();
    void setGuessedValue(int guessedValue);
    int getGuessedValue();
};
 
