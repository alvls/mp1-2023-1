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
   show_polynomial = 0, degree_of_the_polynomial = 1, coefficient_value = 2, value_polynomial = 3, derivative_polynomial = 4, Change = 5, EXIT = 6
};

char Menu[7][50] = {
   "�������� �������",
   "������ ������� ��������",
   "������ �������� ������������ �� ��� ������",
   "��������� �������� �������� � �������� ����� �",
   "����� ����������� ��������",
   "����� ��������",
   "�����"
};
int active_menu = 0;
#define SIZE 7

class polinom
{
public:

   polinom(int deg)
   {
      degree = deg;
   }

   int get_degree()              //  ������� ��������
   {
      return degree;
   }

   void set_degree(int deg)
   {
      degree = deg;
   }

   double get_coef(int ind)     //  �������� ����. �� ������
   {
      return pol[ind];
   }

   void set_coef(double cf, int ind)
   {
      pol[ind] = cf;
   }

   double get_value(double x)                   // ��������� �������� �������� � �������� ����� �
   {
      double answ = 0;
      for (int m = 0; m <= degree; m++)
      {
         answ += pol[m] * double(pow(x, m));
      }
      return answ;
   }

   polinom derivative_pol()                      // ���������� �����������
   {
      polinom der(degree - 1);

      for (int m = 1; m <= degree; m++)
      {
         der.set_coef(pol[m] * m, m - 1);
      }
      return der;
   }

   void Print()                          // ����� ��������
   {
      if (degree == 1)
      {
         if (pol[1] == 1)
            cout << "x";
         else if (pol[1] != 0)
            cout << noshowpos << pol[1] << "x";
         if (pol[0] != 0)
            cout << showpos << pol[0];
      }

      else if (degree > 1)
      {
         if (pol[degree] == 1)
            cout << noshowpos << "x^" << degree;
         else
            cout << noshowpos << pol[degree] << "x^" << degree;

         for (int m = degree - 1; m > 1; m--)
         {
            cout << showpos << pol[m] << noshowpos<< "x^" << m;
         }

         cout << showpos << pol[1] << "x";
         cout << showpos << pol[0];
      }
      else
         cout << pol[0];
   }

   
private:

   double pol[13] = {0};
   int degree;

};


void main()
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("�������");
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
   cout << "����� ���������� � ���������, ������� �������� c \"���������\"\n\n" << endl;
   gotoxy(variable_x, wherey() + 1);
   cout << "���������� ������ ������� �������� � ������������ ������� ��������, � ����� ������� ���� �� ������������ ��������\n\n" << endl;
   gotoxy(variable_x + 30, wherey() + 1);
   cout << "������� ������������ ���������� � ������� �������\n\n" << endl;
   gotoxy(variable_x + 35, wherey() + 1);
   system("pause");

start:
   int deg, x, tmp_deg, tmp_ind;
   double cf, tmp_coef, rez;

   polinom poly(0);
   polinom deriv(0);


   textcolor(MAGENTA);
   system("cls");
   do
   {
      system("cls");
      cout << "������� ������� ��������: ";
      cin >> deg;
   } while (deg < 0 || deg > 12);
   poly.set_degree(deg);

   system("cls");
   for (int i = 0; i <= deg; i++)
   {  
      do
      {
         system("cls");
         cout << "������� ����������� ��� " << noshowpos << i + 1 << " ������: ";
         cin >> cf;
      } while (cf == 0);
      poly.set_coef(cf, i);
      system("cls");
   }
  
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
         switch (active_menu)
         {
         case show_polynomial:
            system("cls");
            cout << "�������: ";
            poly.Print();
            cout << endl;
            system("pause");
            break;

         case degree_of_the_polynomial :
            system("cls");
            tmp_deg = poly.get_degree();
            cout << "������� ��������: " << noshowpos << tmp_deg << endl;
            system("pause");
            break;

         case coefficient_value:
            do
            {
               system("cls");
               cout << "������� ����� ������������(������� � 1): ";         // ��� �������� ���������� � 1, � �� � 0
               cin >> tmp_ind;
            } while (tmp_ind < 0 || tmp_ind > deg + 1);
            tmp_ind -= 1;
            system("cls");
            tmp_coef = poly.get_coef(tmp_ind);
            cout << "����������� = " << noshowpos << tmp_coef << endl;
            system("pause");
            break;

         case value_polynomial:
            system("cls");
            cout << "������� �������� x: ";
            cin >> x;
            system("cls");
            rez = poly.get_value(x);
            cout << "���������: " << noshowpos << rez << endl;
            system("pause");
            break;

         case derivative_polynomial:
            deriv = poly.derivative_pol();
            system("cls");
            cout << "����������� ��������: ";
            deriv.Print();
            cout << endl;
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
   }
}
