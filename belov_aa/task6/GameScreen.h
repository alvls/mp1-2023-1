#pragma once

struct Rect
{
	int top, left, bottom, right;
};

struct Point
{
	int x, y;

	bool operator ==(const Point& other)
	{
		return x == other.x && y == other.y;
	}
};

class GameScreen
{
public:
	enum PixelColor {
		BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
		DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
		LIGHTMAGENTA, YELLOW, WHITE
	};

	enum class Key
	{
		Up,
		Right,
		Down,
		Left,
		Unknown
	};

	virtual void flush() = 0;
	virtual void clear() = 0;

	virtual void write(int x, int y, std::string s) = 0;
	virtual void set_pixel(int x, int y, char value) = 0;

	virtual void set_pixel_foreground(int color) = 0;
	virtual void set_pixel_background(int color) = 0;

	virtual Key get_pressed_key() = 0;

	virtual ~GameScreen() {};
};