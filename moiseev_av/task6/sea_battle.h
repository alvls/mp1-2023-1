#pragma once
#include <vector>
#include <random>

#include "field.h"
#include "ship.h"

using namespace std;

enum Keycodes {

    Enter = 13,
    Left = 75,
    Right = 77,
    Up = 72,
    Down = 80,
    W = 87,
    A = 65,
    S = 83,
    D = 68,
    R = 82,
    W_l = 119,
    A_l = 97,
    S_l = 115,
    D_l = 100,
    R_l = 114,
    Special = -32
};


class sea_battle {

public:
    sea_battle();

    void start();

private:
    field Field;
    COORD dxy;
    TColor color = GREEN;
    random_device rd;
    vector<ship> ships;
    vector<ship> enemy_ships;
    vector<COORD> busy_poits;
    vector<COORD> enemy_busy_poits;
    vector<COORD> turns;
    vector<COORD> player_turns;
    vector<Keycodes> keys = { Keycodes::A, Keycodes::A_l, Keycodes::D, Keycodes::D_l,
    Keycodes::W, Keycodes::W_l, Keycodes::S, Keycodes::S_l };
    vector<int> num = { 0, 1, -1, 9, -9, 10, -10, 11, -11 };
    vector<int> num2 = { 10, -10, 1, -1 };
    bool special_key = false;
    bool first_turn = true;
    bool rotate = false;
    bool fight = false;
    bool spot = false;
    bool cont = false;
    bool perm = true;
    bool was = false;
    bool win = true;
    int main_dp;
    int offset;
    int cnt;
    int dp;
    char c;

    string label = "(___/(____)(__)(__)  (____/(__)(__)(__)  (__) (____)(____)"
        "\n\\__ \\ )__)  /(__)\\    ) _ < /(__)\\  )(    )(   )(__  )__)"
        "\n/ __)( ___)  /__\\    (  _ \\  /__\\ (_  _)(_  _)(  )  ( ___)"
        "\n ___  ____    __      ____    __   ____  ____  __    ____\n";

    void label_animation(int time = 0);

    void splash_screen();

    void create_ships(int n, int deck, vector<ship>& ships);

    void set_point(int cnt);

    void occupied_point(int x, int y, int cnt);

    bool sides(bool x, int bord_1, int bord_2, int cnt, int dxy);

    void not_special_key(bool option, bool x, int bord_1, int bord_2, int bord_3,
        int bord_4, int cnt, int dx, int dy);

    void add_main_points(vector<COORD>& points, bool enemy, int i);

    void add_tail_points(vector<COORD>& points, vector<ship>& ships,
        bool enemy, int i, int ship_iter);

    void print_points(COORD point, bool enemy, int i);

    void dead_ship(COORD point, int i);

    void insert_ships();

    void insert_enemy_ships();

    void enemy_turn();

    void player_turn();
};