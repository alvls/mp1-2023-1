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
            cout << "������� ������������ �����. ���������� �����." << endl;
        }
    }
    int New_gameORnot()
    {
        cout << "������ ������ ����� ���� - ������� 1; ����� ������� - 2" << endl;
        check(1, 2);
        system("cls");
        return true_numb;
    }
    void coincidences(int cows, int bulls)
    {
        cout << "�����: " << cows << "   " << "�����: " << bulls<< endl;
    }
    int number_of_digits()
    { 
        cout << "����� ����. ���� � ������." << endl;
        cout << "�������������� ����� �� ������ �������� ? " << endl;
        check(1, 9);
        return true_numb;
    }
    void show_win(int estimated_number, int attempts)
    {
        cout << "�� ��������! ���� �������� �����: " << estimated_number << endl;
        cout << "����� �������: " << attempts << endl;
    }
    int input(int g)
    {
        cout << "������� �������������� �����" << "\n" << endl;
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
                cout << "������� ������������ �����. ������� ���������� �����, ������� ��������� �� ���������� ����(��� ������) �� ���������, ������� ��������� �����." << endl;
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