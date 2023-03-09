#include <iostream>
#include <cstdint>

using namespace std;

#define _MY64BITNUMBER_BASE 4294967296   // 2**32

class My64BitNumber
{
private:

    uint32_t first;
    uint32_t second;

    int64_t val64()
    {
        return ((int64_t)(first)*_MY64BITNUMBER_BASE) + second;
    }

    static My64BitNumber from_i64(int64_t i64)
    {
        return My64BitNumber(i64 & 0xFFFFFFFF, (i64 >> 32) & 0xFFFFFFFF);
    }

public:

    My64BitNumber(uint32_t second, uint32_t first)
    {
        this->second = second;
        this->first = first;
    }

    void dump()
    {
        cout << val64();
    }

    My64BitNumber add(My64BitNumber other)
    {
        return from_i64(val64() + other.val64());
    }

    My64BitNumber subtract(My64BitNumber other)
    {
        return from_i64(val64() - other.val64());
    }

    My64BitNumber divide(My64BitNumber other)
    {
        return from_i64(val64() / other.val64());
    }

    My64BitNumber multiply(My64BitNumber other)
    {
        return from_i64(val64() * other.val64());
    }

    My64BitNumber remainder(My64BitNumber other)
    {
        return from_i64(val64() % other.val64());
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    My64BitNumber num1(7, -3);
    My64BitNumber num2(8, 5);

    cout << "Число 1: ";
    num1.dump();
    cout << endl;

    cout << "Число 2: ";
    num2.dump();
    cout << endl;

    cout << endl;
    cout << "Арифметические операции:" << endl;

    cout << "1) 1 + 2: ";
    num1.add(num2).dump();
    cout << endl;

    cout << "2) 1 - 2: ";
    num1.subtract(num2).dump();
    cout << endl;

    cout << "3) 1 * 2: ";
    num1.multiply(num2).dump();
    cout << endl;

    cout << "4) 1 / 2: ";
    num1.divide(num2).dump();
    cout << endl;

    cout << "5) 1 % 2: ";
    num1.remainder(num2).dump();
    cout << endl;

    system("pause");
    return 0;
}