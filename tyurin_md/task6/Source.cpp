#include <iostream>
#include <locale>
#include <string>
#include <conio.h>
#include "Header.h"
#include <windows.h>
#include <vector>
#include <fstream>

using namespace std;
SMALL_RECT window;
COORD buf;

enum Direction_Keys {
   UP = 72, DOWN = 80, ENTER = 13, LEFT = 75, RIGHT = 77
};

enum  Menu {
   Changing_speed_snake = 0, Changing_size_snake = 1, Changing_size_field = 2, Start_the_game = 3, EXIT = 4
};
enum  Menu_1 {
   Start_over = 0, Exit_menu = 1
};

char Menu[5][50] = {
   "Сменить скорость змейки",
   "Сменить размер змейки",
   "Сменить размеры игрового поля",
   "Начать игру",
   "Выход"
};
char Menu_1[2][50] = {
   "Начать заново",
   "Выйти в меню"
};

int active_menu = 0, active_menu_1 = 0;
#define SIZE 5
#define SIZE_1 2
#define Size_start 5

class Playing_field
{
public:
   Playing_field(int w = 0, int h = 0) : Width(w), Height(h) { }

   void Show_Walls()
   {
      textcolor(RED);
      for (size_t i = 0; i < Height; i++)
      {
         for (size_t j = 0; j < Width; j++)
         {
            if (i == 0 || i == Height - 1)
               cout << "#";
            else if (j == 0 || j == Width - 1)
               cout << "#";
            else
               cout << " ";
         }
         cout << endl;
      }
   }
   int Get_Height() { return Height; }
   int Get_Width() { return Width; }
   void Set_Width(int w) { Width = w; }
   void Set_Height(int h) { Height = h; }

private:
   int Height;
   int Width;
};

struct Coord
{
   int X;
   int Y;
   bool operator==(Coord ot)
   {
      if (X == ot.X && Y == ot.Y)
         return true;
      else
         return false;
   }
};

class Food
{
public:
   Food(Coord _Coord_Food) : Coord_Food(_Coord_Food) { }

   Food(int x, int y)
   {
      Coord_Food.X = x;
      Coord_Food.Y = y;
   }

   Coord Get_Coord_Food() { return Coord_Food; }

   void Show_food()
   {
      gotoxy(Coord_Food.X, Coord_Food.Y);
      cout << "*";
   }

private:
   Coord Coord_Food;
};

class Snake
{
public:
   Snake(int x = 0, int y = 0) : Dir_Snake(LEFT)
   {
      Coord tmp = { x, y };
      for (size_t i = 0; i < Size_start; i++)
      {
         if (snake.empty())
            snake.push_back(tmp);
         else
            snake.push_back(tmp);
         tmp.X = tmp.X + 1;
      }
   }

   Coord Get_head_coord() { return snake[0]; }
   Direction_Keys Get_snake_dir() { return Dir_Snake; }
   void Set_snake_Dir(Direction_Keys _Dir_Snake) { Dir_Snake = _Dir_Snake; }
   vector<Coord> Get_snake() { return snake; }

   void Snake_show()
   {
      for (size_t i = 0; i < snake.size(); i++)
      {
         gotoxy(snake[i].X, snake[i].Y);
         if (i == 0)
         {
            textcolor(MAGENTA);
            cout << "0";
            continue;
         }
         else
         {
            textcolor(YELLOW);
            cout << "о";
         }
      }
   }
   void Snake_move()
   {
      switch (Dir_Snake)
      {
      case LEFT:
         Change_snake_pos(-1, 0);
         break;
      case RIGHT:
         Change_snake_pos(1, 0);
         break;
      case DOWN:
         Change_snake_pos(0, 1);
         break;
      case UP:
         Change_snake_pos(0, -1);
         break;
      }
   }
   void Snake_hide()
   {
      for (size_t i = 0; i < snake.size(); i++)
      {
         gotoxy(snake[i].X, snake[i].Y);
         cout << " ";
      }
   }
   void Push_last_part(Coord last_part) { snake.push_back(last_part); }

private:
   Direction_Keys Dir_Snake;
   vector<Coord> snake;
   void Change_snake_pos(int X, int Y)
   {
      Coord last_coord = snake[snake.size() - 1];
      Coord tmp = { snake[0].X + X, snake[0].Y + Y };
      snake.insert(snake.begin(), tmp);
      snake.pop_back();
   }
};

class Game
{
public:
   Game(int _Snake_Size, int _Speed, int w, int h)
   {
      Snake_Size = _Snake_Size;
      Speed = _Speed;
      Playing_field tmp_field(w, h);
      field = tmp_field;
      Snake tmp_snake(field.Get_Width() / 2, field.Get_Height() / 2);
      snake = tmp_snake;
      win_status = false;
      Score = 0;
   }

