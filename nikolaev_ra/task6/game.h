#pragma once

#include <stdexcept>
#include <unordered_set>
#include <string>

const int MIN_N = 1;
const int MAX_N = 5;

class Game {
private:
    int n;
    int value;

public:
    void set_n(int _n);
    [[nodiscard]] int get_n() const;

    [[nodiscard]] int getValue() const;
    void setValue(int _value);

    [[nodiscard]] bool isValidValue(int val) const;
    static bool isValid_n(int n);
};