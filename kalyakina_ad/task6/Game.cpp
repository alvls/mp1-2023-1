#include "Game.h"

Ship::Ship(int _i1, int _j1, int _i2, int _j2) :i1(_i1), i2(_i2), j1(_j1), j2(_j2)
{
	if (i1 != i2)
		count_of_all = i2 - i1 + 1;
	else
		count_of_all = j2 - j1 + 1;
	count_of_remaining = count_of_all;
}

bool  Ship::is_hit(int i, int j)
{
	if ((i >= i1) && (i <= i2) && (j >= j1) && (j <= j2))
	{
		count_of_remaining--;
		return true;
	}
	else
		return false;
}

bool Ship::is_intersect(Ship const s)
{
	if (i1 > s.i2 + 1)
		return false;
	else if (i2 < s.i1 - 1)
		return false;
	else if (j1 > s.j2 + 1)
		return false;
	else if (j2 < s.j1 - 1)
		return false;
	else
		return true;
}

bool Ship::is_all()
{
	return(count_of_remaining == 0);
}

void Ship::find_index(int& i1, int& j1, int& i2, int& j2)
{
	i1 = this->i1;
	i2 = this->i2;
	j1 = this->j1;
	j2 = this->j2;
}

Game::Game()
{
	memset(ship_count, 0, 8 * sizeof(int));
	memset(player_playground, 0, 100 * sizeof(int));
	memset(computer_playground, 0, 100 * sizeof(int));
	last_i1 = last_j1 = last_i2 = last_j2 = -1;

	auto_placement(1);
}

vector <tuple<int, int, int, int>> Game::auto_placement(int num)
{
	srand(time(NULL));
	vector <tuple<int, int, int, int>> result;
	int i1, j1, i2, j2;
	if (num == 2)
	{
		num = 0;
		memset(ship_count[num], 0, 4 * sizeof(int));
		ships_to_remember[num].clear();
	}
	for (int i = 4; i > 0; i--)
	{
		for (int j = 0; j < 4 - i + 1; j++)
		{
			do
			{
				do
				{
					i1 = rand() % 10;
					j1 = rand() % 10;
					if (rand() % 2 == 1)
					{
						i2 = i1 + i - 1;
						j2 = j1;
					}
					else
					{
						i2 = i1;
						j2 = j1 + i - 1;
					}
				} while ((i2 > 9) || (j2 > 9));
			} while (!initialize_of_ship(i1, j1, i2, j2, num));
			result.push_back({ i1, j1, i2, j2 });
		}
	}
	return result;
}

bool Game::initialize_of_ship(int i1, int j1, int i2, int j2, int num)
{
	bool intersect = false;
	if ((i2 < i1) || (j2 < j1))
	{
		i1 += i2;
		i2 = i1 - i2;
		i1 -= i2;
		j1 += j2;
		j2 = j1 - j2;
		j1 -= j2;
	}
	if ((i2 - i1 > 3) || (j2 - j1 > 3) || (i2 - i1 >= 1) && (j2 - j1 >= 1) 
		|| (ship_count[num][__max(i2 - i1, j2 - j1)] == (4 - __max(i2 - i1, j2 - j1))))
		return false;
	Ship p(i1, j1, i2, j2);
	for (int i = 0; i < ships_to_remember[num].size(); i++)
		if (p.is_intersect(ships_to_remember[num].at(i)))
		{
			intersect = true;
			break;
		}
	if (intersect)
		return false;
	else
	{
		if (num == 0)
		{
			for (int i = i1; i <= i2; i++)
			{
				for (int j = j1; j <= j2; j++)
					player_playground[i][j] = 1;
			}
		}
		ship_count[num][__max(i2 - i1, j2 - j1)]++;
		ships_to_remember[num].push_back(p);
		return true;
	}
}

bool Game::is_all()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += ship_count[0][i];
	}
	return(sum == 10);
}

