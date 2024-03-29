#pragma once
#include <string>
#include "console.h"
#include <conio.h>
#include <functional>

class Menu {
private:
  int size;
  std::string* menu;
  int point;

public:
  Menu(int Size, int Item = 0) {
    size = Size;
    point = Item;
    menu = new std::string[size];
    for (int i = 0; i < size; i++)
      menu[i] = "";
  }

  Menu(const Menu& Another) {
    size = Another.size;
    point = Another.point;
    menu = new std::string[size];
    for (int i = 0; i < size; i++)
      menu[i] = Another.menu[i];
  }

  ~Menu() {
    delete[] menu;
  }

  int Get_size() {
    return size;
  }

  void Set_name(int Point, std::string Name) {
    if (Point < 0 || Point >= size)
      return;
    menu[Point] = Name;
  }

  void AddItem(std::string Name) {
    std::string* new_menu = new std::string[size + 1];
    if (new_menu == nullptr) {
      std::cout << "Error allocating memory" << std::endl;
      return;
    }
    for (int i = 0; i < size; i++)
      new_menu[i] = menu[i];
    new_menu[size] = Name;
    size++;
    delete[] menu;
    menu = new_menu;
  }

  void RemoveItem(int Point) {
    if (Point < 0 || Point >= size)
      return;
    std::string* new_menu = new std::string[size - 1];
    if (new_menu == nullptr) {
      std::cout << "Error allocating memory" << std::endl;
      return;
    }
    for (int i = 0, j = 0; i < size; i++) {
      if (i == Point)
        continue;
      new_menu[j] = menu[i];
      j++;
    }
    size--;
    delete[] menu;
    menu = new_menu;
    if (point >= size)
      point = size - 1;
  }

  void Print(int x = 0, int y = 0, std::function<void(int)> callback = nullptr) {
    char ch;
    bool flag = true;
    hidecursor();
    while (flag) {
      for (int i = 0; i < size; i++) {
        if (i == point)
          textcolor(YELLOW);
        else
          textcolor(LIGHTGRAY);
        gotoxy(x, y + i + 1);
        std::cout << i + 1 << ". " << menu[i] << std::endl;
      }
      ch = _getch();
      if (ch == ARROW)
        ch = _getch();
      switch (ch) {
      case UP:
        if (point > 0)
          point--;
        break;
      case DOWN:
        if (point < size - 1)
          point++;
        break;
      case ESCAPE:
        exit(0);
        break;
      case ENTER:
      case SPACE:
      case RIGHT:
        flag = false;
        system("cls");
        gotoxy(x, y);
        if (callback != nullptr)
          callback(point + 1);
        gotoxy(x, y + 1);
        system("PAUSE");
        break;
      }
      system("cls");
    }
  }
};

void myCallback(int selectedItem)
{
  // ��������, ������� ����� ��������� ��� ������ ������������� ������������� ������ ����
  textcolor(LIGHTGRAY);
  std::cout << "You chose menu item " << selectedItem << std::endl;
}