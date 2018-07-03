#include "Big_Nought.h"



Big_Nought::Big_Nought(int board_x, int board_y) : Animation(16 + board_x * 18, board_y * 18, 1, 36)
{
}


Big_Nought::~Big_Nought()
{
}


void Big_Nought::draw_frame(Bitmap& target)
{
	switch (frame)
	{
	case 35:
		target.negate(x + 6, y);
		target.negate(x + 6, y + 1);
	case 34:
		target.negate(x + 5, y);
		target.negate(x + 5, y + 1);
	case 33:
		target.negate(x + 3, y + 1);
		target.negate(x + 4, y + 1);
		target.negate(x + 4, y + 2);
	case 32:
		target.negate(x + 2, y + 2);
		target.negate(x + 3, y + 2);
		target.negate(x + 3, y + 3);
	case 31:
		target.negate(x + 1, y + 3);
		target.negate(x + 2, y + 3);
		target.negate(x + 2, y + 4);
	case 30:
		target.negate(x + 1, y + 4);
	case 29:
		target.negate(x, y + 5);
		target.negate(x + 1, y + 5);
	case 28:
		target.negate(x, y + 6);
		target.negate(x + 1, y + 6);
	case 27:
		target.negate(x, y + 7);
		target.negate(x + 1, y + 7);
	case 26:
		target.negate(x, y + 8);
		target.negate(x + 1, y + 8);
	case 25:
		target.negate(x, y + 9);
		target.negate(x + 1, y + 9);
	case 24:
		target.negate(x + 1, y + 10);
		target.negate(x + 2, y + 10);
		target.negate(x + 1, y + 11);
	case 23:
		target.negate(x + 2, y + 11);
		target.negate(x + 3, y + 11);
		target.negate(x + 2, y + 12);
	case 22:
		target.negate(x + 3, y + 12);
		target.negate(x + 4, y + 12);
		target.negate(x + 3, y + 13);
	case 21:
		target.negate(x + 4, y + 13);
	case 20:
		target.negate(x + 5, y + 13);
		target.negate(x + 5, y + 14);
	case 19:
		target.negate(x + 6, y + 13);
		target.negate(x + 6, y + 14);
	case 18:
		target.negate(x + 7, y + 13);
		target.negate(x + 7, y + 14);
	case 17:
		target.negate(x + 8, y + 13);
		target.negate(x + 8, y + 14);
	case 16:
		target.negate(x + 9, y + 13);
		target.negate(x + 9, y + 14);
	case 15:
		target.negate(x + 10, y + 12);
		target.negate(x + 10, y + 13);
		target.negate(x + 11, y + 13);
	case 14:
		target.negate(x + 11, y + 11);
		target.negate(x + 11, y + 12);
		target.negate(x + 12, y + 12);
	case 13:
		target.negate(x + 12, y + 10);
		target.negate(x + 12, y + 11);
		target.negate(x + 13, y + 11);
	case 12:
		target.negate(x + 13, y + 10);
	case 11:
		target.negate(x + 13, y + 9);
		target.negate(x + 14, y + 9);
	case 10:
		target.negate(x + 13, y + 8);
		target.negate(x + 14, y + 8);
	case 9:
		target.negate(x + 13, y + 7);
		target.negate(x + 14, y + 7);
	case 8:
		target.negate(x + 13, y + 6);
		target.negate(x + 14, y + 6);
	case 7:
		target.negate(x + 13, y + 5);
		target.negate(x + 14, y + 5);
	case 6:
		target.negate(x + 13, y + 3);
		target.negate(x + 13, y + 4);
		target.negate(x + 12, y + 4);
	case 5:
		target.negate(x + 12, y + 2);
		target.negate(x + 12, y + 3);
		target.negate(x + 11, y + 3);
	case 4:
		target.negate(x + 11, y + 1);
		target.negate(x + 11, y + 2);
		target.negate(x + 10, y + 2);
	case 3:
		target.negate(x + 10, y + 1);
	case 2:
		target.negate(x + 9, y);
		target.negate(x + 9, y + 1);
	case 1:
		target.negate(x + 8, y);
		target.negate(x + 8, y + 1);
	case 0:
		target.negate(x + 7, y);
		target.negate(x + 7, y + 1);
	}
}