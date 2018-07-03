#include "Small_Cross.h"



Small_Cross::Small_Cross(int board_x, int board_y, int x, int y) : Animation(16 + 18 * board_x + 6 * x, 18 * board_y + 6 * y, 2, 6)
{
}


Small_Cross::~Small_Cross()
{
}


void Small_Cross::draw_frame(Bitmap& target)
{
	switch (frame)
	{
	case 5: target.negate(x, y + 2);
	case 4:
	case 3: target.negate(x + 2, y);
	case 2: target.negate(x + 2, y + 2);
	case 1: target.negate(x + 1, y + 1);
	case 0: target.negate(x, y);
	}
}