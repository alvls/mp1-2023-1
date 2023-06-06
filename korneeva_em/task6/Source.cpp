#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class RandomGenerator
{
private:
	int length;

public:
	RandomGenerator(int _length = 0) : length(_length) {}
	void setLength(int length)
	{
		this->length = length;
	}
	int getRandomNumber()
	{
		int randomNumber = 0;
		vector<int> digits;

		if (length <= 0 || length >= 10)
		{
			throw invalid_argument("������������ ����� �����");
		}

		for (int i = 0; i <= 9; i++)
		{
			digits.push_back(i);
		}
		while (digits[0] == 0)
		{
			shuffle(digits.begin(), digits.end(), random_device());
		}

		for (int i = 0; i < length; i++)
		{
			randomNumber = randomNumber * 10 + digits[i];
		}

		return randomNumber;
	}
};

class BullsAndCowsGame {
private:
	int length;
	RandomGenerator rng;

public:
	BullsAndCowsGame() : length(0) {}

	int getLength() const
	{
		return length;
	}
	int getNumberLength(int number)
	{
		int NumberLength = 0;
		while (number != 0)
		{
			number /= 10;
			NumberLength++;

		}
		return NumberLength;
	}
	int generateSecretNumber()
	{
		return rng.getRandomNumber();
	}
	void setLength(int length)
	{
		this->length = length;
		rng.setLength(length);
	}

	vector<int> getDigits(int number) 
	{
		vector<int> digits;

		while (number > 0) {
			digits.push_back(number % 10);
			number /= 10;
		}
		reverse(digits.begin(), digits.end());

		return digits;
	}
	pair<int,int> calculateBullsAndCows(const vector<int>& guessDigits, const vector<int>& secretDigits) {
		int bulls = 0;
		int cows = 0;

		for (int i = 0; i < length; i++) {
			if (guessDigits[i] == secretDigits[i]) {
				bulls++;
			}
			else {
				for (int j = 0; j < length; j++) {
					if (guessDigits[i] == secretDigits[j]) {
						cows++;
						break;
					}
				}
			}
		}
		return { bulls,cows };
	}

	void play(int _length)
	{
		setLength(_length);

		int secretNumber = generateSecretNumber();
		int guess;
		int attempts = 0;
		vector<int> secretDigits = getDigits(secretNumber);

		cout << "�������� " << length << "-������� �����. ��� ����, ����� ������� ������� '-1'" << endl;

		while (true) 
		{

			cout << "������� ������������� �����: ";
			cin >> guess;

			if (guess == -1)
			{
				cout << "�� �������. ���������� ����� ����: " << secretNumber << endl;
				break;
			}

			while (getNumberLength(guess) != length)
			{
				cout << "�������� ����� �� ������������� �� �����, ������� �����:  ";
				cin >> guess;
			}
			attempts++;

			vector<int> guessDigits = getDigits(guess);
			pair<int,int> BullsAndCows = calculateBullsAndCows(guessDigits, secretDigits);

			if (BullsAndCows.first == length)
			{
				cout << endl << "�����������, �� ��������! ���������� �������: " << attempts << endl;
				break;
			}

			cout << "����: " << BullsAndCows.first << ", ������: " << BullsAndCows.second << endl;
		}
	}
	void MultipleGames()
	{
		int choice;
		cout << "����� ���������� � ����!" << endl;

		do {
			cout << "������� ����� ������������� ����� (�� 1 �� 9): ";
			cin >> length;

			system("cls");
			play(length);

			cout << "������ ������� ��� ���? (��� ����������� ���� ������� 1): ";
			cin >> choice;
			system("cls");
		} while (choice == 1);
	}
};

int main() 
{
	setlocale(LC_ALL, "Russian");

	BullsAndCowsGame game;
	game.MultipleGames();

}