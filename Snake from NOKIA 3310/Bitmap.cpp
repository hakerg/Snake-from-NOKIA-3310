#include "Bitmap.h"
#include <iostream>



Bitmap::Bitmap(int width, int height) : w(width), h(height), data(new bool[width * height])
{
}


Bitmap::Bitmap(int width, int height, bool _data[]) : w(width), h(height), data(new bool[width * height])
{
	memcpy(data, _data, width * height);
}


Bitmap::~Bitmap()
{
	delete[] data;
}


void Bitmap::blit_to(int x, int y, Bitmap& target)
{
	for (int ty = 0; ty < h; ty++)
	{
		for (int tx = 0; tx < w; tx++)
		{
			if (at(tx, ty)) target.negate(x + tx, y + ty);
		}
	}
}


void Bitmap::clear()
{
	memset(data, 0, w * h);
}


void Bitmap::draw_border()
{
	for (int x = 1; x < w - 1; x++)
	{
		negate(x, 0);
		negate(x, h - 1);
	}
	for (int y = 0; y < h; y++)
	{
		negate(0, y);
		negate(w - 1, y);
	}
}


void Bitmap::draw_border(int x, int y, int width, int height)
{
	for (int tx = x + 1; tx < x + width - 1; tx++)
	{
		negate(tx, y);
		negate(tx, y + height - 1);
	}
	for (int ty = y; ty < y + height; ty++)
	{
		negate(x, ty);
		negate(x + width - 1, ty);
	}
}


void Bitmap::negate(int x, int y)
{
	bool& p = at(x, y);
	p = !p;
}


void Bitmap::draw_rectangle(int x, int y, int w, int h)
{
	for (int tx = x; tx < x + w; tx++)
		for (int ty = y; ty < y + h; ty++)
		{
			negate(tx, ty);
		}
}


void Bitmap::draw_rectangle(int x, int y, int w, int h, bool color)
{
	for (int tx = x; tx < x + w; tx++)
		for (int ty = y; ty < y + h; ty++)
		{
			at(tx, ty) = color;
		}
}