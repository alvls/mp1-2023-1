//hello
#include <iostream>
#include <limits>


const long long LIM = UINT32_MAX;

class LongNumber
{
private:

    // unsigned int - 32-bit

    unsigned int high;
    unsigned int low;

public:

    LongNumber(unsigned int low, unsigned int high) : low(low), high(high) {}
    LongNumber(unsigned int low) : LongNumber(low, 0) {}

    LongNumber& operator =(const LongNumber& other) = default;


    bool operator ==(const LongNumber& other) const
    {
        return low == other.low && high == other.high;
    }

    bool operator !=(const LongNumber& other) const
    {
        return !(*this == other);
    }

    LongNumber operator -() const
    {
        // инвертируем все биты - знак поменяется
        // мы работаем с дополнительным кодом,
        // поэтому прибавим единицу

        return LongNumber(~low, ~high) + 1;
    }

    LongNumber operator +(const LongNumber& other) const
    {
        long long result = (static_cast<long long>(high) + other.high) * LIM
            + (static_cast<long long>(low) + other.low);
        return LongNumber(
            result & 0xFFFFFFFF,
            (result >> 32) & 0xFFFFFFFF
        );
    }

    LongNumber& operator +=(const LongNumber& other)
    {
        long long result = (static_cast<long long>(high) + other.high) * LIM
            + (static_cast<long long>(low) + other.low);

        this->low = result & 0xFFFFFFFF;
        this->high = (result >> 32) & 0xFFFFFFFF;

        return *this;
    }

    LongNumber operator -(const LongNumber& other) const
    {
        return *this + (-other);
    }

    LongNumber& operator -=(const LongNumber& other)
    {
        *this += -other;

        return *this;
    }

    LongNumber operator *(const LongNumber& other) const
    {
        long long result = (static_cast<long long>(high) * LIM + low)
            * (other.high * LIM + other.low);

        return LongNumber(
            result & 0xFFFFFFFF,
            (result >> 32) & 0xFFFFFFFF
        );
    }

    LongNumber& operator *=(const LongNumber& other)
    {
        *this = *this * other;

        return *this;
    }

    LongNumber operator /(const LongNumber& other) const
    {
        long long result = (high * LIM + low)
            / (other.high * LIM + other.low);

        return LongNumber(
            result & 0xFFFFFFFF,
            (result >> 32) & 0xFFFFFFFF
        );
    }

    LongNumber& operator /=(const LongNumber& other)
    {
        *this = *this / other;

        return *this;
    }

    LongNumber operator %(const LongNumber& other) const
    {
        long long result = (high * LIM + low)
            % (other.high * LIM + other.low);

        return LongNumber(
            result & 0xFFFFFFFF,
            (result >> 32) & 0xFFFFFFFF
        );
    }

    LongNumber& operator %=(const LongNumber& other)
    {
        *this = *this % other;

        return *this;
    }

    LongNumber& operator ++() // ++a
    {
        LongNumber result = *this;
        *this += LongNumber(1, 0);
        return result;
    }

    LongNumber operator ++(int) // a++
    {
        return *this + LongNumber(1, 0);
    }

    LongNumber& operator --() // --a
    {
        LongNumber result = *this;
        *this -= LongNumber(1, 0);
        return result;
    }

    LongNumber operator --(int) // a--
    {
        return *this - LongNumber(1, 0);
    }

    friend std::ostream& operator <<(std::ostream& os, const LongNumber& n)
    {
        os << (static_cast<long long>(n.high) * LIM) + n.low;
        return os;
    }
    
    static void print_result(LongNumber num1, LongNumber num2)
    {
        std::cout << "Number 1: " << num1 << std::endl;
        std::cout << "Number 2: " << num2 << std::endl;
        std::cout << std::endl;
        std::cout << "Number 1 + Number 2: " << num1 + num2 << std::endl;
        std::cout << "Number 1 - Number 2: " << num1 - num2 << std::endl;
        std::cout << "Number 1 * Number 2: " << num1 * num2 << std::endl;
        std::cout << "Number 1 / Number 2: " << num1 / num2 << std::endl;
        std::cout << "Number 1 % Number 2: " << num1 % num2 << std::endl;
    }
};



int main()
{
    LongNumber num1(4, 8);
    LongNumber num2(9, -6);
    LongNumber :: print_result(num1, num2);
    system("PAUSE");
    return 0;
}