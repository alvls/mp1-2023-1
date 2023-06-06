#include <iostream>
#include <time.h>
#include <cmath>
#include <string>

using namespace std;

class RandomGeneration
{
	int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
public:
	int Create(int n)
	{
		int number = 0;
		srand(time(NULL));
		int x = 0 + rand() % 9;
		number += a[x];
		a[x] = 999;
		for (int i = 1; i < n; i++) {
			x = 0 + rand() % 10;
			if (a[x] != 999) {
				number += a[x] * pow(10, i);
				a[x] = 999;
			}
			else {
				while (a[x] == 999) {
					x = 0 + rand() % 10;
				}
				number += a[x] * pow(10, i);
				a[x] = 999;
			}
		}
		return number;
	}
};

class BullsAndCows
{
	RandomGeneration random;
	int n;
	int number[10];
	int answer[10];
	int bulls = 0;
	int cows = 0;
public:

	void SetLen(int n)
	{
		if (n > 10) {
			throw invalid_argument("The number is more than the maximum possible!");
		}
		else { this->n = n; };
	}

	void Answer(int ans) {
		int a = ans;
		if (to_string(ans).length() > n) {
			throw invalid_argument("The entered number is greater than the previously specified length!");
		}
		else if (to_string(ans)[0] == '0') {
			throw invalid_argument("The number cannot start with 0!");
		}
		else
		{
			for (int i = n - 1; i >= 0; i--) {
				answer[i] = a % 10;
				a = a / 10;
			}
		}
	}

	void Number() {
		int a = random.Create(n);
		for (int i = n - 1; i >= 0; i--) {
			number[i] = a % 10;
			a = a / 10;
		}
	}

	void Check() {
		bulls = 0;
		cows = 0;
		for (int i = 0; i < n; i++) {
			if (number[i] == answer[i]) {
				bulls++;
			}
			for (int j = 0; j < n; j++) {
				if (number[i] == answer[j]) {
					cows++;
				}
			}
		}
		cows = cows - bulls;
	}

	int GetBulls()
	{
		return bulls;
	}

	int GetCows()
	{
		return cows;
	}

};


void main() {
	int n;
	int ans;
	BullsAndCows player;
	cout << "Enter the length of the number (maximum length - 10)\n";
	cin >> n;
	player.SetLen(n);
	player.Number();
	while (player.GetBulls() != n)
	{
		cout << "Enter a suggested answer\n";
		cin >> ans;
		player.Answer(ans);
		player.Check();
		cout << "Number of bulls:" << player.GetBulls() << endl;
		cout << "Number of cows:" << player.GetCows() << endl;
	}
}