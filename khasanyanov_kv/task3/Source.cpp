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
	Menu(Menu& other)
	{
		size = other.size;
		punkt = other.punkt;
		for (int i = 0; i < size; i++)
			menu[i] = other.menu[i];
	}
	~Menu() { delete[] menu; }
	void set_size(int Size) { size = Size; }
	int get_size() { return size; }
	void set_name(int index, string name) { menu[index] = name; }
	string get_name(int index) { return menu[index]; }
	int get_last_punkt() { return punkt + 1; }
	void print_menu()
	{
		char ch;
		bool flag = true;
		while(flag)
		{
			for (int i = 0; i < size; i++)
			{
				if (i == punkt)
					textcolor(GREEN);
				else
					textcolor(LIGHTGRAY);
				cout << i + 1 << ". " << menu[i] << endl;
			}
			ch = _getch();
			if (ch == -32)
				ch = _getch();
			switch (ch)
			{
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
	system("PAUSE");
}