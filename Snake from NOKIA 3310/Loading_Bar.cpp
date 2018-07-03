#include "Loading_Bar.h"



Loading_Bar::Loading_Bar(int pos_x, int pos_y, int width, int height, int float_length) : Animation(pos_x, pos_y, 15, float_length * 2, true)
{
	w = width;
	h = height;
	f = float_length;
}


Loading_Bar::~Loading_Bar()
{
}


void Loading_Bar::draw_frame(Bitmap& target)
{
	target.draw_border(x, y, w, h);
	for (int tx = 0; tx < w - 2; tx++)
	{
		for (int ty = 0; ty < h - 2; ty++)
		{
			target.at(x + 1 + tx, y + 1 + ty) = ((tx + ty + frame) / f) & 1;
		}
	}
}