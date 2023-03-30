#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <conio.h>

#include "Menu.h"
#include "ConsoleUtils.h"

using namespace std;

enum Keycodes
{
	NUMLOCK = -32,
	ENTER = 13,
	UP = 72,
	DOWN = 80
};

Menu::Menu(int size, COORD menu_area, COORD work_area)
	: size(size), menu_area(menu_area), work_area(work_area), selected(0)
{
	if (size <= 0)
	{
		throw std::invalid_argument("Меню не может быть пустым");
	}

	items = new MenuItem[size];
}

Menu::~Menu()
{
	delete[] items;
}

MenuItem& Menu::get_item(int index) // Возвращает команду
{
	if (!(index >= 0 && index < size))
	{
		throw std::invalid_argument("Меню не может быть пустым");
	}

	return items[index];
}

void Menu::add_item(MenuItem item) // Добавление команды
{
	set_size(size + 1);
	items[size - 1] = item;
}

void Menu::set_size(int size) // Задать число команд
{
	if (this->size == size)
	{
		return;
	}

	MenuItem* new_items = new MenuItem[size]();
	std::copy(items, &items[size < this->size ? size : this->size], new_items);

	this->size = size;

	delete[] items;
	items = new_items;
}

int Menu::get_size() const // Получить число команд
{
	return size;
}

void Menu::listen() // Вывод меню и выбор пункта
{
	hidecursor();

	int i;
	char ch = 0;
	while (ch != ENTER)
	{
		for (i = 0; i < size; i++)
		{
			gotoxy(menu_area.X, menu_area.Y + i);
			textcolor(i == selected ? YELLOW : LIGHTGREEN);
			cout << i + 1 << ". " << items[i].title;
		}

		ch = _getch();
		if (ch == NUMLOCK)
		{
			ch = _getch();
		}

		if (ch != UP && ch != DOWN)
		{
			continue;
		}

		selected += ch == UP ? -1 : 1;
		
		if (selected < 0)
		{
			selected = size - 1;
		}
		else
		{
			selected %= size;
		}
	}

	textcolor(LIGHTGRAY);

	gotoxy(work_area.X, work_area.Y);
	showcursor();

	items[selected].handler();
}

int Menu::get_selection() const // Получить номер последнего выбранного пункта
{
	return selected;
}
