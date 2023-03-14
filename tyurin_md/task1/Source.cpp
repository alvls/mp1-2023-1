#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include  "Header.h"
#include <windows.h>

using namespace std;

SMALL_RECT window;
COORD buf;

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13
};

enum Sorting_Selection {
   Addition = 0, Subtraction = 1, Multiplication = 2, Division = 3, Change = 4, EXIT = 5
};

char Menu[6][30] = {
   "Сложение",
   "Вычитание",
   "Умножение",
   "Деление",
   "Смена дробей",
   "Выход"
};
int active_menu = 0;
#define SIZE 6

class rational_function 
{
public:

   void Print_fraction()
   {
      cout << "Дробь: " << numerator << "/" << denominator << endl;
   }

   void Set_fraction(long num, unsigned long den)
   {
      numerator = num;
      denominator = den;
   }

   rational_function(long a, unsigned long b)
   {
      numerator = a;
      denominator = b;
      Simplify();
   }

   void Sum(rational_function fraction)
   {
      long num = fraction.numerator;
      unsigned long den = fraction.denominator;
      
      numerator *= den;
      num *= denominator;
      denominator *= den;
      numerator += num;
      Simplify();
   }

   void Dif(rational_function fraction)
   {
      long num = fraction.numerator;
      unsigned long den = fraction.denominator;

      numerator *= den;
      num *= denominator;
      denominator *= den;
      numerator -= num;
      Simplify();
   }

   void Mult(rational_function fraction)
   {
      long num = fraction.numerator;
      unsigned long den = fraction.denominator;

      numerator *= num;
      denominator *= den;
      Simplify();
   }

   int Div(rational_function fraction)
   {
      long num = fraction.numerator;
      long den = long(fraction.denominator);
      unsigned long tmp_num;

      if (num < 0)
      {
         num *= -1;
         den *= -1;
      }

      tmp_num = unsigned(num);

      if (tmp_num == 0)
         return 0;

      numerator *= den;
      denominator *= tmp_num;
      Simplify();
      return 1;
   }

private:
   long numerator;
   unsigned long denominator;

   unsigned long NOD(unsigned long num, unsigned long dem) 
   {
      if (num % dem == 0)
         return dem;
      if (dem % num == 0)
         return num;
      if (num > dem)
         return NOD(num % dem, dem);
      return NOD(num, dem % num);

   }

   void Simplify()
   {
      unsigned long Nod, tmp_num;

      if (numerator == 0)      // дробь 0/1
      {
         denominator = 1;
         return;
      }

      else if (numerator < 0)
         tmp_num = numerator * (-1);

      else
         tmp_num = numerator;

      Nod = NOD(tmp_num, denominator);
      numerator = numerator / long(Nod);
      denominator = denominator / Nod;
   }
};

void main() 
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Рациональная дробь");
   textbackground(BLACK);
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   int variable_x;
   char ch;
   clrscr();
   variable_x = (window.Left + window.Right) / 30;
   textcolor(MAGENTA);
   gotoxy(variable_x + 25, wherey() + 5);
   cout << "Добро пожаловать в программу, которая работает c \"Рациональными дробями\"\n\n" << endl;
   gotoxy(variable_x + 20, wherey() + 1);
   cout << "Необходимо ввести данные 2 дробей, а затем выбрать одну из предложенных операций\n\n" << endl;
   gotoxy(variable_x + 35, wherey() + 1);
   system("pause");

start:
   unsigned long den_1 =1, den_2 = 1;
   long num_1 = 0, num_2 = 0;
   int check;

   textcolor(MAGENTA);
   system("cls");
   cout << "Введите числитель первой дроби: ";
   cin >> num_1;
   system("cls");
   do
   {
      system("cls");
      cout << "Введите знаменатель первой дроби: ";
      cin >> den_1;
   } while (den_1 == 0);
   system("cls");
   rational_function fraction_1(num_1, den_1);

   cout << "Введите числитель второй дроби: ";
   cin >> num_2;
   system("cls");
   do
   {
      system("cls");
      cout << "Введите знаменатель второй дроби: ";
      cin >> den_2;
   } while (den_2 == 0);
   system("cls");
   rational_function fraction_2(num_2, den_2);

   while (1) {
      hidecursor();
      system("cls");
      for (int i = 0; i < SIZE; i++) {
         if (i == active_menu)
            textcolor(GREEN);
         else
            textcolor(YELLOW);
         printf("%s\n", Menu[i]);
      }
      ch = _getch();
      if (ch == -32)
         ch = _getch();

      switch (ch)
      {
      case UP:
         if (active_menu > 0)
            active_menu--;
         break;
      case DOWN:
         if (active_menu < SIZE - 1)
            active_menu++;
         break;
      case ENTER:
         system("cls");
         switch (active_menu)
         {
         case Addition:
            fraction_1.Sum(fraction_2);
            fraction_1.Print_fraction();
            system("pause");
            break;

         case Subtraction:
            fraction_1.Dif(fraction_2);
            fraction_1.Print_fraction();
            system("pause");
            break;

         case Multiplication:
            fraction_1.Mult(fraction_2);
            fraction_1.Print_fraction();
            system("pause");
            break;

         case Division:
            check = fraction_1.Div(fraction_2);
            if (check == 0)
            {
               system("cls");
               textcolor(RED);
               cout << "Нельзя делить на ноль" << endl;
            }
            else
               fraction_1.Print_fraction();
            system("pause");
            break;

         case Change:
            goto start;
            break;

         case EXIT:
            exit(0);
            break;
         }
      }
      fraction_1.Set_fraction(num_1, den_1);
   }
}