   int Get_Score() { return Score; }
   bool Get_res() { return win_status; }

   void new_attempt() 
   { 
      Score = 0; 
      snake.Set_snake_Dir(LEFT);
      win_status = false;
      all_Food.clear();
   }

   void Changing_Size_Field(int w, int h)
   {
      field.Set_Width(w);
      field.Set_Height(h);
   }

   void Changing_Size_Field(int s){ Snake_Size = s; }
   void Changing_Speed_Snake(int speed) { Speed = speed; }

   void Start_Game()
   {
      int ch = 0;
      int width = field.Get_Width();
      int height = field.Get_Height();

      srand(time(NULL));

      Snake tmp_snake(field.Get_Width() / 2, field.Get_Height() / 2);
      snake = tmp_snake;

      for (size_t i = 0; i < Snake_Size; i++)
      {
         Food tmp = { rand() % (width - 3) + 1, rand() % (height - 3) + 1 };
         all_Food.push_back(tmp);
      }

      field.Show_Walls();
      cout << endl;
      textcolor(YELLOW);
      cout << "Счет: " << Score << endl;
      snake.Snake_show();
      ShowFood();
      snake.Snake_hide();

      while (1)
      {
         while (!_kbhit())
         {
            EatFood();

            if (Score == (Snake_Size - 5) * 50)
            {
               win_status = true;
               return;
            }

            if (Bounds_check(width, height))
               return;

            if (Collision_check())
               return;

            snake.Snake_move();
            snake.Snake_show();
            Sleep(Speed);
            snake.Snake_hide();
         }

         ch = _getch();

         switch (ch)
         {
         case RIGHT:
            if (snake.Get_snake_dir() != LEFT)
               snake.Set_snake_Dir(RIGHT);
            break;
         case DOWN:
            if (snake.Get_snake_dir() != UP)
               snake.Set_snake_Dir(DOWN);
            break;
         case LEFT:
            if (snake.Get_snake_dir() != RIGHT)
               snake.Set_snake_Dir(LEFT);
            break;
         case UP:
            if (snake.Get_snake_dir() != DOWN)
               snake.Set_snake_Dir(UP);
            break;
         }
      }
   }

private:
   vector <Food> all_Food;
   Playing_field field;
   Snake snake;
   bool win_status;
   int Speed;
   int Score;
   int Food_ind;
   int Snake_Size;

   void EatFood()
   {
      vector<Coord> tmp = snake.Get_snake();
      if (all_Food[Food_ind].Get_Coord_Food() == tmp[0])
      {
         Direction_Keys tmp_dir = snake.Get_snake_dir();
         Coord lastPart = tmp[tmp.size() - 1];
         switch (tmp_dir)
         {
         case LEFT:
            lastPart.X += 1;
            break;
         case RIGHT:
            lastPart.X -= 1;
            break;
         case UP:
            lastPart.Y += 1;
            break;
         case DOWN:
            lastPart.Y -= 1;
            break;
         }
         Score += 50;
         snake.Push_last_part(lastPart);
         Food_ind = rand() % all_Food.size();
         ShowFood();
         gotoxy(0, field.Get_Height() + 1);
         cout << "Счет: " << Score << endl;
      }
   }
   void ShowFood()
   {
      vector<Coord> tmp = snake.Get_snake();
      bool _exit = true;
      while (1)
      {
         for (size_t i = 0; i < tmp.size(); i++)
         {
            if (all_Food[Food_ind].Get_Coord_Food() == tmp[i])
            {
               Food_ind = rand() % all_Food.size();
               _exit = false;
               break;
            }
         }
         if (_exit == true)
            break;
         _exit = true;
      }
      all_Food[Food_ind].Show_food();
   }
   bool Bounds_check(const int& w, const int& h)
   {
      Coord tmp = snake.Get_head_coord();
      if (tmp.X < 1 || tmp.X > w - 2 || tmp.Y < 1 || tmp.Y > h - 2)
         return true;
      else
         return false;
   }
   bool Collision_check()
   {
      vector<Coord> tmp = snake.Get_snake();
      for (size_t i = 1; i < tmp.size(); i++)
      {
         if (tmp[0] == tmp[i])
            return true;
      }
      return false;
   }
};

