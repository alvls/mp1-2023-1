#include <iostream> 
#include <cmath>
using namespace std;

typedef double (*MathFunction)(double);

class IntegralCalculator {
private:
    MathFunction function; // ������� ��� �������������� 
    double lower_limit, upper_limit; // ������� �������������� 
    int num_segments; // ����� �������� ������ ���������������
    int method; // ����� ����������  

public:
    IntegralCalculator(MathFunction function, double lower_limit, double upper_limit, int num_segments, int method)
        : function(function), lower_limit(lower_limit), upper_limit(upper_limit), num_segments(num_segments), method(method)
    {}

    ~IntegralCalculator()
    {}

    double get_lowerLimit() // ������ ������ ������ ��������������
    {
        return lower_limit;
    }

    double get_upperLimit() // ������ ������� ������ ��������������
    {
        return upper_limit;
    }

    int get_numSegments() // ������ ����� �������� ������ ���������������
    {
        return num_segments;
    }

    int get_method() // ������ ����� ����������
    {
        return method;
    }

    void set_limits(double lower_limit, double upper_limit) // ������ ������� �������������� 
    {
        this->lower_limit = lower_limit;
        this->upper_limit = upper_limit;
    }

    void set_numSegments(int num_segments) // ������ ����� �������� ������ ���������������
    {
        this->num_segments = num_segments;
    }

    void set_method(int method) // ������� ����� ����������
    {
        this->method = method;
    }

    double calculate() // ��������� �������� ��������� ��������� �������
    {
        double rect_width = (upper_limit - lower_limit) / num_segments;
        double sum = 0;
        double x;

        switch (method) {
        case 0:
            // ����� �������������� 
            for (int i = 0; i < num_segments; i++) {
                x = lower_limit + i * rect_width;
                sum += function(x);
            }
            break;

        case 1:
            // ������ �������������� 
            for (int i = 1; i <= num_segments; i++) {
                x = lower_limit + i * rect_width;
                sum += function(x);
            }
            break;

        case 2:
            // ������� �������������� 
            for (int i = 0; i < num_segments; i++) {
                x = lower_limit + (i + 0.5) * rect_width;
                sum += function(x);
            }
            break;
        }

        sum *= rect_width;

        return sum;
    }

    void print() // ������� ��������� ���������� �� �����
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