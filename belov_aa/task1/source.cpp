#include <iostream>
#include <stdexcept>

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
    void add(RationalFraction fraction)
    {
        this->numerator = this->numerator * fraction.denominator + fraction.numerator * this->denominator;
        this->denominator *= fraction.denominator;

        ReduceFraction();
    }
    void subtract(RationalFraction fraction)
    {
        this->numerator = this->numerator * fraction.denominator - fraction.numerator * this->denominator;
        this->denominator *= fraction.denominator;

        ReduceFraction();
    }
    void multiply(RationalFraction fraction)
    {
        this->numerator *= fraction.numerator;
        this->denominator *= fraction.denominator;

        ReduceFraction();
    }
    void divide(RationalFraction fraction)
    {
        if (fraction.numerator == 0)
        {
            throw std::invalid_argument("Incorrect fraction");
        }

        this->numerator *= fraction.denominator;
        this->denominator *= fraction.numerator;

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
        if (denominator == 0)
        {
            throw std::invalid_argument("Incorrect fraction. The denominator must not contain zero");
        }

        this->numerator = numerator;
        this->denominator = denominator;
        
        ReduceFraction();
    }
};

int main()
{
    RationalFraction fraction(2, 3);
    fraction.divide({ 0, 5 });
    fraction.print();

    system("PAUSE");
}