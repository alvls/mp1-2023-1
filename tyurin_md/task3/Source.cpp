#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include "Header.h"
#include <windows.h>
#include <cmath>
#include <memory>

using namespace std;
SMALL_RECT window;
COORD buf;
typedef double(*pointFunc)(double);

enum KEYS {
   UP = 72, DOWN = 80, ENTER = 13, LEFT = 75
};

enum  Menu{
   Set_function = 0, Set_integration_limits = 1, Find_limits_integration = 2, Set_number_segments = 3, Select_calculation_method = 4, Calculate_value_integral = 5, EXIT = 6
};

enum  math_functions {
   Line = 0, Sin = 1, Cos = 2, Exp = 3, Tan = 4, Atan = 5, Sqrt = 6
};

enum  sol_methods {
   method_left_rectangles = 0, method_right_rectangles = 1, method_medium_rectangles = 2
};

char Menu[7][50] = {
   "Задать текущую функцию",
   "Задать пределы интегрирования",
   "Узнать пределы интегрирования",
   "Задать число отрезков метода прямоугольников",
   "Выбрать метод вычисления",
   "Вычислить значение интеграла",
   "Выход"
};

char Menu_2[7][30] = {
   "line",
   "sin",
   "cos",
   "exp",
   "tan",
   "atan",
   "sqrt"
};

char Menu_3[3][50] = {
   "Метод левых прямоугольников",
   "Метод правых прямоугольников",
   "Метод средних прямоугольников"
};

int active_menu = 0, active_menu_2 = 0, active_menu_3 = 0;
#define SIZE 8
#define SIZE_2 7
#define SIZE_3 3

double line(double x) {
   return x;
}

class integral
{
public:

   integral()
   {
      segments = 1;
      value = 0;
      lim_a = 0;
      lim_b = 1;
      method = method_left_rectangles;
      function = line;
   }

   void set_function(pointFunc func) {
      function = func;
   }

   void set_limits(double a, double b) {
      lim_a = a;
      lim_b = b;
   }

   double get_lim_a() {
      return lim_a;
   }

   double get_lim_b() {
      return lim_b;
   }

   void set_segments(int seg) {
      segments = seg;
   }

   void set_method(sol_methods met) {
      method = met;
   }

   void get_value() {

      double a = lim_a;
      double h = (lim_b - lim_a) / segments;

      value = 0;

      switch (method)
      {
      case method_left_rectangles:
         for (int i = 0; i < segments; i++) {
            value += function(a + i * h);
         }
         value *= h;
         break;
      case method_right_rectangles:
         a += h;
         for (int i = 0; i < segments; i++) {
            value += function(a + i * h);
         }
         value *= h;
         break;
 
      case method_medium_rectangles:

         for (int i = 0; i < segments; i++) {
            value += function(a+h/2 + i * h);
         }
         value *= h;
         break;
      }
   }

   void Print() {
      cout << "Ответ: " << value << endl;
   }

private:
   int segments;
   double value;
   double lim_a;
   double lim_b;
   sol_methods method;
   pointFunc function;
};


void main()
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Интеграл");
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   int variable_x;
   char ch;
   clrscr();
   variable_x = (window.Left + window.Right) / 30;
   textcolor(MAGENTA);
   gotoxy(variable_x + 25, wherey() + 10);
   cout << "Добро пожаловать в программу, которая работает c \"Интегралами\"\n\n" << endl;
   gotoxy(variable_x + 35, wherey() + 1);
   system("pause");

   sol_methods method_selection = method_medium_rectangles;
   pointFunc func_selection = line;
   int flag = 0, seg;
   double a, b;

   integral integ;

   while (1) {
      hidecursor();
      system("cls");
      for (int i = 0; i < SIZE; i++) {
         if (i == active_menu)
            textcolor(GREEN);
         else
            textcolor(YELLOW);
         cout << Menu[i] << "\n";
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
         case Set_function:
            flag = 1;
            while (flag) {
               system("cls");
               for (int i = 0; i < SIZE_2; i++) {
                  if (i == active_menu_2)
                     textcolor(GREEN);
                  else
                     textcolor(YELLOW);
                  cout << Menu_2[i] << "\n";
               }
               ch = _getch();
               if (ch == -32)
                  ch = _getch();

               switch (ch)
               {
               case UP:
                  if (active_menu_2 > 0)
                     active_menu_2--;
                  break;
               case DOWN:
                  if (active_menu_2 < SIZE_2 - 1)
                     active_menu_2++;
                  break;
               case LEFT:
                  flag = 0;
                  break;
               case ENTER:
                  switch (active_menu_2)
                  {
                  case Line:
                     func_selection = line;
                     break;

                  case Sin:
                     func_selection = sin;
                     break;

                  case Cos:
                     func_selection = cos;
                     break;

                  case Exp:
                     func_selection = exp;
                     break;

                  case Tan:
                     func_selection = tan;
                     break;

                  case Atan:
                     func_selection = atan;
                     break;

                  case Sqrt:
                     func_selection = sqrt;
                     break;

                  }
                  integ.set_function(func_selection);
                  flag = 0;
               }
            }
            break;

         case Set_integration_limits:

            cout << "Введите нижний предел интегрирования: ";
            cin >> a;
            cout << "\nВведите верхний предел интегрирования: ";
            cin >> b;
            integ.set_limits(a, b);
            break;

         case Find_limits_integration:

            cout << "Нижний предел интегрирования: " << integ.get_lim_a() << endl;
            cout << "Верхний предел интегрирования: " << integ.get_lim_b() << endl;
            system("pause");
            break;

         case Set_number_segments:
            cout << "Введите число отрезков метода прямоугольников: ";
            cin >> seg;
            integ.set_segments(seg);

            break;

         case Select_calculation_method:
            flag = 1;
            while (flag) {
               system("cls");
               for (int i = 0; i < SIZE_3; i++) {
                  if (i == active_menu_3)
                     textcolor(GREEN);
                  else
                     textcolor(YELLOW);
                  cout << Menu_3[i] << "\n";
               }
               ch = _getch();
               if (ch == -32)
                  ch = _getch();

               switch (ch)
               {
               case UP:
                  if (active_menu_3 > 0)
                     active_menu_3--;
                  break;
               case DOWN:
                  if (active_menu_3 < SIZE_3 - 1)
                     active_menu_3++;
                  break;
               case LEFT:
                  flag = 0;
                  break;
               case ENTER:
                  switch (active_menu_3)
                  {
                  case method_left_rectangles:
                     method_selection = method_left_rectangles;
                     break;

                  case method_right_rectangles:
                     method_selection = method_right_rectangles;
                     break;

                  case method_medium_rectangles:
                     method_selection = method_medium_rectangles;
                     break;

                  }
                  integ.set_method(method_selection);
                  flag = 0;
               }
            }   
            break;

         case Calculate_value_integral:
            integ.get_value();
            integ.Print();
            system("pause");
            break;

         case EXIT:
            exit(0);
            break;
           
         }
      }
   }
}