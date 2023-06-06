#pragma once

#include "GameScreen.h"
#include "ConsoleGameScreen.h"

#include <iostream>
#include <conio.h>
#include <Windows.h>

class BufferedConsoleGameScreen : public ConsoleGameScreen
{
private:
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO buf_info;
	COORD buf_coord = { 0, 0 };
	CHAR_INFO* buf;
	int buf_size;

	int background = BLACK;
	int foreground = LIGHTGRAY;
	int attr = background * 16 + foreground;

public:

	BufferedConsoleGameScreen()
	{
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &buf_info);
		buf = new CHAR_INFO[buf_size = buf_info.dwSize.X * buf_info.dwSize.Y];
	}

	void flush() override
	{
		Console::hidecursor();
		WriteConsoleOutput(
			hConsole,
			buf,
			buf_info.dwSize,
			buf_coord,
			&buf_info.srWindow);
	}

	void clear() override
	{
		memset(buf, 0, buf_size);
	}

	void write(int x, int y, std::string s) override
	{
		for (int xc = 0; xc < s.length(); xc++)
		{
			set_pixel(x + xc, y, s[xc]);
		}
	}
	void set_pixel(int x, int y, char value) override
	{
		buf[y * buf_info.dwSize.X + x].Char.AsciiChar = value;
		buf[y * buf_info.dwSize.X + x].Attributes = attr;
	}

	void set_pixel_foreground(int color) override
	{
		foreground = color;
		attr = (foreground % 16) + background * 16;
	}
	void set_pixel_background(int color) override
	{
		background = color;
		attr = background * 16 + foreground;
	}

	~BufferedConsoleGameScreen()
	{
		delete[] buf;
	}
};