void main()
{
   setlocale(LC_ALL, "Russian");
   system("chcp 1251");
   SetConsoleTitle("Змейка");
   setwindow(170, 70);
   SMALL_RECT window;
   COORD buf;
   getwindow(&window, &buf);

   int variable_x;
   char ch;
   clrscr();
   variable_x = (window.Left + window.Right) / 30;
   textcolor(MAGENTA);
   gotoxy(variable_x + 45, wherey() + 5);
   cout << "Добро пожаловать в игру \"Змейка\"\n\n" << endl;
   gotoxy(variable_x + 35, wherey() + 1);
   cout << "Вам необходимо задать необходимые параметры для игры,\n\n" << endl;
   gotoxy(variable_x + 45, wherey());
   cout << "после чего можно приступать к ней \n\n" << endl;
   gotoxy(variable_x + 42, wherey());
   system("pause");

   int Snake_size = 0, Width = 0, Height = 0, Speed = 0, flag = 0, score = 0;
   bool status, _ex = true;


   textcolor(MAGENTA);
   system("cls");

   do
   {
      system("cls");
      gotoxy(variable_x + 20, wherey() + 5);
      cout << "Введите скорость змейки, чем больше значение, тем меньше скорость(от 100 до 400): ";
      cin >> Speed;
      cout << endl;
   } while (Speed < 100 || Speed > 400);

   do
   {
      gotoxy(variable_x + 20, wherey() + 1);
      cout << "Введите размер змейки, при котором завершится игра(не меньше 6): ";
      cin >> Snake_size;
      cout << endl;
   } while (Snake_size < 6);

   do
   {
      gotoxy(variable_x + 20, wherey() + 1);
      cout << "Введите высоту игрового поля(от 10 до 25): ";
      cin >> Height;
      cout << endl;
   } while (Height < 10 || Height > 25);

   do
   {
      gotoxy(variable_x + 20, wherey() + 1);
      cout << "Введите ширину игрового поля(от 50 до 120): ";
      cin >> Width;
      cout << endl;
   } while (Width < 50 || Width > 120);

   Game game(Snake_size, Speed, Width, Height);

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
         switch(active_menu)
         {
         case Changing_speed_snake:
            do
            {
               textcolor(MAGENTA);
               system("cls");
               gotoxy(variable_x + 20, wherey() + 10);
               cout << "Введите скорость змейки, чем больше значение, тем меньше скорость(от 100 до 400): ";
               cin >> Speed;
               cout << endl;
            } while (Speed < 100 || Speed > 400);
            game.Changing_Speed_Snake(Speed);
            break;

         case Changing_size_snake:
            do
            {
               textcolor(MAGENTA);
               system("cls");
               gotoxy(variable_x + 30, wherey() + 10);
               cout << "Введите размер змейки, при котором завершится игра(не меньше 6): ";
               cin >> Snake_size;
               cout << endl;
            } while (Snake_size < 6);
            game.Changing_Size_Field(Snake_size);
            break;

         case Changing_size_field:
            do
            {
               textcolor(MAGENTA);
               system("cls");
               gotoxy(variable_x + 30, wherey() + 10);
               cout << "Введите высоту игрового поля(от 10 до 25): ";
               cin >> Height;
               cout << endl;
            } while (Height < 10 || Height > 25);
            do
            {
               system("cls");
               gotoxy(variable_x + 30, wherey() + 10);
               cout << "Введите ширину игрового поля(от 50 до 120): ";
               cin >> Width;
               cout << endl;
            } while (Width < 50 || Width > 120);
            game.Changing_Size_Field(Width, Height);
            break;

         case Start_the_game:
            _ex = true;
            while (_ex)
            {
               system("cls");
               game.Start_Game();
               status = game.Get_res();
               score = game.Get_Score();
               system("cls");
               textcolor(MAGENTA);
               if (status)
               {
                  gotoxy(variable_x + 42, wherey() + 7);
                  cout << "Поздравляем, вы выиграли!!!";
                  gotoxy(variable_x + 42, wherey() + 1);
                  cout << "Ваш счет: " << score << "\n";

               }
               else
               {
                  gotoxy(variable_x + 42, wherey() + 7);
                  cout << "Вы проиграли, попробуйте еще раз";
                  gotoxy(variable_x + 42, wherey() + 1);
                  cout << "Ваш счет: " << score << "\n";
               }
               gotoxy(variable_x + 42, wherey() + 1);
               system("pause");
               flag = 1;
               while (flag) {
                  system("cls");
                  for (int i = 0; i < SIZE_1; i++) {
                     if (i == active_menu_1)
                        textcolor(GREEN);
                     else
                        textcolor(YELLOW);
                     cout << Menu_1[i] << "\n";
                  }
                  ch = _getch();
                  if (ch == -32)
                     ch = _getch();

                  switch (ch)
                  {
                  case UP:
                     if (active_menu_1 > 0)
                        active_menu_1--;
                     break;
                  case DOWN:
                     if (active_menu_1 < SIZE_1 - 1)
                        active_menu_1++;
                     break;
                  case ENTER:
                     switch (active_menu_1)
                     {
                     case Start_over:
                        flag = 0;
                        game.new_attempt();
                        break;

                     case Exit_menu:
                        game.new_attempt();
                        _ex = false;
                        flag = 0;
                        break;

                     }
                  }
               }
            }
            break;

         case EXIT:
            exit(0);
            break;

         }
      }
   }
}