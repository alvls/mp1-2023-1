#pragma once

#include "GameScreen.h"

#include <iostream>
#include <conio.h>
#include "Console.h"

class ConsoleGameScreen : public GameScreen
{
public:
	void flush() override {}

	void clear() override
	{
		Console::hidecursor();
		Console::clrscr();
	}

	void write(int x, int y, std::string s) override
	{
		Console::gotoxy(x, y);
		std::cout << s;
	}
	void set_pixel(int x, int y, char value) override
	{
		Console::gotoxy(x, y);
		std::cout << value;
	}

	void set_pixel_foreground(int color) override
	{
		Console::textcolor(color);
	}
	void set_pixel_background(int color) override
	{
		Console::textbackground(color);
	}

	virtual Key get_pressed_key() override
	{
		if (!_kbhit())
		{
			// NotPressed
			return Key::Unknown;
		}

		switch (_getch())
		{
		case -32:
			return get_pressed_key();
		case 72: // ArrowUP
		case 119: // W	
			return Key::Up;
		case 77: // RightArrow
		case 100: // D
			return Key::Right;
		case 80: // ArrowDown
		case 115: // S
			return Key::Down;
		case 75: // LeftArrow
		case 97:  // A
			return Key::Left;
		default:
			return get_pressed_key();
			//return Key::Unknown;
		}
	}
};