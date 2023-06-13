#pragma once
#include <cctype>
#include <algorithm>
using namespace std;
class Display {
public:
    int temp_input;
    int true_numb;
    void check(int a, int b)
    {
        while (true)
        {
            string inpt;
            cin >> inpt;
            bool numbORnot = !inpt.empty() && all_of(inpt.begin(), inpt.end(), isdigit);
            if (numbORnot)
            {
                true_numb = stoi(inpt);
                if ((true_numb >= a) && (true_numb <= b))
                {
                    break;
                }
            }
            cout << "Введено некорректное число. Попробуйте снова." << endl;
        }
    }
    int New_gameORnot()
    {
        cout << "Хотите начать новую игру - введите 1; Иначе введите - 2" << endl;
        check(1, 2);
        system("cls");
        return true_numb;
    }
    void coincidences(int cows, int bulls)
    {
        cout << "Коров: " << cows << "   " << "Быков: " << bulls<< endl;
    }
    int number_of_digits()
    { 
        cout << "Новая игра. Быки и коровы." << endl;
        cout << "Сколькизначное число вы хотите отгадать ? " << endl;
        check(1, 9);
        return true_numb;
    }
    void show_win(int estimated_number, int attempts)
    {
        cout << "Вы отгадали! Было загадано число: " << estimated_number << endl;
        cout << "Всего попыток: " << attempts << endl;
    }
    int input(int g)
    {
        cout << "Введите предполалаемое число" << "\n" << endl;
        cin >> temp_input;
        int copy_input = temp_input;
        for (int i = 0; i < g; i++)
        {
            temp_input /= 10;
        }
        if (temp_input == 0)
            return copy_input;
        else
        {
            while (copy_input != 0)
            {
                cout << "Введено некорректное число. Введите корректное число, которое совпадает по количеству цифр(или меньше) со значением, которое вводилось ранее." << endl;
                cin >> temp_input;
                g = temp_input;
                for (int i = 0; i < g; i++)
                {
                    temp_input /= 10;
                }
                copy_input = temp_input;
            }
            return g;
        }
    }
};