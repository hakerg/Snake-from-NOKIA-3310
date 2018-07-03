#pragma once
#include "Animation.h"
class Big_Nought :
	public Animation
{
private:
	void draw_frame(Bitmap& target);

public:
	Big_Nought(int board_x, int board_y);
	~Big_Nought();
};

