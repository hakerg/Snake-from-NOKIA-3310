#pragma once
#include "Animation.h"
class Small_Cross :
	public Animation
{
private:
	void draw_frame(Bitmap& target);

public:
	Small_Cross(int board_x, int board_y, int x, int y);
	~Small_Cross();
};

