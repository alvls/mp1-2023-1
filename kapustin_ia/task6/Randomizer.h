
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
class Randomizer {
public:
    vector<int> digits;
    Randomizer()  = default;
    std::vector<int> secret;  
    std::pair<int, int> Randomizer::checkGuess(int guess, int count_numb)
    {
        std::vector<int> guessDigits;
        std::vector<int> secretDigits;
        int tempGuess = guess;
        for (int i = 0; i < count_numb; i++) {
            guessDigits.push_back(tempGuess % 10);
            tempGuess /= 10;
        }
        int tempSecret = generatedNumber;
        for (int i = 0; i < count_numb; i++) {
            secretDigits.push_back(tempSecret % 10);
            tempSecret /= 10;
        }
        int cows = 0;
        int bulls = 0;
        for (int i = 0; i < count_numb; i++) {
            if (guessDigits[i] == secretDigits[i])
            {
                bulls++;
            }
            else if (find(secretDigits.begin(), secretDigits.end(), guessDigits[i]) != secretDigits.end())
            {
                cows++;
            }
        }
        return make_pair(cows, bulls);
    }
    int Randomizer::generator(int numDigits)
    {
        generatedNumber = 0;
        digits.clear();
        default_random_engine gen(std::time(nullptr));
        uniform_int_distribution<int> distribution(0, 9);
        while (digits.size() < numDigits)
        {
            int digit = distribution(gen);
            if (find(digits.begin(), digits.end(), digit) == digits.end())
            {
                digits.push_back(digit);
            }
        }
        for (int i = 0; i < numDigits; ++i)
        {
            generatedNumber = generatedNumber * 10 + digits[i];
        }
        return generatedNumber;

    }
private:
    int generatedNumber = 0;
};