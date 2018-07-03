#pragma once
#include "Animation.h"
class Small_Nought :
	public Animation
{
private:
	void draw_frame(Bitmap& target);

public:
	Small_Nought(int board_x, int board_y, int x, int y);
	~Small_Nought();
};

