#pragma once

#include <string>
#include "ConsoleUtils.h"

struct MenuItem
{
	std::string title;
	void(*handler)();
};

class Menu
{
private:
	COORD menu_area;
	COORD work_area;

	int selected;

	MenuItem* items;
	int size;

public:
	Menu(int size, COORD menu_area, COORD work_area);

	~Menu();

	MenuItem& get_item(int index);
	void add_item(MenuItem item);

	void set_size(int size);
	int get_size() const;
	
	void listen();
	int get_selection() const;
};