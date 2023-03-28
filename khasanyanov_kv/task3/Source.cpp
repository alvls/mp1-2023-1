#include <iostream>
#include <string>
#include "console.h"
#include <conio.h>
using namespace std;

#define ESCAPE 27
#define UP 72
#define DOWN 80
#define RIGHT 77
#define ENTER 13
#define SPACE 32



class Menu
{
	int size;
	string* menu;
	int punkt;
public:
	Menu() { size = 0; punkt = 0; menu = nullptr; }
	Menu(int Size)
	{
		size = Size;
		punkt = 0;
		menu = new string[size];
		for (int i = 0; i < size; i++)
			menu[i] = "";
	}
	Menu(int Size, int item)
	{
		size = Size;
		punkt = item;
		menu = new string[size];
		for (int i = 0; i < size; i++)
			menu[i] = "";
	}
	Menu(const Menu& other)
	{
		size = other.size;
		punkt = other.punkt;
		for (int i = 0; i < size; i++)
			menu[i] = other.menu[i];
	}
	~Menu() { delete[] menu; }
	void set_size(int Size) 
	{ 
		if (Size == size)
			return;
		else if(Size > size)
		{
			string* temp = new string[size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = menu[i];
			}
			menu = new string[Size];
			for (int i = 0; i < size; i++)
			{
				menu[i] = temp[i];
			}
			for (int i = size; i < Size; i++)
			{
				menu[i] = "";
			}
			size = Size;
			delete[] temp;
		}
		else if (Size < size)
		{
			string* temp = new string[Size];
			for (int i = 0; i < Size; i++)
			{
				temp[i] = menu[i];
			}
			menu = new string[Size];
			for (int i = 0; i < Size; i++)
			{
				menu[i] = temp[i];
			}
			size = Size;
			delete[] temp;
		}
	}
	int get_size() { return size; }
	void set_name(int index, string name) { menu[index] = name; }
	string get_name(int index) { return menu[index]; }
	void set_item(int item) { punkt = item; }
	int get_last_punkt() { return punkt + 1; }
	void print_menu()
	{
		char ch;
		bool flag = true;
		while(flag)
		{
			textcolor(LIGHTGRAY);
			cout << "-----------------" << endl;
			for (int i = 0; i < size; i++)
			{
				if (i == punkt)
					textcolor(GREEN);
				else
					textcolor(LIGHTGRAY);
				cout << i + 1 << ". " << menu[i] << endl;
			}
			textcolor(LIGHTGRAY);
			cout << "-----------------" << endl;
			ch = _getch();
			if (ch == -32)
				ch = _getch();
			switch (ch)
			{
			case 1:
			case UP:
				if(punkt>0)
					--punkt;
				break;
			case DOWN:
				if (punkt < size - 1)
					++punkt;
				break;
			case ESCAPE:
				exit(0);
				break;
			case ENTER:
			case SPACE:
			case RIGHT:
				flag = false;
				cout <<"You have choosen option numder "<< punkt + 1 << endl;
				system("PAUSE");
				break;
			
			}
			clrscr();
		}
	}
	

};

void main()
{
	system("title Bussines lunch");
	hidecursor();
	Menu lunch(4);
	lunch.set_name(0, "Soup");
	lunch.set_name(1, "Pasta");
	lunch.set_name(2, "Juice");
	lunch.set_name(3, "Cheesecake");
	lunch.print_menu();
	cout << "Last selected item:" << lunch.get_last_punkt() << endl;
	lunch.set_size(3);
	system("PAUSE");
	system("cls");
	lunch.print_menu();
	cout << "Last selected item:" << lunch.get_last_punkt() << endl;
	system("PAUSE");
}