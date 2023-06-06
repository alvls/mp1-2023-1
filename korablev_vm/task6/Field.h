#include "Header.h"
class Field
{
private:
	int width;
	int height;
	string wst;
	string hst;

public:
	Field(int _w, int _h)
	{
		width = _w;
		height = _h;
	}
	void draw_field()
	{
		wst = "";
		hst = "";
		for (int i = 0; i < width + 2; i++)
			wst += '#';
		wst += '\n';
		hst += '#';
		for (int j = 0; j < width; j++)
			hst += ' ';
		hst += "#\n";
	}
	void show_field()
	{
		cout << wst;
		for (int i = 0; i < height; i++)
			cout << hst;
		cout << wst;
	}
	int return_width() { return width; }
	int return_height() { return height; }
};

