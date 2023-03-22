#include <iostream>
#include <string>
#include "console.h"
#include <conio.h>

class Menu
{
private:
	int size;
	std::string* menu;
	int point;
public:
	Menu(int Size, int Item = 0)
	{
		size = Size;
		point = Item;
		menu = new std::string[size];
		for (int i = 0; i < size; i++)
			menu[i] = "";
	}
	Menu(Menu& Another)
	{
		size = Another.size;
		point = Another.point;
		for (int i = 0; i < size; i++)
			menu[i] = Another.menu[i];
	}
	~Menu() 
	{ 
		delete[] menu;
	}
	void Set_size(int Size) 
	{ 
		size = Size; 
	}
	int Get_size() 
	{ 
		return size; 
	}
	void Set_name(int Point, std::string Name) 
	{ 
		menu[Point] = Name; 
	}
	void Print(int x = 0, int y = 0)
	{
		char ch;
		bool flag = true;
		while (flag)
		{
			for (int i = 0; i < size; i++)
			{
				if (i == point)
					textcolor(GREEN);
				else
					textcolor(LIGHTGRAY);
				gotoxy(x, y + i + 1);
				std::cout << i + 1 << ". " << menu[i] << std::endl;
			}
			ch = _getch();
			if (ch == ARROW)
				ch = _getch();
			switch (ch)
			{
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
				textcolor(LIGHTGRAY);
				std::cout << "You choosed " << point + 1 << "menu item" << std::endl;
				gotoxy(x, y + 1);
				system("PAUSE");
				break;

			}
			system("cls");
		}
	}
};