#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <clocale>
#include <windows.h>
#include "Header.h"
using namespace std;
enum Direction { LEFT, RIGHT, UP, DOWN };




class Field
{
    int width;
    int height;
    char border;
public:
    Field() : Field(40, 20, '#') {}
    Field(int w, int h, char ch) : width(w), height(h), border(ch) {}
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    char getBorder() const { return border; }
};

class Snake
{
    Field f;
    Direction direction;
    char head;
    char tail;
    int x;
    int y;
    int TailX[100];
    int TailY[100];
    int length;
public:
    Snake() : Snake(0, LEFT, 'O', 'o', 0, 0, Field()) {}
    Snake(int l, Direction dir, char hch, char tch, int X, int Y, Field field) : length(l), direction(dir), head(hch), tail(tch), x(X), y(Y), f(field) { }

    Direction getDirection() const { return direction; }
    char getHead() const { return head; }
    char getTail() const { return tail; }
    int getX() const { return x; }
    int getY() const { return y; }
    int getTailX(int index) const { return TailX[index]; }
    int getTailY(int index) const { return TailY[index]; }
    int getLength() const { return length; }
    void grownUp() { length++; }
    void setTailX(int i, int x) { TailX[i] = x; }
    void setTailY(int i, int x) { TailY[i] = x; }
    void setX(int X) { x = X; }
    void setY(int Y) { y = Y; }
};

class Fruit
{
    Field f;
    char fruit;
    int x;
    int y;
public:
    Fruit() : Fruit(1, 1, '@', Field()) {}
    Fruit(int X, int Y, char fch, Field field) : f(field), fruit(fch), x(X), y(Y) {}
    char getFruit() { return fruit; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int X) { x = X; }
    void setY(int Y) { y = Y; }

};

class SnakeGame
{
    enum Mode { EASY, HARD };
    enum Result
    {
        WIN,
        LOSE,
        GAME
    };
    int score;
    int record;
    int finish = INT_MAX;
    Result res = GAME;
    Mode mode;
    Field field;
    Snake snake;
    Fruit fruit;
    Direction dir = snake.getDirection();
public:
    SnakeGame() : snake(Snake()), field(Field()), fruit(Fruit()), mode(HARD) { score = snake.getLength() * 10; }
    SnakeGame(Field f, Snake s, Fruit fr, Mode m) : mode(m), field(f), snake(s), fruit(fr) { score = s.getLength() * 10; }

    void setup()
    {
        srand(time(NULL));
        ifstream f;
        f.open("SnakeRecord.txt");
        if (!f.is_open())
            throw exception("error");
        f >> record;
        f.close();
        fruit.setX(rand() % field.getWidth());
        fruit.setY(rand() % field.getHeight());
        switch (snake.getDirection())
        {
        case LEFT:
            snake.setX(rand() % (field.getWidth() - snake.getLength()));
            snake.setY(rand() % field.getHeight());
            break;
        case RIGHT:
            snake.setX(snake.getLength() + rand() % (field.getWidth() - snake.getLength()));
            snake.setY(rand() % field.getHeight());
            break;
        case DOWN:
            snake.setX(rand() % field.getWidth());
            snake.setY(snake.getLength() + rand() % (field.getWidth() - snake.getLength()));
            break;
        case UP:
            snake.setX(rand() % field.getWidth());
            snake.setY(rand() % (field.getWidth() - snake.getLength()));
            break;
        }
        clrscr();
    }

