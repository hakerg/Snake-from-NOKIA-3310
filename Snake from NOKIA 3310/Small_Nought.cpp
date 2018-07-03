#include "Small_Nought.h"



Small_Nought::Small_Nought(int board_x, int board_y, int x, int y) : Animation(16 + 18 * board_x + 6 * x, 18 * board_y + 6 * y, 3, 4)
{
}


Small_Nought::~Small_Nought()
{
}


void Small_Nought::draw_frame(Bitmap& target)
{
	switch (frame)
	{
	case 3: target.negate(x, y + 1);
	case 2: target.negate(x + 1, y + 2);
	case 1: target.negate(x + 2, y + 1);
	case 0: target.negate(x + 1, y);
	}
}