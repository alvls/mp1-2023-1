#include <iostream>

using namespace std;

class RationalFraction
{
private:
    int numerator = 0;
    int denominator = 0;

    void ReduceFraction() // Алгоритм Евклида
    {
        int a, b, c;
        a = numerator;
        b = denominator;
        while (b != 0)
        {
            c = a % b;
            a = b;
            b = c;
        }
        numerator /= a;
        denominator /= a;
    }
public:
    void add(int numerator, int denominator)
    {
        this->numerator = this->numerator * denominator + numerator * this->denominator;
        this->denominator *= denominator;

        ReduceFraction();
    }
    void subtract(int numerator, int denominator)
    {
        this->numerator = this->numerator * denominator - numerator * this->denominator;
        this->denominator *= denominator;

        ReduceFraction();
    }
    void multiply(int numerator, int denominator)
    {
        if (denominator == 0)
        {
            cout << "Second fraction is incorrect. The denominator must not contain zero\n";
        }
        else
        {
            this->numerator *= numerator;
            this->denominator *= denominator;

            ReduceFraction();
        }
    }
    void divide(int numerator, int denominator)
    {
        if (numerator * denominator == 0) // если хотя бы один из двух множителей = 0, то и их произведение = 0
        {
            cout << "Second fraction is incorrect. The numerator and denominator must not contain zero!\n";
            return;
        }

        this->numerator *= denominator;
        this->denominator *= numerator;

        ReduceFraction();
    }
    void print()
    {
        if (numerator == 0)
        {
            cout << "Result: " << numerator << "\n";
        }
        else if (denominator < 0)
        {
            cout << "Result: " << -numerator << "/" << -denominator << "\n";
        }
        else
        {
            cout << "Result: " << numerator << "/" << denominator << "\n";
        }
        
    }
    RationalFraction(int numerator, int denominator)
    {
        this->numerator = numerator;
        this->denominator = denominator;

        if (denominator == 0)
        {
            cout << "The denominator must not contain zero!\n";
        }
        else
        {
            ReduceFraction();
        }
    }
};

int main() // функция использовалась для отладки
{
    RationalFraction fraction(1, 4);
    fraction.divide(3, 2);
    fraction.print();

    system("PAUSE");
}