vector <vector<tuple<int, int, int, int>>> Game::new_move(int i1, int j1)
{
	vector <vector<tuple<int, int, int, int>>> result;
	vector <tuple<int, int, int, int>> moment_result;
	int i;
	int new_i, new_j;
	bool move = true;
	if (computer_playground[i1][j1] >= 0)
	{
		for (i = 0; i < 10; i++)
			if (ships_to_remember[1].at(i).is_hit(i1, j1))
			{
				move = false;
				break;
			}
		if (move)
		{
			computer_playground[i1][j1] = -1;
			result.push_back({ { 2, i1, j1, -1 } });
			do
			{
				if (last_i1 == -1)
				{
					do
					{
						new_i = rand() % 10;
						new_j = rand() % 10;
					} while (player_playground[new_i][new_j] < 0);
				}
				else if (last_i2 == -1)
				{
					int rand_num = (rand() % 10) + 1;
					do
					{
						do
						{
							if (rand_num % 2 == 0)
							{
								new_i = last_i1 + rand() % 3 - 1;
								new_j = last_j1;
							}
							else
							{
								new_i = last_i1;
								new_j = last_j1 + rand() % 3 - 1;
							}
							rand_num++;
						} while ((new_i < 0) || (new_j < 0) || (new_i > 9) || (new_j > 9));
					} while (player_playground[new_i][new_j] < 0);
				}
				else
				{
					int rand_num = (rand() % 10) + 1;
					do
					{
						do
						{
							if (last_j1 == last_j2)
							{
								if (rand_num % 2 == 0)
								{
									new_i = last_i1 - 1;
									new_j = last_j1;
								}
								else
								{
									new_i = last_i2 + 1;
									new_j = last_j2;
								}
							}
							else
							{
								if (rand_num % 2 == 0)
								{
									new_i = last_i1;
									new_j = last_j1 - 1;
								}
								else
								{
									new_i = last_i2;
									new_j = last_j2 + 1;
								}
							}
							rand_num++;
						} while ((new_i < 0) || (new_j < 0) || (new_i > 9) || (new_j > 9));
					} while (player_playground[new_i][new_j] < 0);
				}

				if (player_playground[new_i][new_j] != 1)
				{
					player_playground[new_i][new_j] = -1;
					result.push_back({ { 1, new_i, new_j, -1 } });
					move = false;
				}
				else
				{
					player_playground[new_i][new_j] = -2;
					result.push_back({ { 1, new_i, new_j, -2 } });
					for (i = 0; i < 10; i++)
						if (ships_to_remember[0].at(i).is_hit(new_i, new_j))
							break;
					if (!ships_to_remember[0].at(i).is_all())
					{
						if (last_i1 == -1)
						{
							last_i1 = new_i;
							last_j1 = new_j;
						}
						else if (last_i2 == -1)
						{
							if ((last_i1 > new_i) || (last_j1 > new_j))
							{
								last_i2 = last_i1;
								last_j2 = last_j1;
								last_i1 = new_i;
								last_j1 = new_j;
							}
							else
							{
								last_i2 = new_i;
								last_j2 = new_j;
							}
						}
						else
						{
							if ((abs(last_i1 - new_i) == 1) || (abs(last_j1 - new_j) == 1))
							{
								last_i1 = new_i;
								last_j1 = new_j;
							}
							else
							{
								last_i2 = new_i;
								last_j2 = new_j;
							}
						}
					}
					else
					{
						ships_to_remember[0].at(i).find_index(i1, j1, new_i, new_j);
						for (int j = __max(j1 - 1, 0); j <= __min(new_j + 1, 9); j++)
						{
							if (i1 > 0)
							{
								player_playground[i1 - 1][j] = -1;
								moment_result.push_back({ 1, i1 - 1, j, -1 });
							}
							if (new_i < 9)
							{
								player_playground[new_i + 1][j] = -1;
								moment_result.push_back({ 1, new_i + 1, j, -1 });
							}
						}
						for (int j = i1; j <= new_i; j++)
						{
							if (j1 > 0)
							{
								player_playground[j][j1 - 1] = -1;
								moment_result.push_back({ 1, j, j1 - 1, -1 });
							}
							if (new_j < 9)
							{
								player_playground[j][new_j + 1] = -1;
								moment_result.push_back({ 1, j, new_j + 1, -1 });
							}
						}
						result.push_back(moment_result);
						moment_result.clear();
						i1 = __max(new_i - i1, new_j - j1);
						if (i1 < 4)
							ship_count[0][i1]--;
						last_i1 = last_i2 = last_j1 = last_j2 = -1;
					}
				}
			}while (move);
		}
		else
		{
			computer_playground[i1][j1] = -2;
			result.push_back({ { 2, i1, j1, -2 } });

			if (ships_to_remember[1].at(i).is_all())
			{
				ships_to_remember[1].at(i).find_index(i1, j1, new_i, new_j);
				for (int j = __max(j1 - 1, 0); j <= __min(new_j + 1, 9); j++)
				{
					if (i1 > 0)
					{
						computer_playground[i1 - 1][j] = -1;
						moment_result.push_back({ 2, i1 - 1, j, -1 });
					}
					if (new_i < 9)
					{
						computer_playground[new_i + 1][j] = -1;
						moment_result.push_back({ 2, new_i + 1, j, -1 });
					}
				}
				for (int j = i1; j <= new_i; j++)
				{
					if (j1 > 0)
					{
						computer_playground[j][j1 - 1] = -1;
						moment_result.push_back({ 2, j, j1 - 1, -1 });
					}
					if (new_j < 9)
					{
						computer_playground[j][new_j + 1] = -1;
						moment_result.push_back({ 2, j, new_j + 1, -1 });
					}
				}
				result.push_back(moment_result);
				moment_result.clear();
				ship_count[1][__max(new_i - i1, new_j - j1)]--;
			}
		}
	}
	return result;
}

bool Game::ending()
{
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < 4; i++)
	{
		sum1 += ship_count[0][i];
		sum2 += ship_count[1][i];
	}
	return ((sum1 == 0) || (sum2 == 0));
}

int Game::winner()
{
	int sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum += ship_count[0][i];
	}
	if (sum == 0)
		return 2;

	else
		return 1;
}