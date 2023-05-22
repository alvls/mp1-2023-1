#pragma once

#include <stdexcept>
#include <unordered_set>
#include <string>

const int MIN_N = 0;
const int MAX_N = 5;

class Game {
private:
    int n;
    int value;

public:
    void set_n(int _n);
    int get_n() const;

    int getValue() const;
    void setValue(int _value);

    bool isValidValue(int val);
    static bool isValid_n(int n);
};