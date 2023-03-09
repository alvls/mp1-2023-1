#include <iostream>
#include <limits>

const long long limit = 0xffffffff + (long long)(1);

class my_long
{
  unsigned int up;
  unsigned int down;
public:
  my_long(unsigned int down, unsigned int up)
  {
    this->down = down;
    this->up = up;
  }

  my_long(unsigned int down)
  {
    this->down = down;
    this->up = 0;
  }

  my_long reverse() const
  {
    return my_long(~down, ~up).plus(1);
  }

  my_long minus(const my_long& number)
  {
    return this->plus(number.reverse());
  }

  my_long plus(const my_long& number)
  {
    long long result = ((long long)(up)+number.up) * limit + ((long long)(down)+number.down);
    return my_long(result & ~0, (result >> 32) & ~0);
  }

  my_long multiple(const my_long& number)
  {
    long long result = (number.up * limit + number.down) * ((long long)(up)*limit + down);
    return my_long(result & ~0, (result >> 32) & ~0);
  }

  my_long int_divide(const my_long& number)
  {
    long long result = (up * limit + down) % (number.up * limit + number.down);
    return my_long(result & ~0, (result >> 32) & ~0);
  }

  my_long divide(const my_long& number)
  {
    long long result = (up * limit + down) / (number.up * limit + number.down);
    return my_long(result & ~0, (result >> 32) & ~0);
  }

  friend std::ostream& operator << (std::ostream& os, const my_long& number)
  {
    os << ((long long)(number.up) * limit) + number.down;
    return os;
  }

  void print()
  {
    std::string cod_up = "", cod_down = "", cod = "";
    unsigned int start = up, end = down;
    int space = 0;
    while (start > 0)
    {
      if (cod_up.length() % 5 == 0)
      {
        cod_up = " " + cod_up;
        space++;
      }
      if (start % 2 == 0)
        cod_up = "0" + cod_up;
      else
        cod_up = "1" + cod_up;
      start /= 2;
    }
    while (cod_up.length() < 32 + space)
    {
      if (cod_up.length() % 5 == 0)
      {
        cod_up = " " + cod_up;
        space++;
      }
      cod_up = "0" + cod_up;
    }

    space = 0;
    while (end > 0)
    {
      if (cod_down.length() % 5 == 0)
      {
        cod_down = " " + cod_down;
        space++;
      }
      if (end % 2 == 0)
        cod_down = "0" + cod_down;
      else
        cod_down = "1" + cod_down;
      end /= 2;
    }
    while (cod_down.length() < 32 + space)
    {
      if (cod_down.length() % 5 == 0)
      {
        cod_down = " " + cod_down;
        space++;
      }
      cod_down = "0" + cod_down;
    }
    std::cout << "\nNumber is equal: " << ((long long)(up)*limit) + down << "\n" << cod_up + " <- up\n" + cod_down << " <- down\n";
  }
};

int main()
{
  my_long digit_1(4294967295, 2147483647);
  my_long digit_2(2325815940, 2325815940);

  digit_1.print();
  digit_2.print();

  digit_1.plus(digit_2).print();
  digit_1.minus(digit_2).print();
  digit_1.multiple(digit_2).print();
  digit_1.divide(digit_2).print();
  digit_1.int_divide(digit_2).print();
  system("pause");
  return 0;
}