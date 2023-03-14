#include <iostream> 
#include <cmath> 
#include <algorithm>
#include <stdexcept>
 
using namespace std; 
 
class Polynomial 
{ 
private: 
    int max_degree; 
    double* coeffs; 
public: 
    Polynomial(int degree) 
    {
        if ((degree < 0) || (degree > 12))
        {
            throw std::invalid_argument("Incorrect degree");
        }

        max_degree = degree + 1;
        coeffs = new double[max_degree]();

    } 

    Polynomial(const Polynomial& source) 
    { 
        max_degree = source.max_degree; 
        coeffs = new double[max_degree]; 
        copy(source.coeffs, &source.coeffs[source.max_degree], coeffs);
    } 
 
    ~Polynomial() 
    { 
        delete[] coeffs; 
    } 

    friend ostream& operator<<(ostream& os, const Polynomial& p)
    { 
        int begin = p.max_degree - 1;
        for (int i = begin; i >= 0; i--)
        {
            if (p.coeffs[i] == 0)
            {
                begin--;
                continue;
            }

            double coeff = p.coeffs[i];
            bool neg = coeff < 0;
            coeff *= neg ? (-1) : 1;

            os << (neg ? "-" : ((i == begin) ? "" : "+")) << ((i == begin) ? "" : " ");
            if (coeff != 1)
            {
                os << coeff;
            }

            if (i != 0)
            {
                os << "x";
                if (i != 1)
                {
                    os << "^" << i;
                }
                os << " ";
            }
        }
        return os;
    } 

    double get_coeff(int power) // узнать значение коэффициента по его номеру
    {
        return coeffs[power];
    }

    void set_coeff(int power, double value) // задать коэффициент для монома степени power
    { 
        coeffs[power] = value;
    } 

    int get_degree() // узнать степень полинома
    { 
        return max_degree - 1; 
    } 

    void set_degree(int degree) // задать степень полинома
    {
        if (max_degree == degree)
        {
            return;
        }

        int old_degree = max_degree;
        max_degree = degree + 1;

        double* new_coeffs = new double[max_degree]();
        copy(coeffs, &coeffs[max_degree], new_coeffs);

        delete[] coeffs;
        coeffs = new_coeffs;
    }

    double calc(double x) // вычисление значения полинома в заданной точке х
    {
        double result = 0;
        for (int i = 0; i < max_degree; i++)
        {
            result += coeffs[i] * pow(x, i);
        }
        return result;
    }

    Polynomial derivative() // вычисление производной
    { 
        Polynomial result(get_degree() - 1);
        for (int i = 1; i < max_degree; i++) 
        { 
            result.set_coeff(i - 1, coeffs[i] * i);
        } 
        return result; 
    }
}; 
 
void main()
{
    Polynomial polynom(4);

    polynom.set_coeff(4, 8);
    polynom.set_coeff(3, 2);
    polynom.set_coeff(2, -7);
    polynom.set_coeff(1, -5);
    polynom.set_coeff(0, 6);

    cout << "Polynomial: " << polynom << endl;
    cout << endl << "Degree of a polynomial: " << polynom.get_degree() << endl;
    cout << endl << "Requested coefficient: " << polynom.get_coeff(2) << endl;
    cout << endl << "Calculated value: " << polynom.calc(2) << endl;
    cout << endl << "Derivative of a polynomial: " << polynom.derivative() << endl;

    polynom.set_degree(polynom.get_degree() - 1);
    cout << endl << "A new polynomial: " << polynom << endl;
    cout << endl;

    system("PAUSE");
    
}