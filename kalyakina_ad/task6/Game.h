#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>

using namespace std;

class Ship
{
	int i1, i2, j1, j2;
	int count_of_all;
	int count_of_remaining;

public:
	Ship(int _i1, int _j1, int _i2, int _j2);

	bool  is_hit(int i, int j);

	bool is_intersect(Ship const s);

	bool is_all();

	void find_index(int& i1, int& j1, int& i2, int& j2);

	~Ship() = default;
};

class Game
{
	int player_playground[10][10], computer_playground[10][10];
	int ship_count[2][4];
	vector <Ship> ships_to_remember[2];
	int last_i1, last_j1, last_i2, last_j2;


public:
	Game();

	vector <tuple<int, int, int, int>> auto_placement(int num = 0);

	bool initialize_of_ship(int i1, int j1, int i2, int j2, int num = 0);

	bool is_all();

	vector <vector<tuple<int, int, int, int>>> new_move(int i1, int j1);

	bool ending();

	int winner();

	~Game() = default;
};