    void Draw()
    {
        hidecursor();
        clrscr();
        for (int i = 0; i < field.getWidth() + 2; i++)
            cout << field.getBorder();
        cout << endl;
        for (int i = 0; i < field.getHeight(); i++)
        {
            for (int j = 0; j < field.getWidth(); j++)
            {
                if (j == 0)
                    cout << field.getBorder();
                if (i == snake.getY() && j == snake.getX())
                    cout << snake.getHead();
                else if (i == fruit.getY() && j == fruit.getX())
                    cout << fruit.getFruit();
                else
                {
                    bool print = false;
                    for (int k = 0; k < snake.getLength(); k++)
                    {
                        if (snake.getTailX(k) == j && snake.getTailY(k) == i)
                        {
                            cout << snake.getTail();
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }

                if (j == field.getWidth() - 1)
                    cout << field.getBorder();
            }
            cout << endl;
        }
        for (int i = 0; i < field.getWidth() + 2; i++)
            cout << field.getBorder();
        cout << endl;
        cout << "Счёт: " << score << " Рекорд: " << record << endl;
    }

    void Input()
    {

        if (_kbhit())
        {

            switch (_getch())
            {
            case 'a':
            case 'A':
            case 'ф':
            case 'Ф':
                dir = LEFT;
                break;
            case 'd':
            case 'D':
            case 'в':
            case 'В':
                dir = RIGHT;
                break;
            case 'w':
            case 'W':
            case 'ц':
            case 'Ц':
                dir = UP;
                break;
            case 's':
            case 'S':
            case 'ы':
            case 'Ы':
                dir = DOWN;
                break;
            case 'x':
            case 'X':
            case 'ч':
            case 'Ч':
                res = LOSE;
                break;
            }
        }
    }

    void Gameplay()
    {
        int prevPosX = snake.getTailX(0);
        int prevPosY = snake.getTailY(0);
        int prev2PosX, prev2PosY;
        snake.setTailX(0, snake.getX());
        snake.setTailY(0, snake.getY());
        for (int i = 1; i < snake.getLength(); i++)
        {
            prev2PosX = snake.getTailX(i);
            prev2PosY = snake.getTailY(i);
            snake.setTailX(i, prevPosX);
            snake.setTailY(i, prevPosY);
            prevPosX = prev2PosX;
            prevPosY = prev2PosY;
        }
        switch (dir)
        {
        case LEFT:
            snake.setX(snake.getX() - 1);
            break;
        case RIGHT:
            snake.setX(snake.getX() + 1);
            break;
        case UP:
            snake.setY(snake.getY() - 1);
            break;
        case DOWN:
            snake.setY(snake.getY() + 1);
            break;
        default:
            break;
        }

        switch (mode)
        {

        case EASY:
            if (snake.getX() >= field.getWidth())
                snake.setX(0);
            else if (snake.getX() < 0)
                snake.setX(field.getWidth() - 1);
            if (snake.getY() >= field.getHeight())
                snake.setY(0);
            else if (snake.getY() < 0)
                snake.setY(field.getHeight() - 1);
            for (int i = 0; i < snake.getLength(); i++)
                if (snake.getTailX(i) == snake.getX() && snake.getTailY(i) == snake.getY())
                {
                    res = LOSE;
                    NewRecord();
                    End();
                }
            break;
        case HARD:
            if ((snake.getX() >= field.getWidth()) || (snake.getX() < 0) || (snake.getY() >= field.getHeight()) || (snake.getY() < 0))
            {
                res = LOSE;
                NewRecord();
                End();
            }
            for (int i = 0; i < snake.getLength(); i++)
                if (snake.getTailX(i) == snake.getX() && snake.getTailY(i) == snake.getY())
                {
                    res = LOSE;
                    NewRecord();
                    End();
                }
        }

        if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY())
        {
            score += 10;
            if (score >= finish)
            {
                res = WIN;
                NewRecord();
                End();
            }
            fruit.setX(rand() % field.getWidth());
            fruit.setY(rand() % field.getHeight());
            snake.grownUp();
        }

    }

    void NewRecord()
    {
        if (score > record)
        {
            ofstream f;
            f.open("SnakeRecord.txt");
            f << score;
            f.close();
            ifstream fi;
            fi.open("SnakeRecord.txt");
            fi >> record;
            fi.close();
        }

    }

    void Start(int fin)
    {
        if (finish <= score)
        {
            exit(0);
        }
        finish = fin;
        setup();
        while (res == GAME)
        {
            Draw();
            Input();
            Gameplay();
            Sleep(30);
        }
    }
    void Start() { Start(INT_MAX); }


    void End()
    {
        system("cls");
        switch (res)
        {
        case WIN:
            cout << "Вы выиграли" << endl;
            break;
        case LOSE:
            cout << "Вы проиграли" << endl;
            break;
        default:
            break;
        }
        cout << "Ваш счёт: " << score << " Ваш рекорд:  " << record << endl;
        system("PAUSE");
    }

};

void main()
{
    setlocale(LC_ALL, "ru");
    textcolor(GREEN);
    SnakeGame s;
    s.Start();
}