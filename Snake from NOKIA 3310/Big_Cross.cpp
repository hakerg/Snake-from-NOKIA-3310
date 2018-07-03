#include "Big_Cross.h"



Big_Cross::Big_Cross(int board_x, int board_y) : Animation(16 + board_x * 18, board_y * 18, 1, 28)
{
}


Big_Cross::~Big_Cross()
{
}


void Big_Cross::draw_frame(Bitmap& target)
{
	target.draw_rectangle(x, y, 2, 2);
	for (int i = 1; i < 14 && i <= frame; i++)
	{
		target.at(x + i, y + 1 + i) = true;
		target.at(x + 1 + i, y + 1 + i) = true;
		target.at(x + 1 + i, y + i) = true;
	}

	if (frame >= 14) target.draw_rectangle(x + 13, y, 2, 2);
	for (int i = 1; i < 14 && i <= frame - 14; i++)
	{
		target.at(x + 14 - i, y + 1 + i) = true;
		target.at(x + 13 - i, y + 1 + i) = true;
		target.at(x + 13 - i, y + i) = true;
	}
}