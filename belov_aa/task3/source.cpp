#include <iostream> 
#include <cmath>
using namespace std;

typedef double (*MathFunction)(double);

class IntegralCalculator {
private:
    MathFunction function; // функци€ дл€ интегрировани€ 
    double lower_limit, upper_limit; // пределы интегрировани€ 
    int num_segments; // число отрезков метода пр€моугольников
    int method; // метод вычислени€  

public:
    IntegralCalculator(MathFunction function, double lower_limit, double upper_limit, int num_segments, int method)
        : function(function), lower_limit(lower_limit), upper_limit(upper_limit), num_segments(num_segments), method(method)
    {}

    ~IntegralCalculator()
    {}

    double get_lowerLimit() // узнать нижний предел интегрировани€
    {
        return lower_limit;
    }

    double get_upperLimit() // узнать верхний предел интегрировани€
    {
        return upper_limit;
    }

    int get_numSegments() // узнать число отрезков метода пр€моугольников
    {
        return num_segments;
    }

    int get_method() // узнать метод вычислени€
    {
        return method;
    }

    void set_limits(double lower_limit, double upper_limit) // задать пределы интегрировани€ 
    {
        this->lower_limit = lower_limit;
        this->upper_limit = upper_limit;
    }

    void set_numSegments(int num_segments) // задать число отрезков метода пр€моугольников
    {
        this->num_segments = num_segments;
    }

    void set_method(int method) // выбрать метод вычислени€
    {
        this->method = method;
    }

    double calculate() // вычислить значение интеграла выбранным методом
    {
        double rect_width = (upper_limit - lower_limit) / num_segments;
        double sum = 0;
        double x;

        switch (method) {
        case 0:
            // Ћевые пр€моугольники 
            for (int i = 0; i < num_segments; i++) {
                x = lower_limit + i * rect_width;
                sum += function(x);
            }
            break;

        case 1:
            // ѕравые пр€моугольники 
            for (int i = 1; i <= num_segments; i++) {
                x = lower_limit + i * rect_width;
                sum += function(x);
            }
            break;

        case 2:
            // —редние пр€моугольники 
            for (int i = 0; i < num_segments; i++) {
                x = lower_limit + (i + 0.5) * rect_width;
                sum += function(x);
            }
            break;
        }

        sum *= rect_width;

        return sum;
    }

    void print() // вывести результат вычислени€ на экран
    {
        cout << "The result of calculation is: " << calculate() << endl;
    }
};

int main()
{
    IntegralCalculator integral([](double x) { return cos(x); }, 0, 1, 1000, 0);
    integral.print();
    system("PAUSE");

    return 